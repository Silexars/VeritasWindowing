#pragma once

#include <Veritas/Orchestra/Orchestra.h>

namespace Veritas {
    namespace Windowing {
        class Window : public Orchestra::Runtime::LocalModule {
            public:
                Window();
                ~Window();

                void run();

                uint64 getNativeHandle() const;
            private:
                static Orchestra::Interfacing::Interfacer interfacer;

                Orchestra::Interfacing::Publisher publisher;

                Module* view;
                Orchestra::Interfacing::Requester requester;

                void Run(const Orchestra::Messaging::Message& message);

                void ViewRequest(const Orchestra::Messaging::Message& message, const Orchestra::Interfacing::Replier& replier);
                void NativeHandleRequest(const Orchestra::Messaging::Message& message, const Orchestra::Interfacing::Replier& replier);

                class PImpl;
                PImpl *impl;
                void systemCWindow(float32 width, float32 height, float32 x, float32 y);
                void systemDWindow();
                void systemRun();
                void systemClose();
                uint64 systemGetNativeHandle() const;
        };
    }
}
