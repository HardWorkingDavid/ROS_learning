// 使用类方法作为回调函数
#include "ros/ros.h"
#include "std_msgs/String.h"

class Listener {
public:
    void callback(const std_msgs::String::ConstPtr& msg) {
        ROS_INFO("I heard: [%s]", msg->data.c_str());
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "Class_listener");
    ros::NodeHandle n;
    Listener listener;
    ros::Subscriber sub = n.subscribe("chatter", 1000, &Listener::callback, &listener);
    ros::spin();
    return 0;
}