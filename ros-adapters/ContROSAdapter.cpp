#include "ContROSAdapter.h"

int
main(int argc, char** argv)
{

    ContROSAdapter* adapter = new ContROSAdapter();
    adapter->init(argc, argv);

    adapter->run(true);

    
    adapter->finalize();
}

ContROSAdapter::ContROSAdapter()
{
    port_in = new ContInPort();
    port_out = new ROSOutPort();

}

void ContROSAdapter::init(int argc, char** argv)
{

    std::cout << "cont ros adapter init" << std::endl;
    Adapter::init(argc, argv);

    // config needed for this specific adapter
    
    std::string _msg_type;
    setup->config("message_type", &_msg_type);
    setup->config("ros_topic", &ros_topic);
    setup->config("command_update_rate", &command_update_rate);
    setup->config("ros_node_name", &ros_node_name);
    setup->config("message_mapping_filename", &mapping_filename);
    readMappingFile();

    static_cast<ROSOutPort*>(port_out)->initROS(argc, argv, ros_node_name.c_str());
    
    switch (msg_type)
    {   
        case Float64MultiArray:
        {
            publisher = static_cast<ROSOutPort*>(port_out)->ros_node->advertise<std_msgs::Float64MultiArray>(ros_topic, 1);
            break;
        }
        case Twist: 
        {
            publisher = static_cast<ROSOutPort*>(port_out)->ros_node->advertise<geometry_msgs::Twist>(ros_topic, 1);
            break;
        }
    }

    std::cout << command_update_rate <<  " cmd " << 1./ (command_update_rate * rtf) << std::endl;
    clock = new RTClock( 1. / (command_update_rate * rtf) );
}

void
ContROSAdapter::tick()
{
}

void
ContROSAdapter::asyncTick()
{
    //std::cout << "cont ros atick " << std::endl; 
    sendROS();
    ros::spinOnce();
    clock->sleepNext();
}

void
ContROSAdapter::sendROS ()
{
  switch (msg_type)
  {   
      case Float64MultiArray:
      {
          std_msgs::Float64MultiArray msg;
          for (int i = 0; i < port_in->data_size; ++i)
          {
              msg.data.push_back(port_in->data[i]);
          }
          publisher.publish(msg);
          break;
      }

      case Twist: 
      {
          for (int i = 0; i < port_in->data_size; ++i)
          {
              if (port_in->data[i] > max_msg)
              {
                  port_in->data[i] = max_msg;
              }
              else if (port_in->data[i] < min_msg)
              {
                  port_in->data[i] = min_msg;
              }
          }

          geometry_msgs::Twist msg;
          
          msg.linear.x = *msg_map[0];
          msg.linear.y = *msg_map[1];
          msg.linear.z = *msg_map[2];

          msg.angular.x = *msg_map[3];
          msg.angular.y = *msg_map[4];
          msg.angular.z = *msg_map[5];
     
          publisher.publish(msg);
          break;
      }
  }
}


void 
ContROSAdapter::readMappingFile()
{
    Json::Reader json_reader;

    std::ifstream mapping_file;
    mapping_file.open(mapping_filename.c_str(), std::ios::in);
    string json_mapping_= "";
    string line;

    while (std::getline(mapping_file, line))
    {
        json_mapping_ += line;
    }
    mapping_file.close();
    
    if ( !json_reader.parse(json_mapping_, json_mapping))
    {
        // report to the user the failure and their locations in the document.
        std::cout   << "WARNING: ROS Command Adapter: Failed to parse file \"" << mapping_filename << "\"\n" 
                    << json_mapping_ << " It has to be in JSON format.\n"
                    << json_reader.getFormattedErrorMessages();
        return;
    }
    else
    {
        std::string _msg_type;
        _msg_type = json_mapping["message_type"].asString();
        if (_msg_type.compare("Float64MultiArray") == 0)
        {
            msg_type = Float64MultiArray;
            // no mapping needed
        }
        else if (_msg_type.compare("Twist") == 0)
        {
            const char *components[] = {
                "linear.x", "linear.y", "linear.z",
                "angular.x", "angular.y", "angular.z"
            };
            const size_t n_components = sizeof(components) / sizeof(components[0]);
            
            msg_type = Twist;
            null = 0;

            for (size_t index = 0; index < n_components; index++)
            {
                msg_map[index] = &null;
                if (json_mapping["mapping"].isMember(components[index])){
                    msg_map[index] = &(port_in->data[json_mapping["mapping"].get(components[index], -1).asInt()]);
                }
            }

            min_msg = 0;
            max_msg = 0;
            min_msg = json_mapping["min"].asDouble();
            max_msg = json_mapping["max"].asDouble();
            
            if (max_msg == 0 && min_msg == 0)
            {
                std::cout << "WARNING: min and max of Twist msg is 0" << std::endl;
            }
        }
        else
        {
            std::cout << "ERROR: msg type unknown" << std::endl;
            finalize();
        }

    }

}



