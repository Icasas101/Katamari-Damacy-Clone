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
  vec2 prince_vert[60];
  vec3 prince_color[60];
    
    vec3 yellow = vec3(1.0, 0.85, 0.41);
    vec3 orange = vec3(0.97, 0.44, 0.30);
    vec3 pink = vec3(1.0, 0.38, 0.38);
    vec3 blue = vec3(0.32, 0.57, 0.74);
    vec3 purple = vec3(0.59, 0.24, 0.54);
    vec3 green = vec3(0.56, 0.75, 0.3);
    vec3 dgreen = vec3(0.24, 0.6, 0.24);
    vec3 almond = vec3(0.93, 0.83, 0.74);
    vec3 brown = vec3(0.44, 0.36, 0.31);
    
    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 white = vec3(1.0,1.0, 1.0);
 
  
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

  struct {
	  vec2 cur_location;   //Current position of the center
	  float angle;         //Rotation angle
	  vec2 pointing;       //Vector pointing to the front of the prince
	  //This function will be helpful to keep track of the direction the prince
	  //is pointing
	  mat2 RotateZ2D(const GLfloat theta) {
		  GLfloat angle = DegreesToRadians * theta;
		  mat2 c;
		  c[0][0] = c[1][1] = cos(angle);
		  c[1][0] = sin(angle);
		  c[0][1] = -c[1][0];
		  return c;
	  }
	  vec2 velocity;       //Velocity
      vec2 katamari;
      vec2 moved;
  } state;
 
  mat4 m1;
    
  mat2 zoom(GLfloat x_scale, GLfloat y_scale) {
      return mat2( x_scale, 0.0, 0.0, y_scale );
  }

  inline void moveLeft() {
      state.moved = vec2(-0.03, 0.0);
      update_state();
    
  }
  inline void moveRight(){
      state.moved = vec2(0.03, 0.0);
      update_state();
  }

  inline void moveForward() {
      state.moved = vec2(0.0, -0.03);
      update_state();
  }
    
  inline void moveDown() {
      state.moved = vec2(0.0, 0.03);
      update_state();
  }

  void update_state();
  
  void gl_init();  
  
  void draw(mat4 proj);

  
};


#endif /* defined(__Katamari__Prince__) */
