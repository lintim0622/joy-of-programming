#include <cstdio>
#include <cstdint>

class CountIf {
public:
    CountIf(char x) : x{x} {}
    size_t operator()(const char* str) const {
        size_t index {}, result {};
        while (str[index]) {
            if (str[index] == x)
                result++;
            index++;
        }
        return result;
    }

private:
    const char x;
};

int main() {
    CountIf s_counter {'s'};
    size_t sally = s_counter("Sally sells seashells by the seashore.");
    printf("Sally: %zd\n", sally);

    size_t sailor = s_counter("Sailor went to sea to see what he could see.");
    printf("Sailor: %zd\n", sailor);

    size_t buffalo = CountIf {'f'}("Buffalo buffalo Buffalo buffalo buffalo buffalo Buffalo buffalo.");
    printf("Buffalo: %zd\n", buffalo);
    return 0;
}