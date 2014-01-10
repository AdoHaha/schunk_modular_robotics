#!/usr/bin/env python


import math,random,pygame



import roslib; roslib.load_manifest('schunk_sdh')
import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64
from dlonurdf.msg import Rekawica
from dlonurdf.msg import Hand
from dlonurdf.msg import Correction
import math

#import roslib; 
#roslib.load_manifest('dlonurdf')
import sys 
#import rospy
#import roslib
import cob_srvs.srv
import std_msgs.msg
import control_msgs.msg
import actionlib_msgs.msg
import trajectory_msgs.msg
import sensor_msgs.msg
import collections
import scipy.signal as signal


                
running = True
pygame.init()
window = pygame.display.set_mode((100, 100))

fps = pygame.time.Clock()
window.fill(pygame.Color(255,255,255))

allrecords=[]


xvector=[]

pubcorrection = rospy.Publisher('/poprawka', Correction)
rospy.init_node('poprawkanode')
def sendcorrection(name,delta):
    if not name=="Enter":
        
        global poprawki
        poprawki[name]+=delta
        cor=Correction()
        cor.name=name
        cor.val=poprawki[name]
        
    else:
        cor=Correction()
        cor.name=name
        cor.val=0.0
    pubcorrection.publish(cor)
names=["shadow_sdh_knuckle_joint","shadow_sdh_thumb_2_joint","shadow_sdh_thumb_3_joint","shadow_sdh_finger_12_joint","shadow_sdh_finger_13_joint",
                           "shadow_sdh_finger_22_joint","shadow_sdh_finger_23_joint"] #names
poprawki={n:0.0 for n in names}
class EscapeException(Exception):
    pass    
    
target_names = ['Cylinder grip', 'Three finger grip','Precision', 'Lateral','Wedge','Indicating pose','Flat hand']
#output = open('data.pkl', 'wb')
output=open('glove_current.pkl', 'wb') #as output:
try:  
    while True:
                    
        fps.tick(15)
        pygame.display.update()
                    #if pygame.QUIT in [e.type for e in pygame.event.get()]:
                    #        break
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                key=pygame.key.get_pressed()
                if key[pygame.K_RETURN]:
                    sendcorrection("Enter",0)
                elif key[pygame.K_q]:
                    print("q pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_thumb_2_joint",0.1)
                elif key[pygame.K_a]:
                    print("a pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_thumb_2_joint",-0.1)
                elif key[pygame.K_w]:
                    print("w pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_thumb_3_joint",0.1)
                elif key[pygame.K_s]:
                    print("s pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_thumb_3_joint",-0.1)    
                elif key[pygame.K_e]:
                    print("e pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_12_joint",0.1) 
                elif key[pygame.K_d]:
                    print("d pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_12_joint",-0.1) 
                elif key[pygame.K_r]:
                    print("r pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_13_joint",0.1)
                elif key[pygame.K_f]:
                    print("f pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_13_joint",-0.1) 
                elif key[pygame.K_t]:
                    print("t pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_22_joint",0.1) 
                elif key[pygame.K_g]:
                    print("g pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_22_joint",-0.1)  
                elif key[pygame.K_y]:
                    print("y pressed")
                    sendcorrection("shadow_sdh_finger_23_joint",0.1) 
                elif key[pygame.K_h]:
                    print("h pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_finger_23_joint",-0.1)   
                elif key[pygame.K_u]:
                    print("u pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_knuckle_joint",0.1) 
                elif key[pygame.K_j]:
                    print("j pressed")
                    #poprawki["shadow_sdh_thumb_2_joint"]+=0.1 #in rad
                    sendcorrection("shadow_sdh_knuckle_joint",-0.1)
                elif key[pygame.K_ESCAPE]:
                    raise EscapeException("Escape pressed, bye")   
except EscapeException:
    print "Escape pressed,bye"
    pygame.quit()              
             
             
             
             
