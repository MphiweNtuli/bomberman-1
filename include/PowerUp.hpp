
#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Bomb.hpp"

class PowerUp : public Bomb
{
    public:
        PowerUp();
        ~PowerUp();

        int     TimerDisplay(int var);
        int     HealthDisplay(int var);
        void    OneUp();
        void    Fire();
        void    Timer();
        void    FireDown();
        void    CollideTimer();
        void    CollideOneUp();
        void    CollideFire();
        void    CollideFireDown();
        void    ActivatePowerUp(int character);
        void    RemoveObject();
        int     type;
        int     timer;
        int     health;
        bool    timeUsed;

    private:
};

#endif