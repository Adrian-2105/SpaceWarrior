#include <stdlib.h>

#include "Animacion.h"
#include "SDL_Wrapper.h"

struct AnimacionRep
{
    Imagen * sprite;
    int x, y, w, h, Nestados, estado, delay, delay_actual;
};

Animacion Animacion_Crea (Imagen * sprite, int x, int y, int w, int h, int Nestados, int delay)
{
    Animacion a = malloc(sizeof(struct AnimacionRep));
    a->sprite = sprite;
    a->x = x;
    a->y = y;
    a->w = w;
    a->h = h;
    a->Nestados = Nestados-1;
    a->estado = 0;
    a->delay = delay;
    a->delay_actual = 0;
    return a;
}

void Animacion_Libera (Animacion a)
{
    free(a);
}

void Animacion_Dibuja (Animacion a)
{
    SDL_Wrapper_DibujaImagen(a->sprite[a->estado], a->x, a->y, a->w, a->h);
}

int Animacion_ActualizaEstado (Animacion a)
{
    a->delay_actual++;
    if (a->delay_actual >= a->delay)
    {
        a->delay_actual = 0;
        a->estado++;
        if (a->estado > a->Nestados)
            return 1;
    }

    return 0;
}

int Animacion_GetX (Animacion a)
{
    return a->x;
}

int Animacion_GetY (Animacion a)
{
    return a->y;
}

int Animacion_GetW (Animacion a)
{
    return a->w;
}

int Animacion_GetH (Animacion a)
{
    return a->h;
}
