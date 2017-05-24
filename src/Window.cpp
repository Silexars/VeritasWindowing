#include <Veritas/Windowing/Window.h>
#include <Veritas/Windowing/View.h>

using namespace Veritas;
using namespace Windowing;
using namespace Data;

using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

Interfacer Window::interfacer = Interfacer(LocalModule::getInterfacer()).set("Reply", ReplyInterface("View", &Window::ViewRequest))
                                                                        .set("Reply", ReplyInterface("NativeHandle", &Window::NativeHandleRequest))
                                                                        .set("Output", OutputInterface("Close"))
                                                                        .set("Input", InputInterface("Run", &Window::Run));

Window::Window()
    : LocalModule(Address(this), interfacer)
    , requester(this)
    , publisher(this)
{
    systemCWindow(800, 600, 0, 0);
    view = new View(this);
    requester.request("Subscription", VO::getInstance().getRunner());
}

Window::~Window() {
    systemDWindow();
}

void Window::run() { systemRun(); }

void Window::Run(const Message& message) { systemRun(); }

void Window::ViewRequest(const Message& message, const Replier& replier) {
    replier.reply(Form().set("Address", view->getAddress()));
}

void Window::NativeHandleRequest(const Message &message, const Replier& replier) {
    replier.reply(Form().set("NativeHandle", (uint64) getNativeHandle()));
}

uint64 Window::getNativeHandle() const { return systemGetNativeHandle(); }
