#include <stdlib.h>

#include "SDL_Wrapper.h"
#include "Personaje.h"


struct PersonajeRep
{
    Imagen * sprite;
    int x,y,w,h,estado;
};

Personaje Personaje_Crea (Imagen * sprite, int x, int y, int w, int h)
{
    Personaje p = malloc(sizeof(struct PersonajeRep));
    p->sprite = sprite;
    p->x = x;
    p->y = y;
    p->w = w;
    p->h = h;
    p->estado = 0;
    return p;
}

void Personaje_Libera (Personaje p)
{
    free(p);
}

void Personaje_Mueve(Personaje p, int vXPersonaje, int vYPersonaje)
{
    p->x += vXPersonaje;
    p->y += vYPersonaje;
    if (p->x<0)
        p->x = 0;
    if (p->y<0)
        p->y = 0;
    if (p->x > SDL_Wrapper_Anchura()-(p->w))
        p->x = SDL_Wrapper_Anchura()-(p->w);
    if (p->y > SDL_Wrapper_Altura()-(p->h))
        p->y = SDL_Wrapper_Altura()-(p->h);
}

void Personaje_Dibuja (Personaje p)
{
    SDL_Wrapper_DibujaImagen(p->sprite[p->estado], p->x, p->y, p->w, p->h);
}

void Personaje_DibujaEnPosicion(Personaje p, int x, int y, int w, int h)
{
    int waux = w;
    int haux = h;
    if (waux==0)
        waux = p->w;
    if (haux==0)
        haux = p->h;
    SDL_Wrapper_DibujaImagen(p->sprite[p->estado], x, y, waux, haux);
}

void Personaje_CambiaEstado (Personaje p, int estado)
{
    p->estado = estado;
}

void Personaje_CambiaCoordenadas (Personaje p, int x, int y)
{
    p->x = x;
    p->y = y;
}

int Personaje_GetX (Personaje p)
{
    return p->x;
}

int Personaje_GetY (Personaje p)
{
    return p->y;
}

int Personaje_GetW (Personaje p)
{
    return p->w;
}

int Personaje_GetH (Personaje p)
{
    return p->h;
}

int Personaje_GetEstado (Personaje p)
{
    return p->estado;
}
