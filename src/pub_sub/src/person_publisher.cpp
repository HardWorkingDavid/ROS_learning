#include "ros/ros.h"
#include "pub_sub/Person.h"

int main(int argc, char** argv) {
    // ROS节点初始化
    ros::init(argc, argv, "person_publisher");
    // 创建节点句柄
    ros::NodeHandle n;
    ros::Publisher person_info_pub = n.advertise<pub_sub::Person>("/person_info", 10);
    ros::Rate loop_rate(1);
    int count = 0;
    while (ros::ok()) {
        pub_sub::Person person_msg;
        person_msg.name = "BigDavid";
        person_msg.age = 24;
        person_msg.sex = pub_sub::Person::male;

        person_info_pub.publish(person_msg);
        ROS_INFO("Publish Person Info: name:%s  age:%d  sex:%d", 
		person_msg.name.c_str(), person_msg.age, person_msg.sex);
        loop_rate.sleep();
    }
    return 0;
}