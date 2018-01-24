/* File: GuideHair.cpp
 * Represents a hair that is the central part of the simulation. Note this hair
 *   is not drawn in the draw calls, but its movement is passed on to follow hairs.
*/

#include "GuideHair.h"

#include <vector>

GuideHair::GuideHair(ngl::Vec3 _root, int _sections)
{
  //K, D and L (spring and dampening factor, and length), are a bit sensitive
  //  so they are kept away from the interface of the demo, these constants
  //  were arrived at through trial and error
  //For straight hair: the length of bending and torsion springs should be 4x
  //  the edge springs. Dynamic properties will not behave properly though.
  float k = 10;
  float d = 11;
  float l = 2;

  //bending springs
  float bK = 10;
  float bD = 11;
  float bL = 2;

  //torsion springs
  float tK = 10;
  float tD = 11;
  float tL = 2;

  //Creates a list of positions to put points on
  std::vector<ngl::Vec3> positions;
  for (int i = 0; i < 5 * _sections; i++)
  {
    if (i % 2 == 0)
    {
      positions.push_back(ngl::Vec3(_root.m_x, _root.m_y, _root.m_z + i));
    } else {
      positions.push_back(ngl::Vec3(_root.m_x + .5f, _root.m_y + .5f, _root.m_z + i));
    }
  }

  //Put springs into their own lists for easy access later
  std::vector<Spring> builderEdge;
  std::vector<Spring> builderBend;
  std::vector<Spring> builderTor;

  Spring firstEdgeSpring(positions[0], positions[1], l, k, d, true, false, 'e');
  builderEdge.push_back(firstEdgeSpring);
  Spring firstBendSpring(positions[0], positions[2], bL, bK, bD, true, false, 'b');
  builderBend.push_back(firstBendSpring);
  Spring firstTorSpring(positions[0], positions[3], tL, tK, tD, true, false, 't');
  builderTor.push_back(firstTorSpring);


  for (int i = 1; i < 4*_sections ; i++)
  {
    Spring buildSpring(positions[i], positions[i+1], l, k, d, false, false, 'e');
    builderEdge.push_back(buildSpring);
  }

  for (int i = 2; i < 5*_sections; i++)
  {
    Spring buildSpring(positions[i-2], positions[i], bL, bK, bD, false, false, 'b');
    builderBend.push_back(buildSpring);
  }
  for (int i = 3; i < 5*_sections; i++)
  {
    Spring buildSpring(positions[i-3], positions[i], tL, tK, tD, false, false, 't');
    builderTor.push_back(buildSpring);
  }

  //Assign hair joints to the positions and add the springs
  HairJoint firstJoint(positions[0], ngl::Vec3(0, -1, 0));
  m_hJoints.push_back(firstJoint);

  int bendIndex = 0;
  int torIndex = 0;
  for (int i = 1; i < 5+((_sections-1)*4); i++)
  {
    std::vector<Spring> build;
    build.push_back(builderEdge[i-1]);
    if (i > 1) {
      build.push_back(builderBend[bendIndex]);
    }
    if (i > 2){
      build.push_back(builderTor[torIndex]);
    }
    HairJoint buildJoint(positions[i], ngl::Vec3(0, -1, 0), build);
    m_hJoints.push_back(buildJoint);
  }
}

void GuideHair::updateJoints(Scalp _scalp)
{
  //Go through each joint
  for (int j = 0; j < m_hJoints.size(); j++)
  {
    //Go through each spring on the joint
    for (auto &spring: m_hJoints[j].m_springs)
    {
      spring.update(); // update the spring
      m_totalUpdate += spring.m_state.m_velocity;
    }

    if (j != 0) //the root/anchor of the hair
    {
      complexCollision(_scalp, j);
    }

    //Scalp penetration detection
    m_realPos = m_hJoints[j].m_position - _scalp.getPos();
    float len = m_realPos.length();
    float minDist = _scalp.getRadius();
    if(len<=minDist)
    {
      float grow = 1 - (len/minDist);
      m_realPos = m_realPos * (grow+.05f); //constant keeps the hair slightly off the scalp
      m_hJoints[j].m_position += m_realPos;
    }
    m_totalUpdate.null();

    //set the correct position of the ends of each spring to match the joints, in cases of joints with multiple springs this is necessary
    for (auto &spring: m_hJoints[j].m_springs)
    {
      //adjust end of spring to take into account any changes after it updated
      spring.m_posB = m_hJoints[j].m_position;
      //adjust head of spring
      if (spring.m_type == 't')
      {
        spring.m_posA = m_hJoints[j-3].m_position;
      } else if (spring.m_type == 'b') {
        spring.m_posA = m_hJoints[j-2].m_position;
      } else {
        spring.m_posA = m_hJoints[j-1].m_position;
      }

    }

    //Set follow hairs to be in sync with the guide
    for (auto &followHair: m_followHairs)
    {
      followHair.m_hJoints[j].m_position = m_hJoints[j].m_position + followHair.offset;
    }
  }
}

void GuideHair::complexCollision(Scalp _scalp, int _curIndex)
{
  //Apply more forces the farther out on the hair
  float grav = 1.0f/2.0f + (_curIndex/(m_hJoints.size()*1.0f)/2.0f);
  ngl::Vec3 normal = m_rootNormal;
  normal.normalize();
  normal = normal*grav;
  m_hJoints[_curIndex].m_velocity = ngl::Vec3(m_totalUpdate.m_x, m_totalUpdate.m_y-grav, m_totalUpdate.m_z);
  if (m_realPos.length() > _scalp.getRadius()*1.25f)
  {
    m_hJoints[_curIndex].m_position += m_hJoints[_curIndex].m_velocity; //adjust the joints position
  } else {
    m_hJoints[_curIndex].m_position += m_hJoints[_curIndex].m_velocity+normal; //adjust the joints position
  }
}

void GuideHair::simpleCollision(Scalp _scalp, int _curIndex)
{
  float grav = 1.0f/2.0f + (_curIndex/(m_hJoints.size()*1.0f)/2.0f);
  m_hJoints[_curIndex].m_velocity = ngl::Vec3(m_totalUpdate.m_x, m_totalUpdate.m_y-grav, m_totalUpdate.m_z);
  m_hJoints[_curIndex].m_position += m_hJoints[_curIndex].m_velocity; //adjust the joints position
}

