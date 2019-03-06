'''
Created on 27/02/2019
@author: Hrans
'''
import time
import numpy as np
import imutils
import cv2
import serial
from Tkinter import *
from PIL import Image, ImageTk
import ttk as ttk
arduino = serial.Serial('com4', 9600)

if __name__ == '__main__':
    pass
camera = cv2.VideoCapture(0+cv2.CAP_DSHOW)
while True :
    lower = {"lata":(16, 146, 145),"plastico":(36,143,58),"vidrio":(0,118,59)}
    upper = {"lata":(25,241,203),"plastico":(56,233,106),"vidrio":(8,255,178)}
    
    tipo=""
    
    
    colors={"lata":(0, 255, 217),"plastico":(0,255,0),"vidrio":(0,0,255)}
    
    
    
    while True:
        
        _, frame = camera.read()
        
        frame=imutils.resize(frame, width=700)
        
        blurred = cv2.GaussianBlur(frame, (11, 11), 0)
        
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
        
        for key, value in upper.items():
            kernel = np.ones((9,9),np.uint8)
            mask = cv2.inRange(hsv, lower[key], upper[key])
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
            cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
            
            if len(cnts) > 0:
                c = max(cnts, key=cv2.contourArea)
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                
                if (radius > 20)&(radius<50):
                    
                    cv2.circle(frame, (int(x), int(y)), int(radius), colors[key], 2)
                    cv2.putText(frame,key, (int(x-radius),int(y-radius)), cv2.FONT_HERSHEY_SIMPLEX, 0.6,colors[key],2) 
                    if key == "lata":
                        tipo="lata"
                    if key == "plastico":
                        tipo="plastico"
                    if key == "vidrio":                              
                        tipo="vidrio"    
        cv2.imshow("Frame", frame)
        key = cv2.waitKey(1) & 0xFF
        if ((tipo=="lata")|((tipo=="vidrio"))|(tipo=="plastico")):
            
            rawString = arduino.writelines("2180")
            time.sleep(5)
           
            rawString = arduino.writelines("4")
            time.sleep(5)
            
            rawString = arduino.writelines("50")
                 
            rawString = arduino.writelines("2180")
            time.sleep(5)
            print"aqui4"
            if(tipo=="lata"):
                tp="1"
            if(tipo=="plastico"):
                tp="2"
            if(tipo=="vidrio"):
                
                tp="3"
    
            rawString = arduino.writelines(tp)
            time.sleep(5)
           
            rawString = arduino.writelines("50")
            
            
            break
 
    
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

camera.release()
cv2.destroyAllWindows()
