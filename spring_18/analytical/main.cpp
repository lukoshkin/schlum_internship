#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "analytical.h"

double u (int i, int n);

int main(int argc, char ** argv) 
{
    int extra_steps, total, status;

    if ( argc != 2 )
    {
        extra_steps = 0;
        total = (N + 1) * M;
    }
    else
    {
        extra_steps = atoi( argv[1] );
        total = (N + 1) * extra_steps;
    }
    
    std::cout << "Time characteristics:"
              << std::endl;

    std::cout << "tau = " 
              << tau 
              << '\t' 
              << "Tdiff = " 
              << l * l / D 
              << std::endl;

    std::cout << "Tmax = "
              << ( M + extra_steps ) * dt
              << '\n' 
              << std::endl;

    std::ofstream fout;
    if ( argc != 2 )
    {
        status = std::system("ls M > /dev/null 2>&1");
        if (!status)
        {
            std::cout << "Nothing new to be done is set"
                      << std::endl;
            std::exit(1);
        }
        fout.open("edata.tsv");
        std::cout << "The process is started" 
                  << std::endl;
        std::cout << "Share of operations performed - 0" 
                  << "/" 
                  << total 
                  << std::flush 
                  << '\r';
        
        for (int i=0; i<N; i++)
            fout << i * h << '\t';
        fout << l << '\n';
        for (int n=0; n<M; n++) 
        {
            for (int i=0; i<N; i++)
                fout << u(n,i) << '\t';
            fout << u(n,N) << '\n';

            std::cout << "Share of operations performed - " 
                      << (N + 1) * (n + 1) <<"/"<< total 
                      << std::flush 
                      << '\r';
        }
        fout.close();
        
        std::cout << '\n';

        fout.open("M");
        fout << M;
        fout.close();
    }
    else
    {
        int start_point;
        status = std::system("ls M > /dev/null 2>&1");
        if (status)
        {
            std::cout << "M is substituted with input argument" 
                      << std::endl;
            start_point = 0;
            extra_steps = M;
        }
        else
        {
        std::string line;
        std::ifstream fin("M");
        std::getline(fin, line);
        fin.close();

        start_point = stoi(line);
        
        fout.open("M");
        fout << start_point + extra_steps;
        fout.close();
        
        system("python transmit.py");
        }
        
        fout.open("edata.tsv", std::ios_base::app);
        std::cout << "The process is started" 
                  << std::endl;
        
        std::cout << "Share of operations performed - 0" 
                  << "/" 
                  << total 
                  << std::flush 
                  << '\r';
        
        for (int n=start_point; n<start_point+extra_steps; n++) 
        {
            for (int i=0; i<N; i++)
                fout << u(n,i) << '\t';
            fout << u(n,N) << '\n';

            std::cout << "Share of operations performed - " 
                      << (N + 1) * (n - start_point + 1) <<"/"<< total 
                      << std::flush 
                      << '\r';
        }
        
        std::cout << '\n' 
                  << "M = " 
                  << start_point + extra_steps 
                  << '\n';
        fout.close();

        std::cout << '\n' 
                  << "..::||DON'T FORGET TO DO MAKE BEFORE YOU MOVE ON TO "
                  <<'\n' 
                  << "\tTHE APPROXIMATE SOLUTION OR THE PLOTTING STAGE||::.."
                  << '\n';
    }
    
    std::cout << "------------------------------"
              << '\n'
              << "runtime of exact.cpp = " 
              << (float)clock()/CLOCKS_PER_SEC 
              << '\n';
}
