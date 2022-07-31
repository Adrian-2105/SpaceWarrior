#ifndef GALAXIA_H_INCLUDED
#define GALAXIA_H_INCLUDED

#include "Potenciador.h"

/**
    \file Galaxia.h
    \brief Fichero cabecera que amplia el wrapper Potenciador.

    La biblioteca Galaxia es un wrapper que amplia el wrapper Potenciador, que a su vez usa el wrapper SDL_Wrapper.h y la librer�a SDL 2.0.<br/>
    El TDA Galaxia nos permitir� trabajar con variables del tipo Potenciador de forma m�s compacta y r�pida, agrupando todas estas en una misma variable.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un conjunto de potenciadores (vac�o inicialmente) con Galaxia_Crea()
    - A�adir nuevos potenciadores con Galaxia_InsertaNuevoPotenciador()
    - Actualizar la posici�n de la Galaxia con Galaxia_Mueve y/o detecta colisiones con Galaxia_Colision()
    - Dibujar en sdl_wrapper todas los potenciadores con Galaxia_Dibuja()
    - Liberar de memoria tras finalizar su uso con Galaxia_Libera()
*/

/**
    \brief TDA Galaxia. Permitir� trabajar con grupos de Potenciador simult�neamente.
*/
typedef struct GalaxiaRep * Galaxia;

/**
    \brief Crea una variable de tipo Galaxia.
    \return Galaxia reci�n creada.
*/
Galaxia Galaxia_Crea(int max_Potenciadores);

/**
    \brief Inserta un nuevo Potenciador a Galaxia.
    \param g Galaxia donde se insertar� el nuevo Potenciador.
    \param a Potenciador a insertar.
*/
void Galaxia_InsertaNuevoPotenciador(Galaxia g, Potenciador a);


/**
    \brief Desplaza todos los potenciadores de forma simult�nea a partir de unas velocidades X e Y.
    \param g Galaxia objetivo.
    \param vx Velocidad del eje X.
    \param vy Velocidad del eje Y.
*/
void Galaxia_Mueve(Galaxia g, int vx, int vy);

/**
    \brief Detecta si se produce una colisi�n entre alguno de los potenciadores de la Galaxia, eliminando aquel con el que colisione.
    \param g Galaxia objetivo.
    \param x Coordenada X del elemento a colisionar.
    \param y Coordenada Y del elemento a colisionar.
    \param w Anchura del elemento a colisionar.
    \param h Altura del elemento a colisionar.
    \param *get_type Variable auxiliar que nos servir� para poder obtener el tipo del potenciador con el que se ha detectado colisi�n. Si no interesa, introduzcase "NULL".
*/
int Galaxia_Colision(Galaxia g,int x,int y,int w,int h, int * get_type);

/**
    \brief Dibuja en sdl_wrapper todos los potenciadores que contenga una variable de tipo Galaxia.
    \param g Galaxia objetivo
*/
void Galaxia_Dibuja(Galaxia g);

/**
    \brief Libera una Galaxia de memoria.
    \param g Galaxia objetivo.
*/
void Galaxia_Libera(Galaxia g);

#endif // GALAXIA_H_INCLUDED
