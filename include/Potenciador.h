#ifndef Potenciador_H_INCLUDED
#define Potenciador_H_INCLUDED

#include "SDL_Wrapper.h"

/**
    \file Potenciador.h
    \brief Fichero cabecera que contiene m�ltiples funciones para poder trabajar con potenciadores (Power UP's).

    La biblioteca Potenciador es un wrapper de la biblioteca SDL 2.0 y el wrapper SDL_Wrapper.h.<br/>
    Su uso est� enfocado en la inclusi�n de distintos tipos de Power UP's, tales como puntos extra, vidas extra, municion extra, etc.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un potenciador con Potenciador_Crea()
    - Actualizar su posici�n mediante Potenciador_Mueve()
    - Dibujar en pantalla el potenciador con Potenciador_Dibuja()
    - Liberar de memoria tras terminar su uso con Potenciador_Libera()
*/


/**
    \brief TDA Potenciador.
*/
typedef struct PotenciadorRep * Potenciador;

/**
    \brief Crea un Potenciador a partir de una Imagen, sus coordenadas, dimensiones, sus velocidades X e Y y un entero que indicar� su tipo.
    \param i Imagen que representar� al Potenciador en pantalla.
    \param x Coordenada X inicial.
    \param y Coordenada Y inicial.
    \param w Anchura del Potenciador.
    \param h Altura del Potenciador.
    \param tipo Tipo/Identificador con el que el usuario podr� diferenciar distintos tipos de potenciadores.
  \return Devuelve la Animacion reci�n creada.
*/
Potenciador Potenciador_Crea(Imagen i, int x, int y, int w, int h, int tipo);

/**
    \brief Desplazar� el Potenciador a partir de las velocidades X e Y introducidas.
    \param a Potenciador objetivo.
    \param vx Cantidad de pixeles en el eje X a desplazar.
    \param vy Cantidad de pixeles en el eje Y a desplazar.
    \return 1 si el Potenciador se ha salido por la parte inferior de la pantalla o 0 en caso contrario.
*/
void Potenciador_Mueve(Potenciador a, int vx, int vy);

/**
    \brief Dibuja el Potenciador en pantalla.
    \param a Potenciador objetivo.
*/
void Potenciador_Dibuja(Potenciador a);

/**
    \brief Libera el potenciador de memoria.
    \param a Potenciador objetivo.
*/
void Potenciador_Libera(Potenciador a);

/**
    \brief Devuelve la coordenada X del Potenciador.
    \param a Potenciador objetivo.
    \return Coordenada X del Potenciador.
*/
int Potenciador_GetX(Potenciador a);

/**
    \brief Devuelve la coordenada Y del Potenciador.
    \param a Potenciador objetivo.
    \return Coordenada Y del Potenciador.
*/
int Potenciador_GetY(Potenciador a);

/**
    \brief Devuelve la anchura del Potenciador.
    \param a Potenciador objetivo.
    \return Anchura del Potenciador.
*/
int Potenciador_GetW(Potenciador a);

/**
    \brief Devuelve la altura del Potenciador.
    \param a Potenciador objetivo.
    \return Altura del Potenciador.
*/
int Potenciador_GetH(Potenciador a);

/**
    \brief Devuelve el tipo del Potenciador (�til si se quieren dar distintos tratamientos dependiendo del tipo que sea).
    \param a Potenciador objetivo.
    \return Tipo del Potenciador.
*/
int Potenciador_GetType(Potenciador a);

#endif // Potenciador_H_INCLUDED
