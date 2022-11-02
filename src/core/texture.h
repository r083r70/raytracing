#pragma once

#include<cstdint>

namespace raytracing
{
    class Texture
    {
    public:
        Texture(uint32_t width, uint32_t height);
        ~Texture();

        void create();

        void resize(uint32_t width, uint32_t height);
        void setData(void* data);

        inline uint32_t get() const { return m_TextureID; }
        
        inline uint32_t getWidth() const { return m_Width; }
        inline uint32_t getHeight() const { return m_Height; }
        
    private:
        uint32_t m_Width, m_Height;
        uint32_t m_TextureID;
    };
}