#pragma once
#include "../CONST.h"

class GameObject
{
public:
    GameObject(){};
    float direccion;
    Rectangle pos;
    Vector2 vel;
    bool lookingRight();
    void mov();
    Rectangle getRec(){return pos;};

};

void GameObject::mov(){
    pos.x += vel.x;
    pos.y += vel.y;

}

bool GameObject::lookingRight()
{
    while (direccion >= 360)
    {
        direccion -= 360;
    }
    
    if ((direccion >= 0 && direccion <= 90) || (direccion >= 270 && direccion < 359))
        return true;

    return false;
}




