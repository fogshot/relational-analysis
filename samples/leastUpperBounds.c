int main() {
    int a, b, c;
    b = 0;
    a = b;
    c = b;

    for (int i = 0; i < 3; i++) {
        a = 2;
        c = 2;
        b = 3;
    }

    return a + b + c;
}
