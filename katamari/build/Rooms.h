//
//  Rooms.h
//  Rooms
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 12/3/2020
//
//

#ifndef __Rooms__
#define __Rooms__

#include "common.h"

class Rooms {

	//Placeholders so everything compiles.  Customize for your ship
	vec2 room_vert[4];
	vec3 room_color[4];

	vec3 tan = vec3(0.824, 0.706, 0.549);

	//OpenGL variables for a ship
	struct {
		GLuint a_vao;           //Vertex array object
		GLuint a_program;       //shader program
		GLuint a_buffer;        //Vertex buffer objects
		GLuint a_vertex_shader, a_fragment_shader;  //Shaders
		GLint a_vpos_location, a_vcolor_location;   //reference to pos and color in shaders
		GLint a_M_location;     //Reference to matrix in shader
	} room_GLvars;

public:


	Rooms();

	void room_gl_init();

	void room_draw(mat4 proj);

};


#endif /* defined(__Rooms__) */
