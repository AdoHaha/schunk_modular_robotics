#include "sdhros.h"
/* my implementation of softController i.e. position controller that as an output has velocity commands for schunk hand
*/		


	void SdhNode::softSpeedController(int nr)
		{
			stopreq=false;

						  BOOST_FOREACH( control_toolbox::Pid & pojed, pid_controllers)
 			   {
     				   pojed.reset(); 
   				}
			while(!stopreq)
			{
		
	 			posmtx_.lock();
						try
						{
				
							actualAngles = sdh_->GetAxisActualAngle( axes_ );
							//ROS_INFO("actu %f",actualAngles[0]);
				
						}
						catch (SDH::cSDHLibraryException* e)
						{
							ROS_ERROR("fu: An exception was caught: %s", e->what());
							delete e;
						}



	/*  BOOST_FOREACH( double & kat, actualAngles)
 			   {
     				  kat=kat*Ma
   				}*/
	//	}
				

				//std::vector<double> actualVelocities;
				
						try
						{
				
							actualVelocities = sdh_->GetAxisActualVelocity( axes_ );
				

						}
						catch (SDH::cSDHLibraryException* e)
						{
							ROS_ERROR("fa: An exception w54as caught: %s", e->what());
							delete e;
						}


				posmtx_.unlock();

				//we have current pos
				std::vector<double> errorAngles_; // in degrees
				errorAngles_.resize(DOF_);
				int nn;
				ros::Time currtime =ros::Time::now();
				ros::Duration dt=currtime-lasttime;
				double checker;
				if((int)actualAngles.size()==DOF_ and (int)targetAngles_.size()==DOF_)
				{
					for(nn=0;nn<DOF_;nn++)
						{
						errorAngles_[nn] = targetAngles_[nn]-actualAngles[nn];
						checker=pid_controllers[nn].updatePid(-errorAngles_[nn],dt); // strange error def inside updatePid
					//	ROS_INFO("checker: %f",checker);
						if(isnan(checker))
						{
						pid_controllers[nn].reset();	
						//velomtx2_.lock();
						velocities_[nn]=0;
						//velomtx2_.unlock();
						}
						else{
						//velomtx2_.lock();
						velocities_[nn]=checker;
						//velomtx2_.unlock();
						}

						}

//ROS_INFO("errors: %f, %f, %f, %f, %f, %f, %f",errorAngles_[0],errorAngles_[1],errorAngles_[2],errorAngles_[3],errorAngles_[4],errorAngles_[5],errorAngles_[6]);
//ROS_INFO("target angles: %f, %f, %f, %f, %f, %f, %f",targetAngles_[0],targetAngles_[1],targetAngles_[2],targetAngles_[3],targetAngles_[4],targetAngles_[5],targetAngles_[6]);
//ROS_INFO("actual angles: %f, %f, %f, %f, %f, %f, %f",actualAngles[0],actualAngles[1],actualAngles[2],actualAngles[3],actualAngles[4],actualAngles[5],actualAngles[6]);
//ROS_INFO("czas dt: %f ",dt.toSec());


//					ROS_INFO("it will set this: %f,%f,%f,%f,%f,%f",velocities_[0],velocities_[1],velocities_[2],velocities_[3],velocities_[4],velocities_[5],velocities_[6]);
//sleep(1);			
                                        posmtx_.lock();
					try
					{
					sdh_->SetAxisTargetVelocity(axes_,velocities_);
					}
					catch (SDH::cSDHLibraryException* e)
						{		
						ROS_ERROR("An exception was caught: %s", e->what());
						delete e;
						}
				        posmtx_.unlock();
				}
				else
				{
				//ROS_ERROR("wymiary");
//actualAngles = sdh_->GetAxisActualAngle( axes_ );
				ROS_ERROR("wymiary: %i %i",actualAngles.size(),targetAngles_.size());
				//ROS_ERROR();
				sleep(1);
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
