import numpy as np
from math import exp

import matplotlib.pyplot as plt 


def parser1(x):
    """
    Remove dashes at the end 
    of string to join them after
    (add 1 spacing if string are 
    not parts of a one word)
    """
    if x:
        if x[-1] == '-': 
            return x[:-1]
        return x + ' '
    else: return ''

def parser2(x):
    """
    Trim spaces at the end of 
    a string; delete dashes 
    inside all strings but
    some specified cases
    """
    x = x[:-1]
    if '- ' in x:
        return x.replace("- ",'')
    elif '-' in x:
        if '10-15' in x: return x
        return x.replace('-','')
    return x

def msigma(x, a, b, c, d):
    """
    Modified sigma function (more general form of the common one).
    It is a univariate function in the sense that it depends only on `x`
    when the other parameters are fixed. Mathematically, `x` is a scalar
    In the terms of num. calculus,`x` may be a scalar or vector.
    If the former is the case, `msigma` calculates func.value at `x`.
    Otherwise, `msigma` computes values at the points which are in 
    the vector given.
    """
    return a / (1 + np.exp(b * x + c)) + d

def dmsigma(x, a, b, c, d):
    """
    Analytical derivative of `msigma`
    In this project it is no sense to expand the input to the case
    when `x` is a vector
    """
    return -a * b * exp(b * x + c) / (1 + exp(b * x + c)) ** 2

def my_fun(x, t, y):
    """
    Function that is to be optimized
    """
    return x[0] / (1 + np.exp(x[1] * t + x[2])) + x[3] - y

def jac_fun(x, t, y):
    """
    Jacobian of the function which is being optimized
    """
    return np.array(
        [1. / (1 + np.exp(x[1] * t + x[2])),
        -x[0] * np.exp(x[1] * t + x[2]) * t / (1 + np.exp(x[1] * t + x[2])) ** 2,
        -x[0] * np.exp(x[1] * t + x[2]) / (1 + np.exp(x[1] * t + x[2])) ** 2,
        np.ones(len(t))]).T

def plot_results(x, y, FDE, coefs, save_plot=False):
    """
    Plot 2D visualization
    x:  x-coords
    y:  y-coords
    FDE:    FD estimate
    save_plot:  save results in curr. dir
    """
    plt.figure(figsize=(16,9))
    line1, = plt.plot(x,y,'o', mfc='none')
    plt.title("Box Counting", size=18)
    plt.xlabel(r"$log_2(\frac{1}{\epsilon})$", size=15)
    plt.ylabel(r"$log_2(N(\epsilon))$", size=15)
    line2, = plt.plot(x, msigma(x, *coefs))
    
    plt.text(min(x) + 1, max(y) - 1, "FD ={:.2f}".format(FDE),fontsize=15)
    plt.legend((line1, line2), (r"$D_2$","sigmoid function"), loc=4)
    
    if save_plot: plt.savefig("bc_plot.png",dpi=1000)
        
def linapprox(x, y):
    """
    Approximate graph curve linearly (which is defined 
    by `x` and `y`) on the range entered from the keyboard
    """
    mask = np.ones(x.shape, dtype=bool)
    sen = input("Enter the boundary values separated by space:")
    if sen:
        l,r = map(float,sen.split())
    mask[x < l] = False
    mask[x > r] = False
    coefs = np.polyfit(x[mask],y[mask],deg=1)
    
    return coefs[0]
