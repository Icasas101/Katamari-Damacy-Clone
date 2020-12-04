//
//  Room.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 12/3/2020
//
//

#include "common.h"

//room constructor
Rooms::Rooms() {
	
};

void Rooms::room_gl_init() {

	room_vert[0] = vec2(-0.75, -0.75);
	room_vert[1] = vec2(-0.75, 0.75);
	room_vert[2] = vec2(0.75, -0.75);
	room_vert[3] = vec2(0.75, 0.75);

	size_t room_vert_bytes = 4 * sizeof(vec2);

	room_color[0] = black;
	room_color[1] = black;
	room_color[2] = black;
	room_color[3] = black;

	size_t room_color_bytes = 4 * sizeof(vec3);

	std::string vshader = shader_path + "vshader_Prince.glsl";
	std::string fshader = shader_path + "fshader_Prince.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	room_GLvars.a_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(room_GLvars.a_vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(room_GLvars.a_vertex_shader);
	check_shader_compilation(vshader, room_GLvars.a_vertex_shader);

	room_GLvars.a_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(room_GLvars.a_fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(room_GLvars.a_fragment_shader);
	check_shader_compilation(fshader, room_GLvars.a_fragment_shader);

	room_GLvars.a_program = glCreateProgram();
	glAttachShader(room_GLvars.a_program, room_GLvars.a_vertex_shader);
	glAttachShader(room_GLvars.a_program, room_GLvars.a_fragment_shader);

	glLinkProgram(room_GLvars.a_program);
	check_program_link(room_GLvars.a_program);

	glBindFragDataLocation(room_GLvars.a_program, 0, "fragColor");

	room_GLvars.a_vpos_location = glGetAttribLocation(room_GLvars.a_program, "vPos");
	room_GLvars.a_vcolor_location = glGetAttribLocation(room_GLvars.a_program, "vColor");
	room_GLvars.a_M_location = glGetUniformLocation(room_GLvars.a_program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &room_GLvars.a_vao);
	//Set GL state to use vertex array object
	glBindVertexArray(room_GLvars.a_vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &room_GLvars.a_buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, room_GLvars.a_buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(room_vert) + sizeof(room_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(room_vert), room_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(room_vert), sizeof(room_color), room_color);

	glEnableVertexAttribArray(room_GLvars.a_vpos_location);
	glEnableVertexAttribArray(room_GLvars.a_vcolor_location);

	glVertexAttribPointer(room_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(room_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_vert)));

	glBindVertexArray(0);
}

//Draw a room
void Rooms::room_draw(mat4 proj) {

	glUseProgram(room_GLvars.a_program);
	glBindVertexArray(room_GLvars.a_vao);
	//    mat4 M2 = (Translate(1,-1,0) * RotateZ(90));
	//    mat4 M3 = (Translate(-2.5,-1.5,0) * Scale(4));
	//    mat4 M4 = (Translate(-0.915,0.5,0) * RotateZ(-45) * Scale(2));

		//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(room_GLvars.a_M_location, 1, GL_TRUE, proj);

	glPointSize(3.0);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
}
