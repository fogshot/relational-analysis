int main() {
  int a = 1;
  int b = 2;
  int c = a + b;

  while (a < b) {
    b++;
    c = a + b;
  }

  return c;
}