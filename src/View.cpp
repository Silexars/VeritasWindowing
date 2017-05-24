#include <Veritas/Windowing/View.h>
#include <Veritas/Windowing/Window.h>

using namespace Veritas;
using namespace Windowing;
using namespace Orchestra;

using namespace Messaging;
using namespace Interfacing;

Interfacer View::interfacer = Interfacer(LocalModule::getInterfacer()).set("Reply", ReplyInterface("Window", &View::WindowRequest));

View::View(Window* window)
    : LocalModule(Address(this), interfacer)
    , window(window)
{
    systemCView(window);
}
View::~View() {
    systemDView();
}

void View::WindowRequest(const Message &message, const Replier &replier) {
    replier.reply(Form().set("Address", window->getAddress()));
}

/*
View::View(Window* parent) : parent(parent), glctx(0) {
    on("Redimension", [](const Message& m) {
        View* view = any_cast<View*>(m.getDestiny());
        view->dimension = m.get<vec2>("Dimension");
    });

    system = new System(this, parent);
    position = system->getPosition();
    dimension = system->getDimension();
    setPixelFormat(RGB888);
}

View::~View() {
    delete glctx;
    delete system;
}

void View::setDimension(const vec2 &dimension) {
    system->setDimension(dimension);
    this->dimension = system->getDimension();
}

vec2 View::getDimension() const { return dimension; }

void View::setPosition(const vec2 &position) {
    system->setPosition(position);
    this->position = system->getPosition();
}
vec2 View::getPosition() const { return position; }

void View::setPixelFormat(PIXELFORMAT pixelFormat) {
    system->setPixelFormat(pixelFormat);
    this->pixelFormat = system->getPixelFormat();
}

View::PIXELFORMAT View::getPixelFormat() const { return pixelFormat; }

Window* View::getParent() const { return parent; }

GLContext* View::getGLContext() const {
    if (!glctx) const_cast<View*>(this)->glctx = new GLContext(const_cast<View*>(this));
    return glctx;
}
*/
