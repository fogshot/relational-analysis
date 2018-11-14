#include <stdlib.h>

int main(int argc, char* argv[]) {
    int a = 0,b = 0;

    if (argc > 2) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    for (int i = 0; i < a; i++) {
        b++;
    }

    if (b > a) {
        a = b;
    }

    return a;
}