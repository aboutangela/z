#ifndef GMATH_H
#define GMATH_H

#include "matrix.h"
#include "ml6.h"

//vector functions
void normalize( double *vector );
double dot_product( double *a, double *b );
double *calculate_normal(struct matrix *polygons, int i);

#endif
