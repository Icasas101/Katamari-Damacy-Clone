//
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"

//Ship constructor
Bullets::Bullets() {
	
	bullet_state.bullet_cur_location = vec2(0.0, 0.15);
	bullet_state.bullet_velocity = normalize(vec2(0.5, 0.5)) * 3.0;

}
void Bullets::update_state()
{
	if (bullet_state.fired) {
		//Set GL state to use vertex array object
		glBindVertexArray(bullet_GLvars.b_vao);

		//Set GL state to use this buffer
		glBindBuffer(GL_ARRAY_BUFFER, bullet_GLvars.b_buffer);

		float dt = 1.0 / 60.0;
		vec2 old_loc = bullet_state.bullet_cur_location;
		vec2 moved;

		bullet_state.bullet_cur_location += bullet_state.bullet_velocity * dt; // calculate new center

		float x_move = old_loc.x - bullet_state.bullet_cur_location.x;
		float y_move = old_loc.y - bullet_state.bullet_cur_location.y;
		moved = vec2(x_move, y_move);
		for (int i = 0; i < 3; i++) {
			bullet_vert[i] += moved;
		}


		//Create GPU buffer to hold vertices and color
		glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vert) + sizeof(bullet_color), NULL, GL_STATIC_DRAW);
		//First part of array holds vertices
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bullet_vert), bullet_vert);
		//Second part of array hold colors (offset by sizeof(triangle))
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(bullet_vert), sizeof(bullet_color), bullet_color);

		glEnableVertexAttribArray(bullet_GLvars.b_vpos_location);
		glEnableVertexAttribArray(bullet_GLvars.b_vcolor_location);

		glVertexAttribPointer(bullet_GLvars.b_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(bullet_GLvars.b_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bullet_vert)));


	}

}

void Bullets::gl_init()
{
	bullet_vert[0] = vec2(0.0, -0.15);
	bullet_vert[1] = vec2(0.01, -0.20);
	bullet_vert[2] = vec2(-0.01, -0.20);
	size_t bullet_vert_bytes = 3 * sizeof(vec2);

	bullet_color[0] = vec3(1.0, 1.0, 1.0);
	bullet_color[1] = vec3(1.0, 1.0, 1.0);
	bullet_color[2] = vec3(1.0, 1.0, 1.0);
	size_t bullet_color_bytes = 3 * sizeof(vec3);

	std::string vshader = shader_path + "vshader_Ship.glsl";
	std::string fshader = shader_path + "fshader_Ship.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	bullet_GLvars.b_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(bullet_GLvars.b_vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(bullet_GLvars.b_vertex_shader);
	check_shader_compilation(vshader, bullet_GLvars.b_vertex_shader);

	bullet_GLvars.b_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(bullet_GLvars.b_fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(bullet_GLvars.b_fragment_shader);
	check_shader_compilation(fshader, bullet_GLvars.b_fragment_shader);

	bullet_GLvars.b_program = glCreateProgram();
	glAttachShader(bullet_GLvars.b_program, bullet_GLvars.b_vertex_shader);
	glAttachShader(bullet_GLvars.b_program, bullet_GLvars.b_fragment_shader);

	glLinkProgram(bullet_GLvars.b_program);
	check_program_link(bullet_GLvars.b_program);

	glBindFragDataLocation(bullet_GLvars.b_program, 0, "fragColor");

	bullet_GLvars.b_vpos_location = glGetAttribLocation(bullet_GLvars.b_program, "vPos");
	bullet_GLvars.b_vcolor_location = glGetAttribLocation(bullet_GLvars.b_program, "vColor");
	bullet_GLvars.b_M_location = glGetUniformLocation(bullet_GLvars.b_program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &bullet_GLvars.b_vao);
	//Set GL state to use vertex array object
	glBindVertexArray(bullet_GLvars.b_vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &bullet_GLvars.b_buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, bullet_GLvars.b_buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vert) + sizeof(bullet_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bullet_vert), bullet_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bullet_vert), sizeof(bullet_color), bullet_color);

	glEnableVertexAttribArray(bullet_GLvars.b_vpos_location);
	glEnableVertexAttribArray(bullet_GLvars.b_vcolor_location);

	glVertexAttribPointer(bullet_GLvars.b_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(bullet_GLvars.b_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bullet_vert)));

	glBindVertexArray(0);
}

void Bullets::draw(mat4 proj)
{
	glUseProgram(bullet_GLvars.b_program);
	glBindVertexArray(bullet_GLvars.b_vao);

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(bullet_GLvars.b_M_location, 1, GL_TRUE, proj);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}
