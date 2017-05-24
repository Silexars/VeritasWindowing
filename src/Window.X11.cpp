#include <Veritas/Definitions/Definitions.h>
#ifdef PLATFORM_LINUX

#include <Veritas/Windowing/Window.h>
#include "Window.X11.h"

#include <cstring>
#include <cstdio>

using namespace Veritas;
using namespace Data;

using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

using Windowing::Window;

void Window::systemCWindow(float32 width, float32 height, float32 x, float32 y) {
    XInitThreads();

    ::Display* display = XOpenDisplay(0);
    ::Window window = XCreateSimpleWindow(display, RootWindow(display, 0), x, y, width, height, 0, BlackPixel(display, 0), WhitePixel(display ,0));

    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | StructureNotifyMask );
    XMapWindow(display, window);

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    if (!setlocale(LC_ALL, "")) perror("setlocale");
    if (!XSupportsLocale()) perror("XSupportsLocale");
    if (!XSetLocaleModifiers("@im=none")) perror("XSetLocaleModifiers");

    XIM inputMethod = XOpenIM(display, 0, 0, 0);
    if (!inputMethod) perror("XOpenIM");

    XIC inputContext = XCreateIC(inputMethod, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, window, NULL);
    if (!inputContext) perror("XCreateIC");
    XSetICFocus(inputContext);

    impl = new PImpl(display, window, wmDeleteMessage, inputMethod, inputContext);
}

void Window::systemDWindow() {
    delete impl;
}

void Window::systemClose() {
    XDestroyWindow(impl->display, impl->window);
    publisher.publish("Close");
}

void Window::systemRun() {
    while (XPending(impl->display)) {
        XEvent e;
        XPeekEvent(impl->display, &e);
        if (e.type == UnmapNotify || e.type == DestroyNotify)
            XNextEvent(impl->display, &e); // if any Window was closed and it's no longer listed, we can ignore their destruction events
        else if (e.xany.window == impl->window) {
            XNextEvent(impl->display, &e);
            if (XFilterEvent(&e, impl->window)) continue;

            switch (e.type) {
                case ClientMessage: if ((Atom) e.xclient.data.l[0] == impl->wmDeleteMessage) {
                    systemClose();
                    break;
                }
            }
        } else return;
    }
}

uint64 Window::systemGetNativeHandle() const { return (uint64) impl->window; }

#endif

//#include <Veritas/Definitions/Definitions.h>
//#ifdef PLATFORM_LINUX

//#include <Veritas/System/UI/Window.h>
//#include "Window.X11.h"

//#include <cstring>
//#include <cstdio>

//using namespace Veritas;
//using namespace Data;
//using namespace System;
//using namespace Math;

//using namespace Orchestra;

//using UI::Window;

//Window::System::System(Window *generic, Window *parent, const String &name) : System(generic, parent, name, vec2(1.0), vec2(0.0)) {}
//Window::System::System(Window* generic, Window* parent, const String& name, const vec2& dimension, const vec2& position) : generic(generic) {
//    ::Display* display = XOpenDisplay(0);
//    ::Window window = XCreateSimpleWindow(display, RootWindow(display, 0), position.x, position.y, dimension.x, dimension.y, 0, BlackPixel(display, 0), WhitePixel(display ,0));

//    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | StructureNotifyMask );
//    XMapWindow(display, window);

//    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
//    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

//    if (!setlocale(LC_ALL, "")) perror("setlocale");
//    if (!XSupportsLocale()) perror("XSupportsLocale");
//    if (!XSetLocaleModifiers("@im=none")) perror("XSetLocaleModifiers");

//    XIM inputMethod = XOpenIM(display, 0, 0, 0);
//    if (!inputMethod) perror("XOpenIM");

//    XIC inputContext = XCreateIC(inputMethod, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, window, NULL);
//    if (!inputContext) perror("XCreateIC");
//    XSetICFocus(inputContext);

//    impl = new PImpl(display, window, wmDeleteMessage, inputMethod, inputContext);
//}

//Window::System::~System() {
//    delete impl;
//}

//void Window::System::close() {
//    XDestroyWindow(impl->display, impl->window);
//}

//void Window::System::setName(const String& name) { XStoreName(impl->display, impl->window, name.c_str()); }

//void Window::System::setPosition(const vec2& position) {
//    vec2 v = generic->getView()->getPosition();
//    vec2 param = position - v;
//    XMoveWindow(impl->display, impl->window, param.x, param.y);
//}
//vec2 Window::System::getPosition() const {
//    #warning TO-DO
//    return vec2(0.0);
//}

//void Window::System::setDimension(const vec2& dimension) {
//    vec2 v = generic->getView()->getPosition();
//    vec2 param = vec2(dimension.x - v.x * 2.0, dimension.y - v.x - v.y);
//    XResizeWindow(impl->display, impl->window, param.x, param.y);
//}
//vec2 Window::System::getDimension() const {
//    #warning TO-DO
//    return vec2(0.0);
//}

///*
//void Window::System::setCursorVisibility(bool b) {
//    if (b && !cursorVisibility) XUndefineCursor(((LinuxWindow*) id)->d,((LinuxWindow*) id)->w);
//    else if (!b && cursorVisibility) {
//        ::Display *display = ((LinuxWindow*) id)->d;
//        ::Window window = ((LinuxWindow*) id)->w;

//        XColor black = {0};
//        static char noData[8] = {0};
//        Pixmap bitmapNoData = XCreateBitmapFromData(display, window, noData, 8, 8);
//        Cursor invisibleCursor = XCreatePixmapCursor(display, bitmapNoData, bitmapNoData, &black, &black, 0, 0);

//        XDefineCursor(display,window, invisibleCursor);

//        XFreePixmap(display,bitmapNoData);
//        XFreeCursor(display, invisibleCursor);
//    }
//    cursorVisibility = b;
//}
//*/

//void Window::System::setFullscreen(bool b) {
//    XEvent xev;
//    Atom wm_state = XInternAtom(impl->display, "_NET_WM_STATE", False);
//    Atom fullscreen = XInternAtom(impl->display, "_NET_WM_STATE_FULLSCREEN", False);

//    memset(&xev, 0, sizeof(xev));
//    xev.type = ClientMessage;
//    xev.xclient.window = impl->window;
//    xev.xclient.message_type = wm_state;
//    xev.xclient.format = 32;
//    xev.xclient.data.l[0] = b;
//    xev.xclient.data.l[1] = fullscreen;
//    xev.xclient.data.l[2] = 0;

//    XSendEvent(impl->display, DefaultRootWindow(impl->display), False, SubstructureNotifyMask, &xev);
//}

//void Window::System::run() {
//    while (XPending(impl->display)) {
//        XEvent e;
//        XPeekEvent(impl->display, &e);
//        if (e.type == UnmapNotify || e.type == DestroyNotify) XNextEvent(impl->display, &e); // if any Window was closed and it's no longer listed, we can ignore their destruction events
//        else if (e.xany.window == impl->window) {
//            XNextEvent(impl->display, &e);
//            if (XFilterEvent(&e, impl->window)) continue;

//            switch (e.type) {
//                case KeymapNotify: XRefreshKeyboardMapping(&e.xmapping); break;
//                case Expose: if (e.xexpose.count == 0) /*runDraw();*/ break;
//                case ConfigureNotify: {
//                    vec2 v = generic->getView()->getPosition();
//                    vec2 np = vec2(e.xconfigure.x, e.xconfigure.y) - v;
//                    vec2 nd = vec2(e.xconfigure.width, e.xconfigure.height) + vec2(v.x, v.x + v.y);

//                    if (nd != v) Message("Redimension").set("Dimension", nd).dispatch(generic, generic);
//                    if (np != generic->getPosition()) Message("Reposition").set("Position", np).dispatch(generic, generic);
//                }
//                break;
//                case FocusIn: Message("Focus").dispatch(generic, generic); break;
//                case FocusOut: Message("Blur").dispatch(generic, generic); break;
//                case ButtonPress:
//                case MotionNotify:
//                case ButtonRelease: {
//                    /*
//                    Touchscreen::Touch *touch;
//                    if (e.type == MotionNotify) {
//                        if (!lmouse->isHovering()) touch = lmouse;
//                        else if (!rmouse->isHovering()) touch = rmouse;
//                        else touch = mmouse;
//                        if (touch->isHovering()) runTouchHover(touch, vec2(e.xmotion.x, e.xmotion.y));
//                        else runTouchMove(touch, vec2(e.xmotion.x, e.xmotion.y));
//                    } else {
//                        if (e.xbutton.button == 1) touch = lmouse;
//                        else if (e.xbutton.button == 2) touch = mmouse;
//                        else if (e.xbutton.button == 3) touch = rmouse;
//                        else if (e.xbutton.button == 4) break; // scroll up
//                        else if (e.xbutton.button == 5) break; // scroll down - if they don't break, they will access a non-allocated touch
//                        if (e.type == ButtonRelease) runTouchEnd(touch, vec2(e.xmotion.x, e.xmotion.y));
//                        else runTouchStart(touch, vec2(e.xmotion.x, e.xmotion.y));
//                    }
//                    */
//                    break;
//                }
//                case KeyPress:
//                case KeyRelease: {
//                    bool shift = e.xkey.state & ShiftMask;
//                    bool numlock = e.xkey.state & Mod2Mask;
//                    bool capslock = e.xkey.state & LockMask;

//                    uint32 keyCode = e.xkey.keycode;
//                    if (e.type == KeyPress) {
//                        KeySym keysym = 0;
//                        Status status = 0;
//                        char str[20];

//                        int isPrintable = Xutf8LookupString(impl->inputContext, (XKeyPressedEvent*) &e, str, sizeof(str), &keysym, &status);
//                        uint32 charCode = isPrintable ? String::getCharCodeFromUTF8(str) : 0;

//                        Message("KeyStart").set("KeyCode", (uint32) keyCode)
//                                           .set("CharCode", (uint32) charCode)
//                                           .set("Shift", (bool) shift)
//                                           .set("Numlock", (bool) numlock)
//                                           .set("Capslock", (bool) capslock)
//                                           .dispatch(generic, generic);
//                    } else Message("KeyEnd").set("KeyCode", keyCode)
//                                            .set("Shift", (bool) shift)
//                                            .set("Numlock", (bool) numlock)
//                                            .set("Capslock", capslock)
//                                            .dispatch(generic, generic);
//                    break;
//                }
//                case ClientMessage: if ((Atom) e.xclient.data.l[0] == impl->wmDeleteMessage) {
//                    Message("Close").dispatch(generic, generic);
//                    break;
//                }
//            }
//        } else return;
//    }
//}

//#endif
