#pragma once

namespace T27
{
    class IBlinkMode
    {
    public:
        virtual ~IBlinkMode()
        {
        }

    public:
        virtual void update() = 0;
        virtual void update(int key) = 0;
    }; // class IBlinkMode
} // namespace T27
