#### 获取当前时间

ros::Time::now()

`得到ros::Time实例化的当前时间`

```cpp
ros::Time begin = ros::Time::now();
```

#### 转换时间和持续时间实例

`时间和持续时间的对象也可以变成浮点秒`

```cpp
double secs = ros::Time::now().toSec();
ros::Duration d(0.5);
secs = d.toSec();
```

#### Sleeping and Rates（睡眠和速率）

函数:ros::Rate

```cpp
ros::Rate r(10); // 10 hz
while (ros::ok())
{
  ... do some work ...
  r.sleep();
}
```