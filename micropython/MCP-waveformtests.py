
from MCP49XX import MCP
from machine import ADC, Pin 

import math


resolution = 128
offset = 1.65
myMCP = MCP("MCP4901", 9)
aInput = machine.ADC(26)
oddlist = (1,3,5,7,9,11,13,15)

#Sin Wave
mySinList = []
for i in range(resolution):
    value = math.sin((i/(resolution-1) *2*math.pi))+offset
    mySinList.insert(i, value)

#Taylor Sawtooth Wave
myCSawList = []
for i in range(resolution):
    x = i/(resolution-1)
    value = 0
    for n in range(10):
        value = value + math.sin((n+1)*x*math.pi*2)/(2*(n+1))
    value = value + offset
    myCSawList.insert(i, value)

#Taylor Approx Triangle Wave
myTaylorTriangleList = []
for i in range(resolution):
    x = (i/(resolution-1))*2*math.pi
    value = math.sin(x)- (math.sin(3*x)/9)
    + (math.sin(5*x)/25)
    - (math.sin(7*x)/49)
    + (math.sin(9*x)/81)
    - (math.sin(11*x)/121)
    + (math.sin(13*x)/169)
    value = value + offset
    myTaylorTriangleList.insert(i, value)


#Taylor Square Wave 
myTSquareList = []
oddlist = [1,3,5,7,9,11]
for i in range(resolution):
    x = (i/resolution-1)*(2*math.pi)
    value = 0
    for n in oddlist:
        value = value + (1/n)*(math.sin(x*n))
    value = value+offset
    myTSquareList.insert(i, value)

   
#Discontinuous Ramp Wave
myDRampList = []
for i in range(resolution):
    value = -1 + (2*(i/(resolution-1))) + offset
    myDRampList.insert(i, value)


    
beegList=[mySinList, myCSawList ,myTaylorTriangleList, myTSquareList,myDRampList]
for lists in beegList:
    print("Break")
    for value in lists:
        myMCP.writeVolt(value)
        reading = aInput.read_u16()
        reading = round(reading*(myMCP.vRef/65536), 3)
        print(reading)
