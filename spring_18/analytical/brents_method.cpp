#include <gsl/gsl_roots.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>

extern const double l, delta, epsilon;

double f (double, void *);

double z(int k)
{
    const gsl_root_fsolver_type * T = gsl_root_fsolver_brent;
    gsl_root_fsolver * s = gsl_root_fsolver_alloc (T);
    
    gsl_function F;
    F.function = &f;

    double  x_lo { M_PI * k + delta },
            x_hi { M_PI * ( k + 1 ) - delta },
            r;

    int status;
    gsl_root_fsolver_set (s,&F,x_lo,x_hi);

    int iter (0);
    do
    {
        iter++;
        status = gsl_root_fsolver_iterate (s);
        r = gsl_root_fsolver_root (s);
        x_lo = gsl_root_fsolver_x_lower (s);
        x_hi = gsl_root_fsolver_x_upper (s);
        status = gsl_root_test_interval (x_lo, x_hi, epsilon, 0.);
//        if (status == GSL_SUCCESS)
//            printf ("Converged:\n");
//        printf ("%5d [%.7f, %.7f] %.7f %.7f\n", iter, 
//        x_lo, x_hi, r, x_hi - x_lo);
    }
    while (status == GSL_CONTINUE);
    gsl_root_fsolver_free (s);
    return r;
}

double mu (int k)
{
    return z(k)/l;
}
