#include <Veritas/Windowing/Window.h>
#include <Veritas/Windowing/View.h>

using namespace Veritas;
using namespace Windowing;
using namespace Data;

/*
Window::Window(const String& name)
    : isopen(true)
    , isfullscreen(false)
{
    systemCWindow(800, 600, 0, 0);
    view = new View(this);

    setName(name);
    setFullscreen(true); // we need an event to get the dimension change
}
*/

Window::Window(const String &name, uint32 width, uint32 height)
    : isopen(true)
    , isfullscreen(false)
{
    systemCWindow(800, 600, 0, 0);
    view = new View(this);

    setName(name);
}

void Window::setName(const String &name) {
    this->name = name;
    systemSetName(name);
}
const String& Window::getName() const { return name; }

void Window::setFullscreen(bool b) {
    if (b != isfullscreen) {
        systemSetFullscreen(b);
        isfullscreen = b;
    }
}
bool Window::isFullscreen() const { return isfullscreen; }

Window::~Window() {
    systemDWindow();
}

void Window::close() {
    systemClose();
    isopen = false;
}

bool Window::isOpen() const { return isopen; }

void Window::run() { systemRun(); }

uint64 Window::getNativeHandle() const { return systemGetNativeHandle(); }
View* Window::getView() const { return view; }
