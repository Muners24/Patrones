#pragma once
#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define JUGAR 0
#define OPCIONES 1
#define SALIR 2

#define DIFICULTAD 0
#define SONIDO 1
#define REGRESAR 2

#define NEWP 0
#define SALIRJ 1

//GENERAL

#define MAXDROPVIDA 10
#define DESPAWNTIME 600
#define MAXDROPASPEED 10
#define DURACIONBUFF 600

#define CAMY 360
#define CAMX 640

#define ALTOP 85
#define ANCHOP 50
#define SUELO 650
#define MAXVIDA 4
#define INVULERABILIDAD 120

#define VS -11
#define VY 3    //multiplicar por -1 para nivel 3

//NIVEL1
#define MAXPLAT 3
//ENEMIGO1
#define MAXANGUILA 3
#define ANGUILASPEED 5
#define MAXSHARK 2
#define SHARKSPEED 7
#define MAXTORTUGA 2
#define TORTUGASPEED 3

//NIVEL2
//ENEMIGO2
#define MAXAVE 5
#define AVESPEED 7
#define MAXEGG 8
#define MAXCAR 2
#define CARSPEED 9

//NIVEL3 
#define RECVEHICULO 900
#define VSJ -4
//ENEMIGO3 
#define MAXTORRE 2
#define TORREASPEED 180
#define TORREVPROYECTIL 6
#define MAXHITTORRE 2
#define MAXOVNI 2
#define OVNISPEED 3
#define OVNILONG 150
#define OVNIAMP 15
//CAMBIAR ATAQUE EN NIVEL3 **

//ATAQUE
#define MAXHIT 500
#define VATAQUE 50
#define VATAQUEBUFF 20
#define VPROYECTIL 10



//PLAYER
#define PLAYER_H    ALTOP-10
#define PLAYER_W    ANCHOP/1.5
#define PLAYER_V 4

//PLAYER LVL1
#define ATACK_CD 50
#define ATACK_CD_BUFF 20
#define ATACK_ANIMATION_DUR 15

//DASH
#define DASH_V 7.5
#define DASH_CD 180
#define DASH_DURATION 20

//RESOLOCUION
#define RANCHO  1280
#define RALTO 720

//LIMITES
#define BORDE_LEFT 0
#define BORDE_UP 0
#define BORDE_DOWN RALTO
#define BORDE_RIGHT RANCHO

//PROYECTILES
#define PROYECTIL_RAD 10 
#define PROYECTIL_V 10

//PIEZAS 
#define DESTINO_Y BORDE_DOWN - 200
#define DESTINO_X 800


#define POS_VIDA 25