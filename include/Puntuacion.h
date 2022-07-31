#ifndef PUNTUACION_H_INCLUDED
#define PUNTUACION_H_INCLUDED

#include "SDL_Wrapper.h"

/**
    \file Puntuacion.h
    \brief Fichero cabecera con m�ltiples funciones para trabajar con puntuaciones y marcadores dentro del juego.

    La librer�a Puntuacion contiene m�ltiples funciones de utilidad para trabajar tanto con ficheros como con el interfaz gr�fico generado por el wrapper SDL_Wrapper.h.<br/>
    Su uso est� enfocado en trabajar con las puntuaciones y los marcadores del juego, aunque tambi�n se puede usar para imprimir enteros tales como enemigos destruidos, tiempo transcurrido, etc.<br/>
*/

/**
    \brief Lee del fichero objetivo cual es la puntuaci�n m�s alta.
    \param file Path del fichero objetivo (ha de ser de formato .txt).
    \return Devuelve la puntuaci�n m�s alta del fichero o 0 en caso de que est� vac�o/no exista.
*/
int LeerRecord (char* file);

/**
    \brief Lee del fichero objetivo las puntuaciones m�s altas, las cuales guarda en un array de mayor a menor.
    \param file Path del fichero objetivo (ha de ser de formato .txt)
    \param elementos N�mero de puntuaciones que queremos leer del fichero.
    \return Array de enteros de longitud "elementos" con las puntuaciones m�s altas ordenadas de mayor ([0]) a menor ([elementos-1]).
*/
int* LeerTop (char* file, int elementos);

/**
    \brief Guarda en el fichero objetivo la nueva puntuaci�n obtenida. Si el fichero no existe se generar� uno nuevo.
    \param file Path del fichero objetivo (ha de ser de formato .txt)
    \param puntos Puntuaci�n a guardar en el fichero objetivo.
*/
void GuardarPuntuacion (char* file, int puntos);

/**
    \brief Dibuja en pantalla la puntuaci�n con alineaci�n izquierda.
    \param numeros Array de im�genes con todos los n�meros (n[0] para el 0, n[1] para el 1, etc...).
    \param x Coordenada X del primer d�gito.
    \param y Coordenada Y para todos los d�gitos.
    \param wDigito Anchura de cada d�gito.
    \param hDigito Altura de cada d�gito.
    \param longMax Longitud a partir de la cual se escalar� el tama�o del n�mero. P�ngase a 0 si no se desea escalado.
    \param puntos N�mero a escribir en pantalla.
*/
void DibujarPuntuacionIzquierda (Imagen * numeros, int x, int y, int wDigito, int hDigito, int longMax, int puntos);

/**
    \brief Dibuja en pantalla la puntuaci�n con alineaci�n izquierda.
    \param numeros Array de im�genes con todos los n�meros (n[0] para el 0, n[1] para el 1, etc...).
    \param x Coordenada X del extremo derecho del �ltimo d�gito.
    \param y Coordenada Y para todos los d�gitos.
    \param wDigito Anchura de cada d�gito.
    \param hDigito Altura de cada d�gito.
    \param longMax Longitud a partir de la cual se escalar� el tama�o del n�mero. P�ngase a 0 si no se desea escalado.
    \param puntos N�mero a escribir en pantalla.
*/
void DibujarPuntuacionDerecha (Imagen * numeros, int x, int y, int wDigito, int hDigito, int longMax, int puntos);

/**
    \brief Dibuja en pantalla la puntuaci�n con alineaci�n centrada.
    \param numeros Array de im�genes con todos los n�meros (n[0] para el 0, n[1] para el 1, etc...).
    \param x Coordenada X del centro del n�mero.
    \param y Coordenada Y para todos los d�gitos.
    \param wDigito Anchura de cada d�gito.
    \param hDigito Altura de cada d�gito.
    \param puntos N�mero a escribir en pantalla.
*/
void DibujarPuntuacionCentrada (Imagen * numeros, int x, int y, int wDigito, int hDigito, int puntos);

/**
    \brief Dibuja en pantalla un contador. S�lo soporta n�meros de 1 d�gito.
    \param numeros Array de im�genes con todos los n�meros (n[0] para el 0, n[1] para el 1, etc...).
    \param img_X Imagen que debe contener el caracter "X", de tal forma que escriba, por ejemplo, "x5".
    \param x Coordenada X del elemento n[10].
    \param y Coordenada Y para todos los d�gitos.
    \param wDigito Anchura de cada d�gito.
    \param hDigito Altura de cada d�gito.
    \param cont N�mero a escribir en pantalla.
*/
void DibujarContador(Imagen * numeros, Imagen img_X, int x, int y, int wDigito, int hDigito, int cont);

#endif // PUNTUACION_H_INCLUDED
