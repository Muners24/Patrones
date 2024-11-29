#pragma once
#include "../CONST.h"
#include "GameObject.h"
#include "Enemigo.h"

class Anguila : public Enemigo
{
private:

public:
    Anguila(){};
    Anguila(Rectangle pos,float direccion,float speed,Texture2D textura): Enemigo(pos,direccion,speed,textura){

    }

  
private:

};






