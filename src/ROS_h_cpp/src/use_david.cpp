#include "ros/ros.h"
#include "david.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "david");
    hello_ns::My my;
    my.run();
    return 0;
}