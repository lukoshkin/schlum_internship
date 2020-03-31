#include <cmath>
#include <iostream>
#include <cfloat>

extern const double D, dt, h, alpha, beta, tau, epsilon;

double mu (int);

double X (int k, int i)
{
    return  beta * sin( mu(k) * i * h ) 
            + mu(k) * cos( mu(k) * i * h );
}

double A (int); 

double B (int);

double E (int);

double theta (int k, int n) 
{
    static const double lambda = 1 / ( 2 * tau );
    double  mult = alpha + mu(k) * mu(k) * D, 
            d = 1 - 4 * tau * mult,  
            factor = exp( -lambda * n * dt ),
            C1, C2, arg, particular_solution;

    particular_solution = B(k) / mult;
    C1 = A(k) - particular_solution;
    C2 = lambda * C1 + E(k);

    if ( fabs(d) < FLT_EPSILON ) 
        return  factor * ( C1 + C2 * n * dt ) 
                + particular_solution;
    
    if ( d > 0 ) 
    {
        arg = lambda * sqrt(d);
        C2 /= arg;
        arg *= n * dt; 
        return  factor * ( C1 * cosh(arg) + C2 * sinh(arg) ) 
                + particular_solution;
    }
    
    arg = lambda * sqrt(-d);
    C2 /= arg;
    arg *= n * dt;
    return  factor * ( C1 * cos(arg) + C2 * sin(arg) ) 
            + particular_solution;
}

double u (int n, int i)
{
    int k (0);
    double  term (1),
            sum (0);
    do
    {
        term = theta(k,n) * X(k,i);
        if ( term != 0. )
            sum += term;
            k++;
    }while ( fabs(term) > epsilon );

    return sum;
}
