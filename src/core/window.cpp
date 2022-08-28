
#include "window.h"

#include "eventdispatcher.h"
#include "log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace raytracing
{
    bool Window::init(const char* title, int width, int height)
    {
        glfwInit();

        m_Handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (m_Handle == nullptr)
            return false;
        
        glfwMakeContextCurrent(m_Handle);
        setupEventCallbacks();

        const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        return status;
    }

    void Window::deinit()
    {
        // Remove callbacks
        glfwSetCharCallback(m_Handle, nullptr);
        glfwSetWindowSizeCallback(m_Handle, nullptr);
        glfwSetWindowCloseCallback(m_Handle, nullptr);
        
        glfwDestroyWindow(m_Handle);
        m_Handle = nullptr;

        glfwTerminate();
    }

    void Window::tick()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Handle);
    }

    void Window::getSize(int& width, int& height) const
    {
        glfwGetWindowSize(m_Handle, &width, &height);
    }

	void Window::setupEventCallbacks()
    {
        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			EventDispatcher::get()->createEvent(EventType::WindowClosed);
        });

        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			auto eventData = new WindowResizedEventData{ width, height };
            EventDispatcher::get()->createEvent(EventType::WindowResized, eventData);
        });
    }
}