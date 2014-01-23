/*********************************************************************
  Computational Learning and Motor Control Lab
  University of Southern California
  Prof. Stefan Schaal 
 *********************************************************************
  \remarks		...
 
  \file		dynamic_movement_primtive_state.cpp

  \author	Peter Pastor, Mrinal Kalakrishnan
  \date		Nov 8, 2010

 *********************************************************************/

// system includes
#include <stdio.h>

// local includes
#include <dmp_lib/dynamic_movement_primitive_state.h>
#include <dmp_lib/logger.h>

namespace dmp_lib
{

bool DynamicMovementPrimitiveState::initialize(bool is_learned, bool is_setup, bool is_start_set,
                                               const Time& current_time,
                                               const unsigned int num_training_samples,
                                               const unsigned int num_generated_samples,
                                               const int seq,
                                               const int successor,
                                               const int predecessor)
{
    is_learned_ = is_learned;
    is_setup_ = is_setup;
    is_start_set_ = is_start_set;
    current_time_ = current_time;
    num_training_samples_ = num_training_samples;
    num_generated_samples_ = num_generated_samples;
    seq_ = seq;
    successor_ = successor;
    predecessor_ = predecessor;
    return true;
}

bool DynamicMovementPrimitiveState::isCompatible(const DynamicMovementPrimitiveState& other_state) const
{
  if ((is_learned_ != other_state.is_learned_) || (is_setup_ != other_state.is_setup_) || (is_start_set_ != other_state.is_start_set_))
  {
    Logger::logPrintf("State is not compatible.", Logger::ERROR);
    return false;
  }
  if(current_time_ != other_state.current_time_)
  {
    Logger::logPrintf("State is not compatible. Current time does not match.", Logger::ERROR);
    return false;
  }
  return true;
}

bool DynamicMovementPrimitiveState::get(bool& is_learned, bool& is_setup, bool& is_start_set,
                                        Time& current_time,
                                        unsigned int& num_training_samples,
                                        unsigned int& num_generated_samples,
                                        int& seq,
                                        int& successor,
                                        int& predecessor) const
{
  is_learned = is_learned_;
  is_setup = is_setup_;
  is_start_set = is_start_set_;
  current_time = current_time_;
  num_training_samples = num_training_samples_;
  num_generated_samples = num_generated_samples_;
  seq = seq_;
  successor = successor_;
  predecessor = predecessor_;
  return true;
}

}
