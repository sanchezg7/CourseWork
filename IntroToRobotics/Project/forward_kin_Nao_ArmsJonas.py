#The Modul has 2 functions to compute the postion of the
#right/left hand Postion using the angles of the Arm joints
#
#Jonas Graf
import numpy as np 
import math

def getPostitionLeftHand(O1,O2,O3,O4,O5):
#DH parameters
    a1=0
    a2=15
    a3=0
    a4=0
    a5=0
    al1=math.pi/2
    al2=-math.pi/2
    al3=math.pi/2
    al4=0
    al5=0
    O1=O1*(math.pi/180)
    O2=O2*(math.pi/180)
    O3=O3*(math.pi/180)
    O4=O4*(math.pi/180)
    O5=O5*(math.pi/180)
    d1=0
    d2=105
    d3=0
    d4=0
    d5=105.95


#A matrixes for every joint
    A1=np.matrix([[math.cos(O1),-math.sin(O1)*math.cos(al1),math.sin(O1)*math.sin(al1),a1*math.cos(O1)],
             [math.sin(O1),math.cos(O1)*math.cos(al1),-math.cos(O1)*math.sin(al1),a1*math.sin(O1)],
             [0,math.sin(al1),math.cos(al1),d1],
             [0,0,0,1]])
    A2=np.matrix([[math.cos(O2),-math.sin(O2)*math.cos(al2),math.sin(O2)*math.sin(al2),a2*math.cos(O2)],
             [math.sin(O2),math.cos(O2)*math.cos(al2),-math.cos(O2)*math.sin(al2),a2*math.sin(O2)],
             [0,math.sin(al2),math.cos(al2),d2],
             [0,0,0,1]])
    A3=np.matrix([[math.cos(O3),-math.sin(O3)*math.cos(al3),math.sin(O3)*math.sin(al3),a3*math.cos(O3)],
             [math.sin(O3),math.cos(O3)*math.cos(al3),-math.cos(O3)*math.sin(al3),a3*math.sin(O3)],
             [0,math.sin(al3),math.cos(al3),d3],
             [0,0,0,1]])
    A4=np.matrix([[math.cos(O4),-math.sin(O4)*math.cos(al4),math.sin(O4)*math.sin(al4),a4*math.cos(O4)],
             [math.sin(O4),math.cos(O4)*math.cos(al4),-math.cos(O4)*math.sin(al4),a4*math.sin(O4)],
             [0,math.sin(al4),math.cos(al4),d4],
             [0,0,0,1]])
    A5=np.matrix([[math.cos(O5),-math.sin(O5)*math.cos(al5),math.sin(O5)*math.sin(al5),a5*math.cos(O5)],
             [math.sin(O5),math.cos(O5)*math.cos(al5),-math.cos(O5)*math.sin(al5),a5*math.sin(O5)],
             [0,math.sin(al5),math.cos(al5),d5],
             [0,0,0,1]])
#Transformation matrix from frame 0 to end frame 
    T04=A1*A2*A3*A4*A5
#get the Position values
    x=T04.item(3)
    y=T04.item(7)
    z=T04.item(11)
    return (x,y,z)
def getPostitionRightHand(O1,O2,O3,O4,O5):
#DH parameters
    a1=0
    a2=15
    a3=0
    a4=0
    a5=0
    al1=-math.pi/2
    al2=math.pi/2
    al3=-math.pi/2
    al4=0
    al5=0
    O1=O1*(math.pi/180)
    O2=O2*(math.pi/180)
    O3=O3*(math.pi/180)
    O4=O4*(math.pi/180)
    O5=O5*(math.pi/180)
    d1=0
    d2=105
    d3=0
    d4=0
    d5=105.95


#A matrixes for every joint
    A1=np.matrix([[math.cos(O1),-math.sin(O1)*math.cos(al1),math.sin(O1)*math.sin(al1),a1*math.cos(O1)],
             [math.sin(O1),math.cos(O1)*math.cos(al1),-math.cos(O1)*math.sin(al1),a1*math.sin(O1)],
             [0,math.sin(al1),math.cos(al1),d1],
             [0,0,0,1]])
    A2=np.matrix([[math.cos(O2),-math.sin(O2)*math.cos(al2),math.sin(O2)*math.sin(al2),a2*math.cos(O2)],
             [math.sin(O2),math.cos(O2)*math.cos(al2),-math.cos(O2)*math.sin(al2),a2*math.sin(O2)],
             [0,math.sin(al2),math.cos(al2),d2],
             [0,0,0,1]])
    A3=np.matrix([[math.cos(O3),-math.sin(O3)*math.cos(al3),math.sin(O3)*math.sin(al3),a3*math.cos(O3)],
             [math.sin(O3),math.cos(O3)*math.cos(al3),-math.cos(O3)*math.sin(al3),a3*math.sin(O3)],
             [0,math.sin(al3),math.cos(al3),d3],
             [0,0,0,1]])
    A4=np.matrix([[math.cos(O4),-math.sin(O4)*math.cos(al4),math.sin(O4)*math.sin(al4),a4*math.cos(O4)],
             [math.sin(O4),math.cos(O4)*math.cos(al4),-math.cos(O4)*math.sin(al4),a4*math.sin(O4)],
             [0,math.sin(al4),math.cos(al4),d4],
             [0,0,0,1]])
    A5=np.matrix([[math.cos(O5),-math.sin(O5)*math.cos(al5),math.sin(O5)*math.sin(al5),a5*math.cos(O5)],
             [math.sin(O5),math.cos(O5)*math.cos(al5),-math.cos(O5)*math.sin(al5),a5*math.sin(O5)],
             [0,math.sin(al5),math.cos(al5),d5],
             [0,0,0,1]])
#Transformation matrix from frame 0 to end frame 
    T04=A1*A2*A3*A4*A5
#get the Position values
    x=T04.item(3)
    y=T04.item(7)
    z=T04.item(11)
    return (x,y,z)
print "Postiton of the Nao robots left hand relative to the shoulder as Base frame:"
print getPostitionLeftHand(20,20,-20,45,77)#random numbers to test
print "Postiton of the Nao robots right hand relative to the shoulder as Base frame:"
print getPostitionRightHand(20,20,-20,45,77)#random numbers to test