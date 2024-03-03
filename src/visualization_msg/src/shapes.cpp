#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    // 将我们的初始形状类型设置为立方体
    uint32_t shape = visualization_msgs::Marker::CUBE;

    while (ros::ok()) {
        visualization_msgs::Marker marker;
        // 设置帧ID和时间戳。有关这些方面的信息，请参阅TF教程。
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        // 设置此标记的命名空间和id。这用于创建一个唯一的ID
        // 使用相同名称空间和id发送的任何标记都将覆盖旧标记
        marker.ns = "basic_shapes";
        marker.id = 0;
        // 设置标记类型。最初，这是立方体，并在它与球体、箭头和圆柱体之间循环
        marker.type = shape;
        // 设置标记动作。ROS Indigo:3（DELETEALL）中的选项有ADD、DELETE和new
        marker.action = visualization_msgs::Marker::ADD;
        // Set the pose of the marker 这是相对于标头中指定的帧/时间的完整6DOF姿势
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        // 设置标记的比例——1x1x1在这里表示侧面1米
        marker.scale.x = 1.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();
        
        while (marker_pub.getNumSubscribers() < 1) {
            if (!ros::ok()) {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            ros::Duration(1.0).sleep();
        }
        marker_pub.publish(marker);

        switch (shape)
        {
            case visualization_msgs::Marker::CUBE:
                shape = visualization_msgs::Marker::SPHERE;
                break;
            case visualization_msgs::Marker::SPHERE:
                shape = visualization_msgs::Marker::ARROW;
                break;
            case visualization_msgs::Marker::ARROW:
                shape = visualization_msgs::Marker::CYLINDER;
                break;
            case visualization_msgs::Marker::CYLINDER:
                shape = visualization_msgs::Marker::CUBE;
                break;
        }
        r.sleep();
    }
}