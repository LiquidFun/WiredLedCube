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
    }; // class IBlinkMode
} // namespace T27
