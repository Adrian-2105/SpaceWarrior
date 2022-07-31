#ifndef RAFAGA_H_INCLUDED
#define RAFAGA_H_INCLUDED

#include "Flota.h"


/**
    \file Rafaga.h
    \brief Fichero cabecera que amplia el wrapper Bala.

    La biblioteca Rafaga es un wrapper que amplia el wrapper Bala, que a su vez usa el wrapper SDL_Wrapper.h y la librer�a SDL 2.0.<br/>
    El TDA Rafaga nos permitir� trabajar con variables del tipo Bala de forma m�s compacta y r�pida, agrupando todas estas en una misma variable.<br/>
    Este wrapper a su vez depender� del wrapper Flota, Animacion y Animacion Multiple, necesarios para poder implementar las dos �ltimas funciones.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un conjunto de balas (vac�o inicialmente) con Rafaga_Crea()
    - A�adir nuevas balas con Rafaga_InsertaNuevaBala()
    - Actualizar la posici�n de todas las balas con Rafaga_Mueve() y/o detectar colisiones con Rafaga_Colision(), Rafaga_ColisionFlota() o, si se quiere con animaci�n, Rafaga_ColisionFlota_ConExplosion().<br/>
    - Dibujar en sdl_wrapper todas las animaciones con Rafaga_Dibuja()
    - Liberar de memoria tras finalizar su uso con Rafaga_Libera()
*/

/**
    \brief TDA R�faga. Permite trabajar con grupos de Bala simult�neamente.
*/
typedef struct RafagaRep * Rafaga;

/**
    \brief Crea una variable de tipo Rafaga.
    \return Rafaga reci�n creada.
*/
Rafaga Rafaga_Crea();

/**
    \brief Inserta una nueva Bala a Rafaga.
    \param r Rafaga donde se insertar� la nueva Bala.
    \param b Bala a insertar.
*/
void Rafaga_InsertaNuevaBala (Rafaga r, Bala b);

/**
    \brief Desplaza todas las balas que contenga una variable de tipo Rafaga a partir de sus velocidades X e Y, elimin�ndolas si estas se han salido de sdl_wrapper.
    \param r Rafaga objetivo
*/
void Rafaga_Mueve (Rafaga r);

/**
    \brief Detecta si ha habido colisi�n entre alguna de las balas contenida en la Rafaga con un objeto a partir de sus coordenadas y dimensiones. La Bala que colisione ser� eliminada.
    \param r Rafaga objetivo.
    \param x Coordenada X del objeto a colisionar.
    \param y Coordenada Y del objeto a colisionar.
    \param w Anchura del objeto a colisionar.
    \param h Altura del objeto a colisionar.
    \return 1 si ha habido una colisi�n o 0 en caso contrario.
*/
int Rafaga_Colision (Rafaga r, int x, int y, int w, int h);

/**
    \brief Detecta si ha habido colisi�n entre alguna de las balas con la Flota. En ese caso, eliminar� tanto la Bala contenida en la Rafaga como el Enemigo contenido en la Flota.
    \param r Rafaga objetivo.
    \param f Flota objetivo.
    \return 1 si ha habido una colisi�n o 0 en caso contrario.
*/
int Rafaga_ColisionFlota(Rafaga r, Flota f);

/**
    \brief Detecta si ha habido colisi�n entre alguna de las balas con la Flota, insertando una animaci�n en ese caso. Tambi�n eliminar� tanto la Bala contenida en la Rafaga como el Enemigo contenido en la Flota.
    \param r Rafaga objetivo.
    \param f Flota objetivo.
    \param am AnimacionMultiple donde se insertar� la nueva Animacion.
    \param explosion Array de im�genes con el sprite de la explosion, ordenadas de [0..Nestados-1].
    \param Nestados N�mero de estados (im�genes) que contendr� el sprite de la explosion.
    \param delay Frames de espera entre cada estado de la Animacion de la explosi�n.
    \return 1 si ha habido una colisi�n o 0 en caso contrario.
*/
int Rafaga_ColisionFlota_ConExplosion (Rafaga r, Flota f, AnimacionMultiple am, Imagen * explosion, int Nestados, int delay);

/**
    \brief Dibuja en sdl_wrapper todas las balas que contenga una variable de tipo Rafaga.
    \param r Rafaga objetivo
*/
void Rafaga_Dibuja (Rafaga r);

/**
    \brief Libera una Rafaga de memoria, incluidas las balas que contenga.
    \param r Rafaga objetivo.
*/
void Rafaga_Libera (Rafaga r);

#endif // RAFAGA_H_INCLUDED
