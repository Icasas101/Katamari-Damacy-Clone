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
};


//Called everytime an animation tick happens
void Prince::update_state(){
  vec2 accel = state.pointing - state.cur_location;
  vec2 new_velocity;
  float dt = 1.0/60.0;
  
  glBindVertexArray(GLvars.vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, GLvars.buffer);
  
  


  
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
    
  state.cur_location = vec2(0.0, 0.0);
  state.pointing = vec2(0.0, 0.15);

  prince_vert[0] = vec2(0.05, -0.05);
  prince_vert[1] = vec2(0.0, -0.15);
  prince_vert[2] = vec2(-0.05, -0.05);
  prince_vert[3] = vec2(0.0, 0.15);
  prince_vert[4] = vec2(0.0, -0.15);
  prince_vert[5] = vec2(0.0, 0.0);
  size_t prince_vert_bytes = 6*sizeof(vec2);

  prince_color[0] = vec3( 1.0, 1.0, 1.0);
  prince_color[1] = vec3( 1.0, 1.0, 0.0);
  prince_color[2] = vec3( 1.0, 1.0, 1.0);
  prince_color[3] = vec3(1.0, 1.0, 1.0);
  prince_color[4] = vec3(1.0, 1.0, 1.0);
  prince_color[5] = vec3(1.0, 1.0, 1.0);
  size_t prince_color_bytes = 6*sizeof(vec3);
  
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
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj*m1);
  
  glDrawArrays(GL_LINE_LOOP, 0, 6);
  
  glBindVertexArray(0);
  glUseProgram(0);
}

