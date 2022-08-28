
#include "renderer.h"
#include "core/log.h"

#include <chrono>

namespace raytracing
{
    constexpr float s_WorkingDistance = 3.f;
    constexpr float s_FOV = 3.f;

    Renderer::Renderer()
        : m_Texture(512, 512)
        , m_ImageWidth(512)
        , m_ImageHeight(512)
        , m_Camera(Vector{ 0.f, 0.f, -s_WorkingDistance }, s_WorkingDistance, s_FOV)
        , m_DirectionalLight(Vector{ 1.f, -1.f, 1.f }.normalize())
    {
        m_Spheres.emplace_back(Vector::Zero(), 1);
    }

    void Renderer::init()
    {
        m_Texture.create();
    }
    
    void Renderer::deinit()
    {
        m_Pixels.clear();
    }

    void Renderer::preTick()
    {
        m_Texture.resize(m_ImageWidth, m_ImageHeight);
    }
    
    void Renderer::tick()
    {
        const auto start = std::chrono::high_resolution_clock::now();

        const size_t width = m_Texture.getWidth();
        const size_t height = m_Texture.getHeight();

        const float doubleInvWidth= 2.f / width;
        const float doubleInvHeight = 2.f / height;

        const size_t newSize = width * height;
        m_TmpPixels.resize(newSize, 0xFF);
        m_Pixels.resize(newSize, 0xFF);

        for (size_t h = 0; h < height; h++)
        {
            for (size_t w = 0; w < width; w++)
            {
                const size_t index = h * width + w;

                float x = (w * doubleInvWidth) - 1;
                float y = (h * doubleInvHeight) - 1;
                Vector color = vertexShader(x, y) * 255.f;

                m_Pixels[index] = ((int32_t)color.R << 24)
                                   + ((int32_t)color.G << 16)
                                   + ((int32_t)color.B << 8)
                                   + 0xFF;
            }
        }

        antiAliasing();

        const auto end = std::chrono::high_resolution_clock::now();
        m_LastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 0.001f;
    }

    void Renderer::postTick()
    {
        m_Texture.setData(m_Pixels.data());
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

    Vector Renderer::vertexShader(float x, float y) // -1:+1
    {
        const Vector direction{ x * m_Camera.FieldOfView, y * m_Camera.FieldOfView, m_Camera.WorkingDistance };
        return checkSphere(direction, m_Spheres[0]);
    }

    Vector Renderer::checkSphere(const Vector& direction, const SphereData& sphere)
    {
        const float a = direction.sqrLength();
        const float b = 2.f * ((m_Camera.Position - sphere.Origin) | direction);
        const float c = m_Camera.Position.sqrLength() - 2.f * (m_Camera.Position | sphere.Origin) - (sphere.Radius * sphere.Radius);

        const float discriminant = (b * b) - (4 * a * c);
        if (discriminant < 0) // No Hit
            return Vector(1.f);

        float t = (- b - std::sqrt(discriminant)) / (2 * a);
        Vector hit = m_Camera.Position + (direction * t);
        Vector hitNormal = hit - sphere.Origin;

        float cos = hitNormal | (- m_DirectionalLight.Direction);
        return sphere.Color * std::max(cos, 0.f);
    }

    void Renderer::antiAliasing()
    {
        return;
        const size_t width = m_Texture.getWidth();
        const size_t height = m_Texture.getHeight();

        for (size_t h = 0; h < height; h++)
        {
            for (size_t w = 0; w < width; w++)
            {
                uint32_t R = 0;
                uint32_t G = 0;
                uint32_t B = 0;
                uint32_t count = 0;
                size_t zero = 0;

                // Close friends
                for (size_t hh = std::max(h-1, zero); hh < std::min(h+2, height); hh++)
                {
                    for (size_t ww = std::max(w-1, zero); ww < std::min(w+2, width); ww++)
                    {
                        const size_t index = hh * width + ww;
                        R += (m_TmpPixels[index] & 0xFF000000) >> 24;
                        G += (m_TmpPixels[index] & 0x00FF0000) >> 16;
                        B += (m_TmpPixels[index] & 0x0000FF00) >> 8;
                        count ++;
                    }
                }

                if (count)
                {
                    uint32_t red = (R / count) << 24;
                    uint32_t green = (G / count) << 16;
                    uint32_t blue = (B / count) << 8;

                    const size_t index = h * width + w;
                    m_Pixels[index] = red + green + blue + 0x000000FF;
                }
            }
        }
    }
}