#pragma once

#include <Veritas/Windowing/Window.h>
#include <Windows.h>

class Veritas::Windowing::Window::PImpl {
    public:
    PImpl(HWND hwnd) : hwnd(hwnd) {}
        ~PImpl() {
        }

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Window *window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
        switch (msg) {
            case WM_DESTROY: window->wasClosed(); break;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    HWND hwnd;
};

using namespace Veritas::Windowing;
