#include <cstdio>

namespace BroopKidron13::Shaltanac {
    enum class Color {
        Mauve,
        Pink,
        Russet
    };
}

using namespace BroopKidron13::Shaltanac;

class JoopleberryShrub {
public:
    const char* name;
    Color shade;
};

bool is_more_mauvey(const JoopleberryShrub& shrub) {
    return shrub.shade == Color::Mauve;
}

int main() {
    const JoopleberryShrub yours {"The other shaltanac", Color::Mauve};
    if (is_more_mauvey(yours))
        printf("%s's joopleberry shrub is always a more mauvey shade of pinky russet.", yours.name);
    return 0;
}