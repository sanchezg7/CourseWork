import naoqi
import time
import almath
#import numpy
from naoqi import ALProxy
#from naoqi import _inaoqi
#from naoqi import ALMotion
import motion


motionProxy = ALProxy("ALMotion", "169.254.226.148", 9559)
tts = ALProxy("ALTextToSpeech", "169.254.226.148", 9559)
#motionProxy = ALProxy("ALMotion", "127.0.0.1", 9559)
#tts = ALProxy("ALTextToSpeech", "127.0.0.1", 9559)

# Function takes 5 joint angles as inputs and moves the Nao Robot's right arm.
def moveArm(SPitch, SRoll, EYaw, ERoll, WYaw, Hand, fractionMaxSpeed, t, stiff):
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
    
    time.sleep(t)
    motionProxy.setStiffnesses("RArm", stiff)
    print "done."

def getPosition():  # Example showing how to get the position of the right hand
    name            = "RHand"
    #space = motion.FRAME_ROBOT
    useSensorValues = True
    result          = motionProxy.getPosition(name, 1, useSensorValues)
    print "Position of", name, " in World is:"
    print result


def ArmInterpolation(names, angleLists, timeLists):
    names  = ["RShoulderPitch","RShoulderRoll","RElbowYaw","RElbowRoll","RWristYaw","RHand"]
    # Each joint can have lists of different lengths, but the number of
    # angles and the number of times must be the same for each joint.
    # Here, the second joint ("HeadPitch") has three angles, and
    # three corresponding times.
    angleLists  = [[0.0*almath.TO_RAD, -90.0*almath.TO_RAD, -70.0*almath.TO_RAD, -45.0*almath.TO_RAD, -15.0*almath.TO_RAD, -7.5*almath.TO_RAD, 0.0*almath.TO_RAD], [0.0*almath.TO_RAD, -90.0*almath.TO_RAD, -45.0*almath.TO_RAD, -45.0*almath.TO_RAD, -25.0*almath.TO_RAD, -12.5*almath.TO_RAD, 0.0*almath.TO_RAD], [90.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD], [0.0*almath.TO_RAD, 75.0*almath.TO_RAD, 40.0*almath.TO_RAD, 40.0*almath.TO_RAD, 20.0*almath.TO_RAD, 10.0*almath.TO_RAD, 0.0*almath.TO_RAD], [90.0*almath.TO_RAD, 0.0*almath.TO_RAD, 0.0*almath.TO_RAD, 45.0*almath.TO_RAD, 60.0*almath.TO_RAD, 75.0*almath.TO_RAD, 90.0*almath.TO_RAD], [50.0*almath.TO_RAD, 60.0*almath.TO_RAD, 60.0*almath.TO_RAD, 60.0*almath.TO_RAD, 60.0*almath.TO_RAD, 60.0*almath.TO_RAD, 60.0*almath.TO_RAD]]
    timeLists   = [[1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0], [1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0], [1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0], [1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0], [1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0], [1.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0]]
    isAbsolute  = True
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)

    time.sleep(1.0)

tts.setVolume(.2)
#test = raw_input("Would you like to test the NAO Robot? (input y for yes, n for no): ")
#if test == "y":

#Longer distance throw
tts.say("Hand me the rock.")
moveArm(0, 0 , 90 , 0, 90, 60, 0.1, 6,1) # Load Arm

# Move Arm in Position
moveArm(0, 0, 90, 0, 90, 0, 0.1, 3, 1)

# Straight Forward Throwing Motion.

tts.say("co bee!")

# throwing motion, arc
moveArm(-90, -78, 90, 70, 0, 0, .3, 1.5, 1)
moveArm(-90, -78, 0, 70, 0, 60, 1, 0, 1)
moveArm(-45, -78, 0, 70, 0, 60, 1, 1.5, 0)


#Shorter distance throw
tts.say("Hand me the rock.")
moveArm(0, 0 , 90 , 0, 90, 60, 0.1, 6,1) # Load Arm

# Move Arm in Position
moveArm(0, 0, 90, 0, 90, 0, 0.1, 3, 1)

# Straight Forward Throwing Motion.

tts.say("co bee!")

# throwing motion, arc
moveArm(-90, -78, 90, 70, 0, 0, .3, 1.5, 1)
moveArm(-90, -78, 0, 70, 0, 60, 0.6, 0, 1)
moveArm(-45, -78, 0, 70, 0, 60, 0.6, 1.5, 0)

