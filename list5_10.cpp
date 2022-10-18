#include <cstdio>

class BaseClass {
public:
    virtual ~BaseClass() = default;
};

class DerivedClass : public BaseClass {
public:
    DerivedClass() {
        printf("DerivedClass() invoked.\n");
    }

    ~DerivedClass() {
        printf("~DerivedClass() invoked.\n");
    }
};

int main() {
    printf("Constructing DerivedClass x.\n");
    BaseClass *x { new DerivedClass{} };
    printf("Deleting x as a BaseClass*.\n");
    delete x;
    return 0;
}