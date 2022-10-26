#include <cstdio>

int main() {
    auto incream = [](auto x, int y=1) { return x + y; };
    printf("incream(10) = %d\n", incream(10));
    printf("incream(10, 5) = %d\n", incream(10, 5));
    return 0;
}