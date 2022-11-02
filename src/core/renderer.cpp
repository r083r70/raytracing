
#include "renderer.h"

#include <chrono>
#include <cfloat>

namespace raytracing
{
    constexpr float s_WorkingDistance = 3.f;
    constexpr float s_FOV = 1.f;

	Renderer* Renderer::s_Instance = nullptr;

    Renderer::Renderer()
        : m_Texture(512, 512)
        , m_ImageWidth(512)
        , m_ImageHeight(512)
        , m_Camera(Vector{ 0.f, 0.f, -10.f }, s_WorkingDistance, s_FOV)
        , m_DirectionalLight(Vector{ 1.f, -1.f, 1.f }.normalize())
    {
		s_Instance = this;
        m_Spheres.emplace_back(Vector{3, 0, 7}, 1, Vector{1, 0, 0});
        m_Spheres.emplace_back(Vector{-3, 0, 7}, 0.7, Vector{0, 1, 0});
        m_Spheres.emplace_back(Vector{0, 3, 7}, 1.3, Vector{0, 0, 1});
        m_Spheres.emplace_back(Vector{0, -3, 7}, 1.8, Vector{1});
    }

    void Renderer::start()
    {
        m_Texture.create();
    }
    
    void Renderer::stop()
    {
        m_Pixels.clear();
    }
    
    void Renderer::tick()
    {
        const auto start = std::chrono::high_resolution_clock::now();

        m_Texture.resize(m_ImageWidth, m_ImageHeight);

        const size_t width = m_Texture.getWidth();
        const size_t height = m_Texture.getHeight();
        const float maxDimension = std::max(width, height);

        const size_t newSize = width * height;
        m_Pixels.resize(newSize, 0xFF);

        for (size_t h = 0; h < height; h++)
        {
            for (size_t w = 0; w < width; w++)
            {
                float x = ((2.f * w) - width) / maxDimension;
                float y = ((2.f * h) - height) / maxDimension;
                Vector color = perPixel(x, y) * 255.f;

                const size_t index = h * width + w;
                m_Pixels[index] = ((int32_t)color.R << 24)
                                   + ((int32_t)color.G << 16)
                                   + ((int32_t)color.B << 8)
                                   + 0xFF;
            }
        }

        m_Texture.setData(m_Pixels.data());

        const auto end = std::chrono::high_resolution_clock::now();
        m_LastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 0.001f;
    }

    void Renderer::setImageSize(uint32_t width, uint32_t height)
    {
        m_ImageWidth = width;
        m_ImageHeight = height;
    }

    void Renderer::moveCamera(const Vector& delta)
    {
        m_Camera.Position = m_Camera.Position + delta;
    }


	Vector Renderer::perPixel(float x, float y)
	{
        const Vector direction{ x * m_Camera.FieldOfView, y * m_Camera.FieldOfView, m_Camera.WorkingDistance };
        return traceRay({ m_Camera.Position, direction });
	}

	Vector Renderer::traceRay(const Ray& ray)
	{
		int32_t closestSphereIndex = -1;
		float closestDistance = FLT_MAX;

		for (int32_t i = 0; i < m_Spheres.size(); i++)
		{
			const auto& sphere = m_Spheres[i];
			const float a = ray.Direction.sqrLength();
			const float b = 2.f * ((ray.Position - sphere.Origin) | ray.Direction);
			const float c = sphere.Origin.sqrLength()
				+ ray.Position.sqrLength()
				- 2.f * (ray.Position | sphere.Origin)
				- (sphere.Radius * sphere.Radius);

			const float discriminant = (b * b) - (4 * a * c);
			if (discriminant < 0)
				continue;

        	const float distance = (- b - std::sqrt(discriminant)) / (2 * a);
			if (distance < 0)
				continue;

			if (distance > closestDistance)
				continue;

			closestSphereIndex = i;
			closestDistance = distance;
		}

		return closestSphereIndex != -1
			? hit(ray, m_Spheres[closestSphereIndex], closestDistance)
			: miss(ray);
	}
	
	Vector Renderer::hit(const Ray& ray, const SphereData& hitObject, float distance)
	{
        Vector hitPosition = ray.Position + (ray.Direction * distance);
        Vector hitNormal = hitPosition - hitObject.Origin;

        float lightCos = hitNormal.normalize() | (- m_DirectionalLight.Direction);
        return hitObject.Color * std::max(lightCos, 0.f);
	}
	
	Vector Renderer::miss(const Ray& ray)
	{
		return Vector{0.7, 0.7, 0.9};
	}
}