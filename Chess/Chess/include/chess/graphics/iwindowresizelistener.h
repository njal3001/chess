#pragma once

namespace Game
{
    class IWindowResizeListener
    {
    public:
        virtual void on_resize(const Vec2i& new_size) = 0;
    };
}