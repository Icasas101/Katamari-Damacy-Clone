//
//  Prince.cpp
//  Katamari Damacy clone
//
//  Created by Lana Biren, Isabella Casas, Ashley Chen on 11/27/2020
//
//

#include "common.h"

//Prince constructor
Prince::Prince(){
      state.cur_location = vec2(0.0, 0.0);
      state.pointing = vec2(0.0, 0.15);
	  state.velocity = normalize(vec2(0.5, 0.5)) * 3.0;
      state.katamari = vec2(0.185, 0.095);
};


//Called everytime an animation tick happens
void Prince::update_state(){
  
  glBindVertexArray(GLvars.vao);
  glBindBuffer(GL_ARRAY_BUFFER, GLvars.buffer);
  
//  vec2 accel = state.pointing - state.cur_location;
//  vec2 new_velocity;
//  float dt = 1.0/60.0;
  
  state.cur_location += state.moved; // calculate new prince center
  state.katamari += state.moved; // calculate new katamari center
  
//  std::cout << "prince at " << state.cur_location << "\n";
//  std::cout << "katamari at " << state.katamari << "\n";
  
//  float x_move = old_loc.x - state.cur_location.x;
//  float y_move = old_loc.y - state.cur_location.y;
//  move = vec2(x_move, y_move);
  for (int i = 0; i < 60; i++) {
    prince_vert[i] += state.moved;
  }
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(prince_vert) + sizeof(prince_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(prince_vert), prince_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(prince_vert), sizeof(prince_color), prince_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(prince_vert)) );


  
  //accel = F;
  //a = F;
  //Force is in the direction the Prince is pointing
  //Clamp acceleration at some maximum value
  
  //v  = old_velocity + a*dt
  // clamp velocity at a maximum value
  // Dampen the velocity at every timestep to lessen intertia
  
  //p  = old_position + v*dt
  // Wrap the Prince position when at the boundary

}

//Initialize the gl state and variables
void Prince::gl_init(){
  //Prince
  //!!!!!!!!Populate prince_vert and prince_color
    
  state.cur_location = vec2(0.08, 0.09);
  state.pointing = vec2(0.0, 0.15);

    prince_vert[0] = vec2(0.08, 0.03);
    prince_vert[1] = vec2(0.08, 0.04);
    
    prince_vert[2] = vec2(0.04, 0.05);
    prince_vert[3] = vec2(0.05, 0.05);
    prince_vert[4] = vec2(0.06, 0.05);
    prince_vert[5] = vec2(0.07, 0.05);
    prince_vert[6] = vec2(0.08, 0.05);
    prince_vert[7] = vec2(0.09, 0.05);
    prince_vert[8] = vec2(0.1, 0.05);
    prince_vert[9] = vec2(0.11, 0.05);
    prince_vert[10] = vec2(0.12, 0.05);
    
    prince_vert[11] = vec2(0.04, 0.06);
    prince_vert[12] = vec2(0.05, 0.06);
    prince_vert[13] = vec2(0.06, 0.06);
    prince_vert[14] = vec2(0.07, 0.06);
    prince_vert[15] = vec2(0.08, 0.06);
    prince_vert[16] = vec2(0.09, 0.06);
    prince_vert[17] = vec2(0.1, 0.06);
    prince_vert[18] = vec2(0.11, 0.06);
    prince_vert[19] = vec2(0.12, 0.06);
    
    prince_vert[20] = vec2(0.04, 0.07);
    prince_vert[21] = vec2(0.05, 0.07);
    prince_vert[22] = vec2(0.06, 0.07);
    prince_vert[23] = vec2(0.07, 0.07);
    prince_vert[24] = vec2(0.08, 0.07);
    prince_vert[25] = vec2(0.09, 0.07);
    prince_vert[26] = vec2(0.1, 0.07);
    prince_vert[27] = vec2(0.11, 0.07);
    prince_vert[28] = vec2(0.12, 0.07);
    
    prince_vert[29] = vec2(0.04, 0.08);
    prince_vert[30] = vec2(0.05, 0.08);
    prince_vert[31] = vec2(0.06, 0.08);
    prince_vert[32] = vec2(0.07, 0.08);
    prince_vert[33] = vec2(0.08, 0.08);
    prince_vert[34] = vec2(0.09, 0.08);
    prince_vert[35] = vec2(0.10, 0.08);
    prince_vert[36] = vec2(0.11, 0.08);
    prince_vert[37] = vec2(0.12, 0.08);
    
    prince_vert[38] = vec2(0.07, 0.09);
    prince_vert[39] = vec2(0.08, 0.09);
    prince_vert[40] = vec2(0.09, 0.09);
    
    prince_vert[41] = vec2(0.06, 0.1);
    prince_vert[42] = vec2(0.07, 0.1);
    prince_vert[43] = vec2(0.08, 0.1);
    prince_vert[44] = vec2(0.09, 0.1);
    prince_vert[45] = vec2(0.1, 0.1);
    
    prince_vert[46] = vec2(0.05, 0.11);
    prince_vert[47] = vec2(0.07, 0.11);
    prince_vert[48] = vec2(0.08, 0.11);
    prince_vert[49] = vec2(0.09, 0.11);
    prince_vert[50] = vec2(0.11, 0.11);
    
    prince_vert[51] = vec2(0.07, 0.12);
    prince_vert[52] = vec2(0.08, 0.12);
    prince_vert[53] = vec2(0.09, 0.12);
    
    prince_vert[54] = vec2(0.07, 0.13);
    prince_vert[55] = vec2(0.09, 0.13);
    
    prince_vert[56] = vec2(0.18, 0.09);
    prince_vert[57] = vec2(0.18, 0.1);
    prince_vert[58] = vec2(0.19, 0.09);
    prince_vert[59] = vec2(0.19, 0.1);
    
    size_t prince_vert_bytes = 60 * sizeof(vec2);
  
    for (int i = 0; i < 60; i++) {
      prince_vert[i] = zoom(0.8, 1.2) * prince_vert[i];
    }
  
    state.cur_location = zoom(0.8, 1.2) * state.cur_location;
    state.katamari = zoom(0.8, 1.2) * state.katamari;
    
    prince_color[0] = orange;
    prince_color[1] = yellow;
    
    prince_color[2] = dgreen;
    prince_color[3] = green;
    prince_color[4] = almond;
    prince_color[5] = almond;
    prince_color[6] = almond;
    prince_color[7] = almond;
    prince_color[8] = almond;
    prince_color[9] = green;
    prince_color[10] = dgreen;
    
    prince_color[11] = dgreen;
    prince_color[12] = green;
    prince_color[13] = almond;
    prince_color[14] = black;
    prince_color[15] = almond;
    prince_color[16] = black;
    prince_color[17] = almond;
    prince_color[18] = green;
    prince_color[19] = dgreen;
    
    prince_color[20] = dgreen;
    prince_color[21] = green;
    prince_color[22] = almond;
    prince_color[23] = almond;
    prince_color[24] = almond;
    prince_color[25] = almond;
    prince_color[26] = almond;
    prince_color[27] = green;
    prince_color[28] = dgreen;
    
    prince_color[29] = dgreen;
    prince_color[30] = green;
    prince_color[31] = green;
    prince_color[32] = green;
    prince_color[33] = green;
    prince_color[34] = green;
    prince_color[35] = green;
    prince_color[36] = green;
    prince_color[37] = dgreen;
    
    prince_color[38] = green;
    prince_color[39] = green;
    prince_color[40] = green;
    
    prince_color[41] = green;
    prince_color[42] = green;
    prince_color[43] = green;
    prince_color[44] = green;
    prince_color[45] = green;
    
    prince_color[46] = green;
    prince_color[47] = green;
    prince_color[48] = green;
    prince_color[49] = green;
    prince_color[50] = green;
    
    prince_color[51] = green;
    prince_color[52] = green;
    prince_color[53] = green;
    
    prince_color[54] = purple;
    prince_color[55] = purple;
    
    prince_color[56] = blue;
    prince_color[57] = purple;
    prince_color[58] = purple;
    prince_color[59] = blue;
    
    size_t prince_color_bytes = 60 * sizeof(vec3);
  
  
  
  std::string vshader = shader_path + "vshader_Prince.glsl";
  std::string fshader = shader_path + "fshader_Prince.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(prince_vert) + sizeof(prince_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(prince_vert), prince_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(prince_vert), sizeof(prince_color), prince_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(prince_vert)) );
  
  glBindVertexArray(0);

}

//Draw a prince
void Prince::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );

  vec2 accel = state.pointing - state.cur_location;
  vec2 new_velocity;
  float dt = 1.0 / 60.0;
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj);
  
  glPointSize(6.0);
  glDrawArrays(GL_POINTS, 0, 60);
  
  glBindVertexArray(0);
  glUseProgram(0);
}

