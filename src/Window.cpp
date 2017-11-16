#include <Veritas/Windowing/Window.h>
#include <Veritas/Windowing/View.h>

using namespace Veritas;
using namespace Windowing;

using std::string;

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

Window::Window(const string &name, uint32 width, uint32 height)
    : isopen(true)
    , isfullscreen(false)
{
    systemCWindow((float32) width, (float32) height, 0.0f, 0.0f);
    view = new View(this, width, height);

    setName(name);
}

void Window::setName(const string &name) {
    this->name = name;
    systemSetName(name);
}
const string& Window::getName() const { return name; }

void Window::setFullscreen(bool b) {
    if (b != isfullscreen) {
        systemSetFullscreen(b);
        isfullscreen = b;
    }
}
bool Window::isFullscreen() const { return isfullscreen; }

void Window::setDimension(uint32 width, uint32 height) {
    systemSetDimension(width, height);
    wasSetDimension(width, height);
}

void Window::wasSetDimension(uint32 width, uint32 height) {
    this->width = width;
    this->height = height;
}

Window::~Window() {
    if (isOpen()) close();
    systemDWindow();
}

void Window::close() {
    systemClose();
    wasClosed();
}

void Window::wasClosed() { isopen = false; }

bool Window::isOpen() const { return isopen; }

void Window::run() { systemRun(); }

uint64 Window::getNativeHandle() const { return systemGetNativeHandle(); }
const View& Window::getView() const { return *view; }
View& Window::getView() { return *view; }

void Window::onKeyDown(KeyEventCallback callback) { onkeydown = callback; }
void Window::onKeyUp(KeyEventCallback callback) { onkeyup = callback; }
