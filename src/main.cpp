
#include "core/app.h"

int main(void)
{
    raytracing::App app{};
    if (app.init())
        app.run();
    return 0;
}