/*
 * Copyright (C) 2015 Open Source Robotics Foundation
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

#include "gazebo/common/Assert.hh"
#include "gazebo/common/Events.hh"
#include "PuzzleModelPlugin.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(PuzzleModelPlugin)

/////////////////////////////////////////////////
PuzzleModelPlugin::PuzzleModelPlugin()
{
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;
  GZ_ASSERT(this->model != NULL, "Received NULL model pointer");

  // Joints
  this->uJoint = this->model->GetJoint("center_joint_0_0_1");
  GZ_ASSERT(this->uJoint != NULL, "No U joint");
  this->dJoint = this->model->GetJoint("center_joint_0_0_-1");
  GZ_ASSERT(this->dJoint != NULL, "No D joint");
  this->rJoint = this->model->GetJoint("center_joint_0_1_0");
  GZ_ASSERT(this->rJoint != NULL, "No R joint");
  this->lJoint = this->model->GetJoint("center_joint_0_-1_0");
  GZ_ASSERT(this->lJoint != NULL, "No L joint");
  this->fJoint = this->model->GetJoint("center_joint_1_0_0");
  GZ_ASSERT(this->fJoint != NULL, "No F joint");
  this->bJoint = this->model->GetJoint("center_joint_-1_0_0");
  GZ_ASSERT(this->bJoint != NULL, "No B joint");

  // Transport
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init();

  this->uSub =
    this->node->Subscribe("~/puzzle/u", &PuzzleModelPlugin::OnU, this);
  this->dSub =
    this->node->Subscribe("~/puzzle/d", &PuzzleModelPlugin::OnD, this);
  this->rSub =
    this->node->Subscribe("~/puzzle/r", &PuzzleModelPlugin::OnR, this);
  this->lSub =
    this->node->Subscribe("~/puzzle/l", &PuzzleModelPlugin::OnL, this);
  this->fSub =
    this->node->Subscribe("~/puzzle/f", &PuzzleModelPlugin::OnF, this);
  this->bSub =
    this->node->Subscribe("~/puzzle/b", &PuzzleModelPlugin::OnB, this);
  this->fixSub =
    this->node->Subscribe("~/puzzle/fix", &PuzzleModelPlugin::OnFix, this);
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnU(ConstIntPtr &_msg)
{
  this->uJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnD(ConstIntPtr &_msg)
{
  this->dJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnR(ConstIntPtr &_msg)
{
  this->rJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnL(ConstIntPtr &_msg)
{
  this->lJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnF(ConstIntPtr &_msg)
{
  this->fJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnB(ConstIntPtr &_msg)
{
  this->bJoint->SetForce(0, _msg->data());
}

/////////////////////////////////////////////////
void PuzzleModelPlugin::OnFix(ConstIntPtr &_msg)
{
  bool fix = _msg->data();

  if (fix)
  {
    this->model->SetWorldPose(math::Pose(math::Vector3(0, 0, 2), math::Quaternion()));

    this->worldJoint =
        this->model->GetWorld()->GetPhysicsEngine()->CreateJoint("fixed",
        this->model);

    auto core = this->model->GetLink("cubie_0_0_0");
    this->worldJoint->Attach(0, core);
    this->worldJoint->Load(0, core, math::Pose::Zero);
  }
  else
  {
    this->worldJoint->Detach();
  }
}
