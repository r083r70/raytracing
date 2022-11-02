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

        Vector traceRay(const Ray& ray);

		Vector hit(const Ray& ray, const SphereData& hitObject, float distance);
        Vector miss(const Ray& ray);

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