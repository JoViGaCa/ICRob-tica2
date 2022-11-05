#include <string>
#include <ros/ros.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <gazebo_msgs/LinkState.h>
#include <gazebo_msgs/GetLinkState.h>
#include <sensor_msgs/Imu.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>





class AndarilhoPub{                      

    public:
        AndarilhoPub(ros::NodeHandle *nh){      
            ros::Rate loop_rate(20);
            LinkState.resize(12);

            Joint_base.resize(8);
            Joint_base = {-40*toRad, 0, -40*toRad, 0, 80*toRad, 80*toRad, -40*toRad, -40*toRad};
            

            joint_pub = nh->advertise<trajectory_msgs::JointTrajectory>("/set_joint_trajectory", 50);
            getState = nh->serviceClient<gazebo_msgs::GetLinkState>("/gazebo/get_link_state");
            sensor1 = nh->subscribe("/sensor_dir_topic", 50, &AndarilhoPub::sensor1CallBack, this);
            sensor2 = nh->subscribe("/sensor_esq_topic", 50, &AndarilhoPub::sensor2CallBack, this);

            traj.joint_names.resize(8);
            traj.joint_names[0] = "quadril_dir_x_joint";
            traj.joint_names[1] = "quadril_dir_y_joint";
            traj.joint_names[2] = "quadril_esq_x_joint";
            traj.joint_names[3] = "quadril_esq_y_joint";
            traj.joint_names[4] = "joelho_dir_joint";
            traj.joint_names[5] = "joelho_esq_joint";
            traj.joint_names[6] = "torn_dir_joint";
            traj.joint_names[7] = "torn_esq_joint";
            traj.header.frame_id = "tronco_link";
            traj.points.resize(1);
            traj.points[0].positions = {0, 0, 1, 0, 0, 0, 0, 0};
            
            for(int i = 0; i < 8; i++){
                traj.points[0].positions[i] = Joint_base[i];
            }

            double posCM[3] = {0,0,1.7};
            double offset = atan(0.5/0.38);
            double dQ = 0.628;
            double leg2 = leg*leg;
            double retaH_dir, retaH_esq;
            double retaH_dir2, retaH_esq2;


            
            while(ros::ok()){
                getAllStates();
                ros::spinOnce();
                joint_pub.publish(traj);

                ang_quad_dir_y = acos((abs(posCM[1]-0.38))/ dQ);
                retaH_dir = posCM[2] - dQ*sin(ang_quad_dir_y);
                retaH_dir2 = retaH_dir*retaH_dir;
                ang_joel_dir = acos((retaH_dir2/(2*leg2)) -1);
                ang_torn_dir = 90*toRad - ang_joel_dir;
                ang_quad_dir_x = 90*toRad - ang_joel_dir;

                ang_quad_esq_y = acos((abs(posCM[1]+0.38))/ dQ);
                retaH_esq = posCM[2] - dQ*sin(ang_quad_esq_y);
                retaH_esq2 = retaH_esq*retaH_esq;
                ang_joel_esq = acos(((retaH_esq2)/(2*leg2)) -1);
                ang_torn_esq = 90*toRad - ang_joel_esq;
                ang_quad_esq_x = 90*toRad - ang_joel_esq;

                ROS_INFO("%.4f - %.4f", ang_joel_dir,ang_joel_esq);

                traj.points[0].positions[0] = -(90*toRad - ang_quad_dir_x);
                traj.points[0].positions[1] = ang_quad_dir_y - offset;
                traj.points[0].positions[2] = -(90*toRad - ang_quad_esq_x);
                traj.points[0].positions[3] = ang_quad_esq_y - offset;
                traj.points[0].positions[4] = (180*toRad - ang_joel_dir);
                traj.points[0].positions[5] = (180*toRad - ang_joel_esq);
                traj.points[0].positions[6] = -ang_torn_dir;
                traj.points[0].positions[7] = -ang_torn_esq;

                for(int i = 0; i < 8; i++){
                    ROS_INFO("Junta %d Valor %.4f", i, traj.points[0].positions[i]);
                }

                double r = LinkState[0].pose.position.z;
                double a = (sensor_dir.linear_acceleration.x + sensor_esq.linear_acceleration.x)/2;
                double g = (sensor_dir.linear_acceleration.z + sensor_esq.linear_acceleration.z)/2;

                double Zmp = -(r*a)/g;

                //ROS_INFO("Valor Zmp = %.4f", Zmp);


                //traj.points[0].positions = {0, 0, -(40*toRad), 0, 0, 0, 0, 0};
                //joint_pub.publish(traj);
                loop_rate.sleep();
            

            }


        }

        void getAllStates(){
            gazebo_msgs::GetLinkState gms;
            for(int i = 0; i < 11; i++){
                gms.request.link_name = Link_name[i];
                if(getState.call(gms)){
                    LinkState[i] = gms.response.link_state;
                }

            }

        }

        void sensor1CallBack(const sensor_msgs::Imu &value){
            sensor_dir = value;
        }

        void sensor2CallBack(const sensor_msgs::Imu &value){
            sensor_esq = value;
        }

        void setAngle(float angle, char axis, int link){
            LinkState[link].pose.orientation.w = cos(angle*toRad);
            LinkState[link].pose.orientation.y = sin(angle*toRad);
        }



    private:
        const double toRad = 3.14159/180;
        ros::Publisher joint_pub;
        ros::ServiceClient getState;
        ros::Subscriber sensor1;
        ros::Subscriber sensor2;
        const char* Link_name[11] = {"tronco_link","quad_dir_link","quad_esq_link","perna1_dir_link",
                                        "perna1_esq_link", "perna2_dir_link", "perna2_esq_link", "joelho_dir_link",
                                        "joelho_esq_link", "pe_dir_link", "pe_esq_link"};
        std::vector<gazebo_msgs::LinkState> LinkState;
        trajectory_msgs::JointTrajectory traj;
        std::vector<double> Joint_base;
        sensor_msgs::Imu sensor_dir;
        sensor_msgs::Imu sensor_esq;
        // movimentação da perna
        const double leg = 0.7;
        double ang_quad_dir_x, ang_quad_dir_y, ang_quad_esq_x, ang_quad_esq_y;
        double ang_joel_dir, ang_joel_esq, ang_torn_dir, ang_torn_esq;

        


};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "andarilho_pub");     
    ros::NodeHandle nh;
    AndarilhoPub joint_state_pub = AndarilhoPub(&nh); 

    
    ros::spin();
    return 0;
}
