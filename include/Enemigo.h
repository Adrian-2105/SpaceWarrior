#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include "SDL_Wrapper.h"

/**
    \file Enemigo.h
    \brief Fichero cabecera para trabajar con enemigos b�sicos.

    La biblioteca Enemigo es un wrapper de la biblioteca SDL 2.0 y el wrapper SDL_Wrapper.h.<br/>
    Su uso est� enfocado en la implementaci�n de enemigos, con soporte para animaciones (aunque este es bastante limitado).<br/>
    Se podr� trabajar hasta con un m�ximo de 5 im�genes para el sprite y bajo las condiciones expuestas en Enemigo_Dibuja(). Si no se desea animacion, utilicese Enemigo_Dibuja_SinSprite().
    Estos enemigos estar�n limitados lateralmente para que no puedan salirse de pantalla, rebotando en los bordes en ese caso.<br/>
    Se especifica m�s acerca de las limitaciones de esta biblioteca en sus funciones correspondientes.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear una bala con Enemigo_Crea()
    - Actualiza su posici�n mediante Enemigo_Mueve() o Enemigo_CambiaCoordenadas()
    - Dibujar en pantalla el Enemigo con Enemigo_Dibuja() o Enemigo_Dibuja_SinSprite()
    - Liberar de memoria tras terminar su uso con Enemigo_Libera()
*/

/**
    \brief TDA Enemigo.
*/
typedef struct EnemigoRep * Enemigo;

/**
  \brief Crea un Enemigo a partir del array de im�genes, sus coordenadas y dimensiones.
  \param sprite Array de im�genes del enemigo. Esta va variando seg�n la velocidad del eje X.<br/>
  La imagen sprite[0] corresponder� al estado neutro, sin girar; sprite[1/2] al estado giro_izquierda; y sprite[3/4] al giro_derecha.<br/>
  Es por esto la gran limitaci�n de esta librer�a para su exportabilidad a otros proyectos.<br/>
  Si se desea trabajar con una imagen est�tica, incluyase �nicamente un array en el que solo est� el estado neutro (sprite[0]) y h�gase uso de la funci�n Enemigo_Dibuja_SinSprite().
  (v�ase Enemigo_Dibuja())
  \param x Coordenada X inicial del enemigo.
  \param y Coordenada Y inicial del enemigo.
  \param w Anchura del enemigo.
  \param h Altura del enemigo.
  \param vx Velocidad del eje X del enemigo.
  \param vy Velocidad del eje Y del enemigo.
  \return Enemigo reci�n creado.
*/
Enemigo Enemigo_Crea (Imagen * sprite, int x, int y, int w, int h, int vx, int vy);

/**
    \brief Desplaza al Enemigo seg�n sus velocidades X e Y. No permite que se salga por lo laterales de la pantalla, haciendo que rebote en esta.
    \param e Enemigo objetivo.
*/
int Enemigo_Mueve(Enemigo e);

/**
    \brief Cambia las coordenadas del Enemigo.
    \param e Enemigo objetivo.
    \param x Nueva coordenada X.
    \param y Nueva coordenada Y.
*/
void Enemigo_CambiaCoordenadas (Enemigo e, int x, int y);

/**
    \brief Dibuja al Enemigo en pantalla bajo unas ciertas condiciones: <br/>
    - Giro leve: cuando el valor absoluto de la velocidad del eje X del Enemigo supere la vMin introducida por el usuario su imagen cambiar� a sprite[1] si su velocidad X es negativa (va hacia la izquierda) o a sprite[2] si su velocidad X es positiva (va hacia la derecha).<br/>
    - Giro brusco: cuando el valor absoluto de la velocidad del eje X del Enemigo supere la vMax introducida por el usuario su imagen cambiar� a sprite[2] si su velocidad X es negativa (va hacia la izquierda) o a sprite[4] si su velocidad X es positiva (va hacia la derecha).<br/>
    - Sin giro: si no se encuentra en estado de giro se dibujar� en su estado neutro (sprite[0]).
    \pre vMin y vMax han de ser mayores que 0.
    \param e Enemigo objetivo.
    \param vMin Velocidad m�nima de giro a la que se producir� el cambio de sprite.
    \param vMax Velocidad m�xima de giro a la que se producir� el cambio de sprite.
*/
void Enemigo_Dibuja (Enemigo e, int vMin, int vMax);

/**
    \brief Dibuja al Personaje, en su estado neutro (sprite[0]), en pantalla.
    \param e Enemigo objetivo.
*/
void Enemigo_Dibuja_SinSprite (Enemigo e);

/**
    \brief Libera el Enemigo de memoria.
    \param e Enemigo objetivo.
*/
void Enemigo_Libera (Enemigo e);

/**
    \brief Devuelve la coordenada X del Enemigo.
    \param e Enemigo objetivo.
    \return Coordenada X del Enemigo.
*/
int Enemigo_GetX (Enemigo e);

/**
    \brief Devuelve la coordenada Y del Enemigo.
    \param e Enemigo objetivo.
    \return Coordenada Y del Enemigo.
*/
int Enemigo_GetY (Enemigo e);

/**
    \brief Devuelve la anchura del Enemigo.
    \param e Enemigo objetivo.
    \return Anchura del Enemigo.
*/
int Enemigo_GetW (Enemigo e);

/**
    \brief Devuelve la altura del Enemigo.
    \param e Enemigo objetivo.
    \return Altura del Enemigo.
*/
int Enemigo_GetH (Enemigo e);

#endif // ENEMIGO_H_INCLUDED
