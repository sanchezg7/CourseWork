#@author Jonas Graf 2015
import sympy as sp
import math 

g=9.81 #gravitation constant 
angle=45 #compute speed with fixed angle 

# the function takes the position of the target and the release position of the ball
# and returns the optimum release speed to hit the target.
# @param x- x value of the Target
# @param y- y value of the Target
# @param x0- x value of the initial position
# @param y0- y value of the initial position
def getReleaseSpeedForTarget(x,y,x0,y0): # x,y = position of target y should be y=0 in most times (target on floor)

    t,v=sp.symbols('t,v')#variables
    
    f1=(v*math.cos(angle)*t)-x+x0#x direction
    f2=(-1/2)*g*t*t+v*math.sin(angle)*t+y0# y direction
    
    e=sp.solvers.solve((f1,f2),(v,t))#solve equations
    
    if e[0][0]>0:return e[0][0]#choose positive solution
    else: return e[1][0]

v = getReleaseSpeedForTarget(1,0,0,0.45959)#example value 1m 
vx= v/math.cos(angle)
vy= v/math.cos(angle)
print 'the result is:'
print('vx= '+str(vx))
print('vy= '+str(vy))
print('v0= '+str(v))


    