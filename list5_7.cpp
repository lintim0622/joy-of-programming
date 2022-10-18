#include <cstdio>

class BaseClass {
public:
    virtual const char* final_message() const {
        return "We apologize for the incontinence.";
    }
};

class DerivedClass : public BaseClass {
public:
    const char* final_message() const override {
        return "We apologize for the inconvenience.";
    }
};

int main() {
    BaseClass base;
    DerivedClass derived;
    BaseClass& ref = derived;
    printf("BaseClass: %s\n", base.final_message());
    printf("DerivedClass: %s\n", derived.final_message());
    printf("BaseClass&: %s\n", ref.final_message());
    return 0;
}