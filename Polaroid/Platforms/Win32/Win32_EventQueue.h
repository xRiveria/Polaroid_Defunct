#pragma once
#include <Windows.h>
#include <queue>
#include "PolaroidDefinitions.h"
#include "../Commons/Event.h"

namespace Polaroid
{
    class Window;
    
    class EventQueue
    {
    public:
        EventQueue();

        void Tick();

        const Event& Front() { return m_Queue.front(); }
        void Pop()           { m_Queue.pop(); }
        bool Empty()         { return m_Queue.empty(); }
        size_t Size()        { return m_Queue.size(); }

        // LRESULT is an integer value that your program returns to Windows, containing a program's response to a particular message. 
        LRESULT PushEvent(MSG incomingMessage, Window* window); // The meaning of this value depends on the message code, with information contained in the MSG struct.

    protected:
        bool m_IsInitialized;
        std::queue<Event> m_Queue;
    };
}