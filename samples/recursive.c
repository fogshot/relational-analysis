int main() {
  int a = 1;
  int b = 2;
  int c = a + b;
  c = rec(a, b, c);
  return c;
}

int rec(int a, int b, int c) {
  if (c > 20)
    return a + b;
  return rec(a, b, c) + 1;
}