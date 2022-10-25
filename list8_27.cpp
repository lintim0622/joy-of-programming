#include <cstdio>

class FibonaccInterator {
public:
    bool operator!=(int x) const {
        return x >= current;
    }
    FibonaccInterator& operator++() {
        const int tmp = current;
        current += last;
        last = tmp;
        return *this;
    }
    int operator*() const {
        return current;
    }

private:
    int current {1};
    int last {1};
};

class FibonacciRange {
public:
    explicit FibonacciRange(int max) : max{max} {}
    FibonaccInterator begin() const {
        return FibonaccInterator{};
    }
    int end() const {
        return max;
    }

private:
    const int max;
};

int main() {
    FibonacciRange range {5000};
    const int end = range.end();
    for (FibonaccInterator x = range.begin(); x != end; ++x) {
        const auto i = *x;
        printf("%d ", i);
    }  
    return 0;
}