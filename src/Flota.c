#include <stdlib.h>
#include <math.h>

#include "Animacion.h"
#include "AnimacionMultiple.h"
#include "Colision.h"
#include "Flota.h"
#include "Enemigo.h"

struct FlotaRep
{
    Enemigo e;
    Flota sig;
};

Flota Flota_Crea()
{
    Flota f = malloc(sizeof(struct FlotaRep));
    f->e = NULL;
    f->sig = NULL;
    return f;
}

void Flota_Libera(Flota f)
{
    while (f->sig != NULL)
    {
        Flota aux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(aux->e);
        free(aux);
    }
    free(f);
}

void Flota_Mueve(Flota f)
{
    while (f->sig != NULL)
    {
        if (Enemigo_Mueve(f->sig->e))
        {
            Flota aux = malloc(sizeof(struct FlotaRep));
            aux = f->sig;
            f->sig = f->sig->sig;
            Enemigo_Libera(aux->e);
            free(aux);
        }
        else
            f = f->sig;
    }
}

void Flota_Dibuja(Flota f, int vMin, int vMax)
{
    for(; f->sig != NULL; f=f->sig)
        Enemigo_Dibuja(f->sig->e, vMin, vMax);
}

void Flota_Dibuja_SinSprite(Flota f)
{
    for(; f->sig != NULL; f=f->sig)
        Enemigo_Dibuja_SinSprite(f->sig->e);
}

void Flota_InsertaNuevoEnemigo(Flota f, Enemigo e)
{
    Flota aux = malloc(sizeof(struct FlotaRep));
    aux->e = e;
    aux->sig = f->sig;
    f->sig = aux;
}

Enemigo Flota_EnemigoMasCercano(Flota f, int x, int y)
{
    Enemigo enem = NULL;
    if (f->sig != NULL)
    {
        float distancia;
        int x_enem = (Enemigo_GetX(f->sig->e)+Enemigo_GetW(f->sig->e)/2);
        int y_enem = (Enemigo_GetY(f->sig->e)+Enemigo_GetH(f->sig->e)/2);
        float distanciaMin = sqrt(pow(x-x_enem, 2) + pow(y-y_enem, 2));
        enem = f->sig->e;
        f = f->sig;
        while (f->sig != NULL)
        {
            x_enem = (Enemigo_GetX(f->sig->e)+Enemigo_GetW(f->sig->e)/2);
            y_enem = (Enemigo_GetY(f->sig->e)+Enemigo_GetH(f->sig->e)/2);
            distancia = sqrt(pow(x-x_enem, 2) + pow(y-y_enem, 2));
            if (distancia < distanciaMin)
            {
                enem = f->sig->e;
                distanciaMin = distancia;
            }
            f = f->sig;
        }
    }
    return enem;
}

Enemigo Flota_EnemigoAleatorio(Flota f)
{
    int n = 0;
    Flota aux = f;
    while (aux->sig != NULL)
    {
        aux = aux->sig;
        n++;
    }
    if (n != 0)
    {
        n = rand()%(n)+1;
        for (int i = 0; i<n; i++)
            f = f->sig;
    }
    return f->e;
}

int Flota_Colision(Flota f, int x, int y, int w, int h)
{
    while ((f->sig != NULL) && (!Colision(Enemigo_GetX(f->sig->e),Enemigo_GetY(f->sig->e),Enemigo_GetW(f->sig->e),Enemigo_GetH(f->sig->e),x,y,w,h)))
        f = f->sig;
    int colision = (f->sig != NULL);
    if (colision)
    {
        Flota aux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(aux->e);
        free(aux);
    }
    return colision;
}

int Flota_ColisionMultiple(Flota f, int x, int y, int w, int h)
{
    int cont = 0;
    while (f->sig != NULL)
    {
        if (Colision(Enemigo_GetX(f->sig->e),Enemigo_GetY(f->sig->e),Enemigo_GetW(f->sig->e),Enemigo_GetH(f->sig->e),x,y,w,h))
        {
            Flota aux = f->sig;
            f->sig = f->sig->sig;
            Enemigo_Libera(aux->e);
            free(aux);
            cont++;
        }
        else
            f = f->sig;
    }
    return cont;
}

int Flota_Colision_ConExplosion(Flota f, AnimacionMultiple am, Imagen * explosion, int Nestados, int x, int y, int w, int h, int delay)
{
    while ((f->sig != NULL) && (!Colision(Enemigo_GetX(f->sig->e),Enemigo_GetY(f->sig->e),Enemigo_GetW(f->sig->e),Enemigo_GetH(f->sig->e),x,y,w,h)))
        f = f->sig;
    int colision = (f->sig != NULL);
    if (colision)
    {
        AnimacionMultiple_InsertaNuevaAnimacion(am, Animacion_Crea(explosion, Enemigo_GetX(f->sig->e), Enemigo_GetY(f->sig->e), Enemigo_GetW(f->sig->e), Enemigo_GetH(f->sig->e), Nestados, delay));
        Flota aux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(aux->e);
        free(aux);
    }
    return colision;
}

void Flota_EnemigoLibera(Flota f, Enemigo e)
{
    while (f->sig != NULL)
    {
        if (f->sig->e == e)
        {
            Flota aux = f->sig;
            f->sig = f->sig->sig;
            Enemigo_Libera(aux->e);
            free(aux);
            return;
        }
        else f = f->sig;
    }
}

int Flota_Vacia(Flota f)
{
    if (f->sig == NULL)
        return 1;
    else
        return 0;
}

Enemigo Flota_EnemigoMejorATiro (Flota f, int x, int y, int w, int h)
{
    Enemigo enem = NULL;
    int distanciaMax = 0;
    while (f->sig != NULL && !distanciaMax)
    {
        if (Enemigo_GetY(f->sig->e)+Enemigo_GetH(f->sig->e) < y)
        {
            distanciaMax = abs(Enemigo_GetX(f->sig->e)+Enemigo_GetW(f->sig->e)/2 - (x+w/2));
            enem = f->sig->e;
        }
        f = f->sig;
    }
    while (f->sig != NULL)
    {
        if (Enemigo_GetY(f->sig->e)+Enemigo_GetH(f->sig->e) < y)
        {
            int distancia = abs(Enemigo_GetX(f->sig->e)+Enemigo_GetW(f->sig->e)/2 - (x+w/2));
            if (distancia < distanciaMax)
            {
                enem = f->sig->e;
                distanciaMax = distancia;
            }
        }
        f = f->sig;
    }
    return enem;
}
