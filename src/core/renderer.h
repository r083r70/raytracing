#pragma once

#include "core/layer.h"
#include "math/vector.h"

#include "scene.h"
#include "texture.h"

#include <vector>

namespace raytracing
{
	struct Ray
	{
		Vector Position;
		Vector Direction;
	};

	struct HitResult
	{
		int32_t ObjectIndex = -1;

		float Distance = 0;
		Vector Position = Vector{0.f};
		Vector Normal = Vector{0.f};
	};

    class Renderer : public kettle::Layer
    {
    public:
		static Renderer* get() { return s_Instance; }
        Renderer();

        virtual void start() override;
        virtual void stop() override;

        virtual void tick() override;

        void setImageSize(uint32_t width, uint32_t height);
        const Texture& getTexture() const { return m_Texture; }

        void moveCamera(const Vector& delta);

        float getLastUpdate() const { return m_LastUpdate; }

    private:
        Vector perPixel(float x, float y);

        HitResult traceRay(const Ray& ray, int32_t bounces = 0);
		HitResult hit(const Ray& ray, float hitDistance, int32_t hitIndex);
        HitResult miss(const Ray& ray);

    private:
		static Renderer* s_Instance;

        Texture m_Texture;
        std::vector<uint32_t> m_Pixels;
        uint32_t m_ImageWidth, m_ImageHeight;

        CameraData m_Camera;
        std::vector<SphereData> m_Spheres;
        LightData m_DirectionalLight;

        float m_LastUpdate;
    };
}