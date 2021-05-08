
from MCP49XX import MCP
from machine import ADC, Pin, Timer
from wavePackets import wavePacket

resolution = 128
frequency = 100
myMCP = MCP("MCP4901", 9)
aInput = machine.ADC(26)
myWavePacket = wavePacket(resolution, "sin", 1.65)

#Function to step through the values of a wave list
soundTimer = Timer()
freqTimer = Timer()


def playSound(soundTimer):
    myMCP.writeVolt(myWavePacket.currentFrameValue)
    myWavePacket.advanceFrame()
    
def update(freqTimer):
    myWavePacket.advanceFrame()
    
soundTimer.init(freq= 44100, mode=Timer.PERIODIC, callback=playSound)
freqTimer.init(freq=frequency, mode=Timer.PERIODIC, callback=update)

