#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "Puntuacion.h"
#include "SDL_Wrapper.h"

int LeerRecord (char* file)
{
    int puntosMax = 0;
    int dato;
    FILE * f = fopen(file,"r");
    if (f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%d",&dato);
            if (dato>puntosMax)
                puntosMax = dato;
        }
        fclose(f);
    }
    return(puntosMax);
}

int LeerRecordMenor (char* file, int max)
{
    int puntosMax = 0;
    int dato;
    FILE * f = fopen(file,"r");
    if (f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%d",&dato);
            if (dato>puntosMax && dato<max)
                puntosMax = dato;
        }
        fclose(f);
    }
    return(puntosMax);
}

int* LeerTop (char* file, int elementos)
{
    int* top = malloc(sizeof(int)*(elementos+1));
    top[0] = LeerRecord(file);
    for (int i = 1; i<elementos; i++)
    {
        top[i] = LeerRecordMenor(file,top[i-1]);
    }
    return top;
}

void GuardarPuntuacion (char* file, int puntos)
{
    FILE * f = fopen(file,"a");
    fprintf(f,"%d\n",puntos);
    fclose(f);
}

void DibujarPuntuacionIzquierda (Imagen * numeros, int x, int y, int wDigito, int hDigito, int longMax, int puntos)
{
    int digito;
    int ndigitos = 1;
    int aux = puntos;
    while ((aux/10) > 0)
    {
        aux = aux / 10;
        ndigitos++;
    }
    if (longMax && (ndigitos*wDigito > longMax))
    {
        aux = ((ndigitos*wDigito) / longMax) +1;
        for (int i=1; i<aux; i++)
        {
            y += hDigito;
            wDigito = 3*wDigito/4;
            hDigito = 3*hDigito/4;
        }
        y -= hDigito;
    }
    for (int i=0; i<ndigitos; i++)
    {
        digito = puntos % 10;
        puntos = puntos / 10;
        SDL_Wrapper_DibujaImagen(numeros[digito],x+(ndigitos-i-1)*wDigito,y,wDigito,hDigito);
    }
}

void DibujarPuntuacionDerecha (Imagen * numeros, int x, int y, int wDigito, int hDigito, int longMax, int puntos) // lo dibuja del rev�s, arreglar
{
    int digito;
    x -= wDigito;
    int xaux = x;
    int ndigitos = 1;
    int aux = puntos;
    while ((aux/10) > 0)
    {
        aux = aux / 10;
        ndigitos++;
    }
    if (longMax && (ndigitos*wDigito > longMax))
    {
        aux = ((ndigitos*wDigito) / longMax) +1;
        for (int i=1; i<aux; i++)
        {
            y += hDigito;
            wDigito = 3*wDigito/4;
            hDigito = 3*hDigito/4;
            x += wDigito;
        }
        y -= hDigito;
    }
    if (xaux != x)
        x -= wDigito;
    for (int i=0; i<ndigitos; i++)
    {
        digito = puntos % 10;
        puntos = puntos / 10;
        SDL_Wrapper_DibujaImagen(numeros[digito],x-i*wDigito,y,wDigito,hDigito);
    }
}

void DibujarPuntuacionCentrada (Imagen * numeros, int x, int y, int wDigito, int hDigito, int puntos)
{
    int digito;
    int ndigitos = 1;
    int aux = puntos;
    while ((aux/10) > 0)
    {
        aux = aux / 10;
        ndigitos++;
    }
    int posx = x;
    for (int i = 0 ; i < ndigitos ; i++)
    {
        posx = posx + wDigito/2 ;
    }
    for (int i=0; i<ndigitos; i++)
    {
        digito = puntos % 10;
        puntos = puntos / 10;
        posx = posx - wDigito;
        SDL_Wrapper_DibujaImagen(numeros[digito],posx,y,wDigito,hDigito);
    }
}

void DibujarContador(Imagen * numeros, Imagen img_X, int x, int y, int wDigito, int hDigito, int cont)
{
    SDL_Wrapper_DibujaImagen(img_X,x,y+hDigito/2,wDigito/2,hDigito/2);
    SDL_Wrapper_DibujaImagen(numeros[cont],x+wDigito/2,y,wDigito,hDigito);
}




