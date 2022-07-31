#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

#include "SDL_Wrapper.h"

/**
    \file Bala.h
    \brief Fichero cabecera que contiene m�ltiples funciones para poder trabajar con disparos.

    La biblioteca Bala es un wrapper de la biblioteca SDL 2.0 y el wrapper SDL_Wrapper.h.<br/>
    Su uso est� enfocado en la implementaci�n de disparos simples, como puede ser el disparo de una nave.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear una bala con Bala_Crea()
    - Actualiza su posici�n mediante Bala_Mueve() o Bala_CambiaCoordenadas()
    - Dibujar en pantalla la bala con Bala_Dibuja()
    - Liberar de memoria tras terminar su uso con Bala_Libera()
*/

/**
    \brief TDA Bala.
*/
typedef struct BalaRep * Bala;

/**
  \brief Crea una Bala a partir de una Imagen, sus coordenadas, dimensiones y sus velocidades X e Y.
  \param i Imagen que representar� a la Bala en pantalla.
  \param x Coordenada X inicial.
  \param y Coordenada Y inicial.
  \param w Anchura de la Bala.
  \param h Altura de la Bala.
  \param vX Velocidad de la Bala en el eje X.
  \param vY Velocidad de la Bala en el eje Y.
  \return Bala reci�n creada.
*/
Bala Bala_Crea (Imagen i, int x, int y, int w, int h, int vX, int vY);

/**
    \brief Desplazar� la Bala a partir de sus velocidades X e Y.
    \param b Bala objetivo.
    \return 1 si la Bala se ha salido de pantalla o 0 en caso contrario.
*/
int Bala_Mueve (Bala b);

/**
    \brief Cambia las coordenadas X e Y de la Bala.
    \param b Bala objetivo.
    \param x Nueva coordenada X.
    \param y Nueva coordenada Y.
*/
void Bala_CambiaCoordenadas (Bala b, int x, int y);

/**
    \brief Cambia las velocidades de los ejes X e Y de la Bala.
    \param b Bala objetivo.
    \param vX Nueva velocidad X.
    \param vY Nueva velocidad Y.
*/
void Bala_CambiaVelocidad (Bala b, int vX, int vY);

/**
    \brief Dibuja la Bala en pantalla.
    \param b Bala objetivo.
*/
void Bala_Dibuja (Bala b);

/**
    \brief Libera la Bala de memoria.
    \param b Bala objetivo.
*/
void Bala_Libera (Bala b);

/**
    \brief Devuelve la coordenada X de la Bala.
    \param b Bala objetivo.
    \return Coordenada X de la Bala objetivo.
*/
int Bala_GetX (Bala b);

/**
    \brief Devuelve la coordenada Y de la Bala.
    \param b Bala objetivo.
    \return Coordenada Y de la Bala objetivo.
*/
int Bala_GetY (Bala b);

/**
    \brief Devuelve la anchura de la Bala.
    \param b Bala objetivo.
    \return Anchura de la Bala objetivo.
*/
int Bala_GetW (Bala b);

/**
    \brief Devuelve la altura de la Bala.
    \param b Bala objetivo.
    \return Altura de la Bala objetivo.
*/
int Bala_GetH (Bala b);

/**
    \brief Devuelve la velocidad del eje X de la Bala.
    \param b Bala objetivo.
    \return Velocidad del eje X de la Bala objetivo.
*/
int Bala_GetVX (Bala b);

/**
    \brief Devuelve la velocidad del eje Y de la Bala.
    \param b Bala objetivo.
    \return Velocidad del eje Y de la Bala objetivo.
*/
int Bala_GetVY (Bala b);

#endif // BALA_H_INCLUDED
