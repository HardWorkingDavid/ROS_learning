// 发布odom坐标系到base_link坐标系的变换和nav_msgs/Odometry消息。需要包含相关头文件
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "odometry_publisher");

    ros::NodeHandle n;
    // 创建ros::Publisher和tf::TransformBroadcaster实例，以便能够分别使用ROS和tf发送消息。
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
    tf::TransformBroadcaster odom_broadcaster;
    
    // 假设机器人最初从“odom”坐标系的原点开始
    double x = 0.0;
    double y = 0.0;
    double th = 0.0;
    // 设置一些速度，其将导致“base_link”坐标系相对于“odom”坐标系，
    // 在x方向上以0.1m/s，在y方向上以-0.1m/s的速率和在th方向以0.1rad/s角度移动。这让虚拟机器人走一个圆圈。
    double vx = 0.1;
    double vy = -0.1;
    double vth = 0.1;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();
    // 以1Hz的速率发布里程计信息
    ros::Rate r(1.0);
    while (n.ok()) {
        ros::spinOnce();
        current_time = ros::Time::now();
        // 根据我们设置的恒定速度更新我们的里程信息
        double dt = (current_time - last_time).toSec();
        double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
        double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
        double delta_th = vth * dt;

        x += delta_x;
        y += delta_y;
        th += delta_th;
        // 用于里程的偏航值转换为四元数而发送出去
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
        // 创建一个TransformStamped消息，我们将通过tf发送。
        // 在“current_time”发布从“odom”坐标系到“base_link”坐标系的转换。
        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_link";
        // odometry数据填充变换消息，然后使用TransformBroadcaster发送变换
        odom_trans.transform.translation.x = x;
        odom_trans.transform.translation.y = y;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        odom_broadcaster.sendTransform(odom_trans);
        // 发布nav_msgs/Odometry消息，以便导航堆栈可以从中获取速度信息
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";
        // 使用里程数据填充消息，并通过线路发送
        // set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;
        // 将消息的child_frame_id设置为“base_link”坐标系，因为这是我们发送速度信息的坐标系
        // set the velocity
        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;

        odom_pub.publish(odom);
        last_time = current_time;
        r.sleep();
    }
}