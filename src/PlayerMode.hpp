#pragma once

#include "Array.hpp"
#include "CubePlexer.hpp"
#include "IBlinkMode.hpp"
#include "MultiArray.hpp"

namespace T27
{
    class PlayerMode : public IBlinkMode
    {
    private:
        CubePlexer &cube_;

        MultiArray<bool, CubePlexer::N, CubePlexer::N, CubePlexer::N> light_is_on{};

        Array<int, 3> player_xyz{1, 1, 1};

    public:
        PlayerMode(CubePlexer &cube)
            : cube_{cube}
        {
        }

    private:
        constexpr static int apply_periodic_boundary(int pos)
        {
            return (pos + CubePlexer::N) % CubePlexer::N;
        }

    public:
        void update() override
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                for (int y = 0; y < CubePlexer::N; ++y)
                {
                    for (int z = 0; z < CubePlexer::N; ++z)
                    {
                        bool should_be_on = light_is_on(x, y, z);
                        cube_.exchange(should_be_on, x, y, z);
                    }
                }
            }
            cube_.on(player_xyz[0], player_xyz[1], player_xyz[2]);
        }

        void update(int key) override
        {
            switch (key)
            {
            case 'e':
                player_xyz.ref(1) = apply_periodic_boundary(player_xyz[1] - 1);
                break;
            case 's':
                player_xyz.ref(0) = apply_periodic_boundary(player_xyz[0] - 1);
                break;
            case 'd':
                player_xyz.ref(1) = apply_periodic_boundary(player_xyz[1] + 1);
                break;
            case 'f':
                player_xyz.ref(0) = apply_periodic_boundary(player_xyz[0] + 1);
                break;
            case ' ':
                player_xyz.ref(2) = apply_periodic_boundary(player_xyz[2] + 1);
                break;
            case 't':
                bool &switcher = light_is_on.ref(player_xyz[0], player_xyz[1], player_xyz[2]);
                switcher = !switcher;
                break;
            }

            this->update();
        }

    }; // class PlayerMode

} // namespace T27
