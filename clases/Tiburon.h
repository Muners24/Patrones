#pragma once
#include "../CONST.h"
#include "GameObject.h"
#include "Enemigo.h"

class Tiburon : public Enemigo
{
private:

public:
    Tiburon(){};
    Tiburon(Rectangle pos,float direccion,float speed,Texture2D textura): Enemigo(pos,direccion,speed,textura){
        
    }
    
private:

};







