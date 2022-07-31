#ifndef COLISION_H_INCLUDED
#define COLISION_H_INCLUDED


/**
   \file Colision.h
   \brief  Fichero de cabecera con una función para detectar colisiones.
*/

/**
    \brief Permite detectar si dos elementos bidimensionales han colisonado a partir de sus coordenadas y dimensiones.
    \param x1 Coordenada X del primer elemento.
    \param y1 Coordenada Y del primer elemento.
    \param w1 Anchura del primer elemento.
    \param h1 Altura del primer elemento.
    \param x2 Coordenada X del segundo elemento.
    \param y2 Coordenada Y del segundo elemento.
    \param w2 Anchura del segundo elemento.
    \param h2 Altura del segundo elemento.
    \return 1 si se ha detectado una colisión o 0 en caso contrario.
*/
int Colision (int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);

#endif // COLISION_H_INCLUDED
