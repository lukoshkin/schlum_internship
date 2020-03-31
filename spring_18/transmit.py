#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 10 12:52:54 2018

@author: lukoshkin@phystech.edu
"""
from subprocess import call

with open("M") as file:
    M = file.read()
if M:
    command = "sed -ri 's/M *= *[0-9]+\.?[0-9]*[eE]?[+-]?[0-9]*/M = " \
    + M + "/g' numerical/numerical.h"
    call(command, shell=True)
