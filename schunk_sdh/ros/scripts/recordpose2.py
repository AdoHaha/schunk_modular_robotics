#!/usr/bin/env python

import math,random,pygame

## 
'''aquisition node'''
import roslib; 
roslib.load_manifest('schunk_sdh')
import sys 
import rospy
import roslib
import cob_srvs.srv
import std_msgs.msg
import control_msgs.msg
import actionlib_msgs.msg
import trajectory_msgs.msg
import collections
from std_msgs.msg import String
from std_msgs.msg import Float64

from dlonurdf.msg import Rekawica
from dlonurdf.msg import Hand

import numpy as np
#from sklearn.svm import SVC
#import sklearn
#import pylab
#from sklearn import cross_validation
import pickle
#savedresults = pickle.load( open( "predictionobject2.p", "rb" ) )
#savedresults = pickle.load( open( "predictionobject_all_people.p","rb"))
#print savedresults
#clf=savedresults["predictor"]
#scaler=savedresults["scaler"]



##

                
running = True
pygame.init()
window = pygame.display.set_mode((100, 100))

fps = pygame.time.Clock()
window.fill(pygame.Color(255,255,255))

allrecords=[]


xvector=[]

def predict(zrekawicy):
    #print zrekawicy
    #r=zrekawicy.
    global xvector
    xvector=[zrekawicy.kciuk0,zrekawicy.palwska0,zrekawicy.palsro0,
             zrekawicy.palser0,zrekawicy.palmal0,zrekawicy.palmal1,
             zrekawicy.palser1,zrekawicy.palsro1,
             zrekawicy.palwska1,zrekawicy.kciuk1]

rospy.init_node('recordopse')
rospy.Subscriber("rekawica",Rekawica,predict)



    #xvector=[float(x) for x in xvector] # for scaler
    #X_test_scaled=scaler.transform(xvector).astype(float)
    #res=clf.predict(X_test_scaled);
    #print res[0]
    #nr=int(res[0])
    #res=String
    #res=target_names[nr]
    #pub.publish(res)
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
                                if key[pygame.K_BACKSPACE]: #delete last one
                                        try:
                                                delar=allrecords.pop()
                                                print "DELETED",target_names[delar[0]],delar
                                        except:
                                                print "nothing to delete"
                                elif key[pygame.K_ESCAPE]:
                                        raise EscapeException("Escape pressed, bye")
                                        
                                #print key[pygame.K_1]
                                #all keys
                                allk=[key[pygame.K_0],key[pygame.K_1],key[pygame.K_2],key[pygame.K_3],key[pygame.K_4],key[pygame.K_5],key[pygame.K_6]]
                                try:
                                        keypressed=next(key for key,value in enumerate(allk) if value==1) #gives first no 
                                        addar=[keypressed]+xvector
                                        print target_names[keypressed],addar
                                        allrecords.append(addar)
                                        pickle.dump(allrecords, open('glove_current.pkl', 'wb'))
                                        #print pickle.dump(allrecords, output)
                                        #print allrecords
                                except:
                                        pass
except EscapeException:
        pickle.dump(allrecords, output)
        pygame.quit()
        print "escape pressed,all saved, bye"
                       
                        
                        
                        
                        
                        
