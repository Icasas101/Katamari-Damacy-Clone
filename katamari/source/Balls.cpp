//
//  Balls.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 9/13/2020
//
//

#include "common.h"

//Ball constructor
Balls::Balls() {
	double random_x = 0.5 - rand() / (float)RAND_MAX;
	double random_y = 0.5 - rand() / (float)RAND_MAX;
	double random_m = rand() % 100;

	ball_state.a_cur_location = vec2(0.5, 0.5);
	ball_state.a_velocity = normalize(vec2(random_x, random_y)) * random_m / 300.0;
	//ball_state.a_velocity = (0.0, 0.0);

};

//Called everytime an animation tick happens
void Balls::ball_update_state() {
	//Set GL state to use vertex array object
	glBindVertexArray(ball_GLvars.a_vao);

	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ball_GLvars.a_buffer);

	float dt = 1.0 / 60.0;
	vec2 old_loc = ball_state.a_cur_location;
	vec2 moved;

	ball_state.a_cur_location += ball_state.a_velocity * dt; // calculate new center

	float x_move = old_loc.x - ball_state.a_cur_location.x;
	float y_move = old_loc.y - ball_state.a_cur_location.y;
	moved = vec2(x_move, y_move);
	for (int i = 0; i < 52; i++) {
		ball_vert[i] += moved;
	}


	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(ball_vert) + sizeof(ball_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ball_vert), ball_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(ball_vert), sizeof(ball_color), ball_color);

	glEnableVertexAttribArray(ball_GLvars.a_vpos_location);
	glEnableVertexAttribArray(ball_GLvars.a_vcolor_location);

	glVertexAttribPointer(ball_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ball_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ball_vert)));


	//glBindVertexArray(0);

}

//Initialize the gl state and variables
void Balls::ball_gl_init() {
	//ball
	//!!!!!!!!Populate balls vert + color

	ball_vert[0] = vec2(0.06, 0.04);
	ball_vert[1] = vec2(0.07, 0.04);
	ball_vert[2] = vec2(0.08, 0.04);

	ball_vert[3] = vec2(0.05, 0.05);
	ball_vert[4] = vec2(0.06, 0.05);
	ball_vert[5] = vec2(0.07, 0.05);
	ball_vert[6] = vec2(0.08, 0.05);
	ball_vert[7] = vec2(0.09, 0.05);

	ball_vert[8] = vec2(0.05, 0.06);
	ball_vert[9] = vec2(0.06, 0.06);
	ball_vert[10] = vec2(0.07, 0.06);
	ball_vert[11] = vec2(0.08, 0.06);
	ball_vert[12] = vec2(0.09, 0.06);

	ball_vert[13] = vec2(0.04, 0.07);
	ball_vert[14] = vec2(0.05, 0.07);
	ball_vert[15] = vec2(0.06, 0.07);
	ball_vert[16] = vec2(0.07, 0.07);
	ball_vert[17] = vec2(0.08, 0.07);
	ball_vert[18] = vec2(0.09, 0.07);

	ball_vert[19] = vec2(0.05, 0.08);
	ball_vert[20] = vec2(0.06, 0.08);
	ball_vert[21] = vec2(0.07, 0.08);
	ball_vert[22] = vec2(0.08, 0.08);
	ball_vert[23] = vec2(0.09, 0.08);

	ball_vert[24] = vec2(0.06, 0.09);
	ball_vert[25] = vec2(0.07, 0.09);
	ball_vert[26] = vec2(0.08, 0.09);
	ball_vert[27] = vec2(0.09, 0.09);
	ball_vert[28] = vec2(0.1, 0.09);
	ball_vert[29] = vec2(0.13, 0.09);

	ball_vert[30] = vec2(0.06, 0.1);
	ball_vert[31] = vec2(0.07, 0.1);
	ball_vert[32] = vec2(0.08, 0.1);
	ball_vert[33] = vec2(0.09, 0.1);
	ball_vert[34] = vec2(0.10, 0.1);
	ball_vert[35] = vec2(0.11, 0.1);
	ball_vert[36] = vec2(0.12, 0.1);
	ball_vert[37] = vec2(0.13, 0.1);

	ball_vert[38] = vec2(0.06, 0.11);
	ball_vert[39] = vec2(0.07, 0.11);
	ball_vert[40] = vec2(0.08, 0.11);
	ball_vert[41] = vec2(0.09, 0.11);
	ball_vert[42] = vec2(0.10, 0.11);
	ball_vert[43] = vec2(0.11, 0.11);
	ball_vert[44] = vec2(0.12, 0.11);
	ball_vert[45] = vec2(0.13, 0.11);

	ball_vert[46] = vec2(0.07, 0.12);
	ball_vert[47] = vec2(0.08, 0.12);
	ball_vert[48] = vec2(0.09, 0.12);
	ball_vert[49] = vec2(0.10, 0.12);
	ball_vert[50] = vec2(0.11, 0.12);
	ball_vert[51] = vec2(0.12, 0.12);


	size_t ball_vert_bytes = 6 * sizeof(vec2);

	ball_color[0] = yellow;
	ball_color[1] = yellow;
	ball_color[2] = yellow;

	ball_color[3] = yellow;
	ball_color[4] = yellow;
	ball_color[5] = yellow;
	ball_color[6] = yellow;
	ball_color[7] = yellow;

	ball_color[8] = orange;
	ball_color[9] = orange;
	ball_color[10] = yellow;
	ball_color[11] = black;
	ball_color[12] = yellow;

	ball_color[13] = orange;
	ball_color[14] = orange;
	ball_color[15] = orange;
	ball_color[16] = yellow;
	ball_color[17] = yellow;
	ball_color[18] = yellow;

	ball_color[19] = yellow;
	ball_color[20] = yellow;
	ball_color[21] = yellow;
	ball_color[22] = yellow;
	ball_color[23] = yellow;

	ball_color[24] = yellow;
	ball_color[25] = yellow;
	ball_color[26] = yellow;
	ball_color[27] = yellow;
	ball_color[28] = yellow;

	ball_color[29] = yellow;
	ball_color[30] = yellow;
	ball_color[31] = yellow;
	ball_color[32] = yellow;
	ball_color[33] = yellow;
	ball_color[34] = yellow;
	ball_color[35] = yellow;
	ball_color[36] = yellow;
	ball_color[37] = yellow;
	ball_color[38] = yellow;
	ball_color[39] = yellow;
	ball_color[40] = yellow;
	ball_color[41] = yellow;
	ball_color[42] = yellow;
	ball_color[43] = yellow;
	ball_color[44] = yellow;
	ball_color[45] = yellow;
	ball_color[46] = yellow;
	ball_color[47] = yellow;
	ball_color[48] = yellow;
	ball_color[49] = yellow;
	ball_color[50] = yellow;
	ball_color[51] = yellow;



	size_t ball_color_bytes = 6 * sizeof(vec3);

	std::string vshader = shader_path + "vshader_Prince.glsl";
	std::string fshader = shader_path + "fshader_Prince.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	ball_GLvars.a_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ball_GLvars.a_vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(ball_GLvars.a_vertex_shader);
	check_shader_compilation(vshader, ball_GLvars.a_vertex_shader);

	ball_GLvars.a_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ball_GLvars.a_fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(ball_GLvars.a_fragment_shader);
	check_shader_compilation(fshader, ball_GLvars.a_fragment_shader);

	ball_GLvars.a_program = glCreateProgram();
	glAttachShader(ball_GLvars.a_program, ball_GLvars.a_vertex_shader);
	glAttachShader(ball_GLvars.a_program, ball_GLvars.a_fragment_shader);

	glLinkProgram(ball_GLvars.a_program);
	check_program_link(ball_GLvars.a_program);

	glBindFragDataLocation(ball_GLvars.a_program, 0, "fragColor");

	ball_GLvars.a_vpos_location = glGetAttribLocation(ball_GLvars.a_program, "vPos");
	ball_GLvars.a_vcolor_location = glGetAttribLocation(ball_GLvars.a_program, "vColor");
	ball_GLvars.a_M_location = glGetUniformLocation(ball_GLvars.a_program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &ball_GLvars.a_vao);
	//Set GL state to use vertex array object
	glBindVertexArray(ball_GLvars.a_vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &ball_GLvars.a_buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ball_GLvars.a_buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(ball_vert) + sizeof(ball_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ball_vert), ball_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(ball_vert), sizeof(ball_color), ball_color);

	glEnableVertexAttribArray(ball_GLvars.a_vpos_location);
	glEnableVertexAttribArray(ball_GLvars.a_vcolor_location);

	glVertexAttribPointer(ball_GLvars.a_vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ball_GLvars.a_vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ball_vert)));

	glBindVertexArray(0);

}

//Draw an ball
void Balls::ball_draw(mat4 proj) {

	glUseProgram(ball_GLvars.a_program);
	glBindVertexArray(ball_GLvars.a_vao);
	mat4 duck_scale = (Scale(0.5));
	//    mat4 M2 = (Translate(1,-1,0) * RotateZ(90));
	//    mat4 M3 = (Translate(-2.5,-1.5,0) * Scale(4));
	//    mat4 M4 = (Translate(-0.915,0.5,0) * RotateZ(-45) * Scale(2));

		//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(ball_GLvars.a_M_location, 1, GL_TRUE, proj * duck_scale);

	glPointSize(3.0);
	glDrawArrays(GL_POINTS, 0, 52);

	glBindVertexArray(0);
	glUseProgram(0);
}
