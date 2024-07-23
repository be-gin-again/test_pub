#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

#include "test_msgs/msg/num.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
    public:
        MinimalPublisher()
        : Node("publisher"), count_(0)
        {
            publisher_ = this->create_publisher<test_msgs::msg::Num>("topic",10);
            timer_ = this->create_wall_timer(
                500ms, std::bind(&MinimalPublisher::timer_callback, this));
        }

    private:
        void timer_callback()
        {         
            auto message = test_msgs::msg::Num();
            message.num = count_++;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", message.num);
            publisher_->publish(message);
        }

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<test_msgs::msg::Num>::SharedPtr publisher_;
        size_t count_;
};



int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}