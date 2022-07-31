#include <stdlib.h>

#include "Potenciador.h"

struct PotenciadorRep
{
    Imagen i;
    int x,y,w,h,tipo;
};

Potenciador Potenciador_Crea(Imagen i, int x, int y, int w, int h, int tipo)
{
    Potenciador a = malloc(sizeof(struct PotenciadorRep));
    a->i = i;
    a->x = x;
    a->y = y;
    a->w = w;
    a->h = h;
    a->tipo = tipo;
    return a;
}

void Potenciador_Dibuja(Potenciador a)
{
    SDL_Wrapper_DibujaImagen(a->i,a->x,a->y,a->w,a->h);
}

void Potenciador_Mueve(Potenciador a, int vx, int vy)
{
    a->x += vx;
    a->y += vy;
}

void Potenciador_Libera(Potenciador a)
{
    free(a);
}

int Potenciador_GetX(Potenciador a)
{
    return a->x;
}

int Potenciador_GetY(Potenciador a)
{
    return a->y;
}

int Potenciador_GetW(Potenciador a)
{
    return a->w;
}

int Potenciador_GetH(Potenciador a)
{
    return a->h;
}

int Potenciador_GetType(Potenciador a)
{
    return a->tipo;
}
