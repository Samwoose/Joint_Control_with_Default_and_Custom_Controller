#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <pluginlib/class_list_macros.h>


namespace controller_ns {

class PositionController : public controller_interface::Controller<
                               hardware_interface::PositionJointInterface> {
private:
  //declare joint handle called joint_
  hardware_interface::JointHandle joint_;
  
  //targetPosition of UR5 after running this node will be -1
  static const double targetPosition_ = -1.00;

public:
  bool init(hardware_interface::PositionJointInterface *hw,
            ros::NodeHandle &n) {
    std::string my_joint;
    if (!n.getParam("joint", my_joint)) {
      ROS_ERROR("Could not find joint name");
      return false; // throws on failure
    }
    
    joint_ = hw->getHandle(my_joint); 
    return true;
  }

  void update(const ros::Time &time, const ros::Duration &period) {
    //set the command value to targetPosition_
    joint_.setCommand(targetPosition_);
  }

  void starting(const ros::Time &time) {}
  void stopping(const ros::Time &time) {}
};
PLUGINLIB_EXPORT_CLASS(controller_ns::PositionController,
                       controller_interface::ControllerBase);
} // namespace controller_ns