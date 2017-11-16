#include <Veritas/Definitions/Definitions.h>
#ifdef PLATFORM_WINDOWS

#include <Veritas/Windowing/View.h>
#include <windows.h>
#include "Window.WINAPI.hpp"

using namespace Veritas;
using namespace Windowing;

void View::systemCView(Window *window, uint32 width, uint32 height) {}
void View::systemDView() {}

void View::systemSetDimension(uint32 width, uint32 height) {
    Window* window = getWindow();

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = width;
    r.bottom = height;

    AdjustWindowRectEx(&r, GetWindowLong((HWND) window->getNativeHandle(), GWL_STYLE), 0, GetWindowLong((HWND) window->getNativeHandle(), GWL_EXSTYLE));

    uint32 ww = r.right - r.left;
    uint32 wh = r.bottom - r.top;
    window->setDimension(ww, wh);
}

#endif
