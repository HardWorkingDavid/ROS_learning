#include "ros/ros.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"set_update_param");
    /*------------------------增加参数-------------------------*/
    vector<string> stus;
    stus.push_back("hhh");
    stus.push_back("aaa");
    map<string, string> friends;
    friends["a"] = "AAA";
    friends["b"] = "BBB";

    ros::NodeHandle n;
    n.setParam("int", 10);
    n.setParam("double", 10.0);
    n.setParam("bool", true);
    n.setParam("string", "hello");
    n.setParam("vector", stus);
    n.setParam("map", friends);

    //修改演示(相同的键，不同的值)
    n.setParam("int",10000);

    ros::param::set("param_int", 20);
    ros::param::set("param_double", 20.0);
    ros::param::set("param_bool", false);
    ros::param::set("param_string", "hello123");
    ros::param::set("param_vector", stus);
    ros::param::set("param_map", friends);

    ros::param::set("param_int", 20000);

    /*---------------------------获取参数---------------------------*/
    // param(键,默认值)  存在，返回对应结果，否则返回默认值
    int res1 = n.param("int", 100);
    ROS_INFO("param获取结果:%d", res1);
    // getParam(键,存储结果的变量)
    // 存在,返回 true,且将值赋值给参数2
    // 若果键不存在，那么返回值为 false，且不为参数2赋值
    double param_double_value;
    ros::param::get("param_double",param_double_value);
    ROS_INFO("getParam获取的结果, %.2f", param_double_value);
    for (auto &&stu : stus)
    {
        ROS_INFO("stus 元素:%s",stu.c_str());        
    }
    for (auto &&f : friends)
    {
        ROS_INFO("map 元素:%s = %s",f.first.c_str(), f.second.c_str());
    }
    /*---------------------------存在 param_int 吗---------------------------*/
    ROS_INFO("存在 param_double 吗? %d", ros::param::has("param_double"));

    /*-------------------------删除参数---------------------------*/
    bool r1 = n.deleteParam("param_string");
    ROS_INFO("删除结果%d ", r1);
    return 0;
}