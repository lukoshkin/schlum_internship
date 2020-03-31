#include <cmath>

extern const double l, alpha, beta, u_special; 

double z (int);

double mu (int); 

double norm (int k)
{
    static double c1 = 0.5 * l * beta * beta;
    double c2 = 0.5 * mu(k) * mu(k) * l;
    double sinc2 = sin( 2 * z(k) ) / (2 * z(k) );

    return c1 * ( 1 - sinc2 ) + c2 * ( 1 + sinc2 ) + beta * sin( z(k) ) * sin( z(k) );
}

double A (int k) 
{
    double arg = 0.5 * z(k);
    return ( beta / mu(k) * ( 1 - cos(arg) ) + sin(arg) ) / norm(k);
}

double B (int k)
{
    double arg = z(k);
    return alpha * u_special * ( beta / mu(k) * ( 1 - cos(arg) ) + sin(arg) ) / norm(k);
}

double E (int k) // via E_K you can set your own condition on time derivative of
{                // the function \theta. At this moment it is not defined in any way
    return 0;    // than zero
}
