/* Represents a spring between 2 points on a hair.
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef SPRING_H
#define SPRING_H

#include <ngl/Vec3.h>
#include "RK4Integrator.h"

class Spring : public RK4Integrator
{
public:
  //Constructor, places a spring between _A and _B, with the specified properties
  //params: _A and _B and the ends of the spring, _length is the rest length, _k
  //  is the spring factor, _damping is the damping factor, _fixedA and _fixedB
  //  are which sides are stationary, _type is what kind of spring it is (edge,
  //  torsion, or bending
  Spring(ngl::Vec3 _A, ngl::Vec3 _B, float _length, float _k, float _damping, bool _fixedA, bool _fixedB, char _type);

  //Updates the forces of the spring
  void update();

  //Calculates the acceleration for a spring
  ngl::Vec3 motionFunction(const State _state);

  //The spring factor
  float m_k;

  //The damping factor
  float m_damping;

  //Velocity
  ngl::Vec3 m_velocity;

  //Position of head of the spring
  ngl::Vec3 m_posA;

  //Position of the end of the spring
  ngl::Vec3 m_posB;

  //Rest length of the spring
  float m_length;

  //Time
  float m_t;

  //Timestep
  float m_timestep;

  //If this end of the spring is stationary
  bool m_fixedA;

  //If this end of the spring is stationary
  bool m_fixedB;

  //What type of spring it is (e, t, b : edge, torsion, bending)
  char m_type;
};
#endif // SPRING_H
