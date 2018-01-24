/* File: Scalp.cpp
 * Represents the head which hairs are attached to.
*/

#include "Scalp.h"

#include <ngl/VAOPrimitives.h>

//Only in here to stop compiler errors
Scalp::Scalp()
{

}

Scalp::Scalp(const ngl::Vec3 &_pos,const ngl::Vec3 &_dir, GLfloat _rad)
{
  m_pos=_pos;
  m_dir=_dir;
  m_radius=_rad;
}

void Scalp :: set(const ngl::Vec3 &_pos,   const ngl::Vec3 &_dir,  GLfloat _rad )
{
  m_pos=_pos;
  m_dir=_dir;
  m_radius=_rad;
}



