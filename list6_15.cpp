#include <cstdio>
#include <utility>
#include "list6_14.cpp"

class Trace {
public:
    Trace(const char* name) : name { name } {
        printf("%s constructed.\n", name);
    }
    ~Trace() {
        printf("%s destructed.\n", name);
    }

private:
    const char* const name;
};

void consumer(SimpleUniquePointer<Trace> consumer_ptr) {
    printf("(cons) consumer_ptr: 0x%p\n", consumer_ptr.get());
}

int main() {
    SimpleUniquePointer<Trace> ptr_a { new Trace { "ptr_a" } };
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    consumer(std::move(ptr_a));
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    return 0;
}