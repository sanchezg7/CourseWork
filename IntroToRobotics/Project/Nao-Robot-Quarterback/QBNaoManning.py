import naoqi
import time
import almath
#import numpy
from naoqi import ALProxy
#from naoqi import _inaoqi
#from naoqi import ALMotion
import motion


motionProxy = ALProxy("ALMotion", "169.254.226.148", 9559)
#motionProxy = ALProxy("ALMotion", "127.0.0.1", 9559)
#postureProxy = ALProxy("ALRobotPosture", "169.254.226.148", 9559)

# Function takes 5 joint angles as inputs and moves the Nao Robot's right arm.
def moveArm(SPitch, SRoll, EYaw, ERoll, WYaw, Hand, fractionMaxSpeed):
   # postureProxy.goToPosture("Stand", 0.8)
    motionProxy.setStiffnesses("RArm", 1.0)

    names            = "RShoulderPitch"
    angles           = SPitch*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)

    names            = "RShoulderRoll"
    angles           = SRoll*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)

    names            = "RElbowYaw"
    angles           = EYaw*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)

    names            = "RElbowRoll"
    angles           = ERoll*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)

    names            = "RWristYaw"
    angles           = WYaw*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)

    names            = "RHand"
    angles           = Hand*almath.TO_RAD
    #fractionMaxSpeed = 0.5
    motionProxy.setAngles(names,angles, fractionMaxSpeed)
    
    time.sleep(3.0)
    motionProxy.setStiffnesses("RArm", 1.0)
    print "done."

def getPosition():  # Example showing how to get the position of the right hand
    name            = "RHand"
    #space = motion.FRAME_ROBOT
    useSensorValues = True
    result          = motionProxy.getPosition(name, 1, useSensorValues)
    print "Position of", name, " in World is:"
    print result

moveArm(0,0,0,0,0,45, 0.1) # Reset arm to standard position
getPosition() # SHOULD return the position of the right arm in frame World
moveArm(-90,-90,0,90,0,0, .1)
getPosition()
moveArm(0,0,0,0,0,0, .1)
getPosition()
