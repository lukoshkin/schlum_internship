#include <gsl/gsl_math.h>

extern const double l, beta;

double f (double x, void * inane)
{
    return beta * l * cos (x) / sin (x) - x;
}
