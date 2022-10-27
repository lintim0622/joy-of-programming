#include <cstdio>
#include <cstdint>

class LambdaFactory {
public:
    LambdaFactory(char in) : to_count{in} {}
    auto make_lambda() {
        return [this](const char* str) {
            size_t index {}, result {};
            while (str[index]) {
                if (str[index] == to_count)
                    result++;
                index++;
            }
            tally += result;
            return result;
        };
    }
    size_t get_tally() const { return tally; }

private:
    const char to_count;
    size_t tally;
};

int main() {
    LambdaFactory factory {'s'};
    auto lambda = factory.make_lambda();
    printf("Tally: %zd\n", factory.get_tally());
    auto sally = lambda("Sally sells seashells by the seashore.");
    printf("Sally: %zd\n", sally);
    printf("Tally: %zd\n", factory.get_tally());
    size_t sailor = lambda("Sailor went to sea to see what he could see.");
    printf("Sailor: %zd\n", sailor);
    printf("Tally: %zd\n", factory.get_tally());
    return 0;
}