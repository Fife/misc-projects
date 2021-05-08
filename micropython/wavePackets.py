#Python wavepacket class for a grainular synthesizer 
import math

class wavePacket():
    def __init__(self, resolution, packetType, offset=None):
        self.packetType = packetType
        self.currentFrame = 0
        self.currentFrameValue = offset if not None else 0
        self.resolution = resolution
        self.oddList = (1,3,5,7,9,11,13,15)
        self.offset = offset if not None else 0 
        self.frameList = self._createFrameList(packetType)

    def _createFrameList(self, packetType):
        if (packetType == "sin") : return self._generateSin()
        elif (packetType == "saw") : return self._generateSaw()
        elif (packetType == "square") : return self._generateSquare()
        elif (packetType == "triangle") : return self._generateTriangle()
        elif (packetType == "dRamp") : return self._generateDRamp()

    #Sin Wave
    def _generateSin(self):
        mySinList = []
        for i in range(self.resolution):
            value = math.sin((i/(self.resolution-1) *2*math.pi))+self.offset
            mySinList.insert(i, value)
        return mySinList

    #Taylor Sawtooth Wave
    def _generateSaw(self):
        myCSawList = []
        for i in range(self.resolution):
            x = i/(self.resolution-1)
            value = 0
            for n in range(10):
                value = value + math.sin((n+1)*x*math.pi*2)/(2*(n+1))
            value = value + self.offset
            myCSawList.insert(i, value)
        return myCSawList

    #Taylor Approx Triangle Wave
    def _generateTriangle(self):
        myTaylorTriangleList = []
        for i in range(self.resolution):
            x = (i/(self.resolution-1))*2*math.pi
            value = math.sin(x)- (math.sin(3*x)/9)
            + (math.sin(5*x)/25)
            - (math.sin(7*x)/49)
            + (math.sin(9*x)/81)
            - (math.sin(11*x)/121)
            + (math.sin(13*x)/169)
            value = value + self.offset
            myTaylorTriangleList.insert(i, value)
        return myTaylorTriangleList

    #Taylor Square Wave 
    def _generateSquare(self):
        myTSquareList = []
        for i in range(self.resolution):
            x = (i/self.resolution-1)*(2*math.pi)
            value = 0
            for n in self.oddList:
                value = value + (1/n)*(math.sin(x*n))
            value = value+self.offset
            myTSquareList.insert(i, value)
        return myTSquareList
    
    def _generateDRamp(self):
        #Discontinuous Ramp Wave
        myDRampList = []
        for i in range(self.resolution):
            value = -1 + (2*(i/(self.resolution-1))) + self.offset
            myDRampList.insert(i, value)
        return myDRampList

    def advanceFrame(self):
        if(self.currentFrame == self.resolution-1): self.currentFrame = 0
        elif(self.currentFrame >= 0 and self.currentFrame < self.resolution): self.currentFrame += 1
        self.currentFrameValue = self.frameList[self.currentFrame]



