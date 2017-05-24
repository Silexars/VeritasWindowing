#include <Veritas/Windowing/View.h>

using namespace Veritas;
using namespace Windowing;
using namespace Orchestra;

using namespace Messaging;

View::View(Window* parent) : parent(parent) {
    system = new System(parent);
    send(this, Message("RequestPixelFormat").set("PixelFormat", "R8G8B8"));
}
View::~View() {
    delete system;
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
