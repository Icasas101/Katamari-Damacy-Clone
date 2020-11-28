//
//  Chicks.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 9/13/2020
//
//

#include "common.h"

//Chick constructor
Chicks::Chicks() {
      double random_x = 0.5 - rand() / (float)RAND_MAX;
      double random_y = 0.5 - rand() / (float)RAND_MAX;
      double random_m = rand() % 100;
  
      chick_state.a_cur_location = vec2(0.5, 0.5);
      chick_state.a_velocity = normalize(vec2(random_x, random_y)) * random_m/300.0;

};

//Called everytime an animation tick happens
void Chicks::chick_update_state() {
	//Set GL state to use vertex array object
	glBindVertexArray(chick_GLvars.a_vao);

	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, chick_GLvars.a_buffer);
    
    float dt = 1.0 / 60.0;
    vec2 old_loc  = chick_state.a_cur_location;
    vec2 moved;

    chick_state.a_cur_location += chick_state.a_velocity * dt; // calculate new center
    
    float x_move = old_loc.x - chick_state.a_cur_location.x;
    float y_move = old_loc.y - chick_state.a_cur_location.y;
    moved = vec2(x_move, y_move);
    for (int i = 0; i < 6; i++) {
        chick_vert[i] += moved;
    }
    

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(chick_vert) + sizeof(chick_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(chick_vert), chick_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(chick_vert), sizeof(chick_color), chick_color);

	glEnableVertexAttribArray(chick_GLvars.a_vpos_location);
	glEnableVertexAttribArray(chick_GLvars.a_vcolor_location);

	glVertexAttribPointer(chick_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(chick_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(chick_vert)));


	//glBindVertexArray(0);

}

//Initialize the gl state and variables
void Chicks::chick_gl_init() {
	//chick
	//!!!!!!!!Populate chicks vert + color
    
    chick_vert[0] = vec2(0.05,-0.7);
    chick_vert[1] = vec2(0.06, -0.72);
    chick_vert[2] = vec2(0.05, -0.76);
    chick_vert[3] = vec2(0.02, -0.78);
    chick_vert[4] = vec2(0.01, -0.75);
    chick_vert[5] = vec2(0.02, -0.7);
	size_t chick_vert_bytes = 6 * sizeof(vec2);

	chick_color[0] = vec3(1.0, 0.0, 0.0);
	chick_color[1] = vec3(1.0, 0.0, 0.0);
	chick_color[2] = vec3(1.0, 0.0, 0.0);
	chick_color[3] = vec3(1.0, 0.0, 0.0);
	chick_color[4] = vec3(1.0, 0.0, 0.0);
    chick_color[4] = vec3(1.0, 0.0, 0.0);
    chick_color[5] = vec3(1.0, 0.0, 0.0);
	size_t chick_color_bytes = 6 * sizeof(vec3);

	std::string vshader = shader_path + "vshader_Prince.glsl";
	std::string fshader = shader_path + "fshader_Prince.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	chick_GLvars.a_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(chick_GLvars.a_vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(chick_GLvars.a_vertex_shader);
	check_shader_compilation(vshader, chick_GLvars.a_vertex_shader);

	chick_GLvars.a_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(chick_GLvars.a_fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(chick_GLvars.a_fragment_shader);
	check_shader_compilation(fshader, chick_GLvars.a_fragment_shader);

	chick_GLvars.a_program = glCreateProgram();
	glAttachShader(chick_GLvars.a_program, chick_GLvars.a_vertex_shader);
	glAttachShader(chick_GLvars.a_program, chick_GLvars.a_fragment_shader);

	glLinkProgram(chick_GLvars.a_program);
	check_program_link(chick_GLvars.a_program);

	glBindFragDataLocation(chick_GLvars.a_program, 0, "fragColor");

	chick_GLvars.a_vpos_location = glGetAttribLocation(chick_GLvars.a_program, "vPos");
	chick_GLvars.a_vcolor_location = glGetAttribLocation(chick_GLvars.a_program, "vColor");
	chick_GLvars.a_M_location = glGetUniformLocation(chick_GLvars.a_program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &chick_GLvars.a_vao);
	//Set GL state to use vertex array object
	glBindVertexArray(chick_GLvars.a_vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &chick_GLvars.a_buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, chick_GLvars.a_buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(chick_vert) + sizeof(chick_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(chick_vert), chick_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(chick_vert), sizeof(chick_color), chick_color);

	glEnableVertexAttribArray(chick_GLvars.a_vpos_location);
	glEnableVertexAttribArray(chick_GLvars.a_vcolor_location);

	glVertexAttribPointer(chick_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(chick_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(chick_vert)));

	glBindVertexArray(0);

}

//Draw an chick
void Chicks::chick_draw(mat4 proj) {

	glUseProgram(chick_GLvars.a_program);
	glBindVertexArray(chick_GLvars.a_vao);

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(chick_GLvars.a_M_location, 1, GL_TRUE, proj);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glBindVertexArray(0);
	glUseProgram(0);
}
