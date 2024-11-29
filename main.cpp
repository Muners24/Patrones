
#include "cinematicas.h"
#include "CONST.h"


// typedef Rectangle Tplayer;
/**************************************************************  Structs Generales *********************************************************/

typedef struct _velocidad
{
    float vx;
    float vy;
} Tvel;

typedef struct _corazon
{
    Rectangle pos;
    int status;
    int time;
}Tcora;

//hit para nivel 1 y 3
//nivel 1 no usa time
typedef struct _hit
{
    Rectangle pos;
    int time;      // 7   0    1
    int status;    //
    int direccion; //--------------------->  //6   p    2
    Tvel v;        //
} Thit;            // 5   4    3

typedef struct _vida
{
    Rectangle pos;
    int num;
    int time;
} Tvida;

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

//algunos nivles no usan todos los campos
typedef struct _jugador
{
    Rectangle pos;
    int dash;
    int buff;
    int jet;
    int jetc;
    int x0;
    int AtkC;
    int y0;
    float v0;
    int timeDash;
    int jump;
    int jumpjump;
    int fall;
    Tvida vida;
} Tplayer;

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
    Tvel v;
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
    Tvel v;
    Tanghit hit;
} Tangui;

/****************************************************************** Prototipo de funciones Generales *********************************************************/
float CalculaAngulo(Rectangle ang, Rectangle player);
void Direccioniugador(int &l, int &r, int &up, int &down, Tplayer player);
void InicializaProyectil(int l, int r, int up, int down, Tplayer player, Thit &hit);
void CalculaComponentesVelocidad(float velocidad, float grados, Tvel &v);
float Radianes(float grados);
void PosicionObieto(float vx, float vy, Rectangle &pos);
int CheckMobColision(Rectangle mob, Thit hit);
int CheckPlayerColision(Rectangle player, Rectangle mob);


/****************************************************************** Prototipo de funciones 1 *********************************************************/
void LimpiaEnemigosLvl1(Tshark shark[], Ttortu tort[], Tangui ang[]);
void AngElectro(Tangui &ang);
void muerteLvl1(Tplayer &player, Tshark shark[], Ttortu tort[], Tangui ang[], Tpart pieza[], Rectangle plat[]);
void cinemaPuzleNivel1(int diflvl);
void Direccioniugador1(int &L, int &R, int &Up, int &Down, Tplayer player);

/****************************************************************** Prototipo de interfaz  *********************************************************/
int mainMenu(Sound seleccion);
int opMenu(int &vol, int &diflvl, Texture2D volumen, Texture2D dif, Sound seleccion, Sound barras);
int juegoMenu(Sound seleccion);
void juego(int diflvl);
void nivel1(int diflvl);

/****************************************************************** MENUS  **************************************************************************/
int main(void)
{
    SetTargetFPS(60);

    int op, subOp, opJug;
    int diflvl = 1, vol = 3;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    float scrollingBack = 0.0f;
    float scrollingBigPlanet = 0.0f;
    float scrollingFarPlanet = 0.0f;
    float scrollingRingPlanet = 0.0f;
    float scrollingSpaceStar = 0.0f;

    InitWindow(screenWidth, screenHeight, "window");
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
    static int op=0;
    int sizeTxt[3],j;
    for(j=0;j<3;j++)
    {
        if(j==op)
        {
            sizeTxt[j]=60;
        }
        else
        {
            sizeTxt[j]=40;
        }
    }

    char mensajes[4][30] = {"JUGAR", "OPCIONES", "SALIR", "MECANICO ARITMETICO"};

    DrawText(mensajes[3],200,65,70,WHITE);
    DrawText(mensajes[0],510,200,sizeTxt[0],WHITE);
    DrawText(mensajes[1],510,300,sizeTxt[1],WHITE);
    DrawText(mensajes[2],510,400,sizeTxt[2],WHITE);


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
    static int op=0;
    int sizeTxt[3],j;
    for(j=0;j<3;j++)
    {
        if(j==op)
        {
            sizeTxt[j]=60;
        }
        else
        {
            sizeTxt[j]=40;
        }
    }

    DrawText("Opciones",450,65,70,WHITE);
    DrawText("Dificultad",510,200,sizeTxt[0],WHITE);
    DrawText("Sonido",510,350,sizeTxt[1],WHITE);
    DrawText("Regresar",510,500,sizeTxt[2],WHITE);

    switch(op)
    {
        case DIFICULTAD:
            DrawTexture(dif,520,-125,WHITE);

            if(IsKeyPressed(KEY_LEFT))
            {
                if(diflvl!=0)
                {
                    diflvl--;
                }
            }
            else
            {
                if(IsKeyPressed(KEY_RIGHT))
                {
                    if(diflvl!=2)
                    {
                        diflvl++;
                    }
                }
            }

            switch(diflvl)
            {
                case 0:
                    DrawText("Fácil",862,100,60,WHITE);
                    break;
                case 1:
                    DrawText("Normal",853,100,60,WHITE);
                    break;
                case 2:
                    DrawText("Difícil",856,100,60,WHITE);
                    break;
            }

            break;
      
        case SONIDO:
            DrawTexture(volumen,485,25,WHITE);
                    
            if(IsKeyPressed(KEY_LEFT))
            {
                if(vol!=0)
                {
                    vol--;
                }
            }
            else
            {
                if(IsKeyPressed(KEY_RIGHT))
                {
                    if(vol!=6)
                    {
                        vol++;
                    }
                }
            }
            
            break;

        case REGRESAR:
            if(IsKeyPressed(KEY_ENTER))
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
     static int op=0;
    int sizeTxt[3],j;
    for(j=0;j<3;j++)
    {
        if(j==op)
        {
            sizeTxt[j]=60;
        }
        else
        {
            sizeTxt[j]=40;
        }
    }

    char mensajes[3][30] = {"NUEVA PARTIDA", "REGRESAR", "MECANICO ARITMETICO"};

    DrawText(mensajes[2],200,65,70,WHITE);
    DrawText(mensajes[0],460,200,sizeTxt[0],WHITE);
    DrawText(mensajes[1],460,350,sizeTxt[1],WHITE);

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
    float VDDIAGONAL = 7.5 * sin(45) / sin(90);
    float G = 0.1;
    float GD = 0.15;
    srand(time(NULL));
    int i, j, k;
    Tplayer player;
    player.pos.height = ALTOP-10;
    player.pos.width = ANCHOP/1.5;
    player.pos.x = RANCHO / 2;
    player.pos.y = SUELO - player.pos.height;
    player.dash = 0;
    player.timeDash = 0;
    player.x0 = player.pos.x;
    player.AtkC = 0;

    // vida
    player.vida.num = MAXVIDA;
    player.vida.pos.width = 25;
    player.vida.pos.height = 25;
    player.vida.pos.x = 25;
    player.vida.pos.y = 25;

    // AtkSpeed
    player.buff = 0;

    int lookR = 1;
    int lookL = 0;
    int lookUp = 0;
    int lookDown = 0;
    int fin = 0;
    int random;
    int disparo=0;
    int framesAutom = 0;
    int framesPersonaje = 0;

    int framesSpeed = 8;

    int currentFrame = 0;
    int currentPersonaje = 0;

    int framesAtaque = 0;
    int currentAtaque = 0;

    int framesSalto=0;
    int currentSalto=0;
    // ********************************** TEXTURAS **************************************************
    Texture2D tortuga = LoadTexture("texturas/tortuga_der1.png");
    Rectangle framesTortuga = {0.0f, 0.0f, (float)tortuga.width / 6, (float)tortuga.height};

    Texture2D tortugaizq = LoadTexture("texturas/tortuga_izq.png");
    Rectangle framesTortugaizq = {0.0f, 0.0f, (float)tortugaizq.width / 6, (float)tortugaizq.height};

    Texture2D anguila = LoadTexture("texturas/anguila.png");
    Rectangle framesAnguila = {0.0f, 0.0f, (float)anguila.width / 6, (float)anguila.height};

    Texture2D anguilaizq = LoadTexture("texturas/anguila_izq.png");
    Rectangle framesAnguilaizq = {0.0f, 0.0f, (float)anguilaizq.width / 6, (float)anguilaizq.height};

    Texture2D ataque_anizq = LoadTexture("texturas/ataqueizq.png");
    Rectangle framesAtaque_anizq = {0.0f, 0.0f, (float)ataque_anizq.width / 6, (float)ataque_anizq.height};

    Texture2D ataque_ani = LoadTexture("texturas/ataqueizq.png");
    Rectangle framesAtaque_ani = {0.0f, 0.0f, (float)ataque_ani.width / 6, (float)ataque_ani.height};

    Texture2D pulpo = LoadTexture("texturas/pulpo.png");
    Rectangle framesPulpo = {0.0f, 0.0f, (float)pulpo.width / 6, (float)pulpo.height};

    Texture2D pulpoizq = LoadTexture("texturas/pulpoizq.png");
    Rectangle framesPulpoizq = {0.0f, 0.0f, (float)pulpoizq.width / 6, (float)pulpoizq.height};

    Texture2D caminar = LoadTexture("texturas/Cyborg_run.png");
    Rectangle framesCaminar = {0.0f, 0.0f, (float)caminar.width / 6, (float)caminar.height};
    Texture2D caminarizq = LoadTexture("texturas/Cyborg_run_left.png");
    Rectangle framesCaminarizq = {0.0f, 0.0f, (float)caminarizq.width / 6, (float)caminarizq.height};
    Texture2D reposo = LoadTexture("texturas/Cyborg_idle.png");
    Rectangle framesReposo = {0.0f, 0.0f, (float)reposo.width / 4, (float)reposo.height};
    Texture2D reposoizq = LoadTexture("texturas/Cyborg_idle_left.png");
    Rectangle framesReposoizq = {0.0f, 0.0f, (float)reposoizq.width / 4, (float)reposoizq.height};
    Texture2D danio = LoadTexture("texturas/Cyborg_hurt.png");
    Rectangle framesDanio = {0.0f, 0.0f, (float)danio.width, (float)danio.height};
    Texture2D salto = LoadTexture("texturas/Cyborg_jump.png");
    Rectangle frameSalto = {0.0f, 0.0f, (float)salto.width / 4, (float)salto.height};
    Texture2D saltoder = LoadTexture("texturas/Cyborg_jumpr.png");
    Rectangle frameSaltoder = {0.0f, 0.0f, (float)saltoder.width / 4, (float)saltoder.height};

    Texture2D back_nv1 = LoadTexture("texturas/back_nv1.png");
    Texture2D backmiddle_nv1 = LoadTexture("texturas/middleback_nv1.png");
    Texture2D middle_nv1 = LoadTexture("texturas/middle_mv1.png");
    Texture2D front_nv1 = LoadTexture("texturas/front_nv1.png");

    Texture2D plataforma_nv1 = LoadTexture("texturas/plataforma_nv1_1.png");

    Texture2D bullet_nv1 = LoadTexture("texturas/bullet_nv1.png");

    Texture2D corazon = LoadTexture("texturas\\corazon.png");
    Texture2D Aspeed=LoadTexture("texturas\\AtkSpeed.png");

    Texture2D ataquesizquierdos[5];
    Texture2D ataquesderechos[5];

    ataquesizquierdos[0] = LoadTexture("texturas/HitL0.png");
    ataquesizquierdos[1] = LoadTexture("texturas/HitL1.png");
    ataquesizquierdos[2] = LoadTexture("texturas/HitL2.png");
    ataquesizquierdos[3] = LoadTexture("texturas/HitL3.png");
    ataquesizquierdos[4] = LoadTexture("texturas/HitL4_1.png");

    ataquesderechos[0] = LoadTexture("texturas/HitR0.png");
    ataquesderechos[1] = LoadTexture("texturas/HitR1.png");
    ataquesderechos[2] = LoadTexture("texturas/HitR2.png");
    ataquesderechos[3] = LoadTexture("texturas/HitR3.png");
    ataquesderechos[4] = LoadTexture("texturas/HitR4_1.png");

    Texture2D piezas_nv1[3];
    piezas_nv1[0] = LoadTexture("texturas/pieza1_nv1.png");
    piezas_nv1[1] = LoadTexture("texturas/pieza2_nv1.png");
    piezas_nv1[2] = LoadTexture("texturas/pieza3_nv1.png");

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
    Sound anguilasound = LoadSound("sonidos/anguilasound.wav");

    SetSoundVolume(disparo_nv1, -0.1f);
    SetSoundVolume(sdash, +10.0f);
    SetMusicVolume(musica_nv1, -1.2f);

    //** proyectil ************************************************************************************************************************
    Thit hit[MAXHIT];
    for (i = 0; i < MAXHIT; i++)
    {
        hit[i].status = 0;
        hit[i].pos.width = bullet_nv1.width;
        hit[i].pos.height = bullet_nv1.height;
        hit[i].pos.x = 1280;
        hit[i].pos.y = 1500;
    }

    //** plataformas **************************************************************************************************************************
    Rectangle plat[MAXPLAT];
    for (i = 0; i < MAXPLAT; i++)
    {
        plat[i].height = plataforma_nv1.height;
        plat[i].width = plataforma_nv1.width;
    }
    plat[0].x = 100;
    plat[0].y = 200;
    plat[1].x = RANCHO / 2 - plat[1].width / 2;
    plat[1].y = 400;
    plat[2].x = RANCHO - 100 - plat[2].width;
    plat[2].y = 200;

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
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 0;
        pieza[j].status = 1;
        pieza[j].pos.x = plat[j].x + plat[j].width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -300;
        pieza[j].listo = 0;
    }

    //** enemigos **********************************************************************************************************************************
    Tshark shark[MAXSHARK];
    for (i = 0; i < MAXSHARK; i++)
    {
        shark[i].status = 0;
        shark[i].right = 0;
        shark[i].left = 0;
        shark[i].pos.x = 2000;
        shark[i].pos.y = 800;
        shark[i].pos.height = 100;
        shark[i].pos.width = 120;
    }

    Ttortu tort[MAXTORTUGA];
    for (i = 0; i < MAXTORTUGA; i++)
    {
        tort[i].status = 0;
        tort[i].pos.x = 2000;
        tort[i].pos.y = 800;
        tort[i].pos.height = tortuga.height - 100;
        tort[i].pos.width = (tortuga.width / 6) - 40;
    }
    tort[0].left = 1;
    tort[0].right = 0;
    tort[1].right = 1;
    tort[1].left = 0;

    Tangui ang[MAXANGUILA];
    for (i = 0; i < MAXANGUILA; i++)
    {
        ang[i].status = 0;
        ang[i].right = 0;
        ang[i].left = 0;
        ang[i].pos.x = 2000;
        ang[i].pos.y = 800;
        ang[i].pos.height = anguila.height - 65;
        ang[i].pos.width = (anguila.width / 6) - 20;
        ang[i].hit.pos.height = ang[0].pos.height * 3;
        ang[i].hit.pos.width = ang[0].pos.width * 1.5;
        ang[i].hit.pos.y = 800;
        ang[i].hit.pos.x = 2000;
        ang[i].hit.status = 0;
        ang[i].hit.time = 0;
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

    while (!WindowShouldClose())
    {
        // printf("x = %f y = %f\n",player.pos.x,player.pos.y);
        player.timeDash++;
        player.AtkC++;
        time++;
        player.vida.time++;
        if(player.AtkC>20)
        {
            disparo=0;
        }
        BeginDrawing();

        BeginMode2D(camara);
        DrawTexture(back_nv1, 0, 0, WHITE);
        DrawTexture(backmiddle_nv1, 0, 0, WHITE);
        DrawTexture(middle_nv1, 0, 0, WHITE);
        DrawTexture(front_nv1, 0, 0, WHITE);

        PlayMusicStream(musica_nv1);
        UpdateMusicStream(musica_nv1);

        //** terminar el nivel ***********************************************************************************
        if (pieza[0].status)
        {
            if (pieza[0].pos.y == SUELO - pieza[0].pos.height)
            {
                if (pieza[1].status)
                {
                    if (pieza[1].pos.y == SUELO - pieza[1].pos.height - 5)
                    {
                        if (pieza[2].status)
                        {
                            if (pieza[2].pos.y == SUELO - pieza[2].pos.height - 8)
                            {
                                if (!fin)
                                {
                                    PlaySound(ludico);
                                    time = 0;
                                }
                                fin = 1;
                                LimpiaEnemigosLvl1(shark, tort, ang);
                                if (time > 300)
                                {
                                    UnloadTexture(tortuga);
                                    UnloadTexture(tortugaizq);
                                    UnloadTexture(anguila);
                                    UnloadTexture(anguilaizq);
                                    UnloadTexture(ataque_ani);
                                    UnloadTexture(ataque_anizq);
                                    UnloadTexture(pulpo);
                                    UnloadTexture(pulpoizq);
                                    UnloadTexture(caminar);
                                    UnloadTexture(caminarizq);
                                    UnloadTexture(reposo);
                                    UnloadTexture(reposoizq);
                                    UnloadTexture(danio);
                                    UnloadTexture(salto);
                                    UnloadTexture(saltoder);
                                    UnloadTexture(back_nv1);
                                    UnloadTexture(backmiddle_nv1);
                                    UnloadTexture(middle_nv1);
                                    UnloadTexture(front_nv1);
                                    UnloadTexture(plataforma_nv1);
                                    UnloadTexture(bullet_nv1);
                                    UnloadTexture(corazon);
                                    UnloadTexture(Aspeed);

                                    UnloadTexture(ataquesizquierdos[0]);
                                    UnloadTexture(ataquesizquierdos[1]);
                                    UnloadTexture(ataquesizquierdos[2]);
                                    UnloadTexture(ataquesizquierdos[3]);
                                    UnloadTexture(ataquesizquierdos[4]);
                                    
                                    UnloadTexture(ataquesderechos[0]);
                                    UnloadTexture(ataquesderechos[1]);
                                    UnloadTexture(ataquesderechos[2]);
                                    UnloadTexture(ataquesderechos[3]);
                                    UnloadTexture(ataquesderechos[4]);

                    

                                    UnloadTexture(piezas_nv1[0]);
                                    UnloadTexture(piezas_nv1[1]);
                                    UnloadTexture(piezas_nv1[2]);

                                    UnloadSound(dolor);
                                    UnloadSound(brinco);
                                    UnloadSound(paso);
                                    UnloadSound(agarrar);
                                    UnloadSound(disparo_nv1);
                                    UnloadSound(sdash);
                                    UnloadSound(disparo_nv1);
                                    UnloadSound(ludico);
                                    UnloadSound(anguilasound);

                                    UnloadMusicStream(musica_nv1);
                                    CloseAudioDevice();
                                    goto next;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!fin)
        {
            // reaiusta posicion si sale de limites *********************************************************************************************
            if (player.pos.y < 25)
            {
                player.pos.y = 25;
            }
            else
            {
                if (player.pos.y > SUELO - player.pos.height)
                {
                    player.pos.y = SUELO - player.pos.height;
                }
                else
                {
                    if (player.pos.x < 0)
                    {
                        player.pos.x = 0;
                    }
                    else
                    {
                        if (player.pos.x > RANCHO - player.pos.width)
                        {
                            player.pos.x = RANCHO - player.pos.width;
                        }
                    }
                }
            }

            //** piezas ****************************************************************************************************************************
            for (j = 0; j < 3; j++)
            {
                //drop
                if(pieza[j].listo)
                {
                    if(!pieza[j].status)
                    {
                        if(CheckPlayerColision(player.pos,pieza[j].pos))
                        {
                            pieza[j].status=1;
                        }
                    }
                }

                //recolleccion
                if(!pieza[j].listo)
                {
                    if(pieza[j].status)
                    {
                        if(CheckPlayerColision(player.pos,pieza[j].pos))
                        {
                            PlaySound(agarrar);
                            pieza[j].status=0;
                            pieza[j].listo=1;
                            pieza[j].pos.y=SUELO-pieza[j].pos.height;
                            piezac++;
                            switch(j)
                            {
                               case 0:
                                pieza[j].pos.x = 900;
                                break;
                                case 1:
                                    pieza[j].pos.x = 980;
                                    pieza[j].pos.y -= 5;
                                    break;
                                case 2:
                                    pieza[j].pos.x = 1055;
                                    pieza[j].pos.y -= 8;
                                    break;
                            }
                            j=3;
                        }
                    }
                }  
            }

            // movimiento piezas
            if (time > 600)
            {
                if (!pieza[0].listo)
                {
                    if (pieza[0].pos.y < plat[0].y - pieza[0].pos.height)
                    {
                        pieza[0].pos.y += 4;
                    }
                    else
                    {
                        if (piezac < 1)
                        {
                            pieza[0].pos.y = plat[0].y - pieza[0].pos.height;
                        }
                    }
                }
                if (time > 1200)
                {
                    if (!pieza[1].listo)
                    {
                        if (pieza[1].pos.y < plat[1].y - pieza[1].pos.height)
                        {
                            pieza[1].pos.y += 4;
                        }
                        else
                        {
                            if (piezac < 2)
                            {
                                pieza[1].pos.y = plat[1].y - pieza[1].pos.height;
                            }
                        }
                    }

                    if (time > 1800)
                    {
                        if (!pieza[2].listo)
                        {
                            if (pieza[2].pos.y < plat[2].y - pieza[2].pos.height)
                            {
                                pieza[2].pos.y += 4;
                            }
                            else
                            {
                                if (piezac < 3)
                                {
                                    pieza[2].pos.y = plat[2].y - pieza[2].pos.height;
                                }
                            }
                        }
                    }
                }
            }

            //** DROPS ************************************************************************************************************************
            for (i = 0; i < MAXDROPVIDA; i++)
            {
                if (dropVida[i].status)
                {
                    // tiempo
                    dropVida[i].time++;
                    // eliminacion
                    if (dropVida[i].time > DESPAWNTIME)
                    {
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }

                    // curacion
                    if (CheckPlayerColision(player.pos, dropVida[i].pos))
                    {
                        player.vida.num++;
                        dropVida[i].status = 0;
                        dropVida[i].time = 0;
                    }
                    else
                    {
                        // movimiento
                        if (dropVida[i].pos.y < SUELO - dropVida[i].pos.height)
                        {
                            dropVida[i].pos.y += 2;
                        }
                        else
                        {
                            dropVida[i].pos.y = SUELO - dropVida[i].pos.height;
                        }
                    }
                }
            }

            for (i = 0; i < MAXDROPASPEED; i++)
            {
                if (dropASpeed[i].statusDraw)
                {
                    // tiempo
                    dropASpeed[i].time++;
                    // eliminacion
                    if (!dropASpeed[i].statusFun)
                    {
                        if (dropASpeed[i].time > DESPAWNTIME)
                        {
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 0;
                            dropASpeed[i].time = 0;
                        }
                        if (CheckPlayerColision(player.pos, dropASpeed[i].pos))
                        {
                            player.buff = 1;
                            dropASpeed[i].statusDraw = 0;
                            dropASpeed[i].statusFun = 1;
                            dropASpeed[i].time = 0;
                            dropASpeed[i].duracion = 0;
                        }
                        else
                        {
                            // movimiento
                            if (dropASpeed[i].pos.y < SUELO - dropASpeed[i].pos.height * 3)
                            {
                                dropASpeed[i].pos.y += 1;
                            }
                            else
                            {
                                dropASpeed[i].pos.y = SUELO - dropASpeed[i].pos.height * 3;
                            }
                        }
                    }
                }
                else
                {
                    if (player.buff)
                    {
                        if (dropASpeed[i].statusFun)
                        {
                            if (dropASpeed[i].duracion < DURACIONBUFF)
                            {
                                dropASpeed[i].duracion++;
                            }
                            else
                            {
                                player.buff = 0;
                                dropASpeed[i].statusFun = 0;
                                dropASpeed[i].statusDraw = 0;
                                dropASpeed[i].time = 0;
                                dropASpeed[i].duracion = 0;
                            }
                        }
                    }
                }
            }

            //** enemigos **
            //** tiburones ******************************************************************************************************************************
            for (i = 0; i < MAXSHARK; i++)
            {
                // comportameinto
                if (shark[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (shark[i].right)
                    { // movimiento
                        if (shark[i].pos.y < 75)
                        {
                            shark[i].pos.x -= SHARKSPEED;
                        }
                        else
                        {
                            if (shark[i].pos.y > SUELO - 50 - shark[i].pos.height)
                            {
                                shark[i].pos.x -= SHARKSPEED;
                            }
                            else
                            {
                                PosicionObieto(shark[i].v.vx, shark[i].v.vy, shark[i].pos);
                            }
                        }

                        // eliminacion
                        if (shark[i].pos.x < 0 - shark[i].pos.width)
                        {
                            shark[i].status = 0;
                        }
                    }
                    else
                    {
                        if (shark[i].left)
                        { // movimiento
                            if (shark[i].pos.y < 75)
                            {
                                shark[i].pos.x += SHARKSPEED;
                            }
                            else
                            {
                                if (shark[i].pos.y > SUELO - 50 - shark[i].pos.height)
                                {
                                    shark[i].pos.x += SHARKSPEED;
                                }
                                else
                                {
                                    PosicionObieto(shark[i].v.vx, shark[i].v.vy, shark[i].pos);
                                }
                            }
                            // eliminacion
                            if (shark[i].pos.x > RANCHO + shark[i].pos.width)
                            {
                                shark[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT; j++)
                        {
                            if (CheckMobColision(shark[i].pos, hit[j]))
                            {
                                shark[i].status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = shark[i].pos.x;
                                                dropVida[k].pos.y = shark[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = shark[i].pos.x;
                                                    dropASpeed[k].pos.y = shark[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Colision con iugador
                    if (shark[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, shark[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXSHARK;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 50) + 1;
                    if (random == 1)
                    {
                        shark[i].right = rand() % 2;
                        random = rand() % 30;
                        if (shark[i].right)
                        {
                            shark[i].status = 1;
                            CalculaComponentesVelocidad(SHARKSPEED, float(random + 165), shark[i].v);
                            shark[i].pos.x = RANCHO;
                            shark[i].pos.y = (rand() % 550) + 50;
                            shark[i].left = 0;
                        }
                        else
                        {
                            shark[i].status = 1;
                            CalculaComponentesVelocidad(SHARKSPEED, float(random + 345), shark[i].v);
                            shark[i].pos.x = 0 - shark[i].pos.width;
                            shark[i].pos.y = (rand() % 550) + 50;
                            shark[i].left = 1;
                        }
                    }
                }
            }

            //** tortugas ******************************************************************************************************************************
            for (i = 0; i < MAXTORTUGA; i++)
            {
                // comportameinto
                if (tort[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (tort[i].right)
                    { // movimiento
                        tort[i].pos.x -= TORTUGASPEED;
                        if (tort[i].pos.x <= 0 - tort[i].pos.height)
                        {
                            tort[i].status = 0;
                        }
                    }
                    else
                    {
                        if (tort[i].left)
                        { // movimiento
                            tort[i].pos.x += TORTUGASPEED;
                            // eliminacion
                            if (tort[i].pos.x > RANCHO + tort[i].pos.width)
                            {
                                tort[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT; j++)
                        {
                            if (CheckMobColision(tort[i].pos, hit[j]))
                            {
                                tort[i].status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = tort[i].pos.x;
                                                dropVida[k].pos.y = tort[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = tort[i].pos.x;
                                                    dropASpeed[k].pos.y = tort[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Colision con iugador
                    if (tort[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, tort[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXTORTUGA;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 100) + 1;
                    if (random == 1)
                    {
                        if (tort[i].right)
                        {
                            tort[i].status = 1;
                            tort[i].pos.x = RANCHO;
                            tort[i].pos.y = (rand() % 550) + 50;
                        }
                        else
                        {
                            tort[i].status = 1;
                            tort[i].pos.x = 0 - tort[i].pos.width;
                            tort[i].pos.y = (rand() % 550) + 50;
                        }
                    }
                }
            }

            //** anguilas *********************************************************************************************************************************
            for (i = 0; i < MAXANGUILA; i++)
            {
                // comportameinto
                if (ang[i].status)
                {
                    // movimiento enemigo **si sale de la pantalla se elimina**
                    if (ang[i].right)
                    { // movimiento
                        if (ang[i].pos.y < 75)
                        {
                            ang[i].pos.x -= ANGUILASPEED;
                        }
                        else
                        {
                            if (ang[i].pos.y > SUELO - 50 - ang[i].pos.height)
                            {
                                ang[i].pos.x -= ANGUILASPEED;
                            }
                            else
                            {
                                PosicionObieto(ang[i].v.vx, ang[i].v.vy, ang[i].pos);
                            }
                        }

                        // eliminacion
                        if (ang[i].pos.x < 0 - ang[i].pos.width)
                        {
                            ang[i].status = 0;
                            ang[i].hit.status = 0;
                        }

                        //** generacion ataque enemigo ************************************************************************************************
                        random = (rand() % 20) + 1;
                        if (random == 1)
                        {
                            if (!ang[i].hit.status)
                            {
                                if (ang[i].pos.x <= player.pos.x + player.pos.width + 200)
                                {
                                    if (ang[i].pos.x >= player.pos.x - 200)
                                    {
                                        if (ang[i].pos.y <= player.pos.y + player.pos.height + 200)
                                        {
                                            if (ang[i].pos.y >= player.pos.y - 200)
                                            {
                                                // random=rand()%MAXANGUILAHIT;
                                                PlaySound(anguilasound);
                                                AngElectro(ang[i]);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        //** comporamiento descarga electrica ************************************************************************************
                        if (ang[i].status)
                        {
                            if (ang[i].hit.status)
                            {
                                if (ang[i].hit.time < 120)
                                {
                                    ang[i].hit.pos.y = ang[i].pos.y - ang[i].pos.height;
                                    ang[i].hit.pos.x = ang[i].pos.x - 21;
                                    ang[i].hit.time++;

                                    // colision con jugador
                                    if (player.vida.time > INVULERABILIDAD)
                                    {
                                        if (CheckPlayerColision(player.pos, ang[i].hit.pos))
                                        {
                                            PlaySound(dolor);
                                            if (player.vida.num < 1)
                                            {
                                                piezac = 0;
                                                time = 0;
                                                muerteLvl1(player, shark, tort, ang, pieza, plat);
                                            }
                                            else
                                            {
                                                player.vida.num--;
                                                player.vida.time = 0;
                                            }
                                            i = MAXANGUILA;
                                        }
                                    }
                                }
                                else
                                {
                                    ang[i].hit.status = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (ang[i].left)
                        { // movimiento
                            if (ang[i].pos.y < 75)
                            {
                                ang[i].pos.x += ANGUILASPEED;
                            }
                            else
                            {
                                if (ang[i].pos.y > SUELO - 50 - ang[i].pos.height)
                                {
                                    ang[i].pos.x += ANGUILASPEED;
                                }
                                else
                                {
                                    PosicionObieto(ang[i].v.vx, ang[i].v.vy, ang[i].pos);
                                }
                            }
                            // eliminacion
                            if (ang[i].pos.x > RANCHO + ang[i].pos.width)
                            {
                                ang[i].status = 0;
                            }
                        }
                    }

                    // Colision con golpe
                    if (hit)
                    {
                        for (j = 0; j < MAXHIT; j++)
                        {
                            if (CheckMobColision(ang[i].pos, hit[j]))
                            {
                                ang[i].status = 0;
                                ang[i].hit.status = 0;
                                random = rand() % 10 + 1;
                                if (random <= 4)
                                {
                                    random = rand() % 2;
                                    if (random)
                                    {
                                        for (k = 0; k < MAXDROPVIDA; k++)
                                        {
                                            if (!dropVida[k].status)
                                            {
                                                dropVida[k].status = 1;
                                                dropVida[k].time = 0;
                                                dropVida[k].pos.x = ang[i].pos.x;
                                                dropVida[k].pos.y = ang[i].pos.y;
                                                k = MAXDROPVIDA;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (k = 0; k < MAXDROPASPEED; k++)
                                        {
                                            if (!dropASpeed[k].statusDraw)
                                            {
                                                if (!dropASpeed[k].statusFun)
                                                {
                                                    dropASpeed[k].statusDraw = 1;
                                                    dropASpeed[k].statusFun = 0;
                                                    dropASpeed[k].time = 0;
                                                    dropASpeed[k].pos.x = ang[i].pos.x;
                                                    dropASpeed[k].pos.y = ang[i].pos.y;
                                                    k = MAXDROPASPEED;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Colision con iugador
                    if (ang[i].status)
                    {
                        if (player.vida.time > INVULERABILIDAD)
                        {
                            if (CheckPlayerColision(player.pos, ang[i].pos))
                            {
                                PlaySound(dolor);
                                if (player.vida.num < 1)
                                {
                                    piezac = 0;
                                    time = 0;
                                    muerteLvl1(player, shark, tort, ang, pieza, plat);
                                }
                                else
                                {
                                    player.vida.num--;
                                    player.vida.time = 0;
                                }
                                i = MAXANGUILA;
                            }
                        }
                    }
                }
                else
                {
                    // generacion
                    random = (rand() % 50) + 1;
                    if (random == 1)
                    {
                        ang[i].right = rand() % 2;
                        if (ang[i].right)
                        {
                            ang[i].status = 1;
                            ang[i].pos.x = RANCHO;
                            ang[i].pos.y = (rand() % 550) + 60;
                            CalculaComponentesVelocidad(ANGUILASPEED, CalculaAngulo(ang[i].pos, player.pos), ang[i].v);
                            ang[i].left = 0;
                        }
                        else
                        {
                            ang[i].status = 1;
                            ang[i].pos.x = 0 - ang[i].pos.width;
                            ang[i].pos.y = (rand() % 550) + 60;
                            CalculaComponentesVelocidad(ANGUILASPEED, CalculaAngulo(ang[i].pos, player.pos), ang[i].v);
                            ang[i].left = 1;
                        }
                    }
                }
            }

            //** dash **************************************************************************************************************************
            if (player.dash)
            {
                if (player.timeDash < 20)
                {
                    if (lookR)
                    {
                        if (lookUp)
                        {
                            player.pos.x += VDDIAGONAL;
                            player.pos.y -= VDDIAGONAL;
                        }
                        else
                        {
                            if (lookDown)
                            {
                                player.pos.x += VDDIAGONAL;
                                player.pos.y += VDDIAGONAL;
                            }
                            else
                            {
                                player.pos.x += 7.5;
                            }
                        }
                    }
                    else
                    {
                        if (lookL)
                        {
                            if (lookUp)
                            {
                                player.pos.x -= VDDIAGONAL;
                                player.pos.y -= VDDIAGONAL;
                            }
                            else
                            {
                                if (lookDown)
                                {
                                    player.pos.x -= VDDIAGONAL;
                                    player.pos.y += VDDIAGONAL;
                                }
                                else
                                {
                                    player.pos.x -= 7.5;
                                }
                            }
                        }
                        else
                        {
                            if (lookUp)
                            {
                                player.pos.y -= 7.5;
                            }
                            else
                            {
                                if (lookDown)
                                {
                                    player.pos.y += 7.5;
                                }
                            }
                        }
                    }
                }
                else
                {
                    lookDown = 0;
                    lookUp = 0;
                    player.dash = 0;
                }
            }

            //** hit ********************************************************************************************************************************
            for (i = 0; i < MAXHIT; i++)
            {
                //** movimiento del disparo ***********************************************************************************
                if (hit[i].status)
                {
                    PosicionObieto(hit[i].v.vx, hit[i].v.vy, hit[i].pos);

                    //** Eliminacion del proyectil *******************************************************************************
                    // si se paso del borde izquierdo
                    if (hit[i].pos.x < 0 - hit[i].pos.width)
                    {
                        hit[i].status = 0;
                    }
                    else
                    {
                        // si se paso del borde derecho
                        if (hit[i].pos.x > RANCHO)
                        {
                            hit[i].status = 0;
                        }
                    }

                    if (hit[i].pos.y < 0)
                    {
                        hit[i].status = 0;
                    }
                    else
                    {
                        if (hit[i].pos.y > RALTO)
                        {
                            hit[i].status = 0;
                        }
                    }
                }
            }

            //** input *****************************************************************************************************************************
            if (!player.dash) // right left
            {
                if (IsKeyDown(KEY_RIGHT))
                {
                    player.x0 = player.pos.x;
                    player.pos.x += 3;
                    lookR = 1;
                    lookL = 0;
                }
                else
                {
                    if (IsKeyDown(KEY_LEFT))
                    {
                        player.x0 = player.pos.x;
                        player.pos.x -= 3;
                        lookR = 1;
                        lookL = 0;
                    }
                }
            }

            if (!player.dash) // up down
            {
                if (IsKeyDown(KEY_UP))
                {
                    player.pos.y -= VY;
                }
                else
                {
                    if (IsKeyDown(KEY_DOWN))
                    {
                        player.pos.y += VY;
                    }
                }
            }

            // dash KEY C
            if (player.timeDash > 80)
            {
                if (!player.dash)
                {
                    if (IsKeyPressed(KEY_C))
                    {
                        PlaySound(sdash);
                        Direccioniugador1(lookL, lookR, lookUp, lookDown, player);
                        player.dash = 1;
                        player.timeDash = 0;
                    }
                }
            }

            // hit
            if (IsKeyDown(KEY_X))
            {
                for (i = 0; i < MAXHIT; i++)
                {
                    Direccioniugador1(lookL, lookR, lookUp, lookDown, player);
                    if (!player.buff) //** Meiora ******************************************************************************************************
                    {
                        if (player.AtkC > VATAQUE)
                        {
                            if (hit[i].status == 0)
                            {
                                hit[i].status = 1;
                                player.AtkC = 0;
                                PlaySound(disparo_nv1);
                                InicializaProyectil(lookL, lookR, lookUp, lookDown, player, hit[i]);
                                CalculaComponentesVelocidad(VPROYECTIL, 45 * hit[i].direccion, hit[i].v);
                                disparo=1;
                                // printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                                i = MAXHIT;
                            }
                        }
                    }
                    else
                    {
                        if (player.AtkC > VATAQUEBUFF)
                        {
                            if (hit[i].status == 0)
                            {
                                hit[i].status = 1;
                                player.AtkC = 0;
                                disparo=1;
                                PlaySound(disparo_nv1);
                                InicializaProyectil(lookL, lookR, lookUp, lookDown, player, hit[i]);
                                CalculaComponentesVelocidad(VPROYECTIL, 45 * hit[i].direccion, hit[i].v);
                                // printf("Direccion = %d l = %d r = %d up = %d down = %d \n",hit[i].direccion,lookL,lookR,lookUp,lookDown);
                                i = MAXHIT;
                            }
                        }
                    }
                }
            }
        }

        // dibujado

        // plataformas
        for (i = 0; i < MAXPLAT; i++)
        {
            DrawTexture(plataforma_nv1, plat[i].x, plat[i].y, WHITE);
            // DrawRectangleRec(plat[i], DARKGREEN);
        }

        framesAutom++;
        if (framesAutom >= (60 / framesSpeed))
        {
            framesAutom = 0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;
            framesTortuga.x = (float)currentFrame * (float)tortuga.width / 6;
            framesTortugaizq.x = (float)currentFrame * (float)tortugaizq.width / 6;
            framesAnguila.x = (float)currentFrame * (float)anguila.width / 6;
            framesAnguilaizq.x = (float)currentFrame * (float)anguilaizq.width / 6;
            framesPulpo.x = (float)currentFrame * (float)pulpo.width / 6;
            framesPulpoizq.x = (float)currentFrame * (float)pulpoizq.width / 6;
            framesReposo.x = (float)currentFrame * (float)reposo.width / 4;
            framesReposoizq.x = (float)currentFrame * (float)reposoizq.width / 4;
        }

       

        for (i = 0; i < MAXHIT; i++)
        {
            if (hit[i].status)
            {
                DrawTexture(bullet_nv1, hit[i].pos.x, hit[i].pos.y, WHITE);
            }
        }
        // suelo

        // vida
        for (i = 1; i <= player.vida.num; i++)
        {
            DrawTexture(corazon, player.vida.pos.x, player.vida.pos.y, WHITE);
            player.vida.pos.x += 25 + player.vida.pos.width;
        }
        player.vida.pos.x = 25;

        // enemigos
        for (i = 0; i < MAXSHARK; i++)
        {
            if (shark[i].status)
            {
                if (shark[i].right)
                {
                    // DrawRectangleRec(shark[i].pos, RED);
                    DrawTextureRec(pulpoizq, framesPulpoizq, Vector2{shark[i].pos.x - 25, shark[i].pos.y - 20}, WHITE);
                }

                if (shark[i].left)
                {
                    // DrawRectangleRec(shark[i].pos, RED);
                    DrawTextureRec(pulpo, framesPulpo, Vector2{shark[i].pos.x + 13, shark[i].pos.y - 20}, WHITE);
                }
            }
        }

        for (i = 0; i < MAXTORTUGA; i++)
        {
            if (tort[i].status)
            {
                if (tort[i].right)
                {
                    DrawTextureRec(tortugaizq, framesTortugaizq, Vector2{tort[i].pos.x - 15, tort[i].pos.y}, WHITE);
                }

                if (tort[i].left)
                {
                    DrawTextureRec(tortuga, framesTortuga, Vector2{tort[i].pos.x - 15, tort[i].pos.y - 50}, WHITE);
                }
            }
        }

        //DROPS
        //DROPS
        for(i=0;i<MAXDROPVIDA;i++)
        {
            if(dropVida[i].status)
            {
                DrawTexture(corazon,dropVida[i].pos.x,dropVida[i].pos.y,WHITE);
            }
        }
        for(i=0;i<MAXDROPASPEED;i++)
        {
            if(dropASpeed[i].statusDraw)
            {
                if(!dropASpeed[i].statusFun)
                 {
                    DrawTexture(Aspeed,dropASpeed[i].pos.x,dropASpeed[i].pos.y,WHITE);
                }
            }
        }
        for (i = 0; i < MAXANGUILA; i++)
        {
            if (ang[i].status)
            {
                if (!ang[i].hit.status)
                {
                    if (ang[i].left)
                    {
                        // DrawRectangleRec(ang[i].pos, RED);
                        DrawTextureRec(anguila, framesAnguila, Vector2{ang[i].pos.x - 5, ang[i].pos.y - 33}, WHITE);
                    }
                    if (ang[i].right)
                    {
                        // DrawRectangleRec(ang[i].pos, RED);
                        DrawTextureRec(anguilaizq, framesAnguilaizq, Vector2{ang[i].pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                }
                else
                {
                    if (ang[i].left)
                    {
                        framesAtaque++;
                        if (framesAtaque >= (60 / framesSpeed))
                        {
                            framesAtaque = 0;
                            currentAtaque++;

                            if (currentAtaque > 6)
                                currentAtaque = 0;
                            framesAtaque_ani.x = (float)currentAtaque * (float)ataque_ani.width / 6;
                            framesAtaque_anizq.x = (float)currentAtaque * (float)ataque_anizq.width / 6;
                        }
                        PlaySound(anguilasound);
                        DrawTextureRec(ataque_ani, framesAtaque_ani, Vector2{ang[i].hit.pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                    if (ang[i].right)
                    {
                        framesAtaque++;
                        if (framesAtaque >= (60 / framesSpeed))
                        {
                            framesAtaque = 0;
                            currentAtaque++;

                            if (currentAtaque > 6)
                                currentAtaque = 0;
                            framesAtaque_ani.x = (float)currentAtaque * (float)ataque_ani.width / 6;
                            framesAtaque_anizq.x = (float)currentAtaque * (float)ataque_anizq.width / 6;
                        }
                        DrawTextureRec(ataque_anizq, framesAtaque_anizq, Vector2{ang[i].hit.pos.x - 12, ang[i].pos.y - 33}, WHITE);
                    }
                }
            }
        }
        // piezas
        for (i = 0; i < 3; i++)
        {
            if (pieza[i].status)
            {
                DrawTexture(piezas_nv1[i], pieza[i].pos.x, pieza[i].pos.y, WHITE);
            }
        }
        // jugador
        Direccioniugador1(lookL,lookR,lookUp,lookDown,player);

        if (!IsKeyDown(KEY_X))
        {
             framesSalto++;
                    if (framesSalto >= (60 / framesSpeed))
                    {
                        framesSalto = 0;
                        currentSalto++;

                        if (currentSalto > 3)
                            currentSalto = 0;
                        frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                        frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
                    }
                    if (lookL)
                    {
                        DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 75, player.pos.y - 50}, WHITE);
                    }
                    else
                    {
                        if (lookR)
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 35, player.pos.y - 50}, WHITE);
                        }
                        else
                        {
                            DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 35, player.pos.y - 50}, WHITE);
                        }
                    }
        }
        else
        {
            if (disparo)
            {
                if (lookR)
                {
                    if (lookUp)
                    {
                        DrawTexture(ataquesderechos[3], player.pos.x - 20, player.pos.y - 30, WHITE);
                    }
                    else
                    {
                        if (lookDown)
                        {
                            DrawTexture(ataquesderechos[1], player.pos.x-20, player.pos.y - 10, WHITE);
                        }
                        else
                        {
                            DrawTexture(ataquesderechos[2], player.pos.x-20, player.pos.y - 10, WHITE);
                        }
                    }
                }
                else
                {
                    if (lookL)
                    {
                        if (lookUp)
                        {
                            DrawTexture(ataquesizquierdos[3], player.pos.x-35, player.pos.y-40, WHITE);
                        }
                        else
                        {
                            if (lookDown)
                            {
                                DrawTexture(ataquesizquierdos[1], player.pos.x - 50, player.pos.y - 10, WHITE);
                            }
                            else
                            {
                                DrawTexture(ataquesizquierdos[2], player.pos.x - 65, player.pos.y - 10, WHITE);
                            }
                        }
                    }
                    else
                    {
                        if (lookUp)
                        {
                            DrawTexture(ataquesderechos[4], player.pos.x-15, player.pos.y - 40, WHITE);
                        }
                        else
                        {
                            if (lookDown)
                            {
                                DrawTexture(ataquesderechos[0], player.pos.x-15, player.pos.y - 10, WHITE);
                            }
                        }
                    }
                }
            }
            else
            {
                framesSalto++;
                if (framesSalto >= (60 / framesSpeed))
                {
                    framesSalto = 0;
                    currentSalto++;
                    if (currentSalto > 3)
                    currentSalto = 0;
                    frameSalto.x = (float)currentSalto * (float)salto.width / 4;
                    frameSaltoder.x = (float)currentSalto * (float)saltoder.width / 4;
                }
                if (lookL)
                {
                    DrawTextureRec(salto, frameSalto, Vector2{player.pos.x - 75, player.pos.y - 50}, WHITE);
                }
                else
                {
                    if (lookR)
                    {
                        DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 35, player.pos.y - 50}, WHITE);
                    }
                    else
                    {
                        DrawTextureRec(saltoder, frameSalto, Vector2{player.pos.x - 35, player.pos.y - 50}, WHITE);
                    }
                }
            }
        }

        EndMode2D();
        EndDrawing();
    }
    next:
        int z=0;
}

/********************************************************  Cuerpo Funciones Generales *****************************************************************/
//1, 3
void Direccioniugador(int &L, int &R, int &Up, int &Down, Tplayer player)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        if (IsKeyDown(KEY_UP))
        {
            R = 1;
            Up = 1;
            Down = 0;
            L = 0;
        }
        else
        {
            if (IsKeyDown(KEY_DOWN))
            {
                R = 1;
                Up = 0;
                Down = 1;
                L = 0;
            }
            else
            {
                R = 1;
                Up = 0;
                Down = 0;
                L = 0;
            }
        }
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 1;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 1;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 0;
                if (player.x0 <= player.pos.x)
                {
                    R = 1;
                    Up = 0;
                    Down = 0;
                    L = 0;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 0;
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
                else
                {
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
            }
        }
    }
}

//1,3
void InicializaProyectil(int L, int R, int Up, int Down, Tplayer player, Thit &hit)
{
    hit.pos.y = player.pos.y + player.pos.height / 4;
    hit.pos.x = player.pos.x + player.pos.width / 2;
    if (R)
    {
        if (Up)
        {
            hit.direccion = 1;
        }
        else
        {
            if (Down)
            {
                hit.direccion = 7;
            }
            else
            {
                hit.direccion = 0;
            }
        }
    }
    else
    {
        if (L)
        {
            if (Up)
            {
                hit.direccion = 3;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 5;
                }
                else
                {
                    hit.direccion = 4;
                }
            }
        }
        else
        {
            if (Up)
            {
                hit.direccion = 2;
            }
            else
            {
                if (Down)
                {
                    hit.direccion = 6;
                }
            }
        }
    }
}

//1,3
void CalculaComponentesVelocidad(float velocidad, float grados, Tvel &v)
{
    if (grados >= 360)
    {
        grados -= 360;
    }

    v.vy = velocidad * sin(Radianes(grados));
    v.vx = sqrt((pow(velocidad, 2) - pow(v.vy, 2)));
    if (grados <= 90)
    {
        v.vy = -v.vy;
    }
    else
    {
        if (grados <= 180)
        {
            v.vx = -v.vx;
            v.vy = -v.vy;
        }
        else
        {
            if (grados <= 270)
            {
                v.vx = -v.vx;
                v.vy = -v.vy;
            }
            else
            {
                v.vy = -v.vy;
            }
        }
    }
}

//1,3
void PosicionObieto(float vx, float vy, Rectangle &pos)
{
    pos.x += vx;
    pos.y += vy;
}

//1,2,3
int CheckPlayerColision(Rectangle player, Rectangle mob)
{
    if (player.x < (mob.x + mob.width))
    {
        if ((player.x + player.width) > mob.x)
        {
            if (player.y < (mob.y + mob.height))
            {
                if ((player.y + player.height) > mob.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//revisar para cada nivel
int CheckMobColision(Rectangle mob, Thit hit)
{
    if (mob.x < (hit.pos.x + hit.pos.width))
    {
        if ((mob.x + mob.width) > hit.pos.x)
        {
            if (mob.y < (hit.pos.y + hit.pos.height))
            {
                if ((mob.y + mob.height) > hit.pos.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//1,3
float CalculaAngulo(Rectangle enemigo, Rectangle player)
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

//1,3
float Radianes(float grados)
{
    return (grados * PI / 180);
}

/********************************************************  Cuerpo Funciones 1 *****************************************************************/
void LimpiaEnemigosLvl1(Tshark shark[], Ttortu tort[], Tangui ang[])
{
    int i;
    for (i = 0; i < MAXSHARK; i++)
    {
        shark[i].status = 0;
    }
    for (i = 0; i < MAXTORTUGA; i++)
    {
        tort[i].status = 0;
    }
    for (i = 0; i < MAXANGUILA; i++)
    {
        ang[i].status = 0;
        ang[i].hit.status = 0;
    }
}

void AngElectro(Tangui &ang)
{
    ang.hit.pos.y = ang.pos.y - ang.pos.height;
    ang.hit.pos.x = ang.pos.x - 21;
    ang.hit.status = 1;
    ang.hit.time = 0;
}

void muerteLvl1(Tplayer &player, Tshark shark[], Ttortu tort[], Tangui ang[], Tpart pieza[], Rectangle plat[])
{
    int j;
    player.pos.x = 400;   // Posicion incial
    player.pos.y = SUELO; //""
    player.timeDash = 70;
    player.vida.num = MAXVIDA;
    LimpiaEnemigosLvl1(shark, tort, ang);
    for (j = 0; j < 3; j++)
    {
        pieza[j].status = 1;
        pieza[j].listo = 0;
        pieza[j].pos.x = plat[j].x + plat[j].width / 2 - pieza[j].pos.width / 2;
        pieza[j].pos.y = -300;
    }
}

void Direccioniugador1(int &L, int &R, int &Up, int &Down, Tplayer player)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        if (IsKeyDown(KEY_UP))
        {
            R = 1;
            Up = 1;
            Down = 0;
            L = 0;
        }
        else
        {
            if (IsKeyDown(KEY_DOWN))
            {
                R = 1;
                Up = 0;
                Down = 1;
                L = 0;
            }
            else
            {
                R = 1;
                Up = 0;
                Down = 0;
                L = 0;
            }
        }
    }
    else
    {
        if (IsKeyDown(KEY_LEFT))
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 1;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 1;
                }
                else
                {
                    R = 0;
                    Up = 0;
                    Down = 0;
                    L = 1;
                }
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP))
            {
                R = 0;
                Up = 1;
                Down = 0;
                L = 0;
            }
            else
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    R = 0;
                    Up = 0;
                    Down = 1;
                    L = 0;
                }
                else
                {
                    if (player.x0 <= player.pos.x)
                    {
                        R = 1;
                        Up = 0;
                        Down = 0;
                        L = 0;
                    }
                    else
                    {
                        R = 0;
                        Up = 0;
                        Down = 0;
                        L = 1;
                    }
                }
            }
        }
    }
}