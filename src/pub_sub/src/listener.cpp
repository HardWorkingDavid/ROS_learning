#include "ros/ros.h"
#include "std_msgs/String.h"
// 定义回调函数chatterCallback，当收到chatter话题的消息就会调用这个函数
// 消息通过boost shared_ptr（共享指针）来传递
void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    // 收到消息，通过ROS_INFO函数显示到终端
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    // 定义订阅节点，名称为chatter，指定回调函数chatterCallback
    // 收到消息，则调用函数chatterCallback来处理
    // 参数1000，定义队列大小，如果处理不够快，超过1000，则丢弃旧的消息
    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    // 调用此函数才真正开始进入循环处理，直到 ros::ok()返回false才停止
    ros::spin();
    return 0;
}

// ros::spin() 和 ros::spinOnce() 
// 相同点:二者都用于处理回调函数；
// 不同点:ros::spin() 是进入了循环执行回调函数，而 ros::spinOnce() 只会执行一次回调函数(没有循环)，在 ros::spin() 后的语句不会执行到，而 ros::spinOnce() 后的语句可以执行。