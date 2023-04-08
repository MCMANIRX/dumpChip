import serial
from time import sleep

y =0


read = serial.Serial ("COM37", 115200,timeout=55)

f = open('flash.bin', 'wb')



while(True):  # Or: while ser.inWaiting():
    buffer = read.readline()[:-2]
    
    if(buffer.decode("utf-8") == "end"):
            break
        
    
    for i in range(15):
        j = i*2
        f.write(int(buffer[j:j+2],16).to_bytes(1,'big'))
        
    print(hex(16*y)+"\t"+str(buffer))
    y+=1


    #f.write(int(buffer,16))
    
    
print("done")