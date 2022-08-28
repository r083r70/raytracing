#pragma once

#include <functional>

namespace raytracing
{
    enum class EventType
    {
        None,
		WindowClosed,
		WindowResized
    };

    struct EventData
    {
        virtual ~EventData() {}
    };

    struct WindowResizedEventData : public EventData
    {
        WindowResizedEventData(int32_t width, int32_t height) : Width(width), Height(height) {}
        int32_t Width;
        int32_t Height;
	};
    
    class Event
    {
    public:
        Event(EventType eventType, EventData* eventData) : m_Type(eventType), m_Data(eventData) {}
        ~Event() { delete m_Data; }

        EventType getType() const { return m_Type; }
		EventData* getRawData() const { return m_Data; }

        template<class T>
		T* getData() const { return static_cast<T*>(m_Data); }

	private:
		EventType m_Type;
		EventData* m_Data;
    };
}