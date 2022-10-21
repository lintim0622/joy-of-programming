#include <limits>
#include <cstdio>
#include <stdexcept>

class CheckInter {
public:
    CheckInter(unsigned int value) : value { value } {}
    CheckInter operator+(unsigned int other) const {
        CheckInter result { value + other };
        if (result.value < value)
            throw std::runtime_error{ "Overflow!" };
        return result;
    }
    unsigned int get_value() const {
        return value;
    }

private:
    const unsigned int value;
};

int main() {
    CheckInter a { 100 };
    auto b = a + 200;
    printf("a + 200 = %u\n", b.get_value());
    try {
        auto c = a + std::numeric_limits<unsigned int>::max();
    }
    catch (const std::overflow_error& e) {
        printf("(a + max) Exception: %s\n", e.what());
    }
    return 0;
}