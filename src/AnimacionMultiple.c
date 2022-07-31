#include <stdlib.h>

#include "Animacion.h"
#include "AnimacionMultiple.h"



struct AnimacionMultipleRep
{
    Animacion a;
    AnimacionMultiple sig;
};

AnimacionMultiple AnimacionMultiple_Crea ()
{
    AnimacionMultiple am = malloc(sizeof(struct AnimacionMultipleRep));
    am->sig = NULL;
    return am;
}

void AnimacionMultiple_Libera (AnimacionMultiple am)
{
    while (am->sig != NULL)
    {
        AnimacionMultiple aux = am->sig;
        am->sig = am->sig->sig;
        Animacion_Libera(aux->a);
        free(aux);
    }
    free(am);
}

void AnimacionMultiple_InsertaNuevaAnimacion(AnimacionMultiple am, Animacion a)
{
    AnimacionMultiple aux = malloc(sizeof(struct AnimacionMultipleRep));
    aux->a = a;
    aux->sig = am->sig;
    am->sig = aux;
}

void AnimacionMultiple_Dibuja (AnimacionMultiple am)
{
    for(; am->sig != NULL; am=am->sig)
        Animacion_Dibuja(am->sig->a);
}

void AnimacionMultiple_ActualizaEstado (AnimacionMultiple am)
{
    while (am->sig != NULL)
    {
        if (Animacion_ActualizaEstado(am->sig->a))
        {
            AnimacionMultiple aux = malloc(sizeof(struct AnimacionMultipleRep));
            aux = am->sig;
            am->sig = am->sig->sig;
            Animacion_Libera(aux->a);
            free(aux);
        }
        else
            am = am->sig;
    }
}
