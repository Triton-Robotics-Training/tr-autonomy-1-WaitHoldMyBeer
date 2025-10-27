#include <chrono>
#include "spin_sol.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

//your code here
SpinSolution::SpinSolution() : Node("spinsolution") //Spinsolution constructor that extends node spin solution with the member "spinsolution"
{
	pos_subscription_ = this->create_subscription<ArrayMsg>("measuredpos", 10, std::bind(&SpinSolution::measuredpos_callback, this, std::placeholders::_1));
	vel_subscription_ = this->create_subscription<ArrayMsg>("measuredvel", 10, std::bind(&SpinSolution::measuredvel_callback, this, std::placeholders::_1));
	publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);
}

void SpinSolution::measuredvel_callback(const ArrayMsg &msg)
{
	velx = msg.data[0];
	vely = msg.data[1];
}

void SpinSolution::measuredpos_callback(const ArrayMsg &msg)
{
	pos_ = ArrayMsg();
	pos_.data = msg.data;
	timer_ = this->create_wall_timer(1ms, std::bind(&SpinSolution::timer_callback, this));
}

void SpinSolution::timer_callback()
{
	pos_.data[0] += velx/1000;
	pos_.data[1] += vely/1000;
	publisher_->publish(pos_);
}
