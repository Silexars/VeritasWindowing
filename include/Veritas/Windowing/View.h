#pragma once

#include <Veritas/Orchestra/Orchestra.h>

namespace Veritas {
    namespace Windowing {
        class Window;
        class View : public Orchestra::Runtime::LocalModule {
            public:
                ~View();
            private:
                Window* window;

                static Orchestra::Interfacing::Interfacer interfacer;

                friend class Window;
                View(Window* window);

                void WindowRequest(const Orchestra::Messaging::Message& message, const Orchestra::Interfacing::Replier& replier);

                void systemCView(Window* window);
                void systemDView();
        };
    }
}
