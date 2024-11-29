#include "../CONST.h"
#include "Player.h"

class Pieza
{
private:
    Texture2D textura;
    Rectangle pos;
    Rectangle plataforma;
    Rectangle destino;
    bool recolectada;
    bool colocada;

public:
    Pieza(Rectangle plataforma, Rectangle destino, Texture2D &textura)
    {
        this->plataforma = plataforma;
        this->destino = destino;
        this->textura = textura;
        this->destino.y;
        recolectada = false;
        colocada = false;
        initPosition();
    }

    void draw();
    void update();
    void colisionPlayer();
    int ready();

private:
    void mov();
    void initPosition();
};

void Pieza::update()
{
    colisionPlayer();
    draw();

    if (colocada)
    {
        return;
    }

    mov();

}

void Pieza::mov()
{
    if(colocada)
        return;

    if ((pos.y + pos.height) > plataforma.y)
        return;

    pos.y += 2;
}

void Pieza::initPosition()
{
    pos.width = textura.width;
    pos.height = textura.height;

    pos.y = BORDE_UP - pos.height * 2;
    pos.x = plataforma.x + plataforma.width / 2 - pos.width / 2;

}

void Pieza::draw()
{
    if (colocada)
    {
        DrawTexture(textura, destino.x, destino.y, WHITE);
        return;
    }

    if (recolectada)
        return;

    DrawTexture(textura, pos.x, pos.y, WHITE);
}

void Pieza::colisionPlayer()
{
    Player* player = Player::getInstance();
    Rectangle rec = player->getRec();

    if (recolectada)
    {
        if (CheckCollisionRecs(rec, destino))
        {
            colocada = true;
        }
        return;
    }

    if (CheckCollisionRecs(rec, pos))
    {
        recolectada = true;
    }
}

int Pieza::ready(){
    if(colocada)
    {
        return 1;
    }
    return 0;
}