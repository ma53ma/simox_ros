/*
 * Copyright (c) 2013 Shadow Robot Company Ltd.
 *  All rights reserved.
 *
 * This code is proprietary and may not be used, copied, distributed without
 *  prior authorisation and agreement from Shadow Robot Company Ltd.
 */

/**
 * @file   urdf_to_simox_xml.hpp
 * @author Yi Li <yi@shadowrobot.com>
 * @brief  Convert from a hand description in URDF format to Simox XML.
 **/

#pragma once

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/actions/SoWriteAction.h>

#include <urdf/model.h>

namespace gsc
{

class UrdfToSimoxXml
{
public:
  UrdfToSimoxXml(const bool urdf_init_param,
                 const std::string urdf_file,
                 const std::string output_dir);
  ~UrdfToSimoxXml();

  void write_xml(const std::string& output_dir,
                 const std::string& simox_xml_filename);

  static bool compareUrdfJoint(boost::shared_ptr<urdf::Joint> j1,
                               boost::shared_ptr<urdf::Joint> j2);

private:
  void add_hand_base_node_(boost::property_tree::ptree & hand_node,
                           const std::string & hand_base,
                           const std::string & hand_tcp,
                           const std::string & hand_gcp,
                           const std::string & base_link);

  void add_hand_tcp_node_(boost::property_tree::ptree & hand_node,
                          const std::string & hand_tcp);

  void add_hand_gcp_node_(boost::property_tree::ptree & hand_node,
                          const std::string & hand_gcp);

  void add_link_node_(boost::property_tree::ptree & hand_node,
                      boost::shared_ptr<const urdf::Link> link);

  void add_joint_node_(boost::property_tree::ptree & hand_node,
                       boost::shared_ptr<const urdf::Joint> child_joint);

private:
  void add_endeffector_node_(boost::property_tree::ptree & hand_node,
                             const std::string & hand_name_upper,
                             const std::string & hand_base,
                             const std::string & hand_tcp,
                             const std::string & hand_gcp,
                             const std::string & base_link);

  void add_hand_joints_node_(boost::property_tree::ptree & hand_node,
                             const std::string & hand_name_upper);

  void get_actors(std::map<int, bool>& actors);

private:
  void set_joint_limits_node_(boost::property_tree::ptree & Limits_node,
                              boost::shared_ptr<urdf::JointLimits> limits);

  void set_axis_node_(boost::property_tree::ptree & Axis_node,
                      urdf::Vector3 axis);

  void set_axis_node_(boost::property_tree::ptree & Axis_node,
                      double x, double y, double z);

  void set_translation_node_(boost::property_tree::ptree & Translation_node,
                             urdf::Vector3 position);

  void set_translation_node_(boost::property_tree::ptree & Translation_node,
                             double x, double y, double z);

  void set_rollpitchyaw_node_(boost::property_tree::ptree & Translation_node,
                              urdf::Rotation rotation);

  void set_rollpitchyaw_node_(boost::property_tree::ptree & Translation_node,
                              double roll, double pitch, double yaw);

  std::string convert_cube_(const std::string & link_name,
                            const double & width,
                            const double & height,
                            const double & depth);
  std::string convert_cylinder_(const std::string & link_name,
                                const double & height,
                                const double & radius);
  std::string convert_sphere_(const std::string & link_name,
                              const double & radius);
  std::string convert_mesh_(const std::string & urdf_filename);

  void write_to_iv_file_(const std::string & file_name,
                         SoSeparator *scene_with_shape);

  std::string to_string_(double x);

private:
  boost::scoped_ptr<urdf::Model> urdf_model_;

  std::string output_dir_;

  std::vector< boost::shared_ptr<urdf::Link> > links_;

  std::vector< boost::shared_ptr<urdf::Joint> > joints_;

  static const std::string mesh_dir_name_;
};

}
