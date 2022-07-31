#include <stdlib.h>

#include "Bala.h"
#include "SDL_Wrapper.h"

struct BalaRep
{
    Imagen i;
    int x, y, w, h, vx, vy;
};

Bala Bala_Crea (Imagen i, int x, int y, int w, int h, int vX, int vY)
{
    Bala b = malloc(sizeof(struct BalaRep));
    b->i = i;
    b->x = x;
    b->y = y;
    b->w = w;
    b->h = h;
    b->vx = vX;
    b->vy = vY;
    return b;
}

void Bala_Libera (Bala b)
{
    free(b);
}

int Bala_Mueve(Bala b)
{
    b->x += b->vx;
    b->y += b->vy;
    return ((b->y+b->h < 0) || (b->x+b->w < 0) || (b->x > SDL_Wrapper_Anchura()));
}

void Bala_CambiaCoordenadas (Bala b, int x, int y)
{
    b->x = x;
    b->y = y;
}

void Bala_CambiaVelocidad (Bala b, int vX, int vY)
{
    b->vx = vX;
    b->vy = vY;
}

void Bala_Dibuja (Bala b)
{
    SDL_Wrapper_DibujaImagen(b->i, b->x, b->y, b->w, b->h);
}

int Bala_GetX (Bala b)
{
    return b->x;
}

int Bala_GetY (Bala b)
{
    return b->y;
}

int Bala_GetW (Bala b)
{
    return b->w;
}

int Bala_GetH (Bala b)
{
    return b->h;
}

int Bala_GetVX (Bala b)
{
    return b->vx;
}

int Bala_GetVY (Bala b)
{
    return b->vy;
}
