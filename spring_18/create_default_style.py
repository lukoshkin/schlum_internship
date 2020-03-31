#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr  10 21:39:23 2018

@author: lukoshkin@phystech.edu
"""

from subprocess import call    
    
style = ['axes.titlesize : 20',  
         'axes.labelsize : 40',
         'lines.linewidth : 2',
         'legend.fontsize : 20',
         'axes.grid : True',
         'xtick.labelsize : 20',
         'ytick.labelsize : 20']

if call('ls style.mplstyle > /dev/null 2>&1', shell=True):
    with open("style.mplstyle", 'w') as file:
        print(*style, file = file, sep = '\n')
