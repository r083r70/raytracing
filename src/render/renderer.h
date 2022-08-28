#pragma once

#include "math/vector.h"
#include "texture.h"

#include <ctime>
#include <vector>

namespace raytracing
{
    struct CameraData
    {
        CameraData(const Vector& position, float workingDistance, float fieldOfView)
            : Position(position), WorkingDistance(workingDistance), FieldOfView(fieldOfView) {}

        Vector Position;
        float WorkingDistance;
        float FieldOfView;
    };

    struct SphereData
    {
        SphereData(const Vector& origin, float radius)
            : Origin(origin), Radius(radius), Color(Vector(1.f, 0.f, 0.f)) {}

        Vector Origin;
        float Radius;

        Vector Color;
    };

    struct LightData
    {
        LightData(const Vector& direction) : Direction(direction) {} 
        Vector Direction;
    };

    class Renderer
    {
    public:
        Renderer();

        void init();
        void deinit();

        void preTick();
        void tick();
        void postTick();

        void setImageSize(uint32_t width, uint32_t height);
        const Texture& getTexture() const { return m_Texture; }

        void moveCamera(const Vector& delta);

        float getLastUpdate() const { return m_LastUpdate; }

    private:
        Vector vertexShader(float x, float y);
        Vector checkSphere(const Vector& direction, const SphereData& sphere);

        void antiAliasing();

    private:
        Texture m_Texture;
        std::vector<uint32_t> m_TmpPixels;
        std::vector<uint32_t> m_Pixels;
        uint32_t m_ImageWidth, m_ImageHeight;

        CameraData m_Camera;
        std::vector<SphereData> m_Spheres;
        LightData m_DirectionalLight;

        float m_LastUpdate;
    };
}