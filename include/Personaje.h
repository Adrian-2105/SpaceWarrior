#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include "SDL_Wrapper.h"

/**
    \file Personaje.h
    \brief Fichero de cabecera que contiene m�ltiples funciones para trabajar con un Personaje (o nave).

    La biblioteca Personaje es un wrapper de la biblioteca SDL 2.0 y el wrapper SDL_Wrapper.h.<br/>
    Esta biblioteca est� pensada para la implementaci�n de una nave/personaje con soporte para animaciones, aunque limitado al tama�o de la pantalla.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un Personaje con Personaje_Crea()
    - Actualiza su posici�n mediante Personaje_Mueve() o Personaje_CambiaCoordenadas() y/o su Imagen mediante Personaje_CambiaImagen() o Personaje_CambiaEstado()
    - Dibujar en pantalla el Personaje con Personaje_Dibuja()
    - Liberar de memoria tras terminar su uso con Personaje_Libera()
*/

/**
    \brief TDA Personaje.
 */
typedef struct PersonajeRep * Personaje;

/**
  \brief Crea un Personaje a partir del array de im�genes, sus coordenadas y dimensiones.
  \param sprite Array de im�genes de la nave. El estado est� ligado a los elementos del array con las im�genes.
  \param x Coordenada X inicial de la nave.
  \param y Coordenada Y inicial de la nave.
  \param w Anchura de la nave.
  \param h Altura de la nave.
  \return Personaje reci�n creado, con estado inicial = 0.
*/
Personaje Personaje_Crea (Imagen * sprite, int x, int y, int w, int h);

/**
    \brief Desplaza al Personaje sum�ndole las velocidades VX y VY introducidas. No permite que se salga de pantalla.
    \param p Personaje objetivo.
    \param vx Cantidad de pixeles a desplazar en el eje X.
    \param vy Cantidad de pixeles a desplazar en el eje Y.
*/
void Personaje_Mueve (Personaje p, int vx, int vy);

/**
    \brief Cambia el estado del Personaje. Esta funci�n a su vez cambiar� la imagen seg�n "sprite[estado]", t�ngase en cuenta a la hora de introducir el array.
    \pre El estado introducido no puede ser mayor al del n�mero de im�genes del sprite.
    \param p Personaje objetivo.
    \param estado Nuevo estado.
*/
void Personaje_CambiaEstado(Personaje p, int estado);

/**
    \brief Cambia la imagen actual del Personaje introducido.
    \param p Personaje al que se le quiere cambiar la imagen.
    \param img Imagen por la que se va a sustituir.
*/
void Personaje_CambiaImagen (Personaje p, Imagen img);

/**
    \brief Cambia las coordenadas del Personaje.
    \param p Personaje objetivo.
    \param x Nueva coordenada X.
    \param y Nueva coordenada Y.
*/
void Personaje_CambiaCoordenadas (Personaje p, int x, int y);

/**
    \brief Dibuja al Personaje, en su estado actual, en pantalla.
    \param p Personaje objetivo.
*/
void Personaje_Dibuja (Personaje p);

/**
    \brief Dibuja al Personaje *en su estado actual* en una posici�n diferente y con tama�o distinto.
    \param p Personaje objetivo.
    \param x Coordenada X donde se quiere dibujar.
    \param y Coordenada Y donde se quiere dibujar.
    \param w Anchura del personaje. P�ngase a 0 si se quiere conservar la original.
    \param h Altura del personaje. P�ngase a 0 si se quiere conservar la original.
*/
void Personaje_DibujaEnPosicion (Personaje p, int x, int y, int w, int h);

/**
    \brief Libera el Personaje de memoria.
    \param p Personaje objetivo.
*/
void Personaje_Libera (Personaje p);

/**
    \brief Devuelve la coordenada X del Personaje.
    \param p Personaje objetivo.
    \return Coordenada X del Personaje.
*/
int Personaje_GetX (Personaje p);

/**
    \brief Devuelve la coordenada Y del Personaje.
    \param p Personaje objetivo.
    \return Coordenada Y del Personaje.
*/
int Personaje_GetY (Personaje p);

/**
    \brief Devuelve la anchura del Personaje.
    \param p Personaje objetivo.
    \return Anchura del Personaje.
*/
int Personaje_GetW (Personaje p);

/**
    \brief Devuelve la altura del Personaje.
    \param p Personaje objetivo.
    \return Altura del Personaje.
*/
int Personaje_GetH (Personaje p);

/**
    \brief Devuelve el estado actual del Personaje.
    \param p Personaje objetivo.
    \return Estado actual del Personaje.
*/
int Personaje_GetEstado (Personaje p);

#endif // PERSONAJE_H_INCLUDED
