#include "Win32_EventQueue.h"
#include "../Commons/Window.h"

#define TITLE_BAR_HEIGHT 32

namespace Polaroid
{
    EventQueue::EventQueue()
    {
        m_IsInitialized = true;
    }

    void EventQueue::Tick()
    {
        /*
            PeekMessage checks the thread message queue for a posted message (incoming event) and retrieves the message (if any exist). Parameters:

            - LPMSG lpMsg:        A pointer to an MSG structure that receives message information.
            - HWND hWnd:          A handle to the window whose messages are to be retrieved. The window must belong on the current thread. If NULL, PeekMessage retrieves messages for any window that belongs to the current thread and any message on the current thread's message queue whose hwnd value is NULL.
            - UINT wMsgFilterMin: The value of the first message in the range of messages to be examined. Use WM_KEYFIRST to specify the first keyboard message or WM_MOUSEFIRST for the first mouse message.
            - UINT wMsgFilterMax: Like the above, but for the last message. If both Min and Max are 0, PeekMessage returns all avaliable messages - no range filtering is performed.
            - UINT wRemoveMsg:    Specifies how the messages are to be handled. For example, to remove from queue after peaking or not. For us, we will use remove after processing.
        
            See: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
        */
        MSG message = {};
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            // Produces WM_CHAR messages only for keys that are mapped to ASCII characters by the keyboard drivers. The character messages are posted to the calling thread's message queue to be read the next time the thread calls the GetMessage or PeekMessage function.
            TranslateMessage(&message);

            // Dispatches a message to a window procedure. Returns an LRESULT which specifies a value (depending on the dispatched message) returned by the window procedure. 
            DispatchMessage(&message); 
        }
    }

    LRESULT EventQueue::PushEvent(MSG incomingMessage, Window* window)
    {
        UINT message = incomingMessage.message;
        LRESULT result = 0; // Contains our application's response to a particular window message.

        if (!m_IsInitialized)
        {
            m_IsInitialized = true;

        }

        Polaroid::Event event = Polaroid::Event(Polaroid::EventType::None, window);

        // Messages are received through a window's WindowProc function.
        switch (message)
        {
            case WM_CREATE:     // Sent when an application requests that a window be created by calling the CreateWindowEx or CreateWindow function. 
            {
                event = Polaroid::Event(Polaroid::EventType::Create, window);
                // Repaint window when borderless to avoid title bar.
                if (!window->RetrieveDescription().m_IsFrameEnabled)
                {
                    RECT lpRect; // The RECT structure defines a rectangle by the coordinates of its upper-left and lower-right corners.
                    GetWindowRect(window->RetrieveHWND(), &lpRect); // Retrieves the dimensions of the bounding rectangle of the specified window. The dimensions are given in screen coordinates that are relative to the upper-left corner of the screen.
                    SetWindowPos(window->RetrieveHWND(), 0, lpRect.left, lpRect.top, lpRect.right - lpRect.left, lpRect.bottom - lpRect.top - TITLE_BAR_HEIGHT, 0); // Changes the size, position and Z order of a child, pop-up or top-level window.
                }         
                break;
            }
            case WM_CLOSE:
            {
                break;
            }
            case WM_DESTROY:    // Sent when a window is being destroyed. This is message is first sent to the window being destroyed, and then to its child windows (if any) as they are destroyed. 
            {
                event = Polaroid::Event(Polaroid::EventType::Close, window);
                break;
            }
            /*
                Sent when the system or another application makes a request to paint a portion of an application's window. The message is sent when the UpdateWindow or RedrawWindow 
                function is called, or by the DispatchMessage function when the application obtains a WM_PAINT message by using the GetMessage or PeekMessage function.
            */
            case WM_PAINT:      
            {
                PAINTSTRUCT paintInformation; // Contains paint information that is used to paint the client area of a window owned by the application.

                // Prepares the specified window for painting and fills a PAINTSTRUCTURE structure with information about the painting.
                BeginPaint(window->RetrieveHWND(), &paintInformation); // All painting occurs here, between BeginPaint and EndPaint.

                RECT rect;
                GetWindowRect(window->RetrieveHWND(), &rect);

                int cXWidth = rect.right - rect.left;
                int cYHeight = rect.bottom - rect.top;
                uint32_t backgroundColor = window->RetrieveDescription().m_BackgroundColor;

                unsigned r = (backgroundColor & 0xFF000000) >> 24;
                unsigned g = (backgroundColor & 0X00FF0000) >> 16;
                unsigned b = (backgroundColor & 0x0000FF00) >> 8;

                // Creates a logical brush that has the specified solid color. It takes in a COLORREF color value (with the RGB macro).
                HBRUSH borderBrush = CreateSolidBrush(RGB(r, g, b)); // A solid brush is a bitmap that the system uses to paint the interiors of filled shapes.

                // Fills a rectangle by using the specified brush. ("hdc" is a pointer to the device context, "lrpc" is a pointer to the RECT structure containing the logical coordinates of the rectangle to be filled, "hbr" is a handle to the brush used to fill the rectangle.
                FillRect(paintInformation.hdc, &rect, borderBrush); 

                // Marks the end of paining in the specified window. Required after painting is complete.
                EndPaint(window->RetrieveHWND(), &paintInformation);

                event = Polaroid::Event(Polaroid::EventType::Paint, window);
                break;
            }
            case WM_SETFOCUS:
            {
                event = Polaroid::Event(Polaroid::FocusData(true), window);
                break;
            }
            case WM_KILLFOCUS:
            {
                event = Polaroid::Event(Polaroid::FocusData(false), window);
                break;
            }
            case WM_SIZING:       // Sent to a window that the user is resizing. By processing this message, an application can monitor the size and position of the drag rectangle and if needed, change its size or position.
            {
                break;
            }
            case WM_SIZE:         // Sent to a window after its size has changed.
            {
                break;
            }
            /*
                Sent when the effective dots per inch (DPI) for a window has changwed. The DPI is the scale factor for a window. There are multiple events that can cause the DPI to change.
                Some possible changes are:

                - The window is moved to a new monitor that has a different DPI.
                - The DPI of the monitor hosting the window changes.

                The current DPI for a window always equals the last DPI sent by WM_DPICHANGED. This is the scale factor that the window should be scaling to for threads that are aware of DPI changes.
            */
            case WM_DPICHANGED:   
            {
                WORD g_DPI = HIWORD(incomingMessage.wParam); // The HIWORD of the wParam contains the U-axis value of the new DPI of the window. LOWARD contains the X axis likewise.
                // The base value of DPI is defined as USER_DEFAULT_SCREEN_DPI. To determine the scaling factor for a monitor, take the DPI value and divide by USER_DEFAULT_SCREEN API.
                FLOAT fScale = (float)g_DPI / USER_DEFAULT_SCREEN_DPI;

                event = Polaroid::Event(DPIData(fScale), window);
                break;
            }
            case WM_GETMINMAXINFO:
            {
                MINMAXINFO* minMax = reinterpret_cast<MINMAXINFO*>(incomingMessage.lParam); // Contains information about a window's maximized size and position and its minimum/maximum tracking size.

                minMax->ptMinTrackSize.x = window->RetrieveDescription().m_WidthMinimum;    // The minimum tracking width of the window.
                minMax->ptMinTrackSize.y = window->RetrieveDescription().m_HeightMinimum;   // The minimum tracking height of the window.
                
                break;
            }
            default:
            {
                break;
            }
        }

        POLAROID_ASSERT(event.RetrieveEventType() != EventType::None);
        m_Queue.emplace(event);
        window->ExecuteEventCallback(event);

        return result;
    }
}