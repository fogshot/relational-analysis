#include <stdio.h>

// test program:
// multiple loops and branches

int main(int argc, char const *argv[]) {
    int x, y;
    y = 2;

    // perform dummy intialization of values
    if (argc == 0) {
        x = 1;
        for (int i = 0; i < y; i++) {
            x += i;
        }
        return x;
    }
    else {
        x = 3;
        for(int i = 0; i<x; i++) {
            if (y < 15) {
                y += 3;
            } else {
                return y;
            }
        }
    }

}
