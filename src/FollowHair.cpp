/* File: FollowHair.cpp
 * Represents a hair to be drawn on the scalp, this hair follows the calculations
 *   of a guide hair. Note that no springs are connect here, unlike the guide hair.
 *   These hairs cannot update forces themselves and only follow a guide hair.
*/

#include "FollowHair.h"

#include <ngl/NGLStream.h>
#include <vector>

FollowHair::FollowHair(ngl::Vec3 _root, int _sections)
{
  //Creates a list of the positions to be used
  std::vector<ngl::Vec3> positions = {};
  for (int i = 0; i < 5 * _sections; i++)
  {
    if (i % 2 == 0)
    {
      positions.push_back(ngl::Vec3(_root.m_x, _root.m_y, _root.m_z + i));
    } else {
      positions.push_back(ngl::Vec3(_root.m_x + .5, _root.m_y + .5, _root.m_z + i));
    }
  }

  //Adds Joints at the corresponding places
  HairJoint firstJoint(positions[0], ngl::Vec3(0, -1, 0));
  m_hJoints.push_back(firstJoint);
  for (int i = 1; i < 5+((_sections-1)*4); i++)
  {
    HairJoint buildJoint(positions[i], ngl::Vec3(0, -1, 0));
    m_hJoints.push_back(buildJoint);
  }

}
