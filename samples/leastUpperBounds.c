int main() {
    int a, b, c;
    a = b;
    b = c;

    for (int i = 0; i < 1; i++) {
        a = 2;
        c = 2;
        b = 3;
    }

    return a + b + c;
}
