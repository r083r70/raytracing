#pragma once

struct GLFWwindow;

namespace raytracing
{
    class Window
    {
    public:
        bool init(const char* title, int width, int height);
        void deinit();
        void tick();

        inline GLFWwindow* getHandle() const { return m_Handle; }
        void getSize(int& width, int& height) const;
    
    private:
        void setupEventCallbacks();

    private:
        GLFWwindow *m_Handle;
    };
}