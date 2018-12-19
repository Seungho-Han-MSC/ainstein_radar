/*
Copyright <2018> <Ainstein, Inc.>

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided
with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "RadarDataViz.h"

int main( int argc, char** argv )
{
  // Initialize ROS node:
  ros::init( argc, argv, "radar_data_viz_node" );

  // Data viz constructor arguments:
  std::string data_topic;
  std::string marker_topic;
    
  // Parse the command line arguments for radar parameters:
  if( argc < 2 )
    {
      std::cerr << "Usage: rosrun radar_ros_interface radar_data_viz_node --topic TOPIC" << std::endl;
      return -1;
    }

  // Parse the command line arguments:
  for( int i = 0; i < argc; ++i )
    {
      // Check for the data topic name:
      if( std::string( argv[i] ) == std::string( "--topic" ) )
	{
	  data_topic = std::string( argv[++i] );
	}
    }

  if( data_topic.empty() )
    {
      std::cerr << "Data topic name must be set. Usage: rosrun radar_ros_interface radar_data_viz_node --topic TOPIC" << std::endl;
      return -1;
    }

  marker_topic = data_topic + "_marker_array";
  
  std::cout << "Running radar data viz node with data topic: " << data_topic << " marker topic: " << marker_topic << std::endl;
    
  // Create visualization node to publish target markers:
  RadarDataViz data_viz( data_topic, marker_topic );

  ros::spin();

  return 0;
}
