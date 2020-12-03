//
//  Prince.h
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 11/27/2020
//
//

#ifndef __Katamari__Prince__
#define __Katamari__Prince__

#include "common.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Prince{

  //Placeholders so everything compiles.  Customize for your ship
  vec2 prince_vert[6];
  vec3 prince_color[6];
  
  //Record of the ship's state
  struct {
    vec2 cur_location;   //Current position of the center
    float angle;         //Rotation angle
    vec2 pointing;       //Vector pointing to the front of the prince
    //This function will be helpful to keep track of the direction the prince
    //is pointing
    mat2 RotateZ2D( const GLfloat theta ){
      GLfloat angle = DegreesToRadians * theta;
      mat2 c;
      c[0][0] = c[1][1] = cos(angle);
      c[1][0] = sin(angle);
      c[0][1] = -c[1][0];
      return c;
    }
    vec2 velocity;       //Velocity
  } state;
  
  //OpenGL variables for a prince
  struct {
    GLuint vao;           //Vertex array object
    GLuint program;       //shader program
    GLuint buffer;        //Vertex buffer objects
    GLuint vertex_shader, fragment_shader;  //Shaders
    GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
    GLint M_location;     //Reference to matrix in shader
  } GLvars;

  
public:
  

  Prince();
 
  mat4 m1;

  inline void rotateLeft() {
    //Do something
	  // update geometry here and change direction it's pointing
    m1 *= RotateZ(-30);
    state.pointing = state.RotateZ2D(-15) * state.pointing;
    
  }
  inline void rotateRight(){
    //Do something
    m1 *= RotateZ(15);
    state.pointing = state.RotateZ2D(30) * state.pointing;
    
  }

  inline void moveForward() {
	  m1 *= Translate(0.0, -0.1, 0.0);
	  state.pointing = state.RotateZ2D(0) * state.pointing;
  }

  void update_state();
  
  void gl_init();  
  
  void draw(mat4 proj);

  
};


#endif /* defined(__Katamari__Prince__) */
