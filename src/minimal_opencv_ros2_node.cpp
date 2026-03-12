#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/header.hpp"
#include "chrono"
#include <cv_bridge/cv_bridge.h>
#include "image_transport/image_transport.hpp"
#include <opencv2/opencv.hpp>
using namespace std:: chrono_literals;
class MinimalImagePublisher : public rclcpp::Node{

     public:
        MinimalImagePublisher():Node ("opencv_image_publisher"),count_(0) {
        publisher_=
        this->create_publisher<sensor_msgs::msg::Image>("random_image",10);
         cap.open(0);
         if(!cap.isOpened())
         {
            RCLCPP_ERROR(this->get_logger(),"Failed to open camera");
            rclcpp::shutdown();
            return ;
         }
        
        timer_=this->create_wall_timer(
            1ms,std::bind(&MinimalImagePublisher::timer_callback,this));
        }
    private:
         void timer_callback()
        {
            RCLCPP_INFO(this->get_logger(), "Timer event");
            cv::Mat  my_image;
            cap.read(my_image) ;
            sensor_msgs::msg::Image ros_image;
            ros_image.header.stamp=this->now();
            ros_image.header.frame_id="camera_frame";
            //cv::randu(my_image,cv::Scalar(0,0,0),cv::Scalar(255,255,255));
            cv_bridge::CvImage   cv_image(std_msgs::msg::Header(),"bgr8",my_image);
            cv_image.toImageMsg( ros_image);
            publisher_->publish(ros_image);
            RCLCPP_INFO(this->get_logger(),"Image %ld published",count_);
            count_++;
        }
        cv::VideoCapture cap;
        rclcpp::TimerBase::SharedPtr timer_;
        sensor_msgs::msg::Image::SharedPtr msg_;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
        size_t count_;
        
};


int main(int argc,char *argv[])
{

rclcpp::init(argc,argv);
auto node =std::make_shared<MinimalImagePublisher>();

rclcpp::spin(node);
rclcpp::shutdown();



   return 0;
}









