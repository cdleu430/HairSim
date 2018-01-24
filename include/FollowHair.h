/* Represents a hair to be drawn on the scalp, this hair follows the calculations
 *   of a guide hair.
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef FOLLOWHAIR_H
#define FOLLOWHAIR_H

#include "HairJoint.h"

#include <vector>
#include <ngl/Vec3.h>

class FollowHair
{
  public:
    //Constructor, builds a set up of points to represent a hair
    //params: _a is the root of the hair, _sections is how many full spring
    //  sections to use (5 points = 1 section)
    FollowHair(ngl::Vec3 _a, int _sections);

    //holds the points of the hair
    std::vector<HairJoint> m_hJoints;

    //a vector that expresses the offset of this follow hair from its guide
    ngl::Vec3 offset;
};


#endif // FOLLOWHAIR_H
