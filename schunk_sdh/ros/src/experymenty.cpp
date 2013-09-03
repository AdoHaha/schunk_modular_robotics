
//##################
//#### includes ####

// standard includes
#include <unistd.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <math.h>
// ROS includes
#include <ros/ros.h>
#include <urdf/model.h>
#include <actionlib/server/simple_action_server.h>

#include <control_toolbox/pid.h>

// ROS message includes
#include <std_msgs/Float32MultiArray.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <sensor_msgs/JointState.h>
//#include <pr2_controllers_msgs/JointTrajectoryAction.h>robot_state_publisher
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <pr2_controllers_msgs/JointTrajectoryControllerState.h>
#include <schunk_sdh/TactileSensor.h>
#include <schunk_sdh/TactileMatrix.h>
#include <brics_actuator/JointVelocities.h>
#include <brics_actuator/JointValue.h>

// ROS service includes
#include <cob_srvs/Trigger.h>
#include <cob_srvs/SetOperationMode.h>

// ROS diagnostic msgs
#include <diagnostic_msgs/DiagnosticArray.h>

// external includes
#include <schunk_sdh/sdh.h>
#include <schunk_sdh/dsa.h>

#include<ostream>

#include "sdhros.h"
/* my implementation of softController i.e. position controller that as an output has velocity commands for schunk hand
*/		

#include <iostream>
#include <iterator>  
#include <algorithm>
#include <fstream> 
#include "boost/date_time/posix_time/posix_time.hpp" 

int main(int argc, char** argv)
{


	return 0;
}



