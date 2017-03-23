import numpy as np

robotHeight = 0.61459
g = 9.8
time = 0.25
angle = np.deg2rad(45)

distance = input("Enter the distance in (x)")
height = input("Enter the height of the target (z)")

velocity = (distance - np.cos(angle)) / time

print "Velocity needed: " , velocity