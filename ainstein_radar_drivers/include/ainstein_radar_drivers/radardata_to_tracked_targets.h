#ifndef RADAR_DATA_TO_TRACKED_TARGETS_H_
#define RADAR_DATA_TO_TRACKED_TARGETS_H_

#include <thread>
#include <ros/ros.h>
#include <ainstein_radar_msgs/RadarTargetArray.h>
#include <ainstein_radar_drivers/radar_target_kf.h>

namespace ainstein_radar_drivers
{
  class RadarDataToTrackedTargets
  {
  public:
    RadarDataToTrackedTargets( const ros::NodeHandle& node_handle,
			       const ros::NodeHandle& node_handle_private ) :
    nh_( node_handle ),
    nh_private_( node_handle_private ) {}

    ~RadarDataToTrackedTargets() {}

    void initialize( void );
    void updateFiltersLoop( double frequency );
    
    void radarDataCallback( const ainstein_radar_msgs::RadarTargetArray::Ptr &msg );

    static const int max_tracked_targets;
    
  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    // Parameters:
    double filter_update_rate_;
    double filter_min_time_;
    double filter_timeout_;
    double filter_val_gate_thresh_;
    
    ros::Subscriber sub_radar_data_raw_;
    ros::Publisher pub_radar_data_tracked_;
    ainstein_radar_msgs::RadarTargetArray msg_tracked_;
    
    std::unique_ptr<std::thread> filter_update_thread_;
    
    std::vector<ainstein_radar_drivers::RadarTargetKF> filters_;
    std::vector<int> meas_count_vec_;
  };

} // namespace ainstein_radar_drivers

#endif // RADAR_DATA_TO_TRACKED_TARGETS_H_