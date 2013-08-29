
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

		/*!
		* \brief Constructor for SdhNode class
		*
/*!
* \brief Implementation of ROS node for sdh.
*
* Offers actionlib and direct command interface.
*/
class SdhNode
{
	public:
		/// create a handle for this node, initialize node
		ros::NodeHandle nh_;
		void softSpeedController(int);
		SdhNode(std::string name);
		~SdhNode();
		bool init();
		void executeCB(const control_msgs::FollowJointTrajectoryGoalConstPtr &goal);
		void topicCallback_setVelocitiesRaw(const std_msgs::Float32MultiArrayPtr& velocities);
	    void topicCallback_setVelocities(const brics_actuator::JointVelocities::ConstPtr& msg);
		bool srvCallback_Stop(cob_srvs::Trigger::Request &req,
							cob_srvs::Trigger::Response &res );
		bool srvCallback_Recover(cob_srvs::Trigger::Request &req,
							cob_srvs::Trigger::Response &res );
		bool srvCallback_SetOperationMode(cob_srvs::SetOperationMode::Request &req,
									cob_srvs::SetOperationMode::Response &res );
		bool srvCallback_Init(cob_srvs::Trigger::Request &req,
							cob_srvs::Trigger::Response &res );
		void updateSdh();
		void updateDsa();
		bool parseDegFromJointValue(const brics_actuator::JointValue& val, double &deg_val);
		bool updateOperationMode();
		bool testflag;
	private:
		//speedvals 
		// declaration of topics to publish
		ros::Publisher topicPub_JointState_;
		ros::Publisher topicPub_ControllerState_;
		ros::Publisher topicPub_TactileSensor_;
		ros::Publisher topicPub_Diagnostics_;
		
		// topic subscribers
		ros::Subscriber subSetVelocitiesRaw_;
		ros::Subscriber subSetVelocities_;

		// service servers
		ros::ServiceServer srvServer_Init_;
		ros::ServiceServer srvServer_Stop_;
		ros::ServiceServer srvServer_Recover_;
		ros::ServiceServer srvServer_SetOperationMode_;

		// actionlib server
		//actionlib::SimpleActionServer<pr2_controllers_msgs::JointTrajectoryAction> as_;
		actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> as_;
		std::string action_name_;

		// service clients
		//--
//print fyufy
		// other variables
		SDH::cSDH *sdh_;
		SDH::cDSA *dsa_;
		std::vector<SDH::cSDH::eAxisState> state_;

		std::string sdhdevicetype_;
		std::string sdhdevicestring_;
		std::string tcp_adr_;
		std::string dsa_tcp_;
		int dsa_tcp_port_;
		int tcp_port_;
		int sdhdevicenum_;
		std::string dsadevicestring_;
		int dsadevicenum_;
		int baudrate_, id_read_, id_write_;
		double timeout_;

		bool isInitialized_;
		bool isDSAInitialized_;
		bool isError_;
		int DOF_;
		double pi_;
		
		trajectory_msgs::JointTrajectory traj_;
		
		std::vector<std::string> joint_names_;
		std::vector<int> axes_;
		std::vector<double> targetAngles_; // in degrees
		std::vector<double> velocities_; // in rad/s
		bool hasNewGoal_;
		std::string operationMode_; 
		boost::thread softcontroller;
		control_toolbox::Pid pid_controllers[7];
		boost::mutex velomtx_;
		boost::mutex posmtx_;
		boost::mutex velomtx2_;
		bool stopreq; //= true;
		std::vector<double> actualAngles;
		
		std::vector<double> actualVelocities;

		ros::Time lasttime;
		XmlRpc::XmlRpcValue softcontroller_params_list;
};	


