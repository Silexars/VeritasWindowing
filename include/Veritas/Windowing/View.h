#pragma once

#include <Veritas/Orchestra/Orchestra.h>

namespace Veritas {
    namespace Windowing {
        class Window;
        class View {
            public:
                ~View();

                Window* getWindow() const;
            private:
                friend class Window;
                View(Window* window);
                Window* window;

                void systemCView(Window* window);
                void systemDView();
        };
    }
}
