/* File: Spring.cpp
 * Represents the springs that go between points on a hair. Note, springs are
 * attached to joints at the end of the spring (posB).
*/

#include "Spring.h"
#include "RK4Integrator.h"

Spring::Spring(ngl::Vec3 _A, ngl::Vec3 _B, float _length, float _k, float _damping, bool _fixedA, bool _fixedB, char _type)
{
  m_posA = _A;
  m_posB = _B;
  m_length = _length;
  m_k = _k;
  m_damping = _damping;
  m_t = 0.0;
  m_timestep = .2;

  m_state.m_position = m_posB - m_posA;
  m_state.m_velocity = 0;

  m_fixedA = _fixedA;
  m_fixedB = _fixedB;

  m_type = _type;
}

void Spring::update()
{
  integrate(m_t, m_timestep);
  m_t += m_timestep;
  if (!m_fixedA){
    m_posA-=m_state.m_velocity;
  }
  if (!m_fixedB){
    m_posB+=m_state.m_velocity;
  }
}

ngl::Vec3 Spring::motionFunction(	const State _state)
{
  ngl::Vec3 distance=m_posB-m_posA;
  float length=distance.length();
  ngl::Vec3 output = -m_k*(length-m_length)*(distance/length)-m_damping*_state.m_velocity;
  return output;
}


