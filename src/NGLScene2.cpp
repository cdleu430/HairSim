#include "NGLScene.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include "State.h"
#include "RK4Integrator.h"
#include "Spring.h"
#include "HairJoint.h"

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

float k = 1;
float damping = 0.1;

float dt = 0.2;

State anchor1;

Spring testSpring1(ngl::Vec3(0,10,0), ngl::Vec3(0, 0, 0), 7, k, damping);
Spring testSpring2(ngl::Vec3(10,0,0), ngl::Vec3(0, 0, 0), 7, k, damping);

std::vector<Spring> build = {testSpring1, testSpring2};

HairJoint testJoint(ngl::Vec3(0, 0, 0), ngl::Vec3(0, -9.8, 0), build);

NGLScene::NGLScene()
{
  setTitle( "Qt5 Simple NGL Demo" );
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
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::instance();
  glClearColor( 0.8f, 0.8f, 0.8f, 1.0f ); // Grey Background
  // enable depth testing for drawing
  glEnable( GL_DEPTH_TEST );
// enable multisampling for smoother drawing
#ifndef USINGIOS_
  glEnable( GL_MULTISAMPLE );
#endif
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  // we are creating a shader called Phong to save typos
  // in the code create some constexpr
  constexpr auto shaderProgram = "Phong";
  constexpr auto vertexShader  = "PhongVertex";
  constexpr auto fragShader    = "PhongFragment";
  // create the shader program
  shader->createShaderProgram( shaderProgram );
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
  shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
  // attach the source
  shader->loadShaderSource( vertexShader, "shaders/PhongVertex.glsl" );
  shader->loadShaderSource( fragShader, "shaders/PhongFragment.glsl" );
  // compile the shaders
  shader->compileShader( vertexShader );
  shader->compileShader( fragShader );
  // add them to the program
  shader->attachShaderToProgram( shaderProgram, vertexShader );
  shader->attachShaderToProgram( shaderProgram, fragShader );


  // now we have associated that data we can link the shader
  shader->linkProgramObject( shaderProgram );
  // and make it active ready to load values
  ( *shader )[ shaderProgram ]->use();
  // the shader will use the currently active material and light0 so set them
  ngl::Material m( ngl::STDMAT::GOLD );
  // load our material values to the shader into the structure material (see Vertex shader)
  m.loadToShader( "material" );
  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from( 0, 1, 40 );
  ngl::Vec3 to( 0, 0, 0 );
  ngl::Vec3 up( 0, 1, 0 );
  // now load to our new camera
  m_cam.set( from, to, up );
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam.setShape( 45.0f, 720.0f / 576.0f, 0.05f, 350.0f );
  shader->setUniform( "viewerPos", m_cam.getEye().toVec3() );
  // now create our light that is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv = m_cam.getViewMatrix();
  iv.transpose();
  ngl::Light light( ngl::Vec3( -2, 5, 2 ), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::POINTLIGHT );
  light.setTransform( iv );
  // load these values to the shader as well
  light.loadToShader( "light" );

}


void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Phong"]->use();

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
  glViewport( 0, 0, m_win.width, m_win.height );
  // clear the screen and depth buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // grab an instance of the shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  ( *shader )[ "Phong" ]->use();

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

  testSpring1.update();
  std::cout << "B: " << testSpring1.m_posB << "\n";
  std::cout << "V: " << testSpring1.m_velocity << "\n";

  testSpring2.update();
  std::cout << "2B: " << testSpring2.m_posB << "\n";
  std::cout << "2V: " << testSpring2.m_velocity << "\n";
  std::cout << "\n";

  testJoint.m_position = testSpring1.m_velocity + testSpring2.m_velocity;

  testSpring1.m_posB = testJoint.m_position;
  testSpring2.m_posB = testJoint.m_position;


  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  // draw
  m_transform.setPosition(ngl::Vec4(0, 10, 0, 1));
  loadMatricesToShader();
  prim->draw( "cube" );

  m_transform.reset();
  // draw
  m_transform.setPosition(ngl::Vec4(10, 0, 0, 1));
  loadMatricesToShader();
  prim->draw( "cube" );

  m_transform.reset();
  // draw
  //m_transform.setPosition(ngl::Vec4(0, initialY.m_x, 0, 1));
  m_transform.setPosition(ngl::Vec4(testJoint.m_position.m_x, testJoint.m_position.m_y, 0, 1));
  loadMatricesToShader();
  prim->draw( "teapot" );

  m_transform.reset();

  // draw
  m_transform.setPosition(ngl::Vec4(testSpring2.m_posA.m_x, testSpring2.m_posA.m_y, testSpring2.m_posA.m_z, 1));
  loadMatricesToShader();
  prim->draw( "cube" );

  m_transform.reset();

  std::vector<ngl::Vec3> points(2);
  points[0]=testSpring1.m_posA;
  points[1]=testSpring1.m_posB;
  shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);
  // load transform stack
  loadMatricesToShader();

  std::unique_ptr<ngl::AbstractVAO> vao(ngl::VAOFactory::createVAO("simpleVAO",GL_LINES));
  vao->bind();
  vao->setData(ngl::AbstractVAO::VertexData(2*sizeof(ngl::Vec3),points[0].m_x));
  vao->setNumIndices(2);
  vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  vao->draw();
  vao->unbind();

  m_transform.reset();

  points[0]=testSpring2.m_posA;
  points[1]=testSpring2.m_posB;
  shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);
  // load transform stack
  loadMatricesToShader();

  vao->bind();
  vao->setData(ngl::AbstractVAO::VertexData(2*sizeof(ngl::Vec3),points[0].m_x));
  vao->setNumIndices(2);
  vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  vao->draw();
  vao->unbind();

  m_transform.reset();


  update();
}

//----------------------------------------------------------------------------------------------------------------------

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
    case Qt::Key_W:
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      break;
    // turn off wire frame
    case Qt::Key_S:
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
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
    default:
      break;
  }
  update();
}
