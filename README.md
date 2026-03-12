# my_opencv_demo

## 项目简介

这是一个基于 ROS 2 和 OpenCV 的简单摄像头图像发布节点。该节点会从本地摄像头读取图像，并将其发布到 ROS 2 话题中，供其他节点订阅和处理。

## 依赖项

- ROS 2 (Humble 或更高版本)
- OpenCV
- rclcpp
- std_msgs
- sensor_msgs
- cv_bridge
- image_transport

## 构建步骤

1. 确保已安装 ROS 2 和所有依赖项
2. 进入工作空间目录：
   ```
   cd ros2_opencv-master\ros2_ws
   ```
3. 构建项目：
   ```
   colcon build --packages-select my_opencv_demo
   ```
4.  sourcing 环境：
   ```
   . install/setup.bat
   ```

## 运行步骤

1. 确保摄像头已连接到计算机
2. 运行节点：
   ```
   ros2 run my_opencv_demo minimal_opencv_ros2_node
   ```

## 功能说明

- 节点会打开默认摄像头（设备 ID 为 0）
- 每 1 毫秒读取一帧图像
- 将图像转换为 ROS 2 消息格式
- 发布到 `random_image` 话题
- 发布的消息包含时间戳和帧 ID

## 发布的话题

- **Topic**: `random_image`
- **Message type**: `sensor_msgs/Image`
- **Frame ID**: `camera_frame`

## 注意事项

1. 确保摄像头设备权限正确，能够被程序访问
2. 如果摄像头无法打开，节点会输出错误信息并关闭
3. 如需使用其他摄像头设备，可修改代码中的 `cap.open(0)` 为对应设备 ID
4. 发布频率为 1000Hz，可能会根据摄像头性能和系统资源有所调整

## 代码结构

- `src/minimal_opencv_ros2_node.cpp`: 主节点代码，包含摄像头读取和图像发布逻辑
- `CMakeLists.txt`: 构建配置文件
- `package.xml`: 包配置文件，定义依赖项和包信息
