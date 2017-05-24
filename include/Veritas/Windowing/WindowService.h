#pragma once

#include <Veritas/Orchestra/Orchestra.h>
#include "Window.h"

namespace Veritas {
    namespace Windowing {
        class WindowService {
            public:
                WindowService();
                ~WindowService();

                Window* requestWindow(const Data::String& name);
        };
    }
}
