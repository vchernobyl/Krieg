#pragma once

namespace CollisionMask {
    constexpr unsigned short Player = 0x0001;
    constexpr unsigned short PlayerProjectile = 0x0002;
    constexpr unsigned short Enemy = 0x0004;
    constexpr unsigned short EnemyProjectile = 0x0008;
    constexpr unsigned short Powerup = 0x0010;
    constexpr unsigned short Default = 0xFFFF;
};
