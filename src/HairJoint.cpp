/* File: HairJoint.cpp
 * Represents a point of the hair, where the hair can bend. Holds position and
 *   velocity and which springs are attached to it. Note that springs are attached
 *   at the end of the spring.
*/

#include "HairJoint.h"

HairJoint::HairJoint(ngl::Vec3 _position, ngl::Vec3 _velocity)
{
  m_position = _position;
  m_velocity = _velocity;
}

HairJoint::HairJoint(ngl::Vec3 _position, ngl::Vec3 _velocity, std::vector<Spring> _springs)
{
  m_position = _position;
  m_velocity = _velocity;
  m_springs = _springs;
}
