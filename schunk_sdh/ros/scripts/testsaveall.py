#!/usr/bin/env python

import math,random,pygame

import csv

'''prediction node'''
import roslib; 
roslib.load_manifest('handkinect')
import sys 
import rospy
import roslib

from std_msgs.msg import String
from std_msgs.msg import Float64
from dlonurdf.msg import Rekawica
from dlonurdf.msg import Hand
from handkinect.msg import HandKinect
import numpy as np
from sklearn.svm import SVC
import sklearn
import pylab
from sklearn import cross_validation
import pickle
lastarray=[]
alluptonow=[]
tfFrameNames=["root","wrist","thumb_proximal","thumb_medial","thumb_distal","index_proximal","index_medial","index_distal",
"middle_proximal","middle_medial","middle_distal","ring_proximal","ring_medial","ring_distal","pinky_proximal","pinky_medial","pinky_distal"]
fd = open('document.csv','a')
csvwriter= csv.writer(fd,delimiter=' ')
def lastzr(zrekawicy):
	global lastarray
	lastarray=[zrekawicy.kciuk0,zrekawicy.palwska0,zrekawicy.palsro0,
             zrekawicy.palser0,zrekawicy.palmal0,zrekawicy.palmal1,
             zrekawicy.palser1,zrekawicy.palsro1,
             zrekawicy.palwska1,zrekawicy.kciuk1]
def kinect(zkinecta):
    global lastarray
    wholeframe=[zkinecta.__getattribute__(element) for element in tfFrameNames]
    wholeframe.extend(lastarray)
    print wholeframe
    #alluptonow.append(wholeframe)
    #pickle.dump( alluptonow, open( "dokalib.p", "wb" ) )
    csvwriter.writerow(wholeframe)    


if __name__ == '__main__':
        rospy.init_node('keyboardsave')
        rospy.Subscriber("rekawica",Rekawica,lastzr)
        rospy.Subscriber("hand_angles",HandKinect,kinect)
        rospy.spin()
    
