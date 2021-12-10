#include <ros/ros.h>
#include <Traverse.h>
#include <vector>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

Traverse::Traverse(ros::NodeHandle nh) {
	node = nh;
}

void Traverse::move_next() {
	MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  	}
  	for(int i = 0; i <= 12; i++) {
  		move_base_msgs::MoveBaseGoal cur_goal;
  		cur_goal.target_pose.header.frame_id = "map";
    	cur_goal.target_pose.header.stamp = ros::Time::now();
    	cur_goal.target_pose.pose.position.x = X[i];
    	cur_goal.target_pose.pose.position.y = Y[i];
    	cur_goal.target_pose.pose.orientation.z = Z[i];
    	cur_goal.target_pose.pose.orientation.w = W[i];
    	goals.push_back(cur_goal);
    	ac.sendGoal(goals[i]);
    	ac.waitForResult();
    	ROS_INFO_STREAM("Reached node " << i);
  	}
}

void Traverse::to_goal(double x, double y) {
	MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
	}
	goals.push_back(goal);
	move_base_msgs::MoveBaseGoal cur_goal;
	cur_goal.target_pose.header.frame_id = "map";
    cur_goal.target_pose.header.stamp = ros::Time::now();
    cur_goal.target_pose.pose.position.x = x;
    cur_goal.target_pose.pose.position.y = y;

    ac.sendGoal(cur_goal);
    ac.waitForResult();
    ROS_INFO_STREAM("Reached near object");
}