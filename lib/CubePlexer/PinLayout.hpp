#pragma once

#include <stdint.h>

namespace T27
{
    enum class PinLayout : uint8_t
    {
        v0 = 0u, // hard-wired
        v1 = 1u, // cable plugs; subject to changes

    }; // enum class PinLayout

} // namespace T27
