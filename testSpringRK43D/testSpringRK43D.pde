/// @author: Chris Leu
/// @file: testSpringRK3D
/// @brief: This is a simple test for a 3D mass-spring using RK4 integration
///          Created with help from https://gafferongames.com/post/integration_basics/
///          and https://www.khanacademy.org/partner-content/pixar/simulation
/// Initial Version 17/11/17
/// \todo optimize (none done here since it needs to be converted to C++ anyways)


import peasy.*;

PeasyCam cam;

//Environment variables
float gravity = 9.8;
float mass = 30;

//Starting positions for the end of the spring
float positionY = -100;
float positionX = -50;
float positionZ = 300;

//Integration variables
float timeStep = 0.2;
float time = 0;

//The anchor is the top of the spring
float anchorX = 0;
float anchorY = -100;

//Spring constants
float k = 4;
float damping = 2;

//A state for each direction
State initialY = new State();
State initialX = new State();
State initialZ = new State();

//Setups up the scene and initalizes the states
void setup(){
  
  size (500, 500, P3D);
  cam = new PeasyCam(this, 0, 0, 0, 500);
  
  initialY.m_x = positionY;
  initialY.m_v = gravity;
  initialY.m_axis = 'y';
  
  initialX.m_x = positionX;
  initialX.m_v = 0;
  initialX.m_axis = 'x';
  
  initialZ.m_x = positionZ;
  initialZ.m_v = 0;
  initialZ.m_axis = 'z';
}

//Draws the frames, updates positions
void draw(){
  
  time += timeStep;
  
  initialY = integrate(initialY, time, timeStep);
  initialX = integrate(initialX, time, timeStep);
  initialZ = integrate(initialZ, time, timeStep);
  
  //drawing
  background(255, 255, 255);
  pushMatrix();
  translate(anchorX, anchorY, 0);
  box(10);
  popMatrix();
  
  line(initialX.m_x, initialY.m_x, initialZ.m_x, anchorX, anchorY, 0);
  pushMatrix();
  translate(initialX.m_x, initialY.m_x, initialZ.m_x);
  sphere(10);
  popMatrix();
}

//Computes RK4 integration (adapted from https://gafferongames.com/post/integration_basics/) 
State integrate( State state, float t, float dt ) {
  Derivative a,b,c,d;

  Derivative starter = new Derivative();
  a = evaluate( state, t, 0.0, starter );
  b = evaluate( state, t, dt*0.5, a );
  c = evaluate( state, t, dt*0.5, b );
  d = evaluate( state, t, dt, c );

  float dxdt = 1.0 / 6.0 * 
    ( a.m_dx + 2.0 * ( b.m_dx + c.m_dx ) + d.m_dx );

  float dvdt = 1.0 / 6.0 * 
    ( a.m_dv + 2.0f * ( b.m_dv + c.m_dv ) + d.m_dv );

  state.m_x = state.m_x + dxdt * dt;
  state.m_v = state.m_v + dvdt * dt;
  return state;
}

//Calculates values for derivatives (adapted from https://gafferongames.com/post/integration_basics/) 
Derivative evaluate(State initial, float t, float dt, Derivative d ) {
  State state = new State();
  state.m_x = initial.m_x + d.m_dx*dt;
  state.m_v = initial.m_v + d.m_dv*dt;

  Derivative output = new Derivative();
  output.m_dx = state.m_v;
  output.m_dv = acceleration(state);
  return output;
}

//Calculates acceleration values (adapted from https://gafferongames.com/post/integration_basics/) 
float acceleration(State state) {
  float springForce = -k * (state.m_x);
  float dampingForce = damping * state.m_v;
  float force = 0;
  if (state.m_axis == 'y') 
  {
    force = springForce + mass * gravity - dampingForce;
  } 
  else 
  {
    force = springForce - dampingForce;
  }
  float acceleration = force/mass;
  return acceleration;
}