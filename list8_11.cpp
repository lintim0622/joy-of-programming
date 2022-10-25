#include <cstdio>

class TextFile {
public:
    bool sucess;
    const char* data;
    size_t n_bytes;
};

TextFile read_text_file(const char* path) {
    const static char contexts[] {"Sometimes the goat is you."};
    return TextFile {true, contexts, sizeof(contexts)};
}

int main() {
    const auto [sucess, contents, length] = read_text_file("REAMDE.txt");
    if (sucess)
        printf("Read %zd bytes: %s\n", length, contents);
    else
        printf("Failed to open REAMDE.txt.");
    return 0;
}