#ifndef NUMERICAL_H
#define NUMERICAL_H
    
constexpr int   N = 100,
                M = 20;
                      
extern constexpr double     l = 1, 
                            h = l/N, 
                            dt = 1E-3, 
                            tau = 0.1, 
                            D = 8, 
                            epsilon = 1E-6,
                            alpha = 1, 
                            beta = 1, 
                            delta = 1E-8,
                            u_special = 2;

#endif 
