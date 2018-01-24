/* File: State.cpp
 * Represents position and velocity, could have been a struct.
*/

#include "State.h"

State::State()
{
  m_position = ngl::Vec3(0, 0, 0);
  m_velocity = ngl::Vec3(0, 0, 0);
}
