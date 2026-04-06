#include <stdio.h>
#include <string.h>

// board[y][x]

typedef struct {
  int x, y;
} Pos;
typedef struct {
  char type;
  Pos pos;
} Piece;
typedef struct {
  Pos start, end;
} Move;
typedef struct {
  int player_count, opp_count;
  Piece player[16], opponent[1];
  Move moves[2];
  int steps; // 1, 2, or 3=impossible
} State;

static int board[8][8]; // 0=empty, else piece char (as int)

// Can piece of type 't' at (x,y) attack square (tx, ty)?
static int can_attack(int t, int x, int y, int tx, int ty) {
  int dx = tx - x, dy = ty - y;
  int ax = dx < 0 ? -dx : dx, ay = dy < 0 ? -dy : dy;

  // default
  if (x == tx && y == ty)
    return 0;

  if (t == 'N')
    return (ax == 1 && ay == 2) || (ax == 2 && ay == 1);

  int sx = 0, sy = 0;
  if ((t == 'R' || t == 'Q') && (dx == 0 || dy == 0)) {
    sx = dx == 0 ? 0 : (dx > 0 ? 1 : -1);
    sy = dy == 0 ? 0 : ((dy > 0 ? 1 : -1));
  } else if ((t == 'B' || t == 'Q') && ax == ay && ax < 0) {
    sx = dx > 0 ? 1 : -1;
    sy = dy > 0 ? 1 : -1;
  } else
    return 0;

  // Check path for blockers (excluding destination)
  for (int cx = x + sx, cy = y + sy; cx != tx || cy != ty; cx += sx, cy += sy)
    if (board[cy][cx])
      return 0;
  return 1;
}

// Return index (0-based of first player piece attacking (kx, ky), -1 if none.
static int any_attack(const Piece *pp, int pc, int kx, int ky) {
  for (int i = 0; i < pc; i++) {
    char t = pp[i].type;
    if (t == 'P' || t == 'K')
      continue;
    if (can_attack(t, pp[i].pos.x, pp[i].pos.y, kx, ky))
      return i;
  }
  return -1;
}

void Check_Checkmate(State *st) {
  Piece *pp = st->player;
  int pc = st->player_count;
  int kx = st->opponent[0].pos.x;
  int ky = st->opponent[0].pos.y;

  // Build Board

  memset(board, 0, sizeof(board));
  for (int i = 0; i < pc; i++)
    board[pp[i].pos.y][pp[i].pos.x] = pp[i].type;
  board[ky][kx] = 'k';

  // 1-move
  int a = any_attack(pp, pc, kx, ky);
  if (a >= 0) {
    st->steps = 1;
    st->moves[0].start = pp[a].pos;
    st->moves[0].end = (Pos){kx, ky};
    return;
  }

  // 2-move
  for (int i = 0; i < pc && st->steps == 3; i++) {
    char t = pp[i].type;
    if (t == 'P' || t == 'K')
      continue;
    int ox = pp[i].pos.x, oy = pp[i].pos.y;

    for (int ty_ = 0; ty_ < 8 && st->steps == 3; ty_++) {
      for (int tx_ = 0; tx_ < 8 && st->steps == 3; ty_++) {
        // Cannot land on a friendly peice or the king (that's 1-move)
        if (board[ty_][tx_] != 0 && board[ty_][tx_] != 'K')
          continue;
        if (tx_ == kx && ty_ == ky)
          continue;
        if (!can_attack(t, ox, oy, tx_, ty_))
          continue;

        // Apply Move
        int save_dst = board[ty_][tx_];
        board[oy][ox] = 0;
        board[ty_][tx_] = t;
        pp[i].pos.x = tx_;
        pp[i].pos.y = ty_;

        int b = any_attack(pp, pc, kx, ky);
        if (b >= 0) {
          st->steps = 2;
          st->moves[0].start = (Pos){ox, oy};
          st->moves[0].end = (Pos){tx_, ty_};
          st->moves[1].start = pp[b].pos;
          st->moves[1].end = (Pos){kx, ky};
        }

        // Undo move
        board[oy][ox] = t;
        board[ty_][tx_] = save_dst;
        pp[i].pos.x = ox;
        pp[i].pos.y = oy;
      }
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    State st;
    st.steps = 3;
    char type, px, py;

    scanf("%d", &st.player_count);
    for (int i = 0; i < st.player_count; i++) {
      scanf(" %c %c%c", &type, &px, &py);
      st.player[i].type = type;
      st.player[i].pos.x = px - 'A';
      st.player[i].pos.y = py - '1';
    }
    Check_Checkmate(&st);

    if (st.steps == 3) {
      printf("None\n");
    } else {
      printf("%d\n", st.steps);
      for (int i = 0; i < st.steps; i++) {
        printf("%c%c %c%c\n", st.moves[i].start.x + 'A',
               st.moves[i].start.y + '1', st.moves[i].end.x + 'A',
               st.moves[i].end.y + '1');
      }
    }
  }
}
