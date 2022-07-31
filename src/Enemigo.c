#include <stdlib.h>

#include "Enemigo.h"
#include "SDL_Wrapper.h"

struct EnemigoRep
{
    Imagen * sprite;
    int x,y,w,h,vx,vy;
};

Enemigo Enemigo_Crea (Imagen * sprite, int x, int y, int w, int h, int vx, int vy)
{
    Enemigo e = malloc(sizeof(struct EnemigoRep));
    e->sprite = sprite;
    e->x = x;
    e->y = y;
    e->w = w;
    e->h = h;
    if (e->vx < 0)
        e->vx = vx/2 - rand()%(vx+2);
    else
        e->vx = vx/2 + rand()%(vx+2);
    e->vy = vy/2 + rand()%(vy+2);
    return e;
}

void Enemigo_Libera (Enemigo e)
{
    free(e);
}

int Enemigo_Mueve(Enemigo e)
{
    e->x += e->vx;
    e->y += e->vy;
    if (e->x < 0)
        e->vx *= -1;
    if (e->x > SDL_Wrapper_Anchura()-Enemigo_GetH(e))
        e->vx *= -1;
    return (e->y > SDL_Wrapper_Altura());
}

void Enemigo_Dibuja (Enemigo e, int vMin, int vMax)
{
    int aux = 0;
    if (e->vx > vMin)
    {
        if (e->vx > vMax)
            aux = 4;
        else aux = 3;
    }
    else if (e->vx < -vMin)
    {
        if (e->vx < -vMax)
            aux = 2;
        else aux = 1;
    }
    SDL_Wrapper_DibujaImagen(e->sprite[aux], e->x, e->y, e->w, e->h);
}

void Enemigo_Dibuja_SinSprite (Enemigo e)
{
    SDL_Wrapper_DibujaImagen(e->sprite[0], e->x, e->y, e->w, e->h);
}

void Enemigo_CambiaCoordenadas (Enemigo e, int x, int y)
{
    e->x = x;
    e->y = y;
}

int Enemigo_GetX (Enemigo e)
{
    return e->x;
}

int Enemigo_GetY (Enemigo e)
{
    return e->y;
}

int Enemigo_GetW (Enemigo e)
{
    return e->w;
}

int Enemigo_GetH (Enemigo e)
{
    return e->h;
}
