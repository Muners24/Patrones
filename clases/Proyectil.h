#pragma once
#include "../CONST.h"
#include "Proyectil.h"
#include "GameObject.h"
#include <unordered_map>


class Proyectil : public GameObject
{
private:
    Vector2 centro;
    float radio;

public:
    Proyectil(Vector2 fuente,float direccion);
    Proyectil(Vector2 fuente,float direccion,int diametro);
    void draw(Texture2D textura);
    bool isOffScreen();
    void update();
    Vector2 getCentro(){return centro;};
    float getRadio(){return radio;};
private:
    Vector2 right(){return {centro.x+radio,centro.y};};
    Vector2 left(){return {centro.x-radio,centro.y};};
    Vector2 down(){return {centro.x,centro.y+radio};};
    Vector2 up(){return {centro.x,centro.y-radio};};
    void initVel();

};

void Proyectil::update()
{
    mov();
    centro.x = pos.x+radio;
    centro.y = pos.y+radio;
}

Proyectil::Proyectil(Vector2 fuente, float direccion,int diametro)
{
    this->direccion = direccion;
    radio = float(diametro/2);
    centro.x = fuente.x;
    centro.y = fuente.y;

    pos.height = diametro;
    pos.width = diametro;
    pos.x = centro.x-radio;
    pos.y = centro.y-radio;
    initVel();
}

Proyectil::Proyectil(Vector2 fuente, float direccion)
{
    this->direccion = direccion;
    radio = PROYECTIL_RAD;
    centro.x = fuente.x;
    centro.y = fuente.y;

    pos.height = radio*2;
    pos.width = radio*2;
    pos.x = centro.x-radio;
    pos.y = centro.y-radio;
    initVel();
}

void Proyectil::initVel(){
    float dir = direccion*DEG2RAD;
    vel.y = sin(dir) * PROYECTIL_V * -1;
    vel.x = cos(dir) * PROYECTIL_V;
}

void Proyectil::draw(Texture2D textura)
{
    DrawTexture(textura,pos.x,pos.y,WHITE);
}

bool Proyectil::isOffScreen(){
    if(left().x > BORDE_RIGHT)
        return true;

    if(right().x < BORDE_LEFT)
        return true;

    if(down().y < BORDE_UP)
        return true;

    if(up().y > RALTO)
        return true;

    return false;
}