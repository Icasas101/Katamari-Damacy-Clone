//
//  Bullets.h
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#ifndef __Bullets__
#define __Bullets__

#include "common.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3

class Bullets {

	//Placeholders so everything compiles.
	vec2 bullet_vert[3];
	vec3 bullet_color[3];

	//Record of the bullet's state
	struct {
		vec2 bullet_cur_location;   //Current position of the center
		vec2 bullet_pointing;       //Vector pointing to the front of the ship
		//This function will be helpful to keep track of the direction the ship
		//is pointing
		vec2 bullet_velocity;       //Velocity
		bool fired;    //Boolean if fire button is pressed
	} bullet_state;

	//OpenGL variables for a bullet
	struct {
		GLuint b_vao;           //Vertex array object
		GLuint b_program;       //shader program
		GLuint b_buffer;        //Vertex buffer objects
		GLuint b_vertex_shader, b_fragment_shader;  //Shaders
		GLint b_vpos_location, b_vcolor_location;   //reference to pos and color in shaders
		GLint b_M_location;     //Reference to matrix in shader
	} bullet_GLvars;


public:


	Bullets();

	inline void fire() { bullet_state.fired = true; }

	void update_state();

	void gl_init();

	void draw(mat4 proj);

};


#endif /* defined(__Bullets__) */
