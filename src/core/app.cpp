
#include "app.h"

#include "events.h"
#include "log.h"
#include "serializer.h"

namespace raytracing
{
	App* App::s_Instance = nullptr;

	App::App() : m_Window()
        , m_ImGuiClient()
        , m_Title("baseApp")
        , m_Width(720)
        , m_Height(480)
        , b_ShouldClose(false)
    { }

	bool App::init()
    {
		s_Instance = this;

		Log::init();
        RT_DEBUG("Log Inited");

        m_EventDispatcher.init();
        m_EventDispatcher.subscribe(this);

		Serializer::loadWindowSize(m_Width, m_Height);
        if (!m_Window.init(m_Title, m_Width, m_Height))
            return false;
        
        if (!m_ImGuiClient.init(m_Window))
            return false;

        m_Screens.push_back(new MainMenuBarScreen());
        m_Screens.push_back(new ImageScreen());
        m_Screens.push_back(new StatsScreen());

        m_Renderer.init();

        RT_DEBUG("Inited");

        return true;
    }
    
    void App::run()
    {
        while (!b_ShouldClose)
		{
            m_EventDispatcher.tick();

            m_Renderer.preTick();
            m_Renderer.tick();
            m_Renderer.postTick();

            m_Window.tick();
            
            m_ImGuiClient.preTick(m_Width, m_Height);
            m_ImGuiClient.tick();
            std::for_each(m_Screens.begin(), m_Screens.end(), [](auto Elem) { Elem->tick(); });
            m_ImGuiClient.postTick();
		}

		Serializer::saveWindowSize(m_Width, m_Height);

        std::for_each(m_Screens.begin(), m_Screens.end(), [](auto& Elem) { delete Elem; Elem = nullptr; });
        m_Screens.clear();
        
        m_ImGuiClient.deinit();
        m_Window.deinit();

        m_Renderer.deinit();

        m_EventDispatcher.deinit();
    }
    
    bool App::onEvent(const Event& event)
    {
        switch (event.getType())
        {
        case raytracing::EventType::WindowClosed:
            b_ShouldClose = true;
            return true;
        case raytracing::EventType::WindowResized:
            m_Width = event.getData<WindowResizedEventData>()->Width;
            m_Height = event.getData<WindowResizedEventData>()->Height;
            RT_DEBUG("WindowResized: {}, {}", m_Width, m_Height);
			return true;
        }

		return false;
    }
}
