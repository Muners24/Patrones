#pragma once
#include "../CONST.h"
#include "GameObject.h"
#include <list>

using std::list;

class Enemigo : public GameObject
{
private:
    Texture2D textura;
    float speed;
    int time;
    float x_frame;
public:
    Enemigo(){};
    Enemigo(Rectangle pos,float direccion,float speed,Texture2D textura){
        this->pos = pos;
        this->direccion = direccion;
        this->speed = speed;
        this->time = 0;
        this->x_frame = 0;
        initVel();
        this->textura = textura;
    }
    
    void initVel();
    void update();
    void draw();
    bool isOffScreen();
    bool colisionProyectil(list<Proyectil> proyectiles);
private:

};

void Enemigo::initVel()
{
    float dir = direccion*DEG2RAD;
    vel.y = sin(dir) * speed * -1;
    vel.x = cos(dir) * speed;
}

void Enemigo::update(){
    mov();
}

void Enemigo::draw()
{
    float width = float(textura.width/6);
    Rectangle frame = Rectangle{0.0f, 0.0f, width, (float)textura.height};

    time++;
    if(time >= 7){
        time = 0;
        x_frame += width;
        if(x_frame >= textura.width)
        {
            x_frame = 0;
        }
    }

    frame.x = x_frame;

    if (lookingRight())
    {
        DrawTextureRec(textura, frame, Vector2{pos.x - pos.width/4, pos.y - pos.height/2}, WHITE);
        return;
    }

    DrawTextureRec(textura, frame, Vector2{pos.x - pos.width/4, pos.y - pos.height/2}, WHITE);
}

bool Enemigo::isOffScreen(){
    if(pos.x + pos.width < BORDE_LEFT - 100)
        return true;

    if(pos.x > BORDE_RIGHT + 100)
        return true;

    return false;
}



bool Enemigo::colisionProyectil(list<Proyectil> proyectiles)
{
    for(auto &proyectil : proyectiles){
        Rectangle rec = pos;
        Vector2 centro = proyectil.getCentro();
        if (CheckCollisionPointLine(centro, {rec.x, rec.y}, {rec.x + rec.width, rec.y}, 8))
        {
            return true;
        }
        if (CheckCollisionPointLine(centro, {rec.x, rec.y + rec.height}, {rec.x + rec.width, rec.y + rec.height}, 8))
        {
            return true;
        }
        if (CheckCollisionPointLine(centro, {rec.x, rec.y}, {rec.x, rec.y + rec.height}, 8))
        {
            return true;
        }
        if (CheckCollisionPointLine(centro, {rec.x + rec.width, rec.y}, {rec.x + rec.width, rec.y + rec.height}, 8))
        {
            return true;
        }
    }

    return false;
}