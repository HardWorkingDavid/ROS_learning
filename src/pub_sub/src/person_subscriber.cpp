#include "ros/ros.h"
#include "pub_sub/Person.h"

void personInfoCallback(const pub_sub::Person::ConstPtr& msg) {
    ROS_INFO("Subcribe Person Info: name:%s  age:%d  sex:%d", msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char **argv){
    // 初始化ROS节点
    ros::init(argc, argv, "person_subscriber");
    // 创建节点句柄
    ros::NodeHandle n;
    // 创建一个Subscriber，订阅名为/person_info的topic，注册回调函数personInfoCallback
    ros::Subscriber person_info_sub = n.subscribe("/person_info", 10, personInfoCallback);
    // 循环等待回调函数
    ros::spin();
    return 0;
}