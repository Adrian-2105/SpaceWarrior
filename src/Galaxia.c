#include <stdlib.h>

#include "Colision.h"
#include "Galaxia.h"
#include "SDL_Wrapper.h"

struct GalaxiaRep
{
    Potenciador * a;
    int max, n;
};

Galaxia Galaxia_Crea(int max_Potenciadores)
{
    Galaxia g = malloc(sizeof(struct GalaxiaRep));
    g->a = malloc(sizeof(Potenciador)*max_Potenciadores);
    g->max = max_Potenciadores;
    g->n = 0;
    return g;
}

void Galaxia_Libera(Galaxia g)
{
    for (int i=0; i<g->n; i++)
        Potenciador_Libera(g->a[i]);
    free(g->a);
    free(g);
}

void Galaxia_InsertaNuevoPotenciador(Galaxia g, Potenciador a)
{
    if (g->n < g->max)
    {
        g->a[g->n] = a;
        g->n++;
    }
}

void Galaxia_Dibuja(Galaxia g)
{
    for (int i=0; i< g->n; i++)
        Potenciador_Dibuja(g->a[i]);
}

void Galaxia_Mueve(Galaxia g, int vx, int vy)
{
    for (int i=0; i< g->n; i++)
    {
        Potenciador_Mueve(g->a[i], vx, vy);
        if (Potenciador_GetY(g->a[i]) > SDL_Wrapper_Altura())
        {
            Potenciador_Libera(g->a[i]);
            g->a[i] = g->a[g->n-1];
            g->n--;
        }
    }
}

int Galaxia_Colision(Galaxia g, int x, int y, int w, int h, int * get_type)
{
    int i= 0;
    while ((i < g->n)&&(!Colision(Potenciador_GetX(g->a[i]), Potenciador_GetY(g->a[i]), Potenciador_GetW(g->a[i]), Potenciador_GetH(g->a[i]), x, y, w, h)))
        i++;
    int colision = (i < g->n);
    if (colision)
    {
        *get_type = Potenciador_GetType(g->a[i]);
        Potenciador_Libera(g->a[i]);
        g->a[i] = g->a[g->n-1];
        g->n--;
    }
    return colision;
}
