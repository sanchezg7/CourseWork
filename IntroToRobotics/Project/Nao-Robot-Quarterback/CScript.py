import sys
import time
import almath

class MyClass(GeneratedClass):
    def __init__(self):
        GeneratedClass.__init__(self)
        self.tts = ALProxy('ALMotion')

    def onLoad(self):
        #put initialization code here
        pass

    def onUnload(self):
        #put clean-up code here
        pass

    def onInput_onStart(self):
        #self.onStopped() #activate the output of the box
        self.tts.setStiffnesses("RArm", 1.0)

        # Manipulating joints in right arm at 5% max speed
        names            = "RShoulderPitch"
        angles           = 119.5*almath.TO_RAD
        fractionMaxSpeed = 1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        names            = "RShoulderRoll"
        angles           = 0*almath.TO_RAD
        fractionMaxSpeed = 1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        names            = "RElbowYaw"
        angles           = 90*almath.TO_RAD
        fractionMaxSpeed = 0.1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        names            = "RElbowRoll"
        angles           = 90*almath.TO_RAD
        fractionMaxSpeed = 1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        names            = "RWristYaw"
        angles           = 90*almath.TO_RAD
        fractionMaxSpeed = 0.1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        names            = "RHand"
        angles           = 30*almath.TO_RAD
        fractionMaxSpeed = 0.1
        self.tts.setAngles(names,angles,fractionMaxSpeed)

        time.sleep(3.0)
        self.tts.setStiffnesses("RArm", 0.0)
        pass

    def onInput_onStop(self):
        self.onUnload() #it is recommended to reuse the clean-up as the box is stopped
        self.onStopped() #activate the output of the box