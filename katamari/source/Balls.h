//
//  Balls.h
//  Balls
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 12/3/2020
//
//

#ifndef __Balls__
#define __Balls__

#include "common.h"
#include "Obstacle.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Balls : public Obstacle {

	//Placeholders so everything compiles.  Customize for your ship
	vec2 ball_vert[69];
	vec3 ball_color[69];

	vec3 yellow = vec3(1.0, 0.85, 0.41);
	vec3 orange = vec3(0.97, 0.44, 0.30);
	vec3 black = vec3(0.0, 0.0, 0.0);
	vec3 white = vec3(1.0, 1.0, 1.0);

	//Record of the ball's state
	struct {
		vec2 a_cur_location;   //Current position of the center
		float a_angle;         //Rotation angle
		vec2 a_pointing;       //Vector pointing to the front of the ship
		//This function will be helpful to keep track of the direction the ship
		//is pointing
		vec2 a_accel;
		mat2 a_RotateZ2D(const GLfloat theta) {
			GLfloat angle = DegreesToRadians * theta;
			mat2 c;
			c[0][0] = c[1][1] = cos(angle);
			c[1][0] = sin(angle);
			c[0][1] = -c[1][0];
			return c;
		}
		vec2 a_velocity;       //Velocity
	} ball_state;

	//OpenGL variables for a ship
	struct {
		GLuint a_vao;           //Vertex array object
		GLuint a_program;       //shader program
		GLuint a_buffer;        //Vertex buffer objects
		GLuint a_vertex_shader, a_fragment_shader;  //Shaders
		GLint a_vpos_location, a_vcolor_location;   //reference to pos and color in shaders
		GLint a_M_location;     //Reference to matrix in shader
	} ball_GLvars;


public:


	Balls();

	mat4 ball_move;

	//    inline void rotateLeft() {
	//        //Do something
	//          // update geometry here and change direction it's pointing
	//        //m2 *= RotateZ(-5);
	//        //state.pointing *= RotateZ2D(-5);
	//
	//    }
	//    inline void rotateRight() {
	//        //Do something
	//        //m2 *= RotateZ(5);
	//        //state.pointing *= RotateZ2D(5);
	//
	//    }

	void ball_update_state();

	void ball_gl_init();

	void ball_draw(mat4 proj);

};


#endif /* defined(__Balls__) */
