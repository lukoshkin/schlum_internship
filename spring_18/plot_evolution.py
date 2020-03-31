#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr  6 22:18:56 2018

@author: lukoshkin@phystech.edu
"""
    
import numpy as np
import matplotlib.pyplot as plt
from subprocess import call, check_output
from re import search




def plot_evolution(frames, EX_DATA = 'edata.tsv', APP_DATA = 'adata.tsv'):
    
    plt.style.use('./style.mplstyle')
    exact_data = np.genfromtxt(EX_DATA, delimiter = '\t')
    approximate_data = np.genfromtxt(APP_DATA, delimiter = '\t')

    M = exact_data.shape[0] - 1
    
    with open("set_all_params_here") as file:
        match = search(' *dt *= *([0-9]+\.?[0-9]*[eE]?[-+]?[0-9]*)', file.read())
    dt = float(match.group(1))
        
    if call('ls storage 2> /dev/null', shell=True):
        call('mkdir storage', shell=True)
        print('storage is created')
        
    if check_output('ls storage', shell=True):
        call('rm storage/*', shell=True)
    
    step = int(M/frames) if frames < M else 1
    abcissa = exact_data[0]
    
    fig, ax = plt.subplots(figsize=(20,20))
    line1, = ax.plot(abcissa, exact_data[1], label='exact solution')
    line2, = ax.plot(abcissa, approximate_data[1], label='approximate one')
    ax.set(xlim=(0,1), ylim=(0, 2))
    ax.set_xlabel('x')
    ax.set_ylabel('n')
    ax.legend()
    
    for i in range(1,M,step):
        plt.title("t = %5.3f" % (i * dt))
        line1.set_data(abcissa,exact_data[i])
        line2.set_data(abcissa,approximate_data[i])
        fig.savefig("storage/image_" + str(i) + ".png")
        

frames = 200
plot_evolution(frames)
