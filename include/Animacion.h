#ifndef Animacion_H_INCLUDED
#define Animacion_H_INCLUDED

#include "SDL_Wrapper.h"


/**
   \file Animacion.h
   \brief  Fichero de cabecera que contiene diversas funciones para poder trabajar con animaciones.

    La biblioteca Animacion es un wrapper de la biblioteca SDL 2.0 y el wrapper SDL_Wrapper.h.<br/>
    Su uso est� enfocado en la implementaci�n de animaciones que s�lo tendr�n un efecto visual en el juego, tales como explosiones, humo, chispas, etc.<br/>
    Su estructura de datos, Animacion, nos permitir� trabajar con animaciones individuales.<br/>
    Se recomienda que todas las im�genes para el sprite tengan las mismas dimensiones para as� evitar posibles errores de tama�o.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear una animaci�n con Animacion_Crea()
    - Actualizar el estado actual de la animaci�n y liberarla si se ha terminado con sii ( Animacion_ActualizaEstado() ) entonces Animacion_Libera()
    - Dibujar en pantalla la animaci�n con Animacion_Dibuja()
*/


/**
    \brief TDA Animacion.
*/
typedef struct AnimacionRep * Animacion;

/**
  \brief Crea una Animacion a partir del array de im�genes, sus coordenadas, sus dimensiones y el n�mero m�ximo de estados (o im�genes del sprite) que tendr�.
  \param sprite Array de im�genes de la animaci�n. Deber�n estar ordenadas en el orden en el que se quiere que se reproduzcan [0..n].
  \param x Coordenada X inicial.
  \param y Coordenada Y inicial.
  \param w Anchura de la Animacion.
  \param h Altura de la Animacion.
  \param Nestados N�mero de estados (im�genes) m�ximo que tendr� la Animacion.
  \param delay Frames de espera entre cada frame de la animacion
  \return Animacion reci�n creada.
*/
Animacion Animacion_Crea (Imagen * sprite, int x, int y, int w, int h, int Nestados, int delay);

/**
    \brief Actualiza el estado actual de la Animacion, elimin�ndola si esta ha llegado a su fin.
    \param a Animacion objetivo.
    \return 1 si la Animacion ha llegado a su fin o 0 en caso contrario.
*/
int Animacion_ActualizaEstado (Animacion a);

/**
    \brief Dibuja la Animacion en pantalla, correspondiendo a su estado actual.
    \param a Animacion objetivo.
*/
void Animacion_Dibuja (Animacion a);

/**
    \brief Libera la Animacion de memoria.
    \param a Animacion objetivo.
*/
void Animacion_Libera (Animacion a);

/**
    \brief Devuelve la coordenada X de la Animacion.
    \param a Animacion objetivo.
    \return Coordenada X de la Animacion objetivo.
*/
int Animacion_GetX (Animacion a);

/**
    \brief Devuelve la coordenada Y de la Animacion.
    \param a Animacion objetivo.
    \return Coordenada Y de la Animacion objetivo.
*/
int Animacion_GetY (Animacion a);

/**
    \brief Devuelve la anchura de la Animacion.
    \param a Animacion objetivo.
    \return Anchura de la Animacion objetivo.
*/
int Animacion_GetW (Animacion a);

/**
    \brief Devuelve la altura de la Animacion.
    \param a Animacion objetivo.
    \return Altura de la Animacion objetivo.
*/
int Animacion_GetH (Animacion a);

#endif // Animacion_H_INCLUDED
