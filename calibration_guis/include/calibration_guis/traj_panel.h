#ifndef TELEOP_PANEL_H
#define TELEOP_PANEL_H

#include <ros/ros.h>
#include <QLabel>
#include <rviz/panel.h>
#include <calibration_guis/drive_widget.h>

/*
#ifndef Q_MOC_RUN
# include <ros/ros.h>
# include <rviz/panel.h>
#endif
*/

namespace calibration_guis
{

class TrajectoryPanel: public rviz::Panel
{
  // This class uses Qt slots and is a subclass of QObject, so it needs
  // the Q_OBJECT macro.
  Q_OBJECT
 public:
  // QWidget subclass constructors usually take a parent widget
  // parameter (which usually defaults to 0).  At the same time,
  // pluginlib::ClassLoader creates instances by calling the default
  // constructor (with no arguments).  Taking the parameter and giving
  // a default of 0 lets the default constructor work and also lets
  // someone using the class for something else to pass in a parent
  // widget as they normally would with Qt.
  TrajectoryPanel( QWidget* parent = 0 );

  ros::ServiceClient captureClient_;
  ros::ServiceClient executeClient_;
  ros::ServiceClient moveNextClient_;
  ros::ServiceClient moveStartClient_;
  ros::ServiceClient executeWCallClient_;
  ros::ServiceClient movePrevClient_;
  ros::ServiceClient moveEndClient_;
  // Now we declare overrides of rviz::Panel functions for saving and
  // loading data from the config file.  Here the data is the
  // topic name.
  virtual void load( const rviz::Config& config );
  virtual void save( rviz::Config config ) const;

  // Next come a couple of public Qt slots.
  public Q_SLOTS:
    void setbutton1Clicked ();
    void setbutton2Clicked ();
    void setbutton3Clicked ();
    void setbutton4Clicked ();
    void setbutton5Clicked ();
    void setbutton6Clicked ();
    void setbutton7Clicked ();
    // The control area, DriveWidget, sends its output to a Qt signal
    // for ease of re-use, so here we declare a Qt slot to receive it.
    void setVel( float linear_velocity_, float angular_velocity_ );

    // In this example setTopic() does not get connected to any signal
    // (it is called directly), but it is easy to define it as a public
    // slot instead of a private function in case it would be useful to
    // some other user.
    void setTopic( const QString& topic );

    /*    // Here we declare some internal slots.
    protected Q_SLOTS:
    */
    // sendvel() publishes the current velocity values to a ROS
    // topic.  Internally this is connected to a timer which calls it 10
    // times per second.
    void sendVel();
    
    // updateTopic() reads the topic name from the QLineEdit and calls
    // setTopic() with the result.
    void updateTopic();
    
    // Then we finish up with protected member variables.
 private:
      // The control-area widget which turns mouse events into command
      // velocities.
      DriveWidget* drive_widget_;

      // One-line text editor for entering the outgoing ROS topic name.
      QLineEdit* output_topic_editor_;

      // The current name of the output topic.
      QString output_topic_;

      // The ROS publisher for the command velocity.
      ros::Publisher velocity_publisher_;

      // The ROS node handle.
      ros::NodeHandle nh_;

      // The latest velocity values from the drive widget.
      float linear_velocity_;
      float angular_velocity_;
      // END_TUTORIAL
};

} // end namespace calibration_guis

#endif // TELEOP_PANEL_H
