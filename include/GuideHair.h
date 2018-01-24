/* Represents a hair on the scalp, the basis of the simulation.
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef GUIDEHAIR_H
#define GUIDEHAIR_H

#include "HairJoint.h"
#include "FollowHair.h"
#include "Scalp.h"
#include <vector>

#include <ngl/Vec3.h>

class GuideHair
{
  public:
    //Constructor, builds a set up of points to represent a hair, then connects
    //  springs to each point
    //params: _a is the root of the hair, _sections is how many full spring
    //  sections to use (5 points and 8 springs = 1 section)
    GuideHair(ngl::Vec3 _a, int _sections);

    //Updates the positions and forces acting on all parts of the hair
    //params: _scalp is the head which the hair is attached to, used for
    //  collisions
    void updateJoints(Scalp _scalp);

    //Controls how much a hair pushes off the scalp, a simplified method useful
    //  for debugging
    //params: _scalp is the head which the hair is attached to, _curIndex
    // is how far along the hair the point is
    void simpleCollision(Scalp _scalp, int _curIndex);

    //Controls how much a hair pushes off the scalp
    //params: _scalp is the head which the hair is attached to, _curIndex
    // is how far along the hair the point is
    void complexCollision(Scalp _scalp, int _curIndex);

    //Stores the points of the hair
    std::vector<HairJoint> m_hJoints;

    //Stores follow hairs which will be drawn
    std::vector<FollowHair> m_followHairs;

    //The a summation of forces, from each of the springs
    ngl::Vec3 m_totalUpdate;

    //A vector used to calculate if a point is too close to the scalp
    ngl::Vec3 m_realPos;

    //The surface normal of the scalp at which the root of the hair is
    ngl::Vec3 m_rootNormal;
};

#endif // GUIDEHAIR_H
