#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <utility>

class SimpleString {
public:
    SimpleString(size_t max_size) : max_size { max_size }, length {} {
        if (max_size == 0)
            throw std::runtime_error {"Max size must be at least 1."};
        buffer = new char[max_size];
        buffer[0] = 0;
    }
    SimpleString(const SimpleString& other) : max_size { other.max_size }, 
        buffer { new char[other.max_size] }, length { other.length } {
        std::strncpy(buffer, other.buffer, max_size);
    }
    SimpleString(SimpleString&& other) noexcept : max_size { max_size }, 
        buffer { other.buffer }, length { other.length } {
        other.length = 0;
        other.buffer = nullptr;
        other.max_size = 0;
    }

    ~SimpleString() { delete [] buffer; }

    void print(const char* tag) const {
        printf("%s: %s", tag, buffer);
    }

    bool append_line(const char* x) {
        const auto x_len = std::strlen(x);
        if (x_len + length + 2 > max_size) return false;
        std::strncpy(buffer + length, x, max_size - length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }

    SimpleString& operator=(const SimpleString& other) {
        if (this == &other) return *this;
        delete [] buffer;
        buffer = new char[other.max_size];
        length = other.length;
        max_size = other.max_size;
        std::strcpy(buffer, other.buffer);
        return *this;
    }

    SimpleString& operator=(SimpleString&& other) noexcept {
        if (this == &other) return *this;
        delete [] buffer;
        buffer = other.buffer;
        length = other.length;
        max_size = other.max_size;
        other.max_size = 0;
        other.length = 0;
        other.buffer = nullptr;
        return *this;
    }

private:
    size_t max_size;
    char *buffer;
    size_t length;
};

class SimpleStringOwner {
public:
    SimpleStringOwner(const char* x) : string { 10 } {
        if (!string.append_line(x))
            throw std::runtime_error {"Not enough memory!"};
        string.print("Constructed: ");
    }
    SimpleStringOwner(SimpleString&& x) : string { std::move(x) } {}
    ~SimpleStringOwner() { string.print("About to destory: "); }

private:
    SimpleString string;
};

int main() {
    SimpleString a { 50 };
    a.append_line("We apologize for the");

    SimpleString b { 50 };
    b.append_line("Last message");

    a.print("a");
    b.print("b");

    b = std::move(a);
    b.print("b");
    return 0;
}
