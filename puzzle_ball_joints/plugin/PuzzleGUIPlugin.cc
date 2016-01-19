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

#include <sstream>
#include <gazebo/msgs/msgs.hh>
#include "PuzzleGUIPlugin.hh"

using namespace gazebo;

// Register this plugin with the simulator
GZ_REGISTER_GUI_PLUGIN(PuzzleGUIPlugin)

/////////////////////////////////////////////////
PuzzleGUIPlugin::PuzzleGUIPlugin()
  : GUIPlugin()
{
  this->setStyleSheet(
      "QFrame {"
        "background-color : black;"
        "color : white;"
        "font-size: 12px;"
      "}");

  auto gridLayout = new QGridLayout();

  // Titles
//  auto angleTitle = new QLabel(tr("Angle"));
//  gridLayout->addWidget(angleTitle, 0, 1);
//  gridLayout->setAlignment(angleTitle, Qt::AlignCenter);

//  auto torqueTitle = new QLabel(tr("Apply Torque"));
//  gridLayout->addWidget(torqueTitle, 0, 1, 1, 2);
//  gridLayout->setAlignment(torqueTitle, Qt::AlignCenter);

  // U
  gridLayout->addWidget(new QLabel(tr("U")), 1, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #00F}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 1, 1);
    this->connect(this, SIGNAL(UpdateUAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("U"));
    clockwise->setShortcut(tr("U"));
    gridLayout->addWidget(clockwise, 1, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnU()));

    auto counterClockwise = new QPushButton("U'");
    counterClockwise->setShortcut(tr("Shift+U"));
    gridLayout->addWidget(counterClockwise, 1, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnUPrime()));
  }

  // D
  gridLayout->addWidget(new QLabel(tr("D")), 2, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #FFF}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 2, 1);
    this->connect(this, SIGNAL(UpdateDAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("D"));
    clockwise->setShortcut(tr("D"));
    gridLayout->addWidget(clockwise, 2, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnD()));

    auto counterClockwise = new QPushButton("D'");
    counterClockwise->setShortcut(tr("Shift+D"));
    gridLayout->addWidget(counterClockwise, 2, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnDPrime()));
  }

  // R
  gridLayout->addWidget(new QLabel(tr("R")), 3, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #0F0}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 3, 1);
    this->connect(this, SIGNAL(UpdateRAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("R"));
    clockwise->setShortcut(tr("R"));
    gridLayout->addWidget(clockwise, 3, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnR()));

    auto counterClockwise = new QPushButton("R'");
    counterClockwise->setShortcut(tr("Shift+R"));
    gridLayout->addWidget(counterClockwise, 3, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnRPrime()));
  }

  // L
  gridLayout->addWidget(new QLabel(tr("L")), 4, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #FF0}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 4, 1);
    this->connect(this, SIGNAL(UpdateLAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("L"));
    clockwise->setShortcut(tr("L"));
    gridLayout->addWidget(clockwise, 4, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnL()));

    auto counterClockwise = new QPushButton("L'");
    counterClockwise->setShortcut(tr("Shift+L"));
    gridLayout->addWidget(counterClockwise, 4, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnLPrime()));
  }

  // F
  gridLayout->addWidget(new QLabel(tr("F")), 5, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #F00}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 5, 1);
    this->connect(this, SIGNAL(UpdateFAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("F"));
    clockwise->setShortcut(tr("F"));
    gridLayout->addWidget(clockwise, 5, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnF()));

    auto counterClockwise = new QPushButton("F'");
    counterClockwise->setShortcut(tr("Shift+F"));
    gridLayout->addWidget(counterClockwise, 5, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnFPrime()));
  }

  // B
  gridLayout->addWidget(new QLabel(tr("B")), 6, 0);
  {
    auto angle = new QLineEdit();
    angle->setStyleSheet("QLineEdit{background-color : #FFA500}");
    angle->setEnabled(false);
    gridLayout->addWidget(angle, 6, 1);
    this->connect(this, SIGNAL(UpdateBAngle(const QString &)), angle,
        SLOT(setText(const QString &)));

    auto clockwise = new QPushButton(tr("B"));
    clockwise->setShortcut(tr("B"));
    gridLayout->addWidget(clockwise, 6, 2);
    this->connect(clockwise, SIGNAL(clicked()), this, SLOT(OnB()));

    auto counterClockwise = new QPushButton("B'");
    counterClockwise->setShortcut(tr("Shift+B"));
    gridLayout->addWidget(counterClockwise, 6, 3);
    this->connect(counterClockwise, SIGNAL(clicked()), this, SLOT(OnBPrime()));
  }

  // Torque magnitude
  this->torque = 10000;
  gridLayout->addWidget(new QLabel(tr("Torque")), 7, 0, 1, 2);
  auto torque = new QSpinBox();
  torque->setMaximum(1000000);
  torque->setValue(this->torque);
  gridLayout->addWidget(torque, 7, 2, 1, 2);
  this->connect(torque, SIGNAL(valueChanged(int)), this, SLOT(OnTorque(int)));

  // Fix center
  auto fix = new QCheckBox();
  gridLayout->addWidget(fix, 8, 0);
  gridLayout->addWidget(new QLabel(tr("Fix to world")), 8, 1, 1, 3);
  this->connect(fix, SIGNAL(toggled(const bool)), this,
      SLOT(OnFix(const bool)));

  auto mainFrame = new QFrame();
  mainFrame->setLayout(gridLayout);

  auto mainLayout = new QHBoxLayout;
  mainLayout->addWidget(mainFrame);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  this->setLayout(mainLayout);
  this->resize(150, 270);

  // Transport
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init();

  this->uPub = this->node->Advertise<msgs::Int>("~/puzzle/u");
  this->dPub = this->node->Advertise<msgs::Int>("~/puzzle/d");
  this->rPub = this->node->Advertise<msgs::Int>("~/puzzle/r");
  this->lPub = this->node->Advertise<msgs::Int>("~/puzzle/l");
  this->fPub = this->node->Advertise<msgs::Int>("~/puzzle/f");
  this->bPub = this->node->Advertise<msgs::Int>("~/puzzle/b");
  this->fixPub = this->node->Advertise<msgs::Int>("~/puzzle/fix");
}

/////////////////////////////////////////////////
PuzzleGUIPlugin::~PuzzleGUIPlugin()
{
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::Load(sdf::ElementPtr _elem)
{
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnTorque(const int _torque)
{
  this->torque = _torque;
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnU()
{
/*
  msgs::JointCmd msg;
  msg.set_name(_name);
  msg.set_force(_value);
  this->dataPtr->jointPub->Publish(msg);
*/
  msgs::Int msg;
  msg.set_data(this->torque);
  this->uPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnD()
{
  msgs::Int msg;
  msg.set_data(this->torque);
  this->dPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnR()
{
  msgs::Int msg;
  msg.set_data(this->torque);
  this->rPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnL()
{
  msgs::Int msg;
  msg.set_data(this->torque);
  this->lPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnF()
{
  msgs::Int msg;
  msg.set_data(this->torque);
  this->fPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnB()
{
  msgs::Int msg;
  msg.set_data(this->torque);
  this->bPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnUPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->uPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnDPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->dPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnRPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->rPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnLPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->lPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnFPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->fPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnBPrime()
{
  msgs::Int msg;
  msg.set_data(-this->torque);
  this->bPub->Publish(msg);
}

/////////////////////////////////////////////////
void PuzzleGUIPlugin::OnFix(const bool _checked)
{
  msgs::Int msg;
  msg.set_data(_checked);
  this->fixPub->Publish(msg);
}

