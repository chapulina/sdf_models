/*
 * Copyright (C) 2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef _PUZZLE_MODEL_PLUGIN_HH_
#define _PUZZLE_MODEL_PLUGIN_HH_

#include <map>
#include "gazebo/common/Event.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/math/Vector3.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/transport.hh"

namespace gazebo
{
  /// \brief A plugin that simulates buoyancy of an object immersed in fluid.
  class GAZEBO_VISIBLE PuzzleModelPlugin : public ModelPlugin
  {
    /// \brief Constructor.
    public: PuzzleModelPlugin();

    /// \brief Read the model SDF to compute volume and center of volume for
    /// each link, and store those properties in volPropsMap.
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

    private: void OnU(ConstIntPtr &_msg);
    private: void OnD(ConstIntPtr &_msg);
    private: void OnR(ConstIntPtr &_msg);
    private: void OnL(ConstIntPtr &_msg);
    private: void OnF(ConstIntPtr &_msg);
    private: void OnB(ConstIntPtr &_msg);
    private: void OnFix(ConstIntPtr &_msg);

    /// \brief Pointer to model containing the plugin.
    private: physics::ModelPtr model;
    private: physics::JointPtr uJoint;
    private: physics::JointPtr dJoint;
    private: physics::JointPtr rJoint;
    private: physics::JointPtr lJoint;
    private: physics::JointPtr fJoint;
    private: physics::JointPtr bJoint;
    private: physics::JointPtr worldJoint;

    /// \brief Node used to establish communication with gzserver.
    private: transport::NodePtr node;
    private: transport::SubscriberPtr uSub;
    private: transport::SubscriberPtr dSub;
    private: transport::SubscriberPtr rSub;
    private: transport::SubscriberPtr lSub;
    private: transport::SubscriberPtr fSub;
    private: transport::SubscriberPtr bSub;

    private: transport::SubscriberPtr fixSub;
  };
}

#endif
