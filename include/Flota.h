#ifndef FLOTA_H_INCLUDED
#define FLOTA_H_INCLUDED

#include "AnimacionMultiple.h"
#include "Enemigo.h"

/**
    \file Flota.h
    \brief Fichero cabecera que amplia el wrapper Enemigo.

    La biblioteca Flota es un wrapper que amplia el wrapper Enemigo, que a su vez usa el wrapper SDL_Wrapper.h y la librer�a SDL 2.0.<br/>
    El TDA Flota nos permitir� trabajar con variables del tipo Enemigo de forma m�s compacta y r�pida, agrupando todos estos en una misma variable.<br/>
    Este wrapper a su vez depender� del wrapper Animacion y Animacion Multiple, necesarios para poder implementar un efecto de explosi�n al colisonar.<br/>
    Al igual que el wrapper Enemigo, este tiene la misma limitaci�n a la hora de dibujar los enemigos en pantalla. Si se quiere incluir una animacion de movimiento
    v�ase la funci�n Enemigo_Dibuja() de Enemigo.h.<br/>

    La estructura principal para la utilizaci�n de este wrapper es:
    - Crear un conjunto de enemigos (vac�o inicialmente) con Flota_Crea()
    - A�adir nuevos enemigos con Flota_InsertaNuevoEnemigo()
    - Actualizar la posici�n de todos los enemigos con Flota_Mueve() y/o detectar colisiones con Flota_Colision() o si se quiere animaci�n Flota_Colision_ConExplosion()
    - Encontrar enemigos espec�ficos con Flota_EnemigoMasCercano(), Flota_EnemigoMejorATiro() o Flota_EnemigoAleatorio() con el fin de implementar disparos o similares
    - Dibujar en pantalla todas las animaciones con Flota_Dibuja() o Flota_Dibuja_SinSprite()
    - Liberar de memoria tras finalizar su uso con Flota_Libera()
*/

/**
    \brief TDA Flota. Permite trabajar con grupos de Enemigo simult�neamente.
*/
typedef struct FlotaRep * Flota;

/**
    \brief Crea una variable de tipo Flota.
    \return Flota reci�n creada.
*/
Flota Flota_Crea();

/**
    \brief Inserta un nuevo Enemigo a Flota.
    \param f Flota donde se insertar� el nuevo Enemigo.
    \param e Enemigo a insertar.
*/
void Flota_InsertaNuevoEnemigo(Flota f, Enemigo e);

/**
    \brief Desplaza todos los enemigos que contenga una variable de tipo Flota a partir de sus velocidades X e Y.<br/>
           Los enemigos rebotar�n en las paredes y ser�n eliminados si salen por la parte inferior de la pantalla.
    \param f Flota objetivo.
*/
void Flota_Mueve(Flota f);

/**
    \brief Dibuja en pantalla todos los enemigos contenidos en una variable de tipo Flota. �nicamente compatible si se va a trabajar con el mismo modelo expuesto en Enemigo.h (v�ase para informaci�n detallada).
    \param f Flota objetivo.
    \param vMin Velocidad m�nima de giro a la que cambiar el sprite.
    \param vMax Velocidad m�xima de giro a la que cambiar el sprite.
*/
void Flota_Dibuja(Flota f, int vMin, int vMax);

/**
    \brief Dibuja en pantalla todos los enemigos, en su estado neutro (sprite[0]), contenidos en una variable de tipo Flota. Para m�s informaci�n v�ase Enemigo.h.
    \param f Flota objetivo.
*/
void Flota_Dibuja_SinSprite(Flota f);

/**
    \brief Indica si una variable de tipo Flota contiene enemigos o est� vac�a.
    \param f Flota objetivo.
    \return 1 si la Flota est� vac�a o 0 en caso contrario.
*/
int Flota_Vacia(Flota f);

/**
    \brief Busca y devuelve el Enemigo contenido en la Flota m�s cercano a una coordenada XY.
    \param f Flota objetivo.
    \param x Coordenada X del objeto.
    \param y Coordenada Y del objeto.
    \return El Enemigo m�s cercano a la coordenada XY introducida o NULL si la Flota est� vac�a.
*/
Enemigo Flota_EnemigoMasCercano(Flota f, int x, int y);

/**
    \brief Busca y devuelve un Enemigo contenido en la Flota de forma aleatoria.
    \param f Flota objetivo.
    \return Un Enemigo aleatorio o NULL si la Flota est� vac�a.
*/
Enemigo Flota_EnemigoAleatorio(Flota f);

/**
    \brief Busca y devuelve el Enemigo contenido en la Flota que est� mejor posicionado para disparar, es decir,
           devolver� el Enemigo que se encuentre m�s pr�ximo y situado por encima de las coordenadas y dimensiones introducidas.
    \param f Flota objetivo.
    \param x Coordenada X del objeto.
    \param y Coordenada Y del objeto.
    \param w Anchura del objeto.
    \param h Altura del objeto.
    \return El Enemigo mejor posicionado, NULL si no hay ning�n en buena posici�n o NULL si la Flota est� vac�a.
*/
Enemigo Flota_EnemigoMejorATiro (Flota f, int x, int y, int w, int h);

/**
    \brief Detecta si ha habido colisi�n entre alguno de los enemigos contenidos en la Flota con un objeto a partir de sus coordenadas y dimensiones,
           eliminando �nicamente el primer enemigo que haya colisionado.
    \param f Flota objetivo.
    \param x Coordenada X del objeto a colisionar.
    \param y Coordenada Y del objeto a colisionar.
    \param w Anchura del objeto a colisionar.
    \param h Altura del objeto a colisionar.
    \return 1 si ha habido una colisi�n o 0 en caso contrario.
*/
int Flota_Colision(Flota f, int x, int y, int w, int h);

/**
    \brief Detecta si ha habido colisi�n entre alguno de los enemigos contenidos en la Flota con un objeto a partir de sus coordenadas y dimensiones,
           eliminando todos los enemigos que hayan colisionado con el mismo objeto.
    \param f Flota objetivo.
    \param x Coordenada X del objeto a colisionar.
    \param y Coordenada Y del objeto a colisionar.
    \param w Anchura del objeto a colisionar.
    \param h Altura del objeto a colisionar.
    \return Un entero n correspondiente al n�mero de enemigos que hayan colisionado.
*/
int Flota_ColisionMultiple(Flota f, int x, int y, int w, int h);

/**
    \brief Detecta si ha habido colisi�n entre alguno de los enemigos contenidos en la Flota con un objeto a partir de sus coordenadas y dimensiones,
           eliminando �nicamente el primer enemigo que haya colisionado e insertando la Animacion de explosi�n introducida,
           que tomar� como coordenadas y dimensiones las del Enemigi colisionado.
    \param f Flota objetivo.
    \param am AnimacionMultiple donde se insertar� la nueva Animacion.
    \param explosion Array de im�genes con el sprite de la explosion, ordenadas de [0..Nestados-1].
    \param Nestados N�mero de estados (im�genes) que contendr� el sprite de la explosion.
    \param x Coordenada X del objeto a colisionar.
    \param y Coordenada Y del objeto a colisionar.
    \param w Anchura del objeto a colisionar.
    \param h Altura del objeto a colisionar.
    \param delay Frames de espera entre cada estado de la Animacion de la explosi�n.
    \return 1 si ha habido una colisi�n o 0 en caso contrario.
*/
int Flota_Colision_ConExplosion(Flota f, AnimacionMultiple am, Imagen * explosion, int Nestados, int x, int y, int w, int h, int delay);

/**
    \brief Elimina el Enemigo introducido de la Flota.
    \param f Flota objetivo.
    \param e Enemigo objetivo
*/
void Flota_EnemigoLibera(Flota f, Enemigo e);

/**
    \brief Libera una Flota de memoria, incluidos los enemigos que contenga.
    \param f Flota objetivo.
*/
void Flota_Libera(Flota f);

#endif // FLOTA_H_INCLUDED
