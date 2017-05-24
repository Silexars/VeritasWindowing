#pragma once

#include <Veritas/Windowing/Window.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xlocale.h>
#include <X11/extensions/XI2.h>

class Veritas::Windowing::Window::PImpl {
    public:
        PImpl(::Display* display, ::Window window, Atom wmDeleteMessage, XIM inputMethod, XIC inputContext) : display(display), window(window), wmDeleteMessage(wmDeleteMessage), inputMethod(inputMethod), inputContext(inputContext) {}
        ~PImpl() {
            XDestroyIC(inputContext);
            XCloseIM(inputMethod);
        }

        ::Display* display;
        ::Window window;
        Atom wmDeleteMessage;
        XIM inputMethod;
        XIC inputContext;
};
