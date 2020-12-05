//
//  Chicks.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 9/13/2020
//
//

#include "common.h"

std::vector < Chicks * > chicks;

//Chick constructor
Chicks::Chicks() {
      double random_x = 0.5 - rand() / (float)RAND_MAX;
      double random_y = 0.5 - rand() / (float)RAND_MAX;
      double random_m = rand() % 100;
  
      chick_state.a_cur_location = vec2(0.07, 0.09);
      chick_state.a_velocity = normalize(vec2(random_x, random_y)) * random_m/150.0;
      //chick_state.a_velocity = (0.3, -0.2);

};

void Chicks::stuck(Prince pr){
    
    //Set GL state to use vertex array object
    glBindVertexArray(chick_GLvars.a_vao);
    
    //Set GL state to use this buffer
    glBindBuffer(GL_ARRAY_BUFFER, chick_GLvars.a_buffer);
    
    float dt = 1.0 / 60.0;
    vec2 old_loc  = chick_state.a_cur_location;
    vec2 moved;
    
    chick_state.a_cur_location = pr.state.katamari + k_offset; // calculate center while with the katamri
    
    float x_move = old_loc.x - chick_state.a_cur_location.x;
    float y_move = old_loc.y - chick_state.a_cur_location.y;
    moved = vec2(-x_move, -y_move);
    for (int i = 0; i < 52; i++) {
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
}

//Called everytime an animation tick happens
void Chicks::chick_update_state() {
	//Set GL state to use vertex array object
	glBindVertexArray(chick_GLvars.a_vao);

	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, chick_GLvars.a_buffer);
    
//    vec2 *pos = new vec2[chicks.size()];
//    vec3 *col = new vec3[chicks.size()];
//
//    for(unsigned int i=0; i < chicks.size(); i++){
//        pos[i] = *(chicks[i]->c_vert_p);
//        col[i] = *(chicks[i]->c_col_p);
//    }
//
    float dt = 1.0 / 60.0;
    vec2 old_loc  = chick_state.a_cur_location;
    vec2 moved;

    chick_state.a_cur_location += chick_state.a_velocity * dt; // calculate new center
    
    float x_move = old_loc.x - chick_state.a_cur_location.x;
    float y_move = old_loc.y - chick_state.a_cur_location.y;
    moved = vec2(-x_move, -y_move);
    for (int i = 0; i < 52; i++) {
        chick_vert[i] += moved;
    }
    
    if (chick_state.a_cur_location.x > 1.2 || chick_state.a_cur_location.x < -1.2 || chick_state.a_cur_location.y > 0.8 || chick_state.a_cur_location.y < -0.8) {
        chick_state.a_velocity = (chick_state.a_velocity * -0.8);
//        chick_state.a_cur_location += chick_state.a_velocity * dt;
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
    
    chick_vert[0] = vec2(0.06, 0.04);
    chick_vert[1] = vec2(0.07, 0.04);
    chick_vert[2] = vec2(0.08, 0.04);
  
    chick_vert[3] = vec2(0.05, 0.05);
    chick_vert[4] = vec2(0.06, 0.05);
    chick_vert[5] = vec2(0.07, 0.05);
    chick_vert[6] = vec2(0.08, 0.05);
    chick_vert[7] = vec2(0.09, 0.05);
  
    chick_vert[8] = vec2(0.05, 0.06);
    chick_vert[9] = vec2(0.06, 0.06);
    chick_vert[10] = vec2(0.07, 0.06);
    chick_vert[11] = vec2(0.08, 0.06);
    chick_vert[12] = vec2(0.09, 0.06);
    
    chick_vert[13] = vec2(0.04, 0.07);
    chick_vert[14] = vec2(0.05, 0.07);
    chick_vert[15] = vec2(0.06, 0.07);
    chick_vert[16] = vec2(0.07, 0.07);
    chick_vert[17] = vec2(0.08, 0.07);
    chick_vert[18] = vec2(0.09, 0.07);
    
    chick_vert[19] = vec2(0.05, 0.08);
    chick_vert[20] = vec2(0.06, 0.08);
    chick_vert[21] = vec2(0.07, 0.08);
    chick_vert[22] = vec2(0.08, 0.08);
    chick_vert[23] = vec2(0.09, 0.08);
    
    chick_vert[24] = vec2(0.06, 0.09);
    chick_vert[25] = vec2(0.07, 0.09);
    chick_vert[26] = vec2(0.08, 0.09);
    chick_vert[27] = vec2(0.09, 0.09);
    chick_vert[28] = vec2(0.1, 0.09);
    chick_vert[29] = vec2(0.13, 0.09);
    
    chick_vert[30] = vec2(0.06, 0.1);
    chick_vert[31] = vec2(0.07, 0.1);
    chick_vert[32] = vec2(0.08, 0.1);
    chick_vert[33] = vec2(0.09, 0.1);
    chick_vert[34] = vec2(0.10, 0.1);
    chick_vert[35] = vec2(0.11, 0.1);
    chick_vert[36] = vec2(0.12, 0.1);
    chick_vert[37] = vec2(0.13, 0.1);
    
    chick_vert[38] = vec2(0.06, 0.11);
    chick_vert[39] = vec2(0.07, 0.11);
    chick_vert[40] = vec2(0.08, 0.11);
    chick_vert[41] = vec2(0.09, 0.11);
    chick_vert[42] = vec2(0.10, 0.11);
    chick_vert[43] = vec2(0.11, 0.11);
    chick_vert[44] = vec2(0.12, 0.11);
    chick_vert[45] = vec2(0.13, 0.11);
    
    chick_vert[46] = vec2(0.07, 0.12);
    chick_vert[47] = vec2(0.08, 0.12);
    chick_vert[48] = vec2(0.09, 0.12);
    chick_vert[49] = vec2(0.10, 0.12);
    chick_vert[50] = vec2(0.11, 0.12);
    chick_vert[51] = vec2(0.12, 0.12);

  
	size_t chick_vert_bytes = 52 * sizeof(vec2);
    for (int i = 0; i < 52; i++) {
        chick_vert[i] = zoom(0.5, 0.5) * chick_vert[i];
        chick_vert[i] += vec2(-0.1, -0.2);
    }
    
    chick_state.a_cur_location = zoom(0.5, 0.5) * chick_state.a_cur_location;
    chick_state.a_cur_location += vec2(-0.1, -0.2);

	chick_color[0] = yellow;
	chick_color[1] = yellow;
	chick_color[2] = yellow;
    
	chick_color[3] = yellow;
	chick_color[4] = yellow;
    chick_color[5] = yellow;
    chick_color[6] = yellow;
    chick_color[7] = yellow;
    
    chick_color[8] = orange;
    chick_color[9] = orange;
    chick_color[10] = yellow;
    chick_color[11] = black;
    chick_color[12] = yellow;
    
    chick_color[13] = orange;
    chick_color[14] = orange;
    chick_color[15] = orange;
    chick_color[16] = yellow;
    chick_color[17] = yellow;
    chick_color[18] = yellow;
    
    chick_color[19] = yellow;
    chick_color[20] = yellow;
    chick_color[21] = yellow;
    chick_color[22] = yellow;
    chick_color[23] = yellow;
    
    chick_color[24] = yellow;
    chick_color[25] = yellow;
    chick_color[26] = yellow;
    chick_color[27] = yellow;
    chick_color[28] = yellow;
    
    chick_color[29] = yellow;
    chick_color[30] = yellow;
    chick_color[31] = yellow;
    chick_color[32] = yellow;
    chick_color[33] = yellow;
    chick_color[34] = yellow;
    chick_color[35] = yellow;
    chick_color[36] = yellow;
    chick_color[37] = yellow;
    chick_color[38] = yellow;
    chick_color[39] = yellow;
    chick_color[40] = yellow;
    chick_color[41] = yellow;
    chick_color[42] = yellow;
    chick_color[43] = yellow;
    chick_color[44] = yellow;
    chick_color[45] = yellow;
    chick_color[46] = yellow;
    chick_color[47] = yellow;
    chick_color[48] = yellow;
    chick_color[49] = yellow;
    chick_color[50] = yellow;
    chick_color[51] = yellow;

  
  
	size_t chick_color_bytes = 52 * sizeof(vec3);

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

//Draw a chick
void Chicks::chick_draw(mat4 proj) {

	glUseProgram(chick_GLvars.a_program);
	glBindVertexArray(chick_GLvars.a_vao);
    mat4 duck_scale = (Scale(0.5));
//    mat4 M2 = (Translate(1,-1,0) * RotateZ(90));
//    mat4 M3 = (Translate(-2.5,-1.5,0) * Scale(4));
//    mat4 M4 = (Translate(-0.915,0.5,0) * RotateZ(-45) * Scale(2));

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(chick_GLvars.a_M_location, 1, GL_TRUE, proj);
    
    glPointSize(3.0);
	
//    for (int i = 0; i < chicks.size(); i++) {
//        glDrawArrays(GL_POINTS, 0, 52);
//    };
    glDrawArrays(GL_POINTS, 0, 52);

	glBindVertexArray(0);
	glUseProgram(0);
}
