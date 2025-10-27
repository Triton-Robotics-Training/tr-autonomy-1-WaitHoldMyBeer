#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;
using std::placeholders::_1;
using namespace std::chrono_literals;

class SpinSolution : public rclcpp::Node {
 public:
  SpinSolution();
 private:
   void measuredpos_callback(const ArrayMsg& msg);
   void measuredvel_callback(const ArrayMsg &msg);
   void timer_callback();   
   rclcpp::Subscription<ArrayMsg>::SharedPtr pos_subscription_; //creates a subscriber member
   rclcpp::Subscription<ArrayMsg>::SharedPtr vel_subscription_; //creates a subscriber member
   rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_; //creates a publisher member
   rclcpp::TimerBase::SharedPtr timer_;
   float velx;
   float vely;
   ArrayMsg pos_;
    // your code here
};

#endif //YOUR_SOLUTION_SRC_SPIN_SOL_H_
