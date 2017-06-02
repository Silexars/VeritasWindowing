#pragma once

#include <Veritas/Data/String.h>
#include <Veritas/Windowing/View.h>

namespace Veritas {
    namespace Windowing {
        class Window {
            public:
                Window(const Data::String& name = "");
                Window(const Data::String& name, uint32 width, uint32 height);
                ~Window();

                View* getView() const;

                bool isOpen() const;

                void setName(const Data::String& name);
                const Data::String& getName() const;

                void setFullscreen(bool b);
                bool isFullscreen() const;

                uint64 getNativeHandle() const;
                void run();
            private:
                View* view;
                Data::String name;
                bool isfullscreen;
                bool isopen;



                void close();

                class PImpl;
                PImpl *impl;
                void systemCWindow(float32 width, float32 height, float32 x, float32 y);
                void systemDWindow();
                void systemRun();
                void systemClose();
                void systemSetFullscreen(bool b);
                void systemSetName(const Data::String& name);
                uint64 systemGetNativeHandle() const;
        };
    }
}
