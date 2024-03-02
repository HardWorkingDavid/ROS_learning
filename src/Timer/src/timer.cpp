/**
 * roscpp定时器，它允许您安排一个回调发生周期性。
 * 什么是Timers(定时器)?
 * *Timers能让你以一定的频率来执行
 * *他们是比ros::Rate更加灵活和有用的形式，ros::Rate在编写简单发布节点和订阅节点用到。
 * *定时器不是实时的线程/内核替换，也不能保证它们的准确度，因为系统负载/功能会有很大的变化
*/
#include "ros/ros.h"

void callback1(const ros::TimerEvent&) {
    ROS_INFO("Callback 1 triggered");
}

void callback2(const ros::TimerEvent&) {
    ROS_INFO("Callback 2 triggered");
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    // 增加两个定时器，一个100毫秒执行一次，一个1秒执行一次
    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);
    ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);

    ros::spin();
    return 0;
}

/**ros::TimerEvent结构体作为参数传入，它提供时间的相关信息，对于调试和配置非常有用
 * ros::TimerEvent结构体说明：

    ros::Time last_expected 上次回调期望发生的时间
    ros::Time last_real 上次回调实际发生的时间
    ros::Time current_expected 本次回调期待发生的时间
    ros::Time current_real 本次回调实际发生的时间
    ros::WallTime profile.last_duration 上次回调的时间间隔（结束时间-开始时间），是wall-clock时间。
*/
/*
Class Methods类方法：
void Foo::callback(const ros::TimerEvent& event)
{
...
}

...
Foo foo_object;
ros::Timer timer = nh.createTimer(ros::Duration(0.1), &Foo::callback, &foo_object);
*/