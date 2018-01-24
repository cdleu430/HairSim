/* Holds data about position and velocity, could have been a struct.
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef STATE_H
#define STATE_H

#include <ngl/Vec3.h>

class State
{
  public:
    State();
    ngl::Vec3 m_position;
    ngl::Vec3 m_velocity;
};

#endif // STATE_H
