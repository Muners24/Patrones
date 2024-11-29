#include "../CONST.h"
#include "Enemigo.h"
#include "Tiburon.h"
#include "Anguila.h"
#include "Tortuga.h"
#include "Player.h"

#include <string>

using std::string;

class FactoryWaterEnemy{

private:
    Texture2D tortuga;
    Texture2D tortugaizq;
    Texture2D anguila;
    Texture2D anguilaizq;
    Texture2D tiburon;
    Texture2D tiburonizq;


public:
    FactoryWaterEnemy(){
        tortuga = LoadTexture("texturas/tortuga_izq.png");
        tortugaizq = LoadTexture("texturas/tortuga_der.png");
        anguila = LoadTexture("texturas/anguila_izq.png");
        anguilaizq = LoadTexture("texturas/anguila.png");
        tiburon = LoadTexture("texturas/pulpoizq.png");
        tiburonizq = LoadTexture("texturas/pulpo.png");
    };

    Enemigo* generarEnemigo(string criterio);
    float calcularAnguloPlayer(Rectangle enemigo,Rectangle player);
};

Enemigo* FactoryWaterEnemy::generarEnemigo(string criterio){

    if (((rand() % 150) + 1) != 1)
        throw std::runtime_error("Enemigo no generado");

    int side = rand() % 2;
    int random = rand() % 30;
    if(criterio == "tortuga"){

        if (side)
        {
            return new Tortuga(Rectangle{RANCHO,float((rand() % 550) + 50),120,20},180,TORTUGASPEED,tortuga);
        }
        else
        {
            return new Tortuga(Rectangle{-150,float((rand() % 550) + 50),120,20},0,TORTUGASPEED,tortugaizq);
        }
    }

    if(criterio == "anguila"){
        Player* player = Player::getInstance();
        if (side)
        {
            Rectangle rec = Rectangle{RANCHO,float((rand() % 550) + 60),100,30};
            return new Anguila(rec,calcularAnguloPlayer(rec,player->getRec()),ANGUILASPEED,anguila);
        }
        else
        {
            Rectangle rec = Rectangle{-150,float((rand() % 550) + 60),100,30};
            return new Anguila(rec,calcularAnguloPlayer(rec,player->getRec()),ANGUILASPEED,anguilaizq);
        }
    }
    if(criterio == "tiburon"){
        random = rand() % 30;
        if (side)
        {   
            return new Tiburon(Rectangle{RANCHO,float((rand()%550)+50),120,100},float(random+165),SHARKSPEED,tiburon);
        }
        else
        {
            return new Tiburon(Rectangle{-120,float((rand() % 550) + 50),120,100},float(random+345),SHARKSPEED,tiburonizq);
        }
    }

    
    throw std::runtime_error("Enemigo no generado");
}


float FactoryWaterEnemy::calcularAnguloPlayer(Rectangle enemigo,Rectangle player)
{
    float difx = fabs(player.x + player.width / 2 - (enemigo.x + enemigo.width / 2));
    float dify = fabs(player.y + player.height / 2 - (enemigo.y + enemigo.height / 2));
    float a = atan2(difx, dify);
    a = a * 180 / PI;
    if (player.x > enemigo.x)
    {
        if (player.y > enemigo.y)
        {
            return (270 + a);
        }
        else
        {
            return (90 - a);
        }
    }
    else
    {
        if (player.y > enemigo.y)
        {
            return (270 - a);
        }
        else
        {
            return (90 + a);
        }
    }
    return 0;
}