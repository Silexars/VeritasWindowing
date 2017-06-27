#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Windowing {
        class Window;
        class View {
            public:
                ~View();

                uint32 getWidth() const;
                uint32 getHeight() const;

                Window* getWindow() const;
            private:
                uint32 width, height;

                friend class Window;
                View(Window* window, uint32 width, uint32 height);
                Window* window;

                void systemCView(Window* window, uint32 width, uint32 height);
                void systemDView();
        };
    }
}
