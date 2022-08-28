#pragma once

#include "render/texture.h"
#include <string>

namespace raytracing
{
    class Screen
    {
    public:
        virtual void tick() = 0;
    };

    class MainMenuBarScreen : public Screen
    {
    public:
        virtual void tick() override;
    };

    class ImageScreen : public Screen
    {
    public:
        ImageScreen();
        virtual void tick();
    private:
        Texture m_Texture;
    };

    class StatsScreen : public Screen
    {
    public:
        virtual void tick();
    private:
        float cameraMovement(const std::string& axesName);
    };
}