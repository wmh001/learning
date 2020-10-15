# -*- coding: utf-8 -*-
"""
Created on Thu Oct 15 22:44:26 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt
from html_movie import movie


def gaussian(s, center=0.0, spread=1.0):
    return np.exp(-2 * (s - center)**2 / spread**2)


xmin, xmax = -4.0, 4.0
ymin, ymax = -3.0, 3.0

dx = 0.01
x = np.arange(xmin, xmax + dx, dx)

tmin, tmax = 0.0, 4.0
num_frames = 100
t = np.linspace(tmin, tmax, num_frames)

r_speed = 2.0
r_0 = -4.0
l_speed = -2.0
l_0 = 4.0

plt.close('all')
fig = plt.figure(figsize=(10, 10))
ax = plt.axes(xlim=(xmin, xmax), ylim=(ymin, ymax))

ax.plot([], [], 'b--', lw=1)
ax.plot([], [], 'r--', lw=1)
ax.plot([], [], 'g-', lw=3)
lines = ax.get_lines()

file_name = "{:03d}_movie.jpg"

for i in range(num_frames):
    r_now = r_0 + r_speed * t[i]
    l_now = l_0 + l_speed * t[i]
    yR = gaussian(x, r_now)
    yL = -gaussian(x, l_now)
    lines[0].set_data(x, yR)
    lines[1].set_data(x, yL)
    lines[2].set_data(x, yR + yL)
    plt.savefig(file_name.format(i))

movie(input_files='*.jpg', output_file='movie.html')
