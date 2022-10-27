#include <cstdio>
#include <cstdint>
#include <functional>

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

size_t count_space(const char* str) {
    size_t index {}, result {};
    while (str[index]) {
        if (str[index] == ' ')
            result++;
        index++;
    }
    return result;
}

std::function<size_t(const char*)> funcs[] {count_space, CountIf{'e'}, [](const char* str) {
        size_t index {};
        while (str[index])
                index++;
        return index;
    }
};

int main() {
    const char* text = "Sailor went to sea to see what he could see.";
    size_t index {};
    for (const std::function<size_t(const char*)>& func : funcs)
        printf("func #%zd: %zd\n", index++, func(text));
    return 0;
}