
#include "cinematicas.h"
#include "clases/Player.h"
#include "clases/Enemigo.h"
#include "clases/Anguila.h"
#include "clases/Tortuga.h"
#include "clases/Tiburon.h"
#include "clases/FactoryWaterEnemy.h"
#include "CONST.h"
#include "clases/Pieza.h"
#include <vector>
#include <list>

using std::list;
using std::vector;

// typedef Rectangle Player;
/**************************************************************  Structs Generales *********************************************************/

typedef struct _corazon
{
    Rectangle pos;
    int status;
    int time;
} Tcora;

// hit para nivel 1 y 3
// nivel 1 no usa time
typedef struct _hit
{
    Rectangle pos;
    int time;      // 7   0    1
    int status;    //
    int direccion; //--------------------->  //6   p    2
    Vector2 vel;   //
} Thit;            // 5   4    3

typedef struct _vehiculo
{
    Rectangle pos;
    int status;
    int listo;
} Tpart;

typedef struct _ASbuff
{
    Rectangle pos;
    int statusDraw;
    int statusFun;
    int time;
    int duracion;
} TatkSpeed;

typedef struct _plataforma
{
    Rectangle pos;
    int status;
    int flag;
} Tplat;

/****************************************************************** Structs Nivel 1 *********************************************************/
typedef struct _shark
{
    Rectangle pos;
    int status = 0;
    int right = 0;
    int left = 0;
    Vector2 vel;
} Tshark;

typedef struct _tortuga
{
    Rectangle pos;
    int status = 0;
    int right = 0;
    int left = 0;
} Ttortu;

typedef struct _anghit
{
    Rectangle pos;
    int status;
    int time;
} Tanghit;

typedef struct _anguila
{
    Rectangle pos;
    int status = 0;
    int right = 0;
    int left = 0;
    Vector2 vel;
    Tanghit hit;
} Tangui;

/****************************************************************** Prototipo de funciones Generales *********************************************************/
float CalculaAngulo(Rectangle ang, Rectangle player);
void InicializaProyectil(int l, int r, int up, int down, Player player, Thit &hit);
void CalculaComponentesVelocidad(float velocidad, float grados, Vector2 &v);
float Radianes(float grados);
void PosicionObieto(float vx, float vy, Rectangle &pos);
int CheckMobColision(Rectangle mob, Thit hit);
int CheckPlayerColision(Rectangle player, Rectangle mob);

int mainMenu(Sound seleccion);
int juegoMenu(Sound seleccion);
int opMenu(int &vol, int &diflvl, Texture2D volumen, Texture2D dif, Sound seleccion, Sound barras);
void juego(int diflvl);
void nivel1(int diflvl);
/****************************************************************** Prototipo de funciones 1 *********************************************************/
void LimpiaEnemigosLvl1(Tshark shark[], Ttortu tort[], Tangui ang[]);
void AngElectro(Tangui &ang);
void muerteLvl1(Player &player, Tshark shark[], Ttortu tort[], Tangui ang[], Tpart pieza[], Rectangle plat[]);
void cinemaPuzleNivel1(int diflvl);

/****************************************************************** MENUS  **************************************************************************/
int main(void)
{
    SetTargetFPS(60);

    int op, subOp, opJug;
    int diflvl = 1, vol = 3;

    float scrollingBack = 0.0f;
    float scrollingBigPlanet = 0.0f;
    float scrollingFarPlanet = 0.0f;
    float scrollingRingPlanet = 0.0f;
    float scrollingSpaceStar = 0.0f;

    InitWindow(RANCHO, RALTO, "window");
    //****************************************************** TEXTURAS ***********************************************************************
    Texture2D volumen[7];
    volumen[0] = LoadTexture("texturas\\vol0.png");
    volumen[1] = LoadTexture("texturas\\vol1.png");
    volumen[2] = LoadTexture("texturas\\vol2.png");
    volumen[3] = LoadTexture("texturas\\vol3.png");
    volumen[4] = LoadTexture("texturas\\vol4.png");
    volumen[5] = LoadTexture("texturas\\vol5.png");
    volumen[6] = LoadTexture("texturas\\vol6.png");

    Texture2D dif[3];
    dif[0] = LoadTexture("texturas\\dif1.png");
    dif[1] = LoadTexture("texturas\\dif2.png");
    dif[2] = LoadTexture("texturas\\dif3.png");

    Texture2D back = LoadTexture("texturas/parallax-space-backgound.png");
    Texture2D bigplanet = LoadTexture("texturas/parallax-space-big-planet.png");
    Texture2D farplanet = LoadTexture("texturas/parallax-space-far-planets.png");
    Texture2D ringplanet = LoadTexture("texturas/parallax-space-ring-planet.png");
    Texture2D stars = LoadTexture("texturas/parallax-space-stars.png");

    //******************************************************* AUDIOS **********************************************************************
    InitAudioDevice();
    Music musica_menu = LoadMusicStream("sonidos/musica.mp3");
    Sound barras = LoadSound("sonidos/beep.mp3");
    Sound seleccion = LoadSound("sonidos/volumen.mp3");

    //************************************************************* LOOP PRINCIPAL ****************************************************************
    while (!WindowShouldClose())
    {
        // Menu principal
        PlayMusicStream(musica_menu);
        do
        {
        menu:
            scrollingBack -= 0.01f;
            scrollingBigPlanet -= 0.025f;
            scrollingFarPlanet -= 0.05f;
            scrollingRingPlanet -= 0.055f;
            scrollingSpaceStar -= 0.01;

            if (scrollingBack <= -back.height)
                scrollingBack = 0;
            if (scrollingBigPlanet <= -bigplanet.height)
                scrollingBigPlanet = 0;
            if (scrollingFarPlanet <= -farplanet.height)
                scrollingFarPlanet = 0;
            if (scrollingRingPlanet <= -ringplanet.height)
                scrollingRingPlanet = 0;
            if (scrollingSpaceStar <= -stars.height)
                scrollingSpaceStar = 0;

            BeginDrawing();
            UpdateMusicStream(musica_menu);

            DrawTextureEx(back, Vector2{0, scrollingBack}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(back, Vector2{0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(bigplanet, Vector2{900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(bigplanet, Vector2{900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(farplanet, Vector2{0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(farplanet, Vector2{0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(ringplanet, Vector2{0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(ringplanet, Vector2{0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(stars, Vector2{0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(stars, Vector2{0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);

            op = mainMenu(seleccion);
            EndDrawing();
        } while (op == -1);

        //******************************************** JUGAR ******************************************************************
        switch (op)
        {
        case JUGAR:
            do
            {
                BeginDrawing();
                UpdateMusicStream(musica_menu);
                scrollingBack -= 0.01f;
                scrollingBigPlanet -= 0.025f;
                scrollingFarPlanet -= 0.05f;
                scrollingRingPlanet -= 0.055f;
                scrollingSpaceStar -= 0.01;

                if (scrollingBack <= -back.height)
                    scrollingBack = 0;
                if (scrollingBigPlanet <= -bigplanet.height)
                    scrollingBigPlanet = 0;
                if (scrollingFarPlanet <= -farplanet.height)
                    scrollingFarPlanet = 0;
                if (scrollingRingPlanet <= -ringplanet.height)
                    scrollingRingPlanet = 0;
                if (scrollingSpaceStar <= -stars.height)
                    scrollingSpaceStar = 0;

                BeginDrawing();
                UpdateMusicStream(musica_menu);

                DrawTextureEx(back, Vector2{0, scrollingBack}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(back, Vector2{0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(bigplanet, Vector2{900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(bigplanet, Vector2{900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(farplanet, Vector2{0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(farplanet, Vector2{0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(ringplanet, Vector2{0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(ringplanet, Vector2{0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(stars, Vector2{0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(stars, Vector2{0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);

                opJug = juegoMenu(seleccion);
                EndDrawing();
            } while (opJug == -1);

            switch (opJug)
            {
            case NEWP:
                goto juegoL;
                break;
            case 1:
                UpdateMusicStream(musica_menu);
                goto menu;
                break;
            }
            break;

        //**************************** OPCIONES ******************************************************************
        case OPCIONES:
            UpdateMusicStream(musica_menu);
            do
            {
                BeginDrawing();
                UpdateMusicStream(musica_menu);
                scrollingBack -= 0.01f;
                scrollingBigPlanet -= 0.025f;
                scrollingFarPlanet -= 0.05f;
                scrollingRingPlanet -= 0.055f;
                scrollingSpaceStar -= 0.01;

                if (scrollingBack <= -back.height)
                    scrollingBack = 0;
                if (scrollingBigPlanet <= -bigplanet.height)
                    scrollingBigPlanet = 0;
                if (scrollingFarPlanet <= -farplanet.height)
                    scrollingFarPlanet = 0;
                if (scrollingRingPlanet <= -ringplanet.height)
                    scrollingRingPlanet = 0;
                if (scrollingSpaceStar <= -stars.height)
                    scrollingSpaceStar = 0;

                BeginDrawing();
                UpdateMusicStream(musica_menu);

                DrawTextureEx(back, Vector2{0, scrollingBack}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(back, Vector2{0, back.height * 2 + scrollingBack}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(bigplanet, Vector2{900, scrollingBigPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(bigplanet, Vector2{900, bigplanet.height * 2 + scrollingBigPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(farplanet, Vector2{0, scrollingFarPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(farplanet, Vector2{0, farplanet.height * 2 + scrollingFarPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(ringplanet, Vector2{0, scrollingRingPlanet}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(ringplanet, Vector2{0, ringplanet.height * 2 + scrollingRingPlanet}, 0.0f, 1.0f, WHITE);

                DrawTextureEx(stars, Vector2{0, scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(stars, Vector2{0, stars.height * 2 + scrollingSpaceStar}, 0.0f, 1.0f, WHITE);
                subOp = opMenu(vol, diflvl, volumen[vol], dif[diflvl], seleccion, barras);
                EndDrawing();

            } while (subOp != -1);
            goto menu;
            break;

        //**************************** SALIR ******************************************************************
        case SALIR:
            goto finJ;
            break;
        }

    juegoL:
        StopMusicStream(musica_menu);
        UnloadTexture(volumen[0]);
        UnloadTexture(volumen[1]);
        UnloadTexture(volumen[2]);
        UnloadTexture(volumen[3]);
        UnloadTexture(volumen[4]);
        UnloadTexture(volumen[5]);
        UnloadTexture(volumen[6]);
        UnloadTexture(dif[0]);
        UnloadTexture(dif[1]);
        UnloadTexture(dif[2]);
        UnloadMusicStream(musica_menu);
        UnloadSound(seleccion);
        CloseAudioDevice();
        juego(diflvl);
        CloseWindow();
        return 0;
    }

finJ:
    //*********************************************************** UNLOAD ******************************************************************
    StopMusicStream(musica_menu);
    UnloadTexture(volumen[0]);
    UnloadTexture(volumen[1]);
    UnloadTexture(volumen[2]);
    UnloadTexture(volumen[3]);
    UnloadTexture(volumen[4]);
    UnloadTexture(volumen[5]);
    UnloadTexture(volumen[6]);
    UnloadTexture(dif[0]);
    UnloadTexture(dif[1]);
    UnloadTexture(dif[2]);
    UnloadMusicStream(musica_menu);
    UnloadSound(seleccion);
    CloseAudioDevice();
    CloseWindow();
    //*****************************************************************************************************************************

    return 0;
}

int mainMenu(Sound seleccion)
{
    static int op = 0;
    int sizeTxt[3], j;
    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            sizeTxt[j] = 60;
        }
        else
        {
            sizeTxt[j] = 40;
        }
    }

    char mensajes[4][30] = {"JUGAR", "OPCIONES", "SALIR", "MECANICO ARITMETICO"};

    DrawText(mensajes[3], 200, 65, 70, WHITE);
    DrawText(mensajes[0], 510, 200, sizeTxt[0], WHITE);
    DrawText(mensajes[1], 510, 300, sizeTxt[1], WHITE);
    DrawText(mensajes[2], 510, 400, sizeTxt[2], WHITE);

    if (IsKeyPressed(KEY_UP))
    {
        if (op != JUGAR)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != SALIR)
            {
                op++;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(seleccion);
        return op;
    }

    return -1;
}

int opMenu(int &vol, int &diflvl, Texture2D volumen, Texture2D dif, Sound seleccion, Sound barras)
{
    static int op = 0;
    int sizeTxt[3], j;
    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            sizeTxt[j] = 60;
        }
        else
        {
            sizeTxt[j] = 40;
        }
    }

    DrawText("Opciones", 450, 65, 70, WHITE);
    DrawText("Dificultad", 510, 200, sizeTxt[0], WHITE);
    DrawText("Sonido", 510, 350, sizeTxt[1], WHITE);
    DrawText("Regresar", 510, 500, sizeTxt[2], WHITE);

    switch (op)
    {
    case DIFICULTAD:
        DrawTexture(dif, 520, -125, WHITE);

        if (IsKeyPressed(KEY_LEFT))
        {
            if (diflvl != 0)
            {
                diflvl--;
            }
        }
        else
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                if (diflvl != 2)
                {
                    diflvl++;
                }
            }
        }

        switch (diflvl)
        {
        case 0:
            DrawText("Fácil", 862, 100, 60, WHITE);
            break;
        case 1:
            DrawText("Normal", 853, 100, 60, WHITE);
            break;
        case 2:
            DrawText("Difícil", 856, 100, 60, WHITE);
            break;
        }

        break;

    case SONIDO:
        DrawTexture(volumen, 485, 25, WHITE);

        if (IsKeyPressed(KEY_LEFT))
        {
            if (vol != 0)
            {
                vol--;
            }
        }
        else
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                if (vol != 6)
                {
                    vol++;
                }
            }
        }

        break;

    case REGRESAR:
        if (IsKeyPressed(KEY_ENTER))
        {
            return -1;
        }
        break;
    }

    if (IsKeyPressed(KEY_UP))
    {
        if (op != DIFICULTAD)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != REGRESAR)
            {
                op++;
            }
        }
    }
    return op;
}

int juegoMenu(Sound seleccion)
{
    static int op = 0;
    int sizeTxt[3], j;
    for (j = 0; j < 3; j++)
    {
        if (j == op)
        {
            sizeTxt[j] = 60;
        }
        else
        {
            sizeTxt[j] = 40;
        }
    }

    char mensajes[3][30] = {"NUEVA PARTIDA", "REGRESAR", "MECANICO ARITMETICO"};

    DrawText(mensajes[2], 200, 65, 70, WHITE);
    DrawText(mensajes[0], 460, 200, sizeTxt[0], WHITE);
    DrawText(mensajes[1], 460, 350, sizeTxt[1], WHITE);

    if (IsKeyPressed(KEY_UP))
    {
        if (op != NEWP)
        {
            op--;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            if (op != SALIRJ)
            {
                op++;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(seleccion);
        return op;
    }

    return -1;
}

/****************************************************************** JUEGO  ************************************************************************/
void juego(int diflvl)
{
    nivel1(diflvl);
    cinemaPuzleNivel1(diflvl);
}

void nivel1(int diflvl)
{
    srand(time(NULL));
    int i, j, k;

    list<Proyectil> proyectiles;
    list<Enemigo *> enemigos;
    list<Pieza> piezas;
    Player *player = Player::getInstance(Vector2{RANCHO / 2, SUELO - PLAYER_H});

    bool fin = false;
    int random;

    // ********************************** TEXTURAS **************************************************
    Texture2D danio = LoadTexture("texturas/Cyborg_hurt.png");
    Rectangle framesDanio = {0.0f, 0.0f, (float)danio.width, (float)danio.height};

    Texture2D salto = LoadTexture("texturas/Cyborg_jump.png");
    Texture2D saltoder = LoadTexture("texturas/Cyborg_jumpr.png");

    Texture2D back_nv1 = LoadTexture("texturas/back_nv1.png");
    Texture2D backmiddle_nv1 = LoadTexture("texturas/middleback_nv1.png");
    Texture2D middle_nv1 = LoadTexture("texturas/middle_mv1.png");
    Texture2D front_nv1 = LoadTexture("texturas/front_nv1.png");

    Texture2D plataformaTxt = LoadTexture("texturas/plataforma_nv1_1.png");

    Texture2D bala = LoadTexture("texturas/bullet_nv1.png");

    Texture2D corazon = LoadTexture("texturas\\corazon.png");
    Texture2D Aspeed = LoadTexture("texturas\\AtkSpeed.png");

    unordered_map<int, Texture2D> ataques;
    ataques[0] = LoadTexture("texturas/Hit0.png");
    ataques[45] = LoadTexture("texturas/Hit1.png");
    ataques[90] = LoadTexture("texturas/Hit2.png");
    ataques[135] = LoadTexture("texturas/Hit3.png");
    ataques[180] = LoadTexture("texturas/Hit4.png");
    ataques[225] = LoadTexture("texturas/Hit5.png");
    ataques[270] = LoadTexture("texturas/Hit6.png");
    ataques[315] = LoadTexture("texturas/Hit7.png");

    Texture2D piezas_nv1[3];
    piezas_nv1[0] = LoadTexture("texturas/SUB1.png");
    piezas_nv1[1] = LoadTexture("texturas/SUB2.png");
    piezas_nv1[2] = LoadTexture("texturas/SUB3.png");

    // ************************************************ SONIDOS ********************************************************************

    InitAudioDevice();

    Sound dolor = LoadSound("sonidos/danio.wav");
    Sound brinco = LoadSound("sonidos/salto.mp3");
    Sound paso = LoadSound("sonidos/paso1.wav");
    Sound agarrar = LoadSound("sonidos/pieza.wav");
    Music musica_nv1 = LoadMusicStream("sonidos/nivel1.mp3");
    Sound sdash = LoadSound("sonidos/paso1.wav");
    Sound disparo_nv1 = LoadSound("sonidos/disparo_nv1.wav");
    Sound ludico = LoadSound("sonidos/nivel_completado.wav");
    // Sound anguilasound = LoadSound("sonidos/anguilasound.wav");

    // SetSoundVolume(disparo_nv1, -0.1f);
    // SetSoundVolume(sdash, +10.0f);
    // SetMusicVolume(musica_nv1, -1.2f);

    //** plataformas **************************************************************************************************************************
    vector<Rectangle> plataformas;
    for (i = 0; i < MAXPLAT; i++)
    {
        plataformas.push_back(Rectangle{0, 0, (float)plataformaTxt.width, (float)plataformaTxt.height});
    }

    plataformas[0].x = 100;
    plataformas[0].y = 200;
    plataformas[1].x = RANCHO / 2 - plataformas[1].width / 2;
    plataformas[1].y = 400;
    plataformas[2].x = RANCHO - 100 - plataformas[2].width;
    plataformas[2].y = 200;

    //** piezas **********************************************************************************************************************************
    int time = 0;
    Tpart pieza[3];
    int piezac = 0;
    pieza[0].pos.height = piezas_nv1[0].height;
    pieza[0].pos.width = piezas_nv1[0].width;
    pieza[1].pos.height = piezas_nv1[1].height;
    pieza[1].pos.width = piezas_nv1[1].width;
    pieza[2].pos.height = piezas_nv1[2].height;
    pieza[2].pos.width = piezas_nv1[2].width;
    int separacion_x = 0;
    for (j = 0; j < 3; j++)
    {
        piezas.push_back(Pieza(plataformas[j],Rectangle{(float)DESTINO_X+separacion_x,DESTINO_Y,(float)piezas_nv1[j].width,(float)piezas_nv1[j].height},piezas_nv1[j]));
        separacion_x += piezas_nv1[j].width;
    }


    // drop
    Tcora dropVida[MAXDROPVIDA];

    for (i = 0; i < MAXDROPVIDA; i++)
    {
        dropVida[i].pos.width = 30;
        dropVida[i].pos.height = 30;
        dropVida[i].status = 0;
        dropVida[i].time = 0;
    }

    TatkSpeed dropASpeed[MAXDROPASPEED];
    for (i = 0; i < MAXDROPASPEED; i++)
    {
        dropASpeed[i].pos.width = 80;
        dropASpeed[i].pos.height = 60;
        dropASpeed[i].statusDraw = 0;
        dropASpeed[i].statusFun = 0;
        dropASpeed[i].time = 0;
        dropASpeed[i].duracion = DURACIONBUFF;
    }

    // Inicializacion camara
    Camera2D camara = {0};
    camara.target.x = 0;
    camara.target.y = 0;
    camara.offset.x = 0;
    camara.offset.y = 0;
    camara.rotation = 0;
    camara.zoom = 1;

    FactoryWaterEnemy factory;
    while (!WindowShouldClose() && !fin)
    {
        try
        {
            enemigos.push_back(factory.generarEnemigo(string("tortuga")));
        }
        catch (const std::exception &e)
        {
        }
        try
        {
            enemigos.push_back(factory.generarEnemigo(string("tiburon")));
        }
        catch (const std::exception &e)
        {
        }

        try
        {
            enemigos.push_back(factory.generarEnemigo(string("anguila")));
        }
        catch (const std::exception &e)
        {
        }

        time++;
        player->update();
        player->recibirDaño(enemigos);

        if (player->atack())
        {
            proyectiles.push_front(Proyectil(player->getPosGun(), player->getDir(), bala.width));
        }

        

        BeginDrawing();

        BeginMode2D(camara);
        DrawTexture(back_nv1, 0, 0, WHITE);
        DrawTexture(backmiddle_nv1, 0, 0, WHITE);
        DrawTexture(middle_nv1, 0, 0, WHITE);
        DrawTexture(front_nv1, 0, 0, WHITE);

        int completado_count = 0;
        for (auto& pieza: piezas){
            pieza.update();
            completado_count += pieza.ready();
        }

        if(completado_count == 3)
        {
            fin = true;
        }
        // PlayMusicStream(musica_nv1);
        // UpdateMusicStream(musica_nv1);

        // dibujado
        for (auto plataforma : plataformas)
        {
            DrawTexture(plataformaTxt, plataforma.x, plataforma.y, WHITE);
        }

        auto enemigo = enemigos.begin();
        while (enemigo != enemigos.end())
        {
            if ((*enemigo)->isOffScreen() || (*enemigo)->colisionProyectil(proyectiles))
            {
                enemigo = enemigos.erase(enemigo);
                continue;
            }

            (*enemigo)->update();
            (*enemigo)->draw();
            enemigo++;
        }

        auto proyectil = proyectiles.begin();
        while (proyectil != proyectiles.end())
        {
            if (proyectil->isOffScreen())
            {
                proyectil = proyectiles.erase(proyectil);
                continue;
            }

            proyectil->update();
            proyectil->draw(bala);
            proyectil++;
        }

        player->draw(salto, saltoder, ataques);

        // vida
        int x = POS_VIDA;
        for (i = 1; i <= player->getVida(); i++)
        {
            DrawTexture(corazon, x, POS_VIDA, WHITE);
            x += 25 + corazon.width;
        }
        EndMode2D();
        EndDrawing();

        
    }
}
