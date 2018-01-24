/* Controls the integration for the simulation of springs. This is done using RK4.
 * This was built based on the example at: https://github.com/NCCA/MassSpring
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef RK4INTEGRATOR_H
#define RK4INTEGRATOR_H

#include "State.h"

class RK4Integrator
{
public:
  //Calculates the acceleration of a spring, implemented in Spring class, as it
  //  is virtual
  //params: _state is some initial position and velocity
  virtual ngl::Vec3 motionFunction(const State _state)=0;

  //The first step in integrating, evaluates without a previous state
  //params: _state is some initial position and velocity, _t is time
  State evaluate(const State &_initial, float _t);

  //The subsequent steps in integrating, evaluates with a previous state
  //params: _state is some initial position and velocity, _t is time, _dt is timestep,
  //  _d is previous
  State evaluate(const State &_initial,float _t, float _dt, const State &_d);

  //The actual RK4 part of this
  //params: _state is some initial position and velocity, _t is the time, _dt is
  //  the timestep, _k is the spring factor, and _damping is the damping factor
  void integrate(float _t,	 float _dt);

  //Holds position and velocity
  State m_state;
};

#endif // RK4INTEGRATOR_H
