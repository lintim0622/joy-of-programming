#include <cstdio>

enum class Color {
    Mauve,
    Pink,
    Russet
};

struct Result {
    const char* name;
    Color color;
};

Result observe_shrub(const char* name) {
    return Result {name, Color::Russet};
}

int main() {
    const char* description {};
    const Result result = observe_shrub("ZAphod");
    switch (result.color) {
        case Color::Mauve: {
            description = "mauvey shade of pinky russet";
            break;
        }
        case Color::Pink: {
            description = "Pink shade of mauvey russet";
            break;
        }
        case Color::Russet: {
            description = "Russet shade of Pink mauvey";
            break;
        }
        default: {
            description = "enigmatic shade or whitish black";
            break;
        }    
    }
    printf("The other Shaltanac's joopleberry shrub is always a more %s.", description);
    return 0;
}