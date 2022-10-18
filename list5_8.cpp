#include <cstdio>

class BaseClass {
public:
    virtual const char* final_message() const = 0;
};

class DerivedClass : public BaseClass {
public:
    const char* final_message() const override {
        return "We apologize for the inconvenience.";
    }
};

int main() {
    DerivedClass derived;
    BaseClass& ref = derived;
    printf("DerivedClass: %s\n", derived.final_message());
    printf("BaseClass&: %s\n", ref.final_message());
    return 0;
}