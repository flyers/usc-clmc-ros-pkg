/*********************************************************************
 Computational Learning and Motor Control Lab
 University of Southern California
 Prof. Stefan Schaal
 *********************************************************************
 \remarks   ...

 \file    joint_states_recorder.cpp

 \author  Peter Pastor
 \date    Jun 21, 2010

 *********************************************************************/


// system includes
#include <usc_utilities/assert.h>
#include <usc_utilities/param_server.h>

#include <task_recorder2_utilities/task_recorder_utilities.h>

// local includes
#include <task_recorder2_recorders/joint_states_recorder.h>

namespace task_recorder2_recorders
{

JointStatesRecorder::JointStatesRecorder(ros::NodeHandle node_handle) :
  num_joint_states_(0)
{
  ROS_VERIFY(usc_utilities::read(node_handle, "joint_names", joint_names_));
  ROS_DEBUG("Starting joint states recorder for joint:");
  for (int i = 0; i < (int)joint_names_.size(); ++i)
  {
    ROS_DEBUG("%i) %s", i+1, joint_names_[i].c_str());
  }
}

bool JointStatesRecorder::transformMsg(const sensor_msgs::JointStateConstPtr joint_state,
                                       task_recorder2_msgs::DataSample& data_sample)
{
  if(first_time_)
  {
    ROS_VERIFY(task_recorder2_utilities::getIndices(joint_state->name, joint_names_, indices_));
    num_joint_states_ = (int)joint_names_.size();
  }

  ROS_ASSERT((int)data_sample.data.size() == (num_joint_states_ * POS_VEL_EFF));
  // positions, velocities, and acceleration
  for (unsigned int i = 0; i < num_joint_states_; ++i)
  {
    data_sample.data[(i * POS_VEL_EFF) + POSITIONS] = joint_state->position[indices_[i]];
    data_sample.data[(i * POS_VEL_EFF) + VELOCITIES] = joint_state->velocity[indices_[i]];
    data_sample.data[(i * POS_VEL_EFF) + EFFORTS] = joint_state->effort[indices_[i]];
  }
  return true;
}

std::vector<std::string> JointStatesRecorder::getNames() const
{
  std::vector<std::string> names;
  const int num_joint_states = (int)joint_names_.size();
  for (int i = 0; i < num_joint_states; ++i)
  {
    names.push_back(joint_names_[i] + std::string("_th"));
    names.push_back(joint_names_[i] + std::string("_thd"));
    names.push_back(joint_names_[i] + std::string("_u"));
  }
  return names;
}

}
