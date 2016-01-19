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
#ifndef _PUZZLE_GUI_PLUGIN_HH_
#define _PUZZLE_GUI_PLUGIN_HH_

#include <string>
#include <vector>
#include <boost/thread/mutex.hpp>

#include <gazebo/common/Events.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Timer.hh>
#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
# include <gazebo/transport/transport.hh>
# include <gazebo/gui/gui.hh>
#endif

namespace gazebo
{
  /// \brief A GUI plugin that controls a puzzle in simulation.
  class GAZEBO_VISIBLE PuzzleGUIPlugin : public GUIPlugin
  {
    Q_OBJECT

    /// \brief Constructor
    public: PuzzleGUIPlugin();

    /// \brief Destructor
    public: virtual ~PuzzleGUIPlugin();

    // Documentation inherited
    public: void Load(sdf::ElementPtr _elem);

    signals: void UpdateUAngle(const QString &_angle);
    signals: void UpdateDAngle(const QString &_angle);
    signals: void UpdateRAngle(const QString &_angle);
    signals: void UpdateLAngle(const QString &_angle);
    signals: void UpdateFAngle(const QString &_angle);
    signals: void UpdateBAngle(const QString &_angle);

    private slots: void OnTorque(const int _torque);
    private slots: void OnU();
    private slots: void OnD();
    private slots: void OnR();
    private slots: void OnL();
    private slots: void OnF();
    private slots: void OnB();
    private slots: void OnUPrime();
    private slots: void OnDPrime();
    private slots: void OnRPrime();
    private slots: void OnLPrime();
    private slots: void OnFPrime();
    private slots: void OnBPrime();

    private slots: void OnFix(const bool _checked);

    /// \brief Node used to establish communication with gzserver.
    private: transport::NodePtr node;
    private: transport::PublisherPtr uPub;
    private: transport::PublisherPtr dPub;
    private: transport::PublisherPtr rPub;
    private: transport::PublisherPtr lPub;
    private: transport::PublisherPtr fPub;
    private: transport::PublisherPtr bPub;
    private: transport::PublisherPtr fixPub;

    private: int torque;
  };
}

#endif
