#include "PowerUp.hpp"
#include "timer.hpp"

PowerUp::PowerUp(){
    srand(time(0));
    type = (rand() % 4 + 1);
    timer = 1;
    health = 1;
    timeUsed = false;

    switch (type){
        case 1 : Fire();
            break;
        case 2 : FireDown();
            break;
        case 3 : OneUp();
            break;
        case 4 : Timer();
    }
}

PowerUp::~PowerUp(){
    RemoveObject();
}

int PowerUp::TimerDisplay(int var){
    if (var == 0)
    {
        timeUsed = true;
        health = 0;
    }
        
    return health;
}

int PowerUp::HealthDisplay(int var){
    if (var == 0)
        timer = 0;
    return timer;
}

void PowerUp::ActivatePowerUp(int character){
    if (character == 1)
    {
        switch (type)
        {
            case 1 : CollideFire();
                break;
            case 2 : CollideFireDown();
                break;
            case 3 : CollideOneUp();
                break;
            case 4 : CollideTimer();
                break;
        }
    }
    else
        PowerUp::~PowerUp();
}

void PowerUp::Timer(){
    
}

void PowerUp::CollideTimer(){
    
}


void PowerUp::Fire(){
}

void PowerUp::CollideFire(){
    int     radius;

    radius = Bomb::get_radius() + 1;
    Bomb::set_radius(radius);
    PowerUp::~PowerUp();       
}

void PowerUp::FireDown(){
}

void PowerUp::CollideFireDown(){
    int     radius;

    radius = Bomb::get_radius() - 1;
    Bomb::set_radius(radius);
    PowerUp::~PowerUp();  
}

void PowerUp::OneUp(){

}

void PowerUp::CollideOneUp(){
    PowerUp::~PowerUp();  
}

void PowerUp::RemoveObject(){
    
}