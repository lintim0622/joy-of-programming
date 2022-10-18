#include <cstddef>

int main() {
    const size_t n { 100 };
    int v[n];
    for (auto &x : v)
        x = 0;
    return 0;
}