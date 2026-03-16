/*
 * Fuzzy Concatenation — Hard Version
 * C translation of the C++ solution.
 *
 * ALGORITHM
 * ---------
 * Build a suffix array (SA) on the combined string:
 *   all[] = s + '%' + t           (length n+1+m, plus a sentinel)
 *
 * from_s[0..from_s_n-1] stores the SA ranks of suffixes that start
 * inside s (position < n), in sorted order.
 *
 * compare_suff(start, pos, ch, suff_num)
 *   Compares a "virtual" modified t-suffix — the t-suffix beginning at
 *   t[start], but with the single character at absolute position `pos`
 *   (i.e. t[pos], where pos >= start) replaced by `ch` — against the
 *   suff_num-th s-suffix (1-indexed) in sorted order.
 *   Returns:
 *     dir       +1  s-suffix ranks lower (comes first in SA)
 *               -1  s-suffix ranks higher
 *     match_len how many characters the two strings share, counting
 *               the substitution at `pos`.
 *
 * get_max_len(start, pos, ch)
 *   Binary-searches from_s[] to find the s-suffix nearest in SA to
 *   the virtual modified t-suffix, checks both neighbours, and returns
 *   the maximum match length.
 *
 * Main greedy
 *   For each position i in t (left to right), try all 26 replacement
 *   characters and compute get_max_len(start, i, ch). Track `pred` =
 *   the best reach seen so far from the current segment start.
 *   When i advances beyond what the current segment can cover
 *   (mx < i - start + 1), commit one operation, advance start by pred,
 *   and restart from there.
 */

#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Dimensions                                                           */
/* n <= 5e5, m <= 5e4 => combined length <= ~5.5e5+3                  */
/* ------------------------------------------------------------------ */
#define MAXALL 600010
#define LOG 20

/* ------------------------------------------------------------------ */
/* Sparse table (range-minimum query, 0-indexed)                       */
/* ------------------------------------------------------------------ */
static int sp[LOG][MAXALL];

static void sp_build(const int *a, int n) {
  for (int i = 0; i < n; i++)
    sp[0][i] = a[i];
  for (int k = 1; (1 << k) <= n; k++)
    for (int i = 0; i + (1 << k) <= n; i++)
      sp[k][i] = (sp[k - 1][i] < sp[k - 1][i + (1 << (k - 1))])
                     ? sp[k - 1][i]
                     : sp[k - 1][i + (1 << (k - 1))];
}

/* Query range [l, r] inclusive (0-indexed). */
static inline int sp_query(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  int a = sp[k][l], b = sp[k][r - (1 << k) + 1];
  return a < b ? a : b;
}

/* ------------------------------------------------------------------ */
/* Suffix array (cyclic-doubling, same algorithm as the C++ source)    */
/* ------------------------------------------------------------------ */
static int SA[MAXALL];   /* suffix array                               */
static int INV[MAXALL];  /* inverse SA (rank of suffix i)              */
static int LCP[MAXALL];  /* LCP[i] = lcp(SA[i], SA[i+1])              */
static int sa_s[MAXALL]; /* coordinate-compressed input                */

/* Temporary arrays reused across calls */
static int sa_c[MAXALL], sa_c2[MAXALL], sa_ns[MAXALL], sa_cnt[MAXALL];

/*
 * build_suffix_array(raw, raw_len)
 *   raw[]    = characters of the combined string (plain char array).
 *   raw_len  = length of raw (without any appended sentinel).
 *
 * Internally appends a sentinel of rank 0 at position raw_len,
 * builds SA[0..raw_len] and LCP[0..raw_len-1], then builds the
 * sparse table on LCP[].
 */
static void build_suffix_array(const char *raw, int raw_len) {
  /* Coordinate-compress characters into ranks 1..k (sentinel = 0). */
  int freq[256];
  memset(freq, 0, sizeof(freq));
  for (int i = 0; i < raw_len; i++)
    freq[(unsigned char)raw[i]]++;
  int remap[256];
  int cc = 1;
  for (int v = 0; v < 256; v++)
    if (freq[v])
      remap[v] = cc++;

  int N = raw_len + 1; /* total length including sentinel */
  for (int i = 0; i < raw_len; i++)
    sa_s[i] = remap[(unsigned char)raw[i]];
  sa_s[N - 1] = 0; /* sentinel — unique minimum */

  /* Initialise SA and rank array c. */
  for (int i = 0; i < N; i++) {
    SA[i] = i;
    sa_c[i] = sa_s[i];
  }

  int *c = sa_c, *c2 = sa_c2;

  for (int gap = 1; (gap >> 1) < N; gap <<= 1) {
    /*
     * Before the stable sort by first key, shift SA so that each
     * element represents the suffix that, when advanced by gap/2,
     * yields the current SA order (second-key pre-sort).
     */
    if (gap != 1) {
      int half = gap >> 1;
      for (int j = 0; j < N; j++)
        SA[j] = (SA[j] - half + N) % N;
    }

    /* Stable counting sort by first key c[]. */
    memset(sa_cnt, 0, sizeof(int) * N);
    for (int j = 0; j < N; j++)
      sa_cnt[c[SA[j]]]++;
    int su = 0;
    for (int j = 0; j < N; j++) {
      su += sa_cnt[j];
      sa_cnt[j] = su - sa_cnt[j];
    }
    for (int j = 0; j < N; j++)
      sa_ns[sa_cnt[c[SA[j]]]++] = SA[j];
    memcpy(SA, sa_ns, sizeof(int) * N);

    /* Recompute ranks for the next doubling step. */
    if (gap != 1) {
      int half = gap >> 1;
      c2[SA[0]] = 0;
      for (int j = 1; j < N; j++) {
        if (c[SA[j]] > c[SA[j - 1]] ||
            c[(SA[j] + half) % N] > c[(SA[j - 1] + half) % N])
          c2[SA[j]] = c2[SA[j - 1]] + 1;
        else
          c2[SA[j]] = c2[SA[j - 1]];
      }
      int *tmp = c;
      c = c2;
      c2 = tmp;
    }
  }
  /* SA is now the correct suffix array. */

  /* Build LCP array via Kasai's algorithm. */
  for (int i = 0; i < N; i++)
    INV[SA[i]] = i;
  int h = 0;
  for (int i = 0; i < N; i++) {
    if (INV[i] == N - 1) {
      h = 0;
      continue;
    }
    if (i > 0 && INV[i - 1] != N - 1)
      h = (h > 1) ? h - 1 : 0;
    else
      h = 0;
    int j = SA[INV[i] + 1];
    while (i + h < N - 1 && j + h < N - 1 && sa_s[i + h] == sa_s[j + h])
      h++;
    LCP[INV[i]] = h;
  }

  /* Build sparse table on LCP[0..N-2]. */
  sp_build(LCP, N - 1);
}

/* LCP of suffix i and suffix j in the combined string. */
static inline int get_lcp(int i, int j) {
  int ri = INV[i], rj = INV[j];
  if (ri > rj) {
    int t = ri;
    ri = rj;
    rj = t;
  }
  /* min of LCP[ri .. rj-1] */
  return sp_query(ri, rj - 1);
}

/* ------------------------------------------------------------------ */
/* Per-test-case globals                                                */
/* ------------------------------------------------------------------ */
static char all_buf[MAXALL]; /* s + '%' + t + '#' (safety char)       */
static int from_s[MAXALL];   /* SA ranks of s-suffixes, sorted        */
static int from_s_n;
static int G_n; /* length of s                           */

/* ------------------------------------------------------------------ */
/* compare_suff                                                         */
/* ------------------------------------------------------------------ */
/*
 * Parameters mirror the C++ lambda:
 *   start    — 0-based index into t where the current operation begins
 *   pos      — 0-based index into t of the character being replaced
 *              (pos >= start)
 *   ch       — replacement character
 *   suff_num — 1-based index into from_s[] of the s-suffix to compare
 *
 * Sets *dir_out (+1 or -1) and *len_out (match length).
 */
static void compare_suff(int start, int pos, char ch, int suff_num,
                         int *dir_out, int *len_out) {
  int n = G_n;
  if (suff_num == 0 || suff_num > n) {
    *dir_out = 1;
    *len_out = 0;
    return;
  }

  int rel_pos = pos - start;            /* changed-char offset within segment */
  int s_suf = SA[from_s[suff_num - 1]]; /* start of the s-suffix in all[]     */

  /*
   * lcp1 = length of longest common prefix between
   *   the plain t-suffix starting at t[start]  (= all[n+1+start])
   *   and the s-suffix starting at s_suf.
   * This ignores the substitution at rel_pos.
   */
  int lcp1 = get_lcp(s_suf, n + 1 + start);

  if (lcp1 < rel_pos) {
    /*
     * First mismatch occurs before the substituted character.
     * The substitution cannot rescue the comparison.
     */
    char ch1 = all_buf[s_suf + lcp1];
    char ch2 = all_buf[n + 1 + start + lcp1];
    *dir_out = (ch1 < ch2) ? 1 : -1;
    *len_out = lcp1;
  } else if (lcp1 > rel_pos) {
    /*
     * First natural agreement ends beyond the substitution point.
     * The substitution is the first place the two strings can differ.
     */
    char ch1 =
        all_buf[s_suf + rel_pos]; /* s character at substitution offset */
    char ch2_cmp;
    int match_so_far;

    if (ch1 != ch) {
      /* s differs from the replacement character — compare them. */
      ch2_cmp = ch;
      match_so_far = rel_pos;
    } else {
      /*
       * s agrees with the replacement character at rel_pos.
       * Jump to lcp1 (the first natural mismatch) and compare there.
       */
      match_so_far = lcp1;
      ch1 = all_buf[s_suf + lcp1];
      ch2_cmp = all_buf[n + 1 + start + lcp1];
    }
    *dir_out = (ch1 < ch2_cmp) ? 1 : -1;
    *len_out = match_so_far;
  } else {
    /*
     * lcp1 == rel_pos: the first natural mismatch is exactly at the
     * substitution position.  Compare s[rel_pos] with ch.
     */
    char ch1 = all_buf[s_suf + lcp1];
    char ch2 = ch;

    if (ch1 < ch2) {
      *dir_out = 1;
      *len_out = rel_pos;
      return;
    }
    if (ch1 > ch2) {
      *dir_out = -1;
      *len_out = rel_pos;
      return;
    }

    /*
     * ch1 == ch: the s character and the replacement agree.
     * Compare what comes after the substitution.
     */
    int lcp2 = get_lcp(s_suf + lcp1 + 1, n + 1 + start + lcp1 + 1);
    ch1 = all_buf[s_suf + lcp1 + 1 + lcp2];
    ch2 = all_buf[n + 1 + start + lcp1 + 1 + lcp2];
    *dir_out = (ch1 < ch2) ? 1 : -1;
    *len_out = rel_pos + 1 + lcp2;
  }
}

/* ------------------------------------------------------------------ */
/* get_max_len                                                          */
/* ------------------------------------------------------------------ */
static int get_max_len(int start, int pos, char ch) {
  /* Binary-search: find the insertion point in from_s[] (1-indexed). */
  int lo = 0, hi = from_s_n;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    int d, l;
    compare_suff(start, pos, ch, mid, &d, &l);
    if (d == -1)
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  /* Check both neighbours of the insertion point. */
  int res = 0, d, l;
  compare_suff(start, pos, ch, lo - 1, &d, &l);
  if (l > res)
    res = l;
  compare_suff(start, pos, ch, lo, &d, &l);
  if (l > res)
    res = l;
  return res;
}

/* ------------------------------------------------------------------ */
/* solve                                                                */
/* ------------------------------------------------------------------ */
static char s_buf[500005], t_buf[50005];

static void solve(void) {
  int n, m;
  scanf("%d %d %s %s", &n, &m, s_buf, t_buf);
  G_n = n;

  /*
   * Construct all[] = s + '%' + t.
   * Append an extra '#' beyond the end so that reads by compare_suff
   * one past the last matching character are always into valid memory.
   */
  memcpy(all_buf, s_buf, n);
  all_buf[n] = '%';
  memcpy(all_buf + n + 1, t_buf, m);
  all_buf[n + 1 + m] = '#'; /* safety character; not part of SA input */
  all_buf[n + 2 + m] = '\0';

  /* Build suffix array on all[0..n+m] (length n+1+m). */
  build_suffix_array(all_buf, n + 1 + m);

  /* Collect SA ranks of s-suffixes. */
  from_s_n = 0;
  for (int i = 0; i < n + 1 + m + 1; i++) /* +1 for the internal sentinel */
    if (SA[i] < n)
      from_s[from_s_n++] = i;

  /* ---- Main greedy ---- */
  int ans = 0, start = 0, pred = -1;
  for (int i = 0; i < m; i++) {
    /* Try all 26 replacement characters at position t[i]. */
    int mx = 0;
    for (char ch = 'a'; ch <= 'z'; ch++) {
      int v = get_max_len(start, i, ch);
      if (v > mx)
        mx = v;
    }
    /* Update the best reach from the current segment start. */
    if (mx > pred)
      pred = mx;

    /*
     * If position i cannot be covered by any operation starting at
     * `start` (i.e., no s-substring of length >= i-start+1 matches
     * the segment t[start..i] with <=1 substitution), we must end
     * the current operation at start + pred and begin a new one.
     */
    if (mx < i - start + 1) {
      ans++;
      start += pred;
      pred = -1;
      i = start - 1; /* loop increments to start */
    }
  }
  if (start != m)
    ans++;

  printf("%d\n", ans);
}

int main(void) {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}
