#pragma once

namespace gamekid::io::video {
    class lcd;

    class lcd {
    private:
        bool _enabled = false;
        bool _window_enabled = false;
    public:
        bool enabled() const;
        void enabled(bool value);

        bool window_enabled() const;
        void window_enabled(bool value);
    };
}

