#include "sdhros.h"
/* my implementation of softController i.e. position controller that as an output has velocity commands for schunk hand
*/		

#include <iostream>
#include <sstream>
#include <iterator>  
#include <algorithm>
#include <fstream> 
#include <boost/timer.hpp>
#include <ostream>
			//typedef boost::posix_time::ptime Time;

	void SdhNode::softSpeedController(int nr)
		{
			stopreq=false;
			std::vector<double> backupAngles; // in degrees
			Time t1;
						  BOOST_FOREACH( control_toolbox::Pid & pojed, pid_controllers)
 			   {
     				   pojed.reset(); 
   				}
   			std::ofstream speedssetcsv("speedsset.csv", std::ofstream::out);
   			std::ofstream speedsgetcsv("speedsget.csv", std::ofstream::out);
   			std::ofstream positionscsv("positions.csv", std::ofstream::out);
			while(!stopreq)
			{
		
	 			posmtx_.lock();
	 					backupAngles=actualAngles;
						try
						{
				
							actualAngles = sdh_->GetAxisActualAngle( axes_ );
							//ROS_INFO("actu %f",actualAngles[0]);
				
						}
						catch (SDH::cSDHLibraryException* e)
						{
							ROS_ERROR("fu: An exception was caught: %s", e->what());
							delete e;
							actualAngles=backupAngles;
						}
						catch (SDH::cSDHErrorCommunication* e)
						{
						ROS_ERROR("fu: An exception was caught: %s", e->what());
							delete e;
							actualAngles=backupAngles;
						}



	/*  BOOST_FOREACH( double & kat, actualAngles)
 			   {
     				  kat=kat*Ma
   				}*/
	//	}
				posmtx_.unlock();

				//std::vector<double> actualVelocities;
				velomtx_.lock();
						try
						{
				
							actualVelocities = sdh_->GetAxisActualVelocity( axes_ );
				

						}
						catch (SDH::cSDHLibraryException* e)
						{
							ROS_ERROR("fa: An exception w54as caught: %s", e->what());
							delete e;
						}


				velomtx_.unlock();

				//we have current pos
				std::vector<double> errorAngles_; // in degrees
				errorAngles_.resize(DOF_);
				int nn;
				ros::Time currtime =ros::Time::now();
				ros::Duration dt=currtime-lasttime;
				double checker;
				t1=boost::posix_time::microsec_clock::local_time();
				positionscsv<<to_iso_extended_string(t1)<<", ";
				std::copy(actualAngles.begin(),actualAngles.end(), std::ostream_iterator<double>(positionscsv, ", "));
				positionscsv<<"\n";
				
				
				
				if((int)actualAngles.size()==DOF_ and (int)targetAngles_.size()==DOF_)
				{
					for(nn=0;nn<DOF_;nn++)
						{
						errorAngles_[nn] = -actualAngles[nn]+targetAngles_[nn];
						checker=pid_controllers[nn].updatePid(-errorAngles_[nn],dt); // strange error def inside updatePid
					//	ROS_INFO("checker: %f",checker);
						if(isnan(checker))
						{
						pid_controllers[nn].reset();	
						velomtx2_.lock();
						velocities_[nn]=0;
						velomtx2_.unlock();
						}
						else{
						velomtx2_.lock();
						velocities_[nn]=checker;
						velomtx2_.unlock();
						}

						}

//ROS_INFO("errors: %f, %f, %f, %f, %f, %f, %f",errorAngles_[0],errorAngles_[1],errorAngles_[2],errorAngles_[3],errorAngles_[4],errorAngles_[5],errorAngles_[6]);
//ROS_INFO("target angles: %f, %f, %f, %f, %f, %f, %f",targetAngles_[0],targetAngles_[1],targetAngles_[2],targetAngles_[3],targetAngles_[4],targetAngles_[5],targetAngles_[6]);
ROS_INFO("actual angles: %f, %f, %f, %f, %f, %f, %f",actualAngles[0],actualAngles[1],actualAngles[2],actualAngles[3],actualAngles[4],actualAngles[5],actualAngles[6]);
//ROS_INFO("czas dt: %f ",dt.toSec());


//					ROS_INFO("it will set this: %f,%f,%f,%f,%f,%f",velocities_[0],velocities_[1],velocities_[2],velocities_[3],velocities_[4],velocities_[5],velocities_[6]);
//sleep(1);			
					try
					{
					sdh_->SetAxisTargetVelocity(axes_,velocities_);
					t1=boost::posix_time::microsec_clock::local_time();
					
					speedssetcsv<<to_iso_extended_string(t1)<<", ";
					std::copy(velocities_.begin(),velocities_.end(), std::ostream_iterator<double>(speedssetcsv, ", "));
					speedssetcsv<<"\n";
					
					speedsgetcsv<<to_iso_extended_string(t1)<<", ";
					std::copy(actualVelocities.begin(),actualVelocities.end(), std::ostream_iterator<double>(speedsgetcsv, ", "));
					speedsgetcsv<<"\n";
					

					}
					catch (SDH::cSDHLibraryException* e)
						{		
						ROS_ERROR("An exception was caught: %s", e->what());
						delete e;
						}
				}
				else
				{
				//ROS_ERROR("wymiary");
//actualAngles = sdh_->GetAxisActualAngle( axes_ );
				//ROS_ERROR("wymiary: %i %i",actualAngles.size(),targetAngles_.size());
				//ROS_ERROR();
				//sleep(1);
				}
				lasttime=currtime;
				usleep(100);
}
			ROS_INFO("Interrupting softSpeedController");
/*	  BOOST_FOREACH( control_toolbox::Pid & pojed, pid_controllers)
 			   {
     				   pojed.stop(); 
   				}*/
		}
