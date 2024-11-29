#pragma once
#include "../CONST.h"
#include "Proyectil.h"
#include "GameObject.h"
#include <unordered_map>
#include <list>
#include "Enemigo.h"

using std::list;
using std::unordered_map;

typedef struct _vida
{
    Rectangle pos;
    int num;
    int time;
} Tvida;

typedef struct _keys
{
    bool right;
    bool left;
    bool up;
    bool down;
    bool c;
    bool x;
} Keys;

class Player : GameObject
{
private:
    static Player* instance;
    bool dashing;
    int dash_timer;
    int atk_timer;
    bool buffed;
    int vida;
    Keys keys;
    int time;
    float x_frame;
    int daño_timer;

public:
    static Player* getInstance(Vector2 pos=Vector2{0.0,0.0}) {
        if (instance == nullptr) {
            instance = new Player(pos);
        }
        return instance;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }

    float getDir() { return direccion; };
    Vector2 getPosGun();

    void update();
    bool isBuffed() { return buffed; };
    void setBuff(bool b) { buffed = b; };
    bool checkColisionRec(Rectangle rec);
    void curar() { vida++; };
    void draw(Texture2D left, Texture2D right, unordered_map<int, Texture2D> ataques);
    bool atack();
    Rectangle getRec(){return pos;};
    int getVida(){return vida;};
    void recibirDaño(list<Enemigo*> enemigos);

private:
    Player(Vector2 pos)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.height = PLAYER_H;
        this->pos.width = PLAYER_W;
        this->dashing = false;
        this->dash_timer = 1000;
        this->atk_timer = 1000;
        this->buffed = false;
        this->vida = MAXVIDA;
        this->direccion = 0;
        this->time = 0;
        this->x_frame = 0;
        this->daño_timer = 0;
    }

    ~Player() {}
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    

    void calcularVelocidad();
    Vector2 vectorUnitario();
    void calcularDireccion();
    void ajustarPosicion();
    void shootAnimation(unordered_map<int, Texture2D> ataques);
    bool canDash();
    void input();
    void dash();
};

Player* Player::instance = nullptr;

void Player::update()
{
    dash_timer++;
    atk_timer++;
    dash_timer++;
    daño_timer++;

    input();
    ajustarPosicion();
    calcularDireccion();
    calcularVelocidad();
    dash();
    mov();
}

void Player::input()
{
    keys.x = IsKeyDown(KEY_X);

    if (dashing)
        return;

    keys.up = IsKeyDown(KEY_UP);
    keys.down = IsKeyDown(KEY_DOWN);
    keys.left = IsKeyDown(KEY_LEFT);
    keys.right = IsKeyDown(KEY_RIGHT);
    keys.c = IsKeyDown(KEY_C);
}

void Player::ajustarPosicion()
{

    if (pos.x < BORDE_LEFT)
    {
        pos.x = BORDE_LEFT;
    }

    if (pos.x + pos.width >= BORDE_RIGHT)
    {
        pos.x = BORDE_RIGHT - pos.width;
    }

    if (pos.y < BORDE_UP)
    {
        pos.y = BORDE_UP;
    }

    if (pos.y + pos.height > SUELO)
    {
        pos.y = SUELO - pos.height;
    }
}

void Player::calcularDireccion()
{
    if (keys.right)
    {
        if (keys.up)
        {
            direccion = 45;
            return;
        }

        if (keys.down)
        {
            direccion = 45 * 7;
            return;
        }

        direccion = 0;
        return;
    }

    if (keys.left)
    {
        if (keys.up)
        {
            direccion = 45 * 3;
            return;
        }

        if (keys.down)
        {
            direccion = 45 * 5;
            return;
        }
        direccion = 45 * 4;
        return;
    }

    if (keys.up)
    {
        direccion = 45 * 2;
    }

    if (keys.down)
    {
        direccion = 45 * 6;
    }
}

void Player::calcularVelocidad()
{
    if (dashing)
        return;

    vel.x = 0;
    vel.y = 0;

    if (!(keys.up || keys.down || keys.left || keys.right))
    {
        return;
    }

    Vector2 vec_unit = vectorUnitario();
    vel.y = vec_unit.y * PLAYER_V * -1;
    vel.x = vec_unit.x * PLAYER_V;
}

void Player::dash()
{
    if (keys.c && canDash())
    {
        // PlaySound(sdash);
        dashing = true;
        dash_timer = 0;
    }

    if (!dashing)
        return;

    if (dash_timer >= DASH_DURATION)
    {
        dashing = false;
        return;
    }

    Vector2 vec_unit = vectorUnitario();
    vel.y = vec_unit.y * DASH_V * -1;
    vel.x = vec_unit.x * DASH_V;
}

bool Player::canDash()
{
    return dash_timer >= DASH_CD;
}

void Player::draw(Texture2D left, Texture2D right, unordered_map<int, Texture2D> ataques)
{
    if (atk_timer < ATACK_ANIMATION_DUR)
    {
        shootAnimation(ataques);
        return;
    }
    
    float width = float(left.width/4);
    Rectangle frame = Rectangle{0.0f, 0.0f, width, (float)left.height};

    time++;
    if(time >= 7){
        time = 0;
        x_frame += width;
        if(x_frame > left.width)
        {
            x_frame = 0;
        }
    }

    frame.x = x_frame;

    if (lookingRight())
    {
        DrawTextureRec(right, frame, Vector2{this->pos.x - 35, this->pos.y - 50}, WHITE);
        return;
    }

    DrawTextureRec(left, frame, Vector2{this->pos.x - 75, this->pos.y - 50}, WHITE);
}

void Player::shootAnimation(unordered_map<int, Texture2D> ataques)
{
    DrawTexture(ataques[direccion], pos.x - 20, pos.y - 30, WHITE);
    return;
}

bool Player::atack()
{

    if (!keys.x)
        return false;

    // falta validar la velocidad de ataque con buff
    int cd = ATACK_CD;
    if (atk_timer >= cd)
    {
        atk_timer = 0;
        return true;
    }

    return false;
}

Vector2 Player::vectorUnitario()
{
    float dir = direccion * DEG2RAD;
    return Vector2{
        (float)cos(dir),
        (float)sin(dir),
    };
}

bool Player::checkColisionRec(Rectangle rec)
{
    return CheckCollisionRecs(pos, rec);
}

Vector2 Player::getPosGun()
{
    return Vector2{pos.x + pos.width / 2,pos.y + pos.height / 4,};
}

void Player::recibirDaño(list<Enemigo*> enemigos){

    if (daño_timer < INVULERABILIDAD)
        return;
    
    for(auto enemigo: enemigos){
        if (CheckCollisionRecs(pos,enemigo->getRec())){
            vida--;
            daño_timer = 0;
            return;
        }
    }
}