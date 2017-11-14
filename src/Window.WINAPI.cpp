#include <Veritas/Definitions/Definitions.h>
#ifdef PLATFORM_WINDOWS

#include <Veritas/Windowing/Window.h>

#include "Window.WINAPI.hpp"

using namespace Veritas;
using namespace Windowing;

void Window::systemCWindow(float32 width, float32 height, float32 x, float32 y) {
    static char szClassName[1024];
    GetModuleFileName(0,szClassName,1024);
    WNDCLASSEX wincl;
    wincl.hInstance = GetModuleHandle(0);
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = PImpl::WindowProc;
    wincl.style = 0;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;

    RegisterClassEx(&wincl);
    HWND hwnd = CreateWindowEx(0, szClassName, "", WS_OVERLAPPEDWINDOW, (int) x, (int) y, (int) width, (int) height, HWND_DESKTOP, NULL, GetModuleHandle(0) ,NULL);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) this);

    RegisterTouchWindow(hwnd,0);
    SetProp(hwnd, "MicrosoftTabletPenServiceProperty", (HANDLE)1);

    ShowWindow(hwnd, SW_SHOW);

    impl = new PImpl(hwnd);
}
void Window::systemDWindow() {
    delete impl;
}

void Window::systemRun() {
    MSG msg;
    while (PeekMessage(&msg, impl->hwnd, 0, 0, PM_REMOVE) > 0) {
        switch (msg.message) { // Friendship is really problematic, isn't it?
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MOUSEMOVE:
//            if (!(GetMessageExtraInfo() & MOUSEEVENTF_FROMTOUCH)) {
//                Touchscreen::Touch *touch;
//                if (msg.message == WM_MOUSEMOVE) {
//                    if (!lmouse->isHovering()) touch = lmouse;
//                    else if (!rmouse->isHovering()) touch = rmouse;
//                    else touch = mmouse;
//                    if (touch->isHovering()) runTouchHover(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
//                    else runTouchMove(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
//                } else {
//                    if (msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) touch = lmouse;
//                    else if (msg.message == WM_MBUTTONDOWN || msg.message == WM_MBUTTONUP) touch = mmouse;
//                    else if (msg.message == WM_RBUTTONDOWN || msg.message == WM_RBUTTONUP) touch = rmouse;
//                    if (msg.message == WM_LBUTTONDOWN || msg.message == WM_MBUTTONDOWN || msg.message == WM_RBUTTONDOWN) runTouchStart(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
//                    else runTouchEnd(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
//                }
//                break;
//            }
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::systemClose() {
    DestroyWindow(impl->hwnd);
}

void Window::systemSetFullscreen(bool b) {}

void Window::systemSetName(const std::string &name) { SetWindowText(impl->hwnd, name.c_str()); }

uint64 Window::systemGetNativeHandle() const { return (uint64) impl->hwnd; }

#endif
