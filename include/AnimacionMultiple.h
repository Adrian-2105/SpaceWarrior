#ifndef ANIMACIONMULTIPLE_H_INCLUDED
#define ANIMACIONMULTIPLE_H_INCLUDED

#include "Animacion.h"


/**
   \file AnimacionMultiple.h
   \brief  Fichero de cabecera que amplia el wrapper Animacion.

    La biblioteca AnimacionMultiple es un wrapper que amplia el wrapper Animacion, que a su vez usa el wrapper SDL_Wrapper.h y la librer�a SDL 2.0.<br/>
    Su uso est� enfocado en la implementaci�n de animaciones que s�lo tendr�n un efecto visual en el juego, tales como explosiones, humo, chispas, etc.<br/>
    Su estructura de datos, AnimacionMultiple, nos permitir� trabajar con distintas animaciones simultaneamente, pudiendo albergar cada una animaciones y duraciones diferentes.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un conjunto de animaciones (vac�o inicialmente) con AnimacionMultiple_Crea()
    - A�adir nuevas animaciones para que se reproduzcan con AnimacionMultiple_InsertaNuevaAnimacion()
    - Actualizar el estado actual de todas las animaciones con AnimacionMultiple_ActualizaEstado()
    - Dibujar en sdl_wrapper todas las animaciones con AnimacionMultiple_Dibuja()
    - Liberar de memoria tras finalizar su uso con AnimacionMultiple_Libera()
*/


/**
    \brief TDA AnimacionMultiple. Permitir� trabajar con varias animaciones simult�neamente.
*/
typedef struct AnimacionMultipleRep * AnimacionMultiple;

/**
    \brief Crea una variable de tipo AnimacionMultiple.
    \return AnimacionMultiple reci�n creada.
*/
AnimacionMultiple AnimacionMultiple_Crea ();

/**
    \brief Inserta una nueva Animacion a AnimacionMultiple.
    \param am AnimacionMultiple donde se insertar� la nueva Animacion.
    \param a Animacion a insertar.
*/
void AnimacionMultiple_InsertaNuevaAnimacion(AnimacionMultiple am, Animacion a);

/**
    \brief Actualiza el estado actual de todas las animaciones, eliminando las que hayan llegado a su fin.
    \param am AnimacionMultiple objetivo.
*/
void AnimacionMultiple_ActualizaEstado (AnimacionMultiple am);

/**
    \brief Dibuja todas las animaciones que contenga la variable en sdl_wrapper.
    \param am AnimacionMultiple objetivo.
*/
void AnimacionMultiple_Dibuja (AnimacionMultiple am);

/**
    \brief Libera una variable del tipo AnimacionMultiple de memoria.
    \param am AnimacionMultiple objetivo.
*/
void AnimacionMultiple_Libera (AnimacionMultiple am);


#endif // ANIMACIONMULTIPLE_H_INCLUDED
