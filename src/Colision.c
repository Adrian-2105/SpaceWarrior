#include <math.h>

#include "Colision.h"

#define PORCENTAJE_DENTRO 25

int Colision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    double cx1 = x1+w1/2.0;
    double cy1 = y1+h1/2.0;
    double cx2 = x2+w2/2.0;
    double cy2 = y2+h2/2.0;
    double r1 = sqrt(pow(h1/2.0,2.0)+pow(w1/2.0,2.0));
    double r2 = sqrt(pow(h2/2.0,2.0)+pow(w2/2.0,2.0));
    double dentro = ((r1+r2)*PORCENTAJE_DENTRO/100);
    return (sqrt(pow(cx1-cx2,2.0)+pow(cy1-cy2,2.0)) < ((r1+r2)-dentro));
}
