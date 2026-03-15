#include <iostream>

int main() {
  int k;
  std::cin >> k;
  std::string s;
  std::cin >> s;
  int asc[5];

  for (int i = 0; i < 5; i++) {
    asc[i] = static_cast<int>(s[i] + k);
    if (asc[i] > 122) {
      asc[i] = (asc[i] % 122) + 96;
    }
    asc[i] -= (97 - 65);

    s[i] = static_cast<char>(asc[i]);
  }
  std::cout << s;
}
