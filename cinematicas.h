#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <raylib.h>

#define COLUMNAS1 3
#define RENGLONES1 2

#define RANCHO 1280
#define RALTO 720


typedef struct _tabla
{
    Rectangle pos;
    int num;
    int numPredict;
    char opRight[2];
    char opDown[2];
    int status;
    int elec;
}Ttab;

void cinemaPuzleNivel1(int diflvl);
void cinemaPuzleNivel2(int diflvl);
void cinemaPuzleNivel3(int diflvl);

void cinemaPuzleNivel1(int diflvl)
{
    Texture2D fondo = LoadTexture("texturas\\motor1.png");
    srand(time(NULL));

    Vector2 v=GetMousePosition();

    Color casillas;
    casillas.r=219;
    casillas.g=145;
    casillas.b=49;
    casillas.a=255;

    Color operacion;
    operacion.b=122;
    operacion.g=183;
    operacion.r=231;
    operacion.a=255;

    
    
    
    BEIGE;
    Rectangle cas;
    cas.height=110;
    cas.width=150;
    cas.x=185;
    cas.y=100;

    Rectangle bordecas;
    bordecas.height=120;
    bordecas.width=160;
    bordecas.x=cas.x-5;
    bordecas.y=cas.y-5;
    
    Rectangle op;
    op.height=60;
    op.width=60;
    op.x=0;
    op.y=0;

    Rectangle bordeop;
    bordeop.height=70;
    bordeop.width=70;

    Color cian;
    cian.b=113;
    cian.g=168;
    cian.r=0;
    cian.a=255;
    cian=BLACK;
    Color colorop;
    colorop.b=6;
    colorop.g=32;
    colorop.r=56;
    colorop.a=255;

    int i,j;
    int random;
    float respuestasx[3];
    float respuestasy[2];
    int fin;
    int maxDraw=1;
    char txt[10];
    Ttab tabla[RENGLONES1][COLUMNAS1];
    int sel[2]={0,0};
    //+ - * /
    char operadores[5][2]={"+","-","*","/","="};
    FILE *fa;
    char t[2];
    int ocultoC=0;
    int predictC=0;
    //for(int k=1;k<=15;k++)
    
        /*
        //asignacion ==
        for(i=0;i<RENGLONES1;i++)
        {
            strcpy(tabla[i][COLUMNAS1-1].opRight,operadores[4]);
        }
        for(i=0;i<COLUMNAS1;i++)
        {
            strcpy(tabla[RENGLONES1-1][i].opDown,operadores[4]);
        }

        //asignacion de operadores y numeros
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {
                random=rand()%10;
                if(random%2==0)
                {
                    tabla[i][j].status=1;
                    tabla[i][j].num=(rand()%40)+1;
                    if(j<COLUMNAS1-1)
                    {
                        if(i<RENGLONES1-1)
                        {
                            strcpy(tabla[i][j].opDown,operadores[rand()%4]);
                            strcpy(tabla[i][j].opRight,operadores[rand()%4]);
                        }
                        else
                        {
                            if(j<COLUMNAS1-1)
                            {
                                strcpy(tabla[i][j].opRight,operadores[rand()%4]);
                            }   
                        }
                    }
                    else
                    {
                        if(i<RENGLONES1-1)
                        {
                            strcpy(tabla[i][j].opDown,operadores[rand()%4]);
                        }
                    }
                }
                else
                {
                    tabla[i][j].status=0;
                    tabla[i][j].num=(rand()%40)+1;
                    if(j<COLUMNAS1-1)
                    {
                        if(i<RENGLONES1-1)
                        {
                            
                            strcpy(tabla[i][j].opDown,operadores[rand()%4]);
                            strcpy(tabla[i][j].opRight,operadores[rand()%4]);
                        }
                        else
                        {
                            if(j<COLUMNAS1-1)
                            {
                                strcpy(tabla[i][j].opRight,operadores[rand()%4]);
                            }   
                        }
                    }
                    else
                    {
                        if(i<RENGLONES1-1)
                        {
                            strcpy(tabla[i][j].opDown,operadores[rand()%4]);
                        }
                    }
                }
            }
        }
        */
        /**/

    if(diflvl==0)
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif1\\dif1_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif1\\dif1_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif1\\dif1_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif1\\dif1_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif1\\dif1_5.txt","r");
                break;
        }
    }
    else
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif2\\dif2_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif2\\dif2_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif2\\dif2_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif2\\dif2_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif2\\dif2_5.txt","r");
                break;
        }
    }
    
    if(fa)
    {    
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {
                tabla[i][j].numPredict=-1;
                tabla[i][j].status=1;
                tabla[i][j].elec=0;
                fscanf(fa,"%d %c %c",&tabla[i][j].num,&tabla[i][j].opRight[0],&tabla[i][j].opDown[0]);
                tabla[i][j].opRight[1]='\0';
                tabla[i][j].opDown[1]='\0';
            }
        }
            fscanf(fa," %f %f %f %f %f ",&respuestasy[0],&respuestasy[1],&respuestasx[0],&respuestasx[1],&respuestasx[2]);
            fclose(fa);
    }

    int random2;
    int random3;
    ocultoC=(rand()%3)+1;
    random3=ocultoC;
    while(random3>0)
    {
        random=rand()%2;
        random2=rand()%3;
        if(tabla[random][random2].status==1)
        {
            tabla[random][random2].status=0;
            tabla[random][random2].numPredict=0;
            random3--;
        }
    }
    tabla[0][0].elec=1;
    
    while (!WindowShouldClose())
    {
        v=GetMousePosition();

        //printf("\noculto = %d predictC = %d \n",ocultoC,predictC);
        //termianr minijuego
        if(IsKeyPressed(KEY_ENTER))
        {
            for(i=0;i<RENGLONES1;i++)
            {
                for(j=0;j<COLUMNAS1;j++)
                {
                    if(!tabla[i][j].status)
                    {
                        if(tabla[i][j].num==tabla[i][j].numPredict)
                        {
                            predictC++;
                        }
                    }
                }
            }

            if(predictC==ocultoC)
            {
                goto fin;
            }
            predictC=0;
        }
        //printf("\nx = %f  y = %f\n",v.x,v.y);
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {  
                if(i==sel[0])
                {
                    
                    if(j==sel[1])
                    {
                        tabla[i][j].elec=1;
                    }
                    else
                    {
                        tabla[i][j].elec=0;
                    }
                }
                else
                {
                    tabla[i][j].elec=0;
                }
            }
        }

        //seleccion right left
        if(IsKeyPressed(KEY_RIGHT))
        {
            if(sel[1]<2)
            {
                sel[1]++;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_LEFT))
            {
                if(sel[1]>0)
                {
                    sel[1]--;
                }
            }
        }

        if(IsKeyPressed(KEY_UP))
        {
            if(sel[0]>0)
            {
                sel[0]--;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_DOWN))
            {
                if(sel[0]<1)
                {
                    sel[0]++;
                }
            }
        }

        
        if(IsKeyPressed(KEY_W))
        {
            if(!tabla[sel[0]][sel[1]].status)
            {
                if(tabla[sel[0]][sel[1]].elec)
                {
                    tabla[sel[0]][sel[1]].numPredict++;
                }
            }
        }
        else
        {
            if(IsKeyPressed(KEY_S))
            {
                if(!tabla[sel[0]][sel[1]].status)
                {
                    if(tabla[sel[0]][sel[1]].elec)
                    {
                        tabla[sel[0]][sel[1]].numPredict--;
                    }
                }
            }
        }
        BeginDrawing();
            DrawTexture(fondo,0,0,WHITE);
            
            for(i=0;i<=RENGLONES1;i++)
            {
                for(j=0;j<=COLUMNAS1;j++)
                {
                    bordecas.x=cas.x-5;
                    bordecas.y=cas.y-5;

                    if(i==RENGLONES1 && j==COLUMNAS1)
                    {
                        continue;
                    }
                    if(i==sel[0])
                    {
                        if(j==sel[1])
                        {
                            DrawRectangleRec(bordecas,BLACK);
                        }
                        else
                        {
                            DrawRectangleRec(bordecas,colorop);
                        }
                    }
                    else
                    {
                        DrawRectangleRec(bordecas,colorop);
                    }
                    DrawRectangleRec(cas,casillas);
                    if(i==0)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[0]);
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                        }
                    }
                    if(i==1)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==0)
                        {
                            sprintf(txt,"%.2f",respuestasx[0]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==1)
                        {
                            sprintf(txt,"%.2f",respuestasx[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==2)
                        {
                            sprintf(txt,"%.2f",respuestasx[2]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                            }
                        }
                    }
                    
                    if(i<RENGLONES1)
                    {  
                        if(j<COLUMNAS1)
                        {
                            op.x=bordecas.x+bordecas.width+15;
                            op.y=bordecas.y+20;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,colorop);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opRight,op.x+((op.width-MeasureText(tabla[i][j].opRight,40))/2),op.y+10,40,BLACK);
                            
                            op.x=bordecas.x+bordecas.width/2-op.width/2;
                            op.y=bordecas.y+bordecas.height+15;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,colorop);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opDown,op.x+((op.width-MeasureText(tabla[i][j].opDown,40))/2),op.y+10,40,BLACK);

                            if(tabla[i][j].status)
                            {
                                itoa(tabla[i][j].num,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,WHITE);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,WHITE);
                                }
                            }
                            else
                            {
                                itoa(tabla[i][j].numPredict,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,cian);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,cian);
                                }
                            }
                        }
                    }

                    
                    if(maxDraw)
                    {
                        if(i==RENGLONES1)
                        {
                            maxDraw=0;
                            j--;
                            
                        }
                    }
                    cas.x+=100+cas.width;
                }
                
                cas.y+=100+cas.height;
                cas.x=185;
            }
            cas.y=100;
        EndDrawing();
    }
    fin:
        int z=0;
}

void cinemaPuzleNivel2(int diflvl)
{
    Texture2D fondo = LoadTexture("texturas\\motor2.png");
    srand(time(NULL));

    Vector2 v=GetMousePosition();

    Color casillas;
    casillas.r=255;
    casillas.g=174;
    casillas.b=0;
    casillas.a=255;

    Color operacion;
    operacion.b=19;
    operacion.g=15;
    operacion.r=15;
    operacion.a=255;

    Rectangle cas;
    cas.height=110;
    cas.width=150;
    cas.x=200;
    cas.y=25;

    Rectangle bordecas;
    bordecas.height=120;
    bordecas.width=160;
    bordecas.x=cas.x-5;
    bordecas.y=cas.y-5;
    
    Rectangle op;
    op.height=60;
    op.width=60;
    op.x=0;
    op.y=0;

    Rectangle bordeop;
    bordeop.height=70;
    bordeop.width=70;

    Color naranja;
    naranja.b=0;
    naranja.g=85;
    naranja.r=255;
    naranja.a=255;

    Color colorop;
    colorop.b=6;
    colorop.g=32;
    colorop.r=56;
    colorop.a=255;

    int i,j;
    int random;
    float respuestasx[3];
    float respuestasy[2];
    int fin;
    int maxDraw=1;
    char txt[10];
    Ttab tabla[RENGLONES1][COLUMNAS1];
    int sel[2]={0,0};
    //+ - * /
    char operadores[5][2]={"+","-","*","/","="};
    FILE *fa;
    char t[2];
    int ocultoC=0;
    int predictC=0;

    if(diflvl==0)
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif1\\dif1_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif1\\dif1_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif1\\dif1_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif1\\dif1_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif1\\dif1_5.txt","r");
                break;
        }
    }
    else
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif2\\dif2_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif2\\dif2_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif2\\dif2_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif2\\dif2_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif2\\dif2_5.txt","r");
                break;
        }
    }

        
    if(fa)
    {    
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {
                tabla[i][j].numPredict=-1;
                tabla[i][j].status=1;
                tabla[i][j].elec=0;
                fscanf(fa,"%d %c %c",&tabla[i][j].num,&tabla[i][j].opRight[0],&tabla[i][j].opDown[0]);
                tabla[i][j].opRight[1]='\0';
                tabla[i][j].opDown[1]='\0';
            }
        }
            fscanf(fa," %f %f %f %f %f ",&respuestasy[0],&respuestasy[1],&respuestasx[0],&respuestasx[1],&respuestasx[2]);
            fclose(fa);
    }

    int random2;
    int random3;
    ocultoC=(rand()%3)+1;
    random3=ocultoC;
    while(random3>0)
    {
        random=rand()%2;
        random2=rand()%3;
        if(tabla[random][random2].status==1)
        {
            tabla[random][random2].status=0;
            tabla[random][random2].numPredict=0;
            random3--;
        }
    }
    tabla[0][0].elec=1;
    
    while (!WindowShouldClose())
    {
        v=GetMousePosition();

        //printf("\noculto = %d predictC = %d \n",ocultoC,predictC);
        //termianr minijuego
        if(IsKeyPressed(KEY_ENTER))
        {
            for(i=0;i<RENGLONES1;i++)
            {
                for(j=0;j<COLUMNAS1;j++)
                {
                    if(!tabla[i][j].status)
                    {
                        if(tabla[i][j].num==tabla[i][j].numPredict)
                        {
                            predictC++;
                        }
                    }
                }
            }

            if(predictC==ocultoC)
            {
                goto fin;
            }
            predictC=0;
        }
        //printf("\nx = %f  y = %f\n",v.x,v.y);
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {  
                if(i==sel[0])
                {
                    
                    if(j==sel[1])
                    {
                        tabla[i][j].elec=1;
                    }
                    else
                    {
                        tabla[i][j].elec=0;
                    }
                }
                else
                {
                    tabla[i][j].elec=0;
                }
            }
        }

        //seleccion right left
        if(IsKeyPressed(KEY_RIGHT))
        {
            if(sel[1]<2)
            {
                sel[1]++;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_LEFT))
            {
                if(sel[1]>0)
                {
                    sel[1]--;
                }
            }
        }

        if(IsKeyPressed(KEY_UP))
        {
            if(sel[0]>0)
            {
                sel[0]--;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_DOWN))
            {
                if(sel[0]<1)
                {
                    sel[0]++;
                }
            }
        }

        
        if(IsKeyPressed(KEY_W))
        {
            if(!tabla[sel[0]][sel[1]].status)
            {
                if(tabla[sel[0]][sel[1]].elec)
                {
                    tabla[sel[0]][sel[1]].numPredict++;
                }
            }
        }
        else
        {
            if(IsKeyPressed(KEY_S))
            {
                if(!tabla[sel[0]][sel[1]].status)
                {
                    if(tabla[sel[0]][sel[1]].elec)
                    {
                        tabla[sel[0]][sel[1]].numPredict--;
                    }
                }
            }
        }
        BeginDrawing();
            DrawTexture(fondo,0,0,WHITE);
            
            for(i=0;i<=RENGLONES1;i++)
            {
                for(j=0;j<=COLUMNAS1;j++)
                {
                    bordecas.x=cas.x-5;
                    bordecas.y=cas.y-5;

                    if(i==RENGLONES1 && j==COLUMNAS1)
                    {
                        continue;
                    }
                    if(i==sel[0])
                    {
                        if(j==sel[1])
                        {
                            DrawRectangleRec(bordecas,naranja);
                        }
                        else
                        {
                            DrawRectangleRec(bordecas,BLACK);
                        }
                    }
                    else
                    {
                        DrawRectangleRec(bordecas,BLACK);
                    }
                    DrawRectangleRec(cas,casillas);
                    if(i==0)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[0]);
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==1)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==0)
                        {
                            sprintf(txt,"%.2f",respuestasx[0]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==1)
                        {
                            sprintf(txt,"%.2f",respuestasx[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==2)
                        {
                            sprintf(txt,"%.2f",respuestasx[2]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    
                    if(i<RENGLONES1)
                    {  
                        if(j<COLUMNAS1)
                        {
                            op.x=bordecas.x+bordecas.width+15;
                            op.y=bordecas.y+20;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,BLACK);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opRight,op.x+((op.width-MeasureText(tabla[i][j].opRight,40))/2),op.y+10,40,GRAY);
                            
                            op.x=bordecas.x+bordecas.width/2-op.width/2;
                            op.y=bordecas.y+bordecas.height+15;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,BLACK);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opDown,op.x+((op.width-MeasureText(tabla[i][j].opDown,40))/2),op.y+10,40,GRAY);

                            if(tabla[i][j].status)
                            {
                                itoa(tabla[i][j].num,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,BLACK);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                                }
                            }
                            else
                            {
                                itoa(tabla[i][j].numPredict,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,naranja);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,naranja);
                                }
                            }
                        }
                    }

                    
                    if(maxDraw)
                    {
                        if(i==RENGLONES1)
                        {
                            maxDraw=0;
                            j--;
                            
                        }
                    }
                    cas.x+=100+cas.width;
                }
                
                cas.y+=100+cas.height;
                cas.x=200;
            }
            cas.y=25;
        EndDrawing();
    }
    fin:
        int z=0;
}

void cinemaPuzleNivel3(int diflvl)
{
    Texture2D fondo = LoadTexture("texturas\\motor3.png");
    srand(time(NULL));

    Vector2 v=GetMousePosition();

    Color casillas;
    casillas.r=202;
    casillas.g=210;
    casillas.b=189;
    casillas.a=255;

    Color operacion;
    operacion.b=19;
    operacion.g=15;
    operacion.r=15;
    operacion.a=255;

    Rectangle cas;
    cas.height=110;
    cas.width=150;
    cas.x=200;
    cas.y=25;

    Rectangle bordecas;
    bordecas.height=120;
    bordecas.width=160;
    bordecas.x=cas.x-5;
    bordecas.y=cas.y-5;
    
    Rectangle op;
    op.height=60;
    op.width=60;
    op.x=0;
    op.y=0;

    Rectangle bordeop;
    bordeop.height=70;
    bordeop.width=70;

    Color grisazul;
    grisazul.b=73;
    grisazul.g=97;
    grisazul.r=73;
    grisazul.a=255;
    Color colorop;
    colorop.b=6;
    colorop.g=32;
    colorop.r=56;
    colorop.a=255;

    int i,j;
    int random;
    float respuestasx[3];
    float respuestasy[2];
    int fin;
    int maxDraw=1;
    char txt[10];
    Ttab tabla[RENGLONES1][COLUMNAS1];
    int sel[2]={0,0};
    //+ - * /
    char operadores[5][2]={"+","-","*","/","="};
    FILE *fa;
    char t[2];
    int ocultoC=0;
    int predictC=0;

    if(diflvl==0)
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif1\\dif1_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif1\\dif1_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif1\\dif1_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif1\\dif1_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif1\\dif1_5.txt","r");
                break;
        }
    }
    else
    {
        random=(rand()%5)+1;
        
        switch (random)
        {
            case 1:
                fa=fopen("puzzles\\dif2\\dif2_1.txt","r");
                break;
            case 2:
                fa=fopen("puzzles\\dif2\\dif2_2.txt","r");
                break;
            case 3:
                fa=fopen("puzzles\\dif2\\dif2_3.txt","r");
                break;
            case 4:
                fa=fopen("puzzles\\dif2\\dif2_4.txt","r");
                break;
            case 5:
                fa=fopen("puzzles\\dif2\\dif2_5.txt","r");
                break;
        }
    }
        
    if(fa)
    {    
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {
                tabla[i][j].numPredict=-1;
                tabla[i][j].status=1;
                tabla[i][j].elec=0;
                fscanf(fa,"%d %c %c",&tabla[i][j].num,&tabla[i][j].opRight[0],&tabla[i][j].opDown[0]);
                tabla[i][j].opRight[1]='\0';
                tabla[i][j].opDown[1]='\0';
            }
        }
            fscanf(fa," %f %f %f %f %f ",&respuestasy[0],&respuestasy[1],&respuestasx[0],&respuestasx[1],&respuestasx[2]);
            fclose(fa);
    }

    int random2;
    int random3;
    ocultoC=(rand()%3)+1;
    random3=ocultoC;
    while(random3>0)
    {
        random=rand()%2;
        random2=rand()%3;
        if(tabla[random][random2].status==1)
        {
            tabla[random][random2].status=0;
            tabla[random][random2].numPredict=0;
            random3--;
        }
    }
    tabla[0][0].elec=1;
    
    while (!WindowShouldClose())
    {
        v=GetMousePosition();

        //printf("\noculto = %d predictC = %d \n",ocultoC,predictC);
        //termianr minijuego
        if(IsKeyPressed(KEY_ENTER))
        {
            for(i=0;i<RENGLONES1;i++)
            {
                for(j=0;j<COLUMNAS1;j++)
                {
                    if(!tabla[i][j].status)
                    {
                        if(tabla[i][j].num==tabla[i][j].numPredict)
                        {
                            predictC++;
                        }
                    }
                }
            }

            if(predictC==ocultoC)
            {
                goto fin;
            }
            predictC=0;
        }
        //printf("\nx = %f  y = %f\n",v.x,v.y);
        for(i=0;i<RENGLONES1;i++)
        {
            for(j=0;j<COLUMNAS1;j++)
            {  
                if(i==sel[0])
                {
                    
                    if(j==sel[1])
                    {
                        tabla[i][j].elec=1;
                    }
                    else
                    {
                        tabla[i][j].elec=0;
                    }
                }
                else
                {
                    tabla[i][j].elec=0;
                }
            }
        }

        //seleccion right left
        if(IsKeyPressed(KEY_RIGHT))
        {
            if(sel[1]<2)
            {
                sel[1]++;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_LEFT))
            {
                if(sel[1]>0)
                {
                    sel[1]--;
                }
            }
        }

        if(IsKeyPressed(KEY_UP))
        {
            if(sel[0]>0)
            {
                sel[0]--;
            }
        }
        else
        {
            if(IsKeyPressed(KEY_DOWN))
            {
                if(sel[0]<1)
                {
                    sel[0]++;
                }
            }
        }

        
        if(IsKeyPressed(KEY_W))
        {
            if(!tabla[sel[0]][sel[1]].status)
            {
                if(tabla[sel[0]][sel[1]].elec)
                {
                    tabla[sel[0]][sel[1]].numPredict++;
                }
            }
        }
        else
        {
            if(IsKeyPressed(KEY_S))
            {
                if(!tabla[sel[0]][sel[1]].status)
                {
                    if(tabla[sel[0]][sel[1]].elec)
                    {
                        tabla[sel[0]][sel[1]].numPredict--;
                    }
                }
            }
        }
        BeginDrawing();
            DrawTexture(fondo,0,0,WHITE);
            
            for(i=0;i<=RENGLONES1;i++)
            {
                for(j=0;j<=COLUMNAS1;j++)
                {
                    bordecas.x=cas.x-5;
                    bordecas.y=cas.y-5;

                    if(i==RENGLONES1 && j==COLUMNAS1)
                    {
                        continue;
                    }
                    if(i==sel[0])
                    {
                        if(j==sel[1])
                        {
                            DrawRectangleRec(bordecas,grisazul);
                        }
                        else
                        {
                            DrawRectangleRec(bordecas,BLACK);
                        }
                    }
                    else
                    {
                        DrawRectangleRec(bordecas,BLACK);
                    }
                    DrawRectangleRec(cas,casillas);
                    if(i==0)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[0]);
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==1)
                    {
                        if(j==3)
                        {
                            sprintf(txt,"%.2f",respuestasy[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==0)
                        {
                            sprintf(txt,"%.2f",respuestasx[0]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==1)
                        {
                            sprintf(txt,"%.2f",respuestasx[1]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    if(i==2)
                    {
                        if(j==2)
                        {
                            sprintf(txt,"%.2f",respuestasx[2]);
                            
                            if(strlen(txt)>1)
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                            else
                            {
                                DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                            }
                        }
                    }
                    
                    if(i<RENGLONES1)
                    {  
                        if(j<COLUMNAS1)
                        {
                            op.x=bordecas.x+bordecas.width+15;
                            op.y=bordecas.y+20;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,BLACK);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opRight,op.x+((op.width-MeasureText(tabla[i][j].opRight,40))/2),op.y+10,40,GRAY);
                            
                            op.x=bordecas.x+bordecas.width/2-op.width/2;
                            op.y=bordecas.y+bordecas.height+15;
                            bordeop.x=op.x-5;
                            bordeop.y=op.y-5;
                            DrawRectangleRec(bordeop,BLACK);
                            DrawRectangleRec(op,operacion);
                            DrawText(tabla[i][j].opDown,op.x+((op.width-MeasureText(tabla[i][j].opDown,40))/2),op.y+10,40,GRAY);

                            if(tabla[i][j].status)
                            {
                                itoa(tabla[i][j].num,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,BLACK);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,BLACK);
                                }
                            }
                            else
                            {
                                itoa(tabla[i][j].numPredict,txt,10);
                                if(tabla[i][j].elec)
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,80))/2),cas.y+((cas.height-80)/2),80,grisazul);
                                }
                                else
                                {
                                    DrawText(txt,cas.x+((cas.width-MeasureText(txt,40))/2),cas.y+((cas.height-40)/2),40,grisazul);
                                }
                            }
                        }
                    }

                    
                    if(maxDraw)
                    {
                        if(i==RENGLONES1)
                        {
                            maxDraw=0;
                            j--;
                            
                        }
                    }
                    cas.x+=100+cas.width;
                }
                
                cas.y+=100+cas.height;
                cas.x=200;
            }
            cas.y=25;
        EndDrawing();
    }
    fin:
        int z=0;

}