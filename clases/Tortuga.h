#pragma once
#include "../CONST.h"
#include "GameObject.h"
#include "Enemigo.h"

class Tortuga : public Enemigo
{
private:
    
public:
    Tortuga(){};
    Tortuga(Rectangle pos,float direccion,float speed,Texture2D textura): Enemigo(pos,direccion,speed,textura){

    }
private:

};





