/* File: NGLScene.cpp
 * Shows the hair simualtion itself. Based on a sample by Jon Macey, can be
 *   found at: https://github.com/NCCA/SimpleNGL
*/

#include "NGLScene.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include "State.h"
#include "RK4Integrator.h"
#include "Spring.h"
#include "HairJoint.h"
#include "GuideHair.h"
#include "Scalp.cpp"
#include "MainWindow.h"

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <stdlib.h>
#include <QString>



NGLScene::NGLScene(QWidget *_parent) : QGLWidget(_parent)
{
  setFocus();
  m_timerValue=30;
  m_fpsTimer =startTimer(0);
  m_fps=0;
  m_frames=0;
  m_FPSTimer.start();
  m_wireframe = false;
  m_drawSelection = 0;

  m_guideCount = 500;
  m_followCount = 1;
  m_hairLength = 6;
  m_hairLOD = 10;

  m_points = std::vector<ngl::Vec3>(8*m_hairLength);

  m_collider = Scalp(ngl::Vec3(0, 5, 0), ngl::Vec3(0,0,0), 10);

  m_toggleFocus = true;

  startSimTimer();
}

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL( int _w, int _h )
{
  m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["nglColourShader"]->use();

  shader->setUniform("Colour",1.0f,0.0f,1.0f,1.0f);
  shader->setUniform("lightPos",1.0f,1.0f,1.0f);
  shader->setUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);

  ngl::Vec3 from(0,0,50);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_cam.set(from,to,up);
  int w=this->size().width();
  int h=this->size().height();

  m_cam.setShape(45,static_cast<float>(w)/h,0.05f,350.0f);
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,width(),height());

  //Create Hairs---------------------------------------------------------------
  for (int i = 0; i < m_guideCount; i++)
  {
    float radS = (rand() % 180) * 3.14 /180;
    float radT = (rand() % 90) * 3.14 /180;

    float buildX = m_collider.getRadius() * cos(radS) * sin(radT);
    float buildY = m_collider.getRadius() * sin(radS) * sin(radT);
    float buildZ = m_collider.getRadius() * cos(radT);

    ngl::Vec3 colliderLoc = ngl::Vec3(buildX,buildY,buildZ) + m_collider.getPos();

    GuideHair testGuideFull(colliderLoc, m_hairLength);
    testGuideFull.m_rootNormal = ngl::Vec3(testGuideFull.m_hJoints[0].m_position - m_collider.getPos());

    float HI = 1.2f;
    float LO = 0.8f;

    for (int i = 0; i < m_followCount; i++)
    {

      float s = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      float t = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

      float followS = radS * s;
      float followT = radT * t;

      float followX = m_collider.getRadius() * cos(followS) * sin(followT);
      float followY = m_collider.getRadius() * sin(followS) * sin(followT);
      float followZ = m_collider.getRadius() * cos(followT);

      ngl::Vec3 followColliderLoc = ngl::Vec3(followX,followY,followZ) + m_collider.getPos();

      FollowHair buildFollow(followColliderLoc, m_hairLength);
      ngl::Vec3 buildOffset = followColliderLoc - colliderLoc;
      buildFollow.offset = buildOffset;

      testGuideFull.m_followHairs.push_back(buildFollow);
    }
    m_guides.push_back(testGuideFull);
  } // hair creation finished -------------------------------------------------

  m_text.reset(new ngl::Text(QFont("Arial",14)));
  m_text->setScreenSize(width(),height());

  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  prim->createSphere("sphere", m_collider.getRadius(), 50);

}


void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=m_transform.getMatrix();
  MV=m_cam.getViewMatrix() *m_mouseGlobalTX*M;
  MVP=m_cam.getProjectionMatrix()*MV;
  normalMatrix=MV;
  normalMatrix.inverse().transpose();
  shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  shader->setUniform("normalMatrix",normalMatrix);
  shader->setUniform("M",M);
}

void NGLScene::paintGL()
{
  if(m_toggleFocus)
  {
    setFocus();
  }
  glViewport( 0, 0, m_win.width, m_win.height );
  // clear the screen and depth buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["nglColourShader"]->use();

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX( m_win.spinXFace );
  rotY.rotateY( m_win.spinYFace );
  // multiply the rotations
  m_mouseGlobalTX = rotX * rotY;
  // add the translations
  m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;

  if(m_drawSelection == 0)
  {
    shader->setUniform("Colour",0.0f,1.0f,0.0f,1.0f);
  } else {
    shader->setUniform("Colour",0.5f,0.5f,0.0f,1.0f);
  }

  std::unique_ptr<ngl::AbstractVAO> vao(ngl::VAOFactory::createVAO("simpleVAO",GL_LINES));

  //Draw each follow hair ------------------------------------------------------
  for (auto &hair: m_guides)
  {
    for (auto &followHair: hair.m_followHairs) {
      if (m_drawSelection == 0)
      {
        drawSprings(followHair, vao);
      }
      if (m_drawSelection == 1)
      {
        drawNGLBez(followHair);
      }
      if (m_drawSelection == 2)
      {
        drawMyBez(followHair, vao);
      }
    }
  } // hair drawing finished --------------------------------------------------

  if (m_wireframe){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  //draws the scalp
  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  m_transform.setPosition(ngl::Vec4(m_collider.getPos().m_x, m_collider.getPos().m_y, m_collider.getPos().m_z, 1));
  shader->setUniform("Colour",0.0f,0.0f,0.5f,1.0f);
  loadMatricesToShader();
  prim->draw("sphere");
  m_transform.reset();

  //FPS updates
  ++m_frames;
  m_text->setColour(1,1,0);
  QString text=QString("%2 fps").arg(m_fps);
  m_text->renderText(10,20,text);
}

void NGLScene::keyPressEvent( QKeyEvent* _event )
{
  // that method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch ( _event->key() )
  {
    // escape key to quit
    case Qt::Key_Escape:
      QGuiApplication::exit( EXIT_SUCCESS );
      break;
// turn on wirframe rendering
#ifndef USINGIOS_
    // Moving the scalp -------------------------------------------------------
    case Qt::Key_W:
      m_collider.set(ngl::Vec3(m_collider.getPos().m_x, ++m_collider.m_pos.m_y, m_collider.getPos().m_z), ngl::Vec3(0,0,0), m_collider.getRadius());
      for (auto &root: m_guides)
      {
        root.m_hJoints[0].m_position.m_y++;
      }
      break;
    case Qt::Key_S:
      m_collider.set(ngl::Vec3(m_collider.getPos().m_x, --m_collider.m_pos.m_y, m_collider.getPos().m_z), ngl::Vec3(0,0,0), m_collider.getRadius());
      for (auto &root: m_guides)
      {
        root.m_hJoints[0].m_position.m_y--;
      }
    break;
    case Qt::Key_A:
      m_collider.set(ngl::Vec3(--m_collider.m_pos.m_x, m_collider.m_pos.m_y, m_collider.getPos().m_z), ngl::Vec3(0,0,0), m_collider.getRadius());
      for (auto &root: m_guides)
      {
        root.m_hJoints[0].m_position.m_x--;
      }
    break;
    case Qt::Key_D:
      m_collider.set(ngl::Vec3(++m_collider.m_pos.m_x, m_collider.m_pos.m_y, m_collider.m_pos.m_z), ngl::Vec3(0,0,0), m_collider.getRadius());
      for (auto &root: m_guides)
      {
        root.m_hJoints[0].m_position.m_x++;
      }
    break;
    // finished moving the scalp ----------------------------------------------

    case Qt::Key_Alt:
      m_toggleFocus = !m_toggleFocus;
    break;
#endif
    // show full screen
    case Qt::Key_F:
      showFullScreen();
    break;
    // show windowed
    case Qt::Key_N:
      showNormal();
    break;
    case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());
    break;
  }
  update();
}

void NGLScene::timerEvent( QTimerEvent *_event)
{
  if(_event->timerId() == m_fpsTimer)
  {
      if( m_FPSTimer.elapsed() > 1000.0)
      {
        m_fps=m_frames;
        m_frames=0;
        m_FPSTimer.restart();
      }
   } else {
    // updates the hairs ------------------------------------------------------
    for (auto &hair : m_guides)
    {
      hair.updateJoints(m_collider);
    }
    update();
  } // hair updates finished --------------------------------------------------

}

void NGLScene::startSimTimer()
{
  m_timer=startTimer(m_timerValue);
}

void NGLScene::stopSimTimer()
{
  killTimer(m_timer);
}


//Draws my bezier curves
void NGLScene::drawMyBez(FollowHair _hair, std::unique_ptr<ngl::AbstractVAO> &_vao)
{
  for (int j = 0; j < m_hairLength; j++)
  {
    //Holds the actual points of the bezier curve
    std::vector<ngl::Vec3> bezPoints(m_hairLOD + 1);
    for(int i = 0; i <= m_hairLOD; i++)
    {
      float t = i / (m_hairLOD * 1.0f);
      float x = (1-t)*(1-t)*(1-t)*(1-t)*_hair.m_hJoints[j*4].m_position.m_x + 4*((1-t)*(1-t)*(1-t))*t*_hair.m_hJoints[j*4+1].m_position.m_x+ 6*((1-t)*(1-t))*(t*t)*_hair.m_hJoints[j*4+2].m_position.m_x + 4*(1-t)*(t*t*t)*_hair.m_hJoints[j*4+3].m_position.m_x + t*t*t*t*_hair.m_hJoints[j*4+4].m_position.m_x;
      float y = (1-t)*(1-t)*(1-t)*(1-t)*_hair.m_hJoints[j*4].m_position.m_y + 4*((1-t)*(1-t)*(1-t))*t*_hair.m_hJoints[j*4+1].m_position.m_y+ 6*((1-t)*(1-t))*(t*t)*_hair.m_hJoints[j*4+2].m_position.m_y + 4*(1-t)*(t*t*t)*_hair.m_hJoints[j*4+3].m_position.m_y + t*t*t*t*_hair.m_hJoints[j*4+4].m_position.m_y;
      float z = (1-t)*(1-t)*(1-t)*(1-t)*_hair.m_hJoints[j*4].m_position.m_z + 4*((1-t)*(1-t)*(1-t))*t*_hair.m_hJoints[j*4+1].m_position.m_z+ 6*((1-t)*(1-t))*(t*t)*_hair.m_hJoints[j*4+2].m_position.m_z + 4*(1-t)*(t*t*t)*_hair.m_hJoints[j*4+3].m_position.m_z + t*t*t*t*_hair.m_hJoints[j*4+4].m_position.m_z;
      bezPoints[t*m_hairLOD] = ngl::Vec3(x, y, z);
    }

    //Holds the points to draw this will be the bezier points in a, AB BC CD DE EF, pattern
    std::vector<ngl::Vec3> drawPoints(2 * m_hairLOD);
    for (int i = 0; i < bezPoints.size()-1; i++)
    {
      drawPoints[i*2]=bezPoints[i];
      drawPoints[i*2+1]=bezPoints[i+1];
    }
    glLineWidth(1);
    // load transform stack
    loadMatricesToShader();
    _vao->bind();
    _vao->setData(ngl::AbstractVAO::VertexData(drawPoints.size()*sizeof(ngl::Vec3),drawPoints[0].m_x));
    _vao->setNumIndices(drawPoints.size());
    _vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
    _vao->draw();
    _vao->unbind();
  }
}

//draws the NGL bezier curves
void NGLScene::drawNGLBez(FollowHair _hair)
{
  ngl::BezierCurve drawHairs;
  //add points
  for (int i = 0; i < _hair.m_hJoints.size(); i++)
  {
    drawHairs.addPoint(_hair.m_hJoints[i].m_position);
  }
  loadMatricesToShader();
  drawHairs.setLOD(5.0f);
  drawHairs.createKnots();
  drawHairs.createVAO();
  drawHairs.draw();
}

//Draws only the edge springs of a hair
void NGLScene::drawSprings(FollowHair _hair, std::unique_ptr<ngl::AbstractVAO>& _vao)
{
  for (int i = 0; i < _hair.m_hJoints.size()-1; i++)
  {
    m_points[i*2]=_hair.m_hJoints[i].m_position;
    m_points[i*2+1]=_hair.m_hJoints[i+1].m_position;
  }
  glLineWidth(2.5f);
  // load transform stack
  loadMatricesToShader();
  _vao->bind();
  _vao->setData(ngl::AbstractVAO::VertexData((8*m_hairLength)*sizeof(ngl::Vec3),m_points[0].m_x));
  _vao->setNumIndices(8*m_hairLength);
  _vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  _vao->draw();
  _vao->unbind();
}

// UI methods -----------------------------------------------------------------
void NGLScene::toggleWireframe(bool _mode)
{
  m_wireframe = _mode;
  update();
}

void NGLScene::setDrawMode(int _i)
{
  m_drawSelection = _i;
  update();
}

void NGLScene::resetSim()
{
  m_guides.clear();
  initializeGL();
  update();
}

void NGLScene::setGuideCount(int _count)
{
  m_guideCount = _count;
  update();
}

void NGLScene::setFollowCount(int _count)
{
  m_followCount = _count;
  update();
}

void NGLScene::setHairLength(int _length)
{
  m_hairLength = _length;
  update();
}

void NGLScene::setHairLOD(int _lod)
{
  m_hairLOD = _lod;
  update();
}

void NGLScene::toggleFocus()
{
  m_toggleFocus = !m_toggleFocus;
  update();
}
// UI methods finished --------------------------------------------------------
