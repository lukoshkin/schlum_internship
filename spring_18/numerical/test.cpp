#include <utility>
#include <fstream>
#include <iostream>
#include "numerical.h"

constexpr double gamma =  2 * tau / dt,
                 eta = 2 * D * dt / h / h,
                 kappa = alpha * dt;

class Layers
{
    int call_number;
    int * queue;
    double ** u;
    double scheme (int);
    std::pair<double,double> set_boundaries ();
    public:
        Layers ();
        ~Layers ();
        void operator++ ();
        void output ();
} layers;

Layers::Layers ()
{
    call_number = 0;

    queue = new int [3];

    u = new double * [3];
    for (int i=0; i<3; i++)
        u[i] = new double [N+1];

    for (int i=0; i<N+1; i++)
        u[0][i] = ( double(i) / N < 0.5 ) ? 1 : 0;

    for (int i=1; i<N; i++)
        u[1][i] = u[0][i] 
                + 0.5 * eta / gamma * ( u[0][i+1] - 2 * u[0][i] + u[0][i-1] ) 
                + kappa / gamma * ( u_special - u[0][i] );
    
    u[1][0] = u[0][0] 
            + eta / gamma * ( u[0][1] - u[0][0] - beta * h * u[0][0] ) 
            + kappa * ( u_special - u[0][0] );
    
    u[1][N] = u[0][N] 
            + eta / gamma * ( u[0][N-1] - u[0][N] ) 
            + kappa * ( u_special - u[0][N] );
}

Layers::~Layers ()
{
    for (int i=0; i<3; i++)
       delete [] u[i];
    delete [] u;
    delete [] queue; 
}

std::pair<double,double> Layers::set_boundaries ()
{
    static const double denom = 1 / (1 + gamma);
    int first = queue[0],
        second = queue[1];
    
    double left = denom * ( u[first][0] 
                + gamma * ( 2 * u[second][0] - u[first][0] )
                + 2 * eta * ( u[second][1] - u[second][0] - beta * h * u[second][0] )
                + 2 * kappa * ( u_special - u[second][0] ) );

    double right    = denom * ( u[first][N] 
                    + gamma * ( 2 * u[second][N] - u[first][N] )
                    + 2 * eta * ( u[second][N-1] - u[second][N] )
                    + 2 * kappa * ( u_special - u[second][N] ) );
    
    return std::make_pair(left,right);
}

double Layers::scheme (int i)
{
    static const double denom = 1 / (1 + gamma);
    int first = queue[0],
        second = queue[1];
    
    double result   = denom * ( u[first][i] + gamma * (2 * u[second][i] - u[first][i] )
                    + eta * ( u[second][i+1] - 2 * u[second][i] + u[second][i-1] )
                    + 2 * kappa * ( u_special - u[second][i] ) ) ;
    
    return result;
}

void Layers::operator++ ()
{
    for (int i=0; i<3; i++)
        queue[i] = (call_number + i) % 3;
    
    call_number++;

    int aim = queue[2];

    for (int i=1; i<N; i++)
        u[aim][i] = scheme(i);
    
    auto [left, right] = set_boundaries();

    u[aim][0] = left, u[aim][N] = right;
}

bool constraints()
{
    if ( ( kappa >= 0 )
        && ( kappa + 2 * eta < 2 * gamma ) )
        return true;
    else
        return false;
}

void Layers::output ()
{
    std::cout << "gamma = " << gamma << '\n' 
    << "eta = " << eta << '\n' 
    << "kappa = " << kappa << '\n';
    
    if ( !constraints() )
        std::cout << '\n' << "constraints are not reached" << '\n';
         
    std::ofstream fout("adata.tsv");
    for (int i=0; i<N; i++)
        fout << i * h << '\t';
    fout << l << '\n';

    for (int n=0; n<2; n++)
    {
        for (int i=0; i<N; i++)
            fout << u[n][i] <<'\t';
        fout << u[n][N] << '\n';
    }

    for (int n=2; n<M+1; n++)
    {
        ++layers;
        for (int i=0; i<N; i++)
            fout << u[n % 3][i] << '\t';
        fout << u[n % 3][N] << '\n';
    }
    fout.close();
}

int main ()
{
    layers.output();
}
