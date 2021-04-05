#pragma once

#include "CubePlexer.hpp"
#include "IBlinkMode.hpp"

namespace T27
{
    class FreezeMode : public IBlinkMode
    {
    private:
    public:
        FreezeMode(CubePlexer & /*cube*/)
        {
        }

    public:
        void update() override
        {
        }

        void update(int /*key*/) override
        {
        }

    }; // class FreezeMode

} // namespace T27
