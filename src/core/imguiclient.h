#pragma once

#include "window.h"
#include<cstdint>

namespace raytracing
{
    class ImGuiClient
    {
    public:
        bool init(const Window& window);
        void deinit();

        void preTick(int32_t width, int32_t height);
        void tick();
        void postTick();
    };
};