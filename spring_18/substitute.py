#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr  9 22:33:14 2018

@author: lukoshkin@phystech.edu
"""

from subprocess import call
from re import search 

pattern = '([a-z_A-Z]+)[ ]*=[ ]*([0-9]+\.?[0-9]*[eE]?[+-]?[0-9]*)'

scheme_params = {}
with open("set_all_params_here") as file:
    for line in file:
        if line[0] != '#':
            match = search(pattern, line)
            if match:
                scheme_params.update({match.group(1) : match.group(2)})

for directory in ['analytical', 'numerical']:           
    for key, value in scheme_params.items():
        command = "sed -ri 's/" + key \
        + " *= *[0-9]+\.?[0-9]*[eE]?[+-]?[0-9]*/" \
        + key + ' = ' + value + "/g' " + directory \
        + "/" + directory + ".h"
        call(command, shell=True)
