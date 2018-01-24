/* Represents a point on hair, hair can bend at these locations.
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef HAIRJOINT_H
#define HAIRJOINT_H

#include "Spring.h"

#include <ngl/Vec3.h>
#include <vector>

class HairJoint
{
public:
  //Constructor, places a joint at a specific position with a given velocity,
  //  usually starting veloctiy is gravity
  //params: _position is where the joint is, _veloctity is the rate of change
  HairJoint(ngl::Vec3 _position, ngl::Vec3 _velocity);

  //Constructor, places a joint at a specific position with a given velocity,
  //  usually starting veloctiy is gravity, adds any connected springs to the
  //  joint
  //params: _position is where the joint is, _veloctity is the rate of change,
  //  _springs is a collection of springs to attach to it
  HairJoint(ngl::Vec3 _position, ngl::Vec3 _velocity, std::vector<Spring> _springs);

  //The position of the joint
  ngl::Vec3 m_position;

  //The velocity of the joint
  ngl::Vec3 m_velocity;

  //The springs attached to a joint
  std::vector<Spring> m_springs;
};

#endif // HAIRJOINT_H
