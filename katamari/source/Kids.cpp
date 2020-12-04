//
//  Kids.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 9/13/2020
//
//

#include "common.h"

//Kid constructor
Kids::Kids() {
	double random_x = 0.5 - rand() / (float)RAND_MAX;
	double random_y = 0.5 - rand() / (float)RAND_MAX;
	double random_m = rand() % 100;

	kid_state.a_cur_location = vec2(0.5, 0.5);
	kid_state.a_velocity = normalize(vec2(random_x, random_y)) * random_m / 300.0;
	//kid_state.a_velocity = (0.0, 0.0);

};

//Called everytime an animation tick happens
void Kids::kid_update_state() {
	//Set GL state to use vertex array object
	glBindVertexArray(kid_GLvars.a_vao);

	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, kid_GLvars.a_buffer);

	float dt = 1.0 / 60.0;
	vec2 old_loc = kid_state.a_cur_location;
	vec2 moved;

	kid_state.a_cur_location += kid_state.a_velocity * dt; // calculate new center

	float x_move = old_loc.x - kid_state.a_cur_location.x;
	float y_move = old_loc.y - kid_state.a_cur_location.y;
	moved = vec2(x_move, y_move);
	for (int i = 0; i < 52; i++) {
		kid_vert[i] += moved;
	}


	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(kid_vert) + sizeof(kid_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(kid_vert), kid_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(kid_vert), sizeof(kid_color), kid_color);

	glEnableVertexAttribArray(kid_GLvars.a_vpos_location);
	glEnableVertexAttribArray(kid_GLvars.a_vcolor_location);

	glVertexAttribPointer(kid_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(kid_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(kid_vert)));


	//glBindVertexArray(0);

}

//Initialize the gl state and variables
void Kids::kid_gl_init() {
	//kid
	//!!!!!!!!Populate kids vert + color

	kid_vert[0] = vec2(0.06, 0.04);
	kid_vert[1] = vec2(0.07, 0.04);
	kid_vert[2] = vec2(0.08, 0.04);

	kid_vert[3] = vec2(0.05, 0.05);
	kid_vert[4] = vec2(0.06, 0.05);
	kid_vert[5] = vec2(0.07, 0.05);
	kid_vert[6] = vec2(0.08, 0.05);
	kid_vert[7] = vec2(0.09, 0.05);

	kid_vert[8] = vec2(0.05, 0.06);
	kid_vert[9] = vec2(0.06, 0.06);
	kid_vert[10] = vec2(0.07, 0.06);
	kid_vert[11] = vec2(0.08, 0.06);
	kid_vert[12] = vec2(0.09, 0.06);

	kid_vert[13] = vec2(0.04, 0.07);
	kid_vert[14] = vec2(0.05, 0.07);
	kid_vert[15] = vec2(0.06, 0.07);
	kid_vert[16] = vec2(0.07, 0.07);
	kid_vert[17] = vec2(0.08, 0.07);
	kid_vert[18] = vec2(0.09, 0.07);

	kid_vert[19] = vec2(0.05, 0.08);
	kid_vert[20] = vec2(0.06, 0.08);
	kid_vert[21] = vec2(0.07, 0.08);
	kid_vert[22] = vec2(0.08, 0.08);
	kid_vert[23] = vec2(0.09, 0.08);

	kid_vert[24] = vec2(0.06, 0.09);
	kid_vert[25] = vec2(0.07, 0.09);
	kid_vert[26] = vec2(0.08, 0.09);
	kid_vert[27] = vec2(0.09, 0.09);
	kid_vert[28] = vec2(0.1, 0.09);
	kid_vert[29] = vec2(0.13, 0.09);

	kid_vert[30] = vec2(0.06, 0.1);
	kid_vert[31] = vec2(0.07, 0.1);
	kid_vert[32] = vec2(0.08, 0.1);
	kid_vert[33] = vec2(0.09, 0.1);
	kid_vert[34] = vec2(0.10, 0.1);
	kid_vert[35] = vec2(0.11, 0.1);
	kid_vert[36] = vec2(0.12, 0.1);
	kid_vert[37] = vec2(0.13, 0.1);

	kid_vert[38] = vec2(0.06, 0.11);
	kid_vert[39] = vec2(0.07, 0.11);
	kid_vert[40] = vec2(0.08, 0.11);
	kid_vert[41] = vec2(0.09, 0.11);
	kid_vert[42] = vec2(0.10, 0.11);
	kid_vert[43] = vec2(0.11, 0.11);
	kid_vert[44] = vec2(0.12, 0.11);
	kid_vert[45] = vec2(0.13, 0.11);

	kid_vert[46] = vec2(0.07, 0.12);
	kid_vert[47] = vec2(0.08, 0.12);
	kid_vert[48] = vec2(0.09, 0.12);
	kid_vert[49] = vec2(0.10, 0.12);
	kid_vert[50] = vec2(0.11, 0.12);
	kid_vert[51] = vec2(0.12, 0.12);


	size_t kid_vert_bytes = 6 * sizeof(vec2);

	kid_color[0] = yellow;
	kid_color[1] = yellow;
	kid_color[2] = yellow;

	kid_color[3] = yellow;
	kid_color[4] = yellow;
	kid_color[5] = yellow;
	kid_color[6] = yellow;
	kid_color[7] = yellow;

	kid_color[8] = orange;
	kid_color[9] = orange;
	kid_color[10] = yellow;
	kid_color[11] = black;
	kid_color[12] = yellow;

	kid_color[13] = orange;
	kid_color[14] = orange;
	kid_color[15] = orange;
	kid_color[16] = yellow;
	kid_color[17] = yellow;
	kid_color[18] = yellow;

	kid_color[19] = yellow;
	kid_color[20] = yellow;
	kid_color[21] = yellow;
	kid_color[22] = yellow;
	kid_color[23] = yellow;

	kid_color[24] = yellow;
	kid_color[25] = yellow;
	kid_color[26] = yellow;
	kid_color[27] = yellow;
	kid_color[28] = yellow;

	kid_color[29] = yellow;
	kid_color[30] = yellow;
	kid_color[31] = yellow;
	kid_color[32] = yellow;
	kid_color[33] = yellow;
	kid_color[34] = yellow;
	kid_color[35] = yellow;
	kid_color[36] = yellow;
	kid_color[37] = yellow;
	kid_color[38] = yellow;
	kid_color[39] = yellow;
	kid_color[40] = yellow;
	kid_color[41] = yellow;
	kid_color[42] = yellow;
	kid_color[43] = yellow;
	kid_color[44] = yellow;
	kid_color[45] = yellow;
	kid_color[46] = yellow;
	kid_color[47] = yellow;
	kid_color[48] = yellow;
	kid_color[49] = yellow;
	kid_color[50] = yellow;
	kid_color[51] = yellow;



	size_t kid_color_bytes = 6 * sizeof(vec3);

	std::string vshader = shader_path + "vshader_Prince.glsl";
	std::string fshader = shader_path + "fshader_Prince.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	kid_GLvars.a_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(kid_GLvars.a_vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(kid_GLvars.a_vertex_shader);
	check_shader_compilation(vshader, kid_GLvars.a_vertex_shader);

	kid_GLvars.a_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(kid_GLvars.a_fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(kid_GLvars.a_fragment_shader);
	check_shader_compilation(fshader, kid_GLvars.a_fragment_shader);

	kid_GLvars.a_program = glCreateProgram();
	glAttachShader(kid_GLvars.a_program, kid_GLvars.a_vertex_shader);
	glAttachShader(kid_GLvars.a_program, kid_GLvars.a_fragment_shader);

	glLinkProgram(kid_GLvars.a_program);
	check_program_link(kid_GLvars.a_program);

	glBindFragDataLocation(kid_GLvars.a_program, 0, "fragColor");

	kid_GLvars.a_vpos_location = glGetAttribLocation(kid_GLvars.a_program, "vPos");
	kid_GLvars.a_vcolor_location = glGetAttribLocation(kid_GLvars.a_program, "vColor");
	kid_GLvars.a_M_location = glGetUniformLocation(kid_GLvars.a_program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &kid_GLvars.a_vao);
	//Set GL state to use vertex array object
	glBindVertexArray(kid_GLvars.a_vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &kid_GLvars.a_buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, kid_GLvars.a_buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(kid_vert) + sizeof(kid_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(kid_vert), kid_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(kid_vert), sizeof(kid_color), kid_color);

	glEnableVertexAttribArray(kid_GLvars.a_vpos_location);
	glEnableVertexAttribArray(kid_GLvars.a_vcolor_location);

	glVertexAttribPointer(kid_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(kid_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(kid_vert)));

	glBindVertexArray(0);

}

//Draw an kid
void Kids::kid_draw(mat4 proj) {

	glUseProgram(kid_GLvars.a_program);
	glBindVertexArray(kid_GLvars.a_vao);
	mat4 duck_scale = (Scale(0.5));
	//    mat4 M2 = (Translate(1,-1,0) * RotateZ(90));
	//    mat4 M3 = (Translate(-2.5,-1.5,0) * Scale(4));
	//    mat4 M4 = (Translate(-0.915,0.5,0) * RotateZ(-45) * Scale(2));

		//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(kid_GLvars.a_M_location, 1, GL_TRUE, proj * duck_scale);

	glPointSize(3.0);
	glDrawArrays(GL_POINTS, 0, 52);

	glBindVertexArray(0);
	glUseProgram(0);
}