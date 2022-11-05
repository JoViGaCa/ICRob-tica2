#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>


class AndarilhoPub{                      

    public:
        AndarilhoPub(ros::NodeHandle *nh){      
            //Inicializar Variaveis
            origem_joint = 0;
            quad_esq_joint = 0;
            quad_dir_joint = 0;
            joelho_dir_joint = 0;
            joelho_esq_joint = 0;
            torn_dir_joint = 0;
            torn_esq_joint = 0;
            ros::Rate loop_rate(30);


            const double degree = M_PI/180;

            joint_pub = nh->advertise<sensor_msgs::JointState>("/joint_states", 1);
            tf::TransformBroadcaster broadcaster;

            
            // declaração de mensagens
            geometry_msgs::TransformStamped odom_trans;
            sensor_msgs::JointState joint_state;
            odom_trans.header.frame_id = "odom";
            odom_trans.child_frame_id = "axis";

            float n = 0;
            float angle = 0;

            while(ros::ok()){
              joint_state.header.stamp = ros::Time::now();
              joint_state.name.resize(9);
              joint_state.position.resize(9);
              joint_state.name[0] = "com_x";
              joint_state.position[0] = n;
              joint_state.name[1] = "com_z";
              joint_state.position[1] = n;
              joint_state.name[2] = "com_y";
              joint_state.position[2] = n;
              joint_state.name[3] = "quadril_esq_joint";
              joint_state.position[3] = angle;
              joint_state.name[4] = "quadril_dir_joint";
              joint_state.position[4] = angle;
              joint_state.name[5] = "joelho_esq_joint";
              joint_state.position[5] = angle;
              joint_state.name[6] = "joelho_dir_joint";
              joint_state.position[6] = angle;
              joint_state.name[7] = "torn_esq_joint";
              joint_state.position[7] = angle;
              joint_state.name[8] = "torn_dir_joint";
              joint_state.position[8] = angle;

              
              odom_trans.header.stamp = ros::Time::now();
              odom_trans.transform.translation.x = 0;
              odom_trans.transform.translation.y = 0;
              odom_trans.transform.translation.z = .7;
              odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);



              joint_pub.publish(joint_state);
              loop_rate.sleep();
            }

        }


    private:
        double origem_joint;
        double quad_esq_joint;
        double quad_dir_joint;
        double joelho_esq_joint;
        double joelho_dir_joint;
        double torn_esq_joint;
        double torn_dir_joint;
        ros::Publisher joint_pub;


};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "andarilho_pub");     
    ros::NodeHandle nh;
    AndarilhoPub joint_state_pub = AndarilhoPub(&nh);     
    
    ros::spin();
    return 0;
}
