/* Represents the scalp which the hair is attached to. Made from an example by
 *   Jon Macey, found at: https://github.com/NCCA/Collisions
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef SCALP_H_
#define SCALP_H_

#include <ngl/Vec3.h>

/*! \brief a simple sphere class */
class Scalp
{
public :
  Scalp();
  /// @brief ctor
  /// @param pos the position of the sphere
  /// @param rad the radius of the sphere */
  Scalp(const  ngl::Vec3  &_pos,  const ngl::Vec3 &_dir,GLfloat _rad	);
  /// draw method
  inline ngl::Vec3 getPos() const {return m_pos;}
  inline GLfloat getRadius() const {return m_radius;}
  /// set the sphere values
  /// @param[in] _pos the position to set
  /// @param[in] _dir the direction of the sphere
  /// @param[in] _rad the radius of the sphere
   void set( const ngl::Vec3 &_pos, const  ngl::Vec3 &_dir,	GLfloat _rad );

  /*! the position of the sphere */
  ngl::Vec3 m_pos;
private :
  /*! the radius of the sphere */
  GLfloat m_radius;
  // the direction of the sphere
  ngl::Vec3 m_dir;
};





#endif
