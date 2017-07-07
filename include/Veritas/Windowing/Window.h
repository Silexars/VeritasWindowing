#pragma once

#include <string>
#include <Veritas/Windowing/View.h>

namespace Veritas {
    namespace Windowing {
        class Window {
            public:
                Window(const std::string& name = "");
                Window(const std::string& name, uint32 width, uint32 height);
                ~Window();

                View& getView();
                const View& getView() const;

                bool isOpen() const;

                void setName(const std::string& name);
                const std::string& getName() const;

                void setFullscreen(bool b);
                bool isFullscreen() const;

                uint64 getNativeHandle() const;
                void run();

                enum KEY {
                    A = 'A',
                    W = 'W',
                    S = 'S',
                    D = 'D',
                    Q = 'Q',
                    E = 'E',
                    LEFT = 8592,
                    UP = 8593,
                    RIGHT = 8594,
                    DOWN = 8595
                };
                typedef std::function<void(KEY key)> KeyEventCallback;
                void onKeyDown(KeyEventCallback callback);
                void onKeyUp(KeyEventCallback callback);
            private:
                View* view;
                std::string name;
                bool isfullscreen;
                bool isopen;

                KeyEventCallback onkeydown, onkeyup;

                void close();

                class PImpl;
                PImpl *impl;
                void systemCWindow(float32 width, float32 height, float32 x, float32 y);
                void systemDWindow();
                void systemRun();
                void systemClose();
                void systemSetFullscreen(bool b);
                void systemSetName(const std::string& name);
                uint64 systemGetNativeHandle() const;
        };
    }
}
