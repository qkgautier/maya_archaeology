#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

// using namespace message_filters;

class Node
{
 public:
  Node()
  {
    sub_1_.subscribe(nh_, "in1", 1);
    sub_2_.subscribe(nh_, "in2", 1);
    sub_3_.subscribe(nh_, "in3", 1);
    sync_.reset(new Sync(MySyncPolicy(10), sub_1_, sub_2_, sub_3_));
    sync_->registerCallback(boost::bind(&Node::callback, this, _1, _2, _3));
  }

  void callback(const sensor_msgs::ImageConstPtr &in1, const sensor_msgs::ImageConstPtr &in2, const sensor_msgs::ImageConstPtr &in3)
  {
    ROS_INFO("Synchronization successful");
    nh_.advertise<sensor_msgs::Image>("out1", 5).publish(in1);
    nh_.advertise<sensor_msgs::Image>("out2", 5).publish(in2);
    nh_.advertise<sensor_msgs::Image>("out3", 5).publish(in3);
  }

 private:
  ros::NodeHandle nh_;
  message_filters::Subscriber<sensor_msgs::Image> sub_1_;
  message_filters::Subscriber<sensor_msgs::Image> sub_2_;
  message_filters::Subscriber<sensor_msgs::Image> sub_3_;

  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "synchronizer");

  Node synchronizer;

  ros::spin();
}
