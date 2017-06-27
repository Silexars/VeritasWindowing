#include <Veritas/Definitions/Definitions.h>
#ifdef PLATFORM_LINUX

#include <Veritas/Windowing/View.h>
#include "Window.X11.h"

using namespace Veritas;
using namespace Windowing;

void View::systemCView(Window *parent, uint32 width, uint32 height) {}
void View::systemDView() {}

#endif

//#include <Veritas/Definitions/Definitions.h>
//#ifdef PLATFORM_LINUX

//#include <Veritas/System/UI/View.h>
//#include "Window.X11.h"

//using namespace Veritas;
//using namespace System;
//using namespace UI;
//using namespace Math;

//View::System::System(View *generic, Window *parent) : generic(generic) {}
//View::System::~System() {}

//void View::System::setDimension(const vec2& dimension) {
//    Window *window = generic->getParent();

//    vec2 p = getPosition();

//    vec2 param = vec2(dimension.x + p.x * 2.0, dimension.y + p.x + p.y);
//    window->setDimension(param);
//}

//vec2 View::System::getDimension() const {
//    Window* window = generic->getParent();

//    ::Window root;
//    int x, y;
//    unsigned int w, h, border, depth;
//    XGetGeometry(window->system->impl->display, window->system->impl->window, &root, &x, &y, &w, &h, &border, &depth);
//    return vec2(w, h);
//}

//void View::System::setPosition(const vec2 &position) {}
//vec2 View::System::getPosition() const {
//    Window *window = generic->getParent();
//    XWindowAttributes xwa;
//    do {
//        XGetWindowAttributes(window->system->impl->display, window->system->impl->window, &xwa);
//    } while (xwa.x < 0 || xwa.y < 0);
//    return vec2(xwa.x, xwa.y);
//}

//void View::System::setPixelFormat(PIXELFORMAT pixelFormat) {}
//View::PIXELFORMAT View::System::getPixelFormat() const { return View::RGB888; }

//#endif
