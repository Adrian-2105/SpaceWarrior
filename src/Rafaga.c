#include <stdlib.h>

#include "Animacion.h"
#include "AnimacionMultiple.h"
#include "Bala.h"
#include "Colision.h"
#include "Flota.h"
#include "Rafaga.h"

struct RafagaRep
{
    Bala b;
    Rafaga sig;
};

Rafaga Rafaga_Crea()
{
    Rafaga r = malloc(sizeof(struct RafagaRep));
    r->sig = NULL;
    return r;
}

void Rafaga_Libera(Rafaga r)
{
    while (r->sig != NULL)
    {
        Rafaga aux = r->sig;
        r->sig = r->sig->sig;
        Bala_Libera(aux->b);
        free(aux);
    }
    free(r);
}

void Rafaga_Mueve(Rafaga r)
{
    while (r->sig != NULL)
    {
        if (Bala_Mueve(r->sig->b))
        {
            Rafaga aux = malloc(sizeof(struct RafagaRep));
            aux = r->sig;
            r->sig = r->sig->sig;
            Bala_Libera(aux->b);
            free(aux);
        }
        else
            r = r->sig;
    }
}

void Rafaga_Dibuja(Rafaga r)
{
    for(; r->sig != NULL; r=r->sig)
        Bala_Dibuja(r->sig->b);
}

void Rafaga_InsertaNuevaBala(Rafaga r, Bala b)
{
    Rafaga aux = malloc(sizeof(struct RafagaRep));
    aux->b = b;
    aux->sig = r->sig;
    r->sig = aux;
}

int Rafaga_Colision(Rafaga r, int x, int y, int w, int h)
{
    while ((r->sig != NULL) && (!Colision(Bala_GetX(r->sig->b),Bala_GetY(r->sig->b),Bala_GetW(r->sig->b),Bala_GetH(r->sig->b),x,y,w,h)))
        r = r->sig;
    int colision = (r->sig != NULL);
    if (colision)
    {
        Rafaga aux = r->sig;
        r->sig = r->sig->sig;
        Bala_Libera(aux->b);
        free(aux);
    }
    return colision;
}

int Rafaga_ColisionFlota (Rafaga r, Flota f)
{
    int colision = 0;
    while ((r->sig != NULL) && !colision)
    {
        if (!Flota_Colision(f, Bala_GetX(r->sig->b), Bala_GetY(r->sig->b), Bala_GetW(r->sig->b), Bala_GetH(r->sig->b)))
            r = r->sig;
        else
            colision = 1;
    }
    if (colision)
    {
        Rafaga aux = r->sig;
        r->sig = r->sig->sig;
        Bala_Libera(aux->b);
        free(aux);
    }
    return colision;
}

int Rafaga_ColisionFlota_ConExplosion (Rafaga r, Flota f, AnimacionMultiple am, Imagen * explosion, int Nestados, int delay)
{
    int colision = 0;
    while ((r->sig != NULL) && !colision)
    {
        if (!Flota_Colision_ConExplosion(f, am, explosion, Nestados, Bala_GetX(r->sig->b), Bala_GetY(r->sig->b), Bala_GetW(r->sig->b), Bala_GetH(r->sig->b), delay))
            r = r->sig;
        else
            colision = 1;
    }
    if (colision)
    {
        Rafaga aux = r->sig;
        r->sig = r->sig->sig;
        Bala_Libera(aux->b);
        free(aux);
    }
    return colision;
}
