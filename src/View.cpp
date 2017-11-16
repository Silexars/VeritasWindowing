#include <Veritas/Windowing/View.h>
#include <Veritas/Windowing/Window.h>

using namespace Veritas;
using namespace Windowing;

View::View(Window* window, uint32 width, uint32 height)
    : window(window)
    , width(width)
    , height(height)
{
    systemCView(window, width, height);
    setDimension(width, height);
}
View::~View() {
    systemDView();
}

Window* View::getWindow() const { return window; }

uint32 View::getWidth() const { return width; }
uint32 View::getHeight() const { return height; }

void View::setDimension(uint32 width, uint32 height) {
    this->width = width;
    this->height = height;
    systemSetDimension(width, height);
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
