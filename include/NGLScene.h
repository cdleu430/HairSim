/* Represents the scene with the hair being drawn and simulated. Created from
 * a sample provided by Jon Macey, can be found at: https://github.com/NCCA/SimpleNGL
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include "WindowParams.h"
#include "HairJoint.h"
#include "GuideHair.h"

#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Text.h>
#include <QOpenGLWindow>
#include <ngl/Transformation.h>
#include <ngl/BezierCurve.h>
#include <QTime>
#include <QtOpenGL>


//Original documentation, not written by Chris Leu
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QGLWidget
{
  Q_OBJECT
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our NGL drawing class
  /// @param [in] parent the parent window to the class
  //----------------------------------------------------------------------------------------------------------------------
  NGLScene(QWidget *_parent);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our NGL drawing class
  /// @param [in] parent the parent window to the class
  //----------------------------------------------------------------------------------------------------------------------
  ~NGLScene();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the initialize class is called once when the window is created and we have a valid GL context
  /// use this to setup any default GL stuff
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(int _w, int _h) override;

  /// @brief set the spring to use
  /// @param[in] _s the spring
  //----------------------------------------------------------------------------------------------------------------------

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the windows params such as mouse and rotations etc
  //----------------------------------------------------------------------------------------------------------------------
  WinParams m_win;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the global mouse transforms
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_mouseGlobalTX;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Our Camera
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Camera m_cam;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the model position for mouse movement
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_modelPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load transform matrices to the shader
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatricesToShader();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Qt Event called when a key is pressed
  /// @param [in] _event the Qt event to query for size etc
  //----------------------------------------------------------------------------------------------------------------------
  void keyPressEvent(QKeyEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent(QWheelEvent *_event) override;

  /// @brief our transformation stack used for drawing
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Transformation m_transform;

  /// @brief the curve to use
  //----------------------------------------------------------------------------------------------------------------------
  std::unique_ptr<ngl::BezierCurve>m_curve;

  /// @brief start the simulation timer
  //----------------------------------------------------------------------------------------------------------------------
  void startSimTimer();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief stop the simulation timer
  //----------------------------------------------------------------------------------------------------------------------
  void stopSimTimer();


  /// @brief set the timer duration value
  /// @param[in] _v the timer value in ms
  //----------------------------------------------------------------------------------------------------------------------
  inline void setTimerDuration(int _v){m_timerValue=_v;}

  /// @brief the timer
  //----------------------------------------------------------------------------------------------------------------------
  int m_timer;

  /// @brief the timer value in ms
  //----------------------------------------------------------------------------------------------------------------------
  int m_timerValue;

  /// @brief timer event trigered by startTimer
  //----------------------------------------------------------------------------------------------------------------------
  void timerEvent(QTimerEvent *_event	);

  int m_fpsTimer;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the fps to draw
  //----------------------------------------------------------------------------------------------------------------------
  int m_fps;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief number of frames for the fps counter
  //----------------------------------------------------------------------------------------------------------------------
  int m_frames;

  QTime m_FPSTimer;

  std::unique_ptr<ngl::Text>m_text;

  //Draws a custom made bezier curve function to create a set of points and
  //  draw them
  //params: _hair is the hair to build points for the curve off of, _vao is the
  // vao used
  void drawMyBez(FollowHair _hair, std::unique_ptr<ngl::AbstractVAO>& _vao);

  //Draws a bezier curve with NGL's bezier curve class
  //params: _hair is the hair to build points for the curve off of
  void drawNGLBez(FollowHair _hair);

  //Draws the individual edge springs for each follow hair. This is the fastest
  //  drawing method of the 3 and thus it works well when debugging
  //params: _hair is the hair to build points for the curve off of, _vao is the
  // vao used
  void drawSprings(FollowHair _hair, std::unique_ptr<ngl::AbstractVAO>& _vao);

  //Controls which of the above drawing methods is used
  int m_drawSelection;

  //Controls where the scalp is drawn in wireframe or not, used for seeing how
  //  individual hairs may collide with the scalp
  bool m_wireframe;

  //Controls how many guide hairs there are
  int m_guideCount;

  //Controls how many follow hairs there are per guide hair
  int m_followCount;

  //Controls how smooth the bezier curves are
  int m_hairLOD;

  //Controls how long the hairs are in sections
  int m_hairLength;

  //Used for drawing the springs quickly
  std::vector<ngl::Vec3> m_points;

  std::vector<GuideHair> m_guides;

  Scalp m_collider;

  bool m_toggleFocus;


//These correspond to controls on the UI
public slots:
  void toggleWireframe(bool _mode);
  void setDrawMode(int _i);
  void resetSim();
  void setGuideCount(int _count);
  void setFollowCount(int _count);
  void setHairLength(int _length);
  void setHairLOD(int _lod);
  void toggleFocus();
};


#endif
