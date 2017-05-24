#include <Veritas/Windowing/Windowing.h>

using namespace Veritas;
using namespace Windowing;

WindowService::WindowService() {}
WindowService::~WindowService() {}

Window* WindowService::requestWindow(const Data::String &name) {
    return new Window();
}

/*
void WindowService::WindowRequest(const Message& message, const Replier& replier) {
    Window* window = new Window();
    replier.reply(Form().set("Address", window->getAddress()));
}
*/
