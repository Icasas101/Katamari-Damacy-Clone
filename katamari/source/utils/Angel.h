//////////////////////////////////////////////////////////////////////////////
//
//  --- Angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_H__
#define __ANGEL_H__

//----------------------------------------------------------------------------
// 
// --- Include system headers ---
//

#include <cmath>
#include <iostream>
#include <cstdio>
#include <stdlib.h>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Include our class libraries and constants ---
//

namespace Angel {

//  Helper function to load vertex and fragment shader files
//GLuint InitShader( const char* vertexShaderFile,
//		   const char* fragmentShaderFile );

//  Defined constant for when numbers are too small to be used in the
//    denominator of a division operation.  This is only used if the
//    DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = M_PI / 180.0;  
const GLfloat  RadiansToDegrees = 180.0/M_PI;

}  // namespace Angel

#include "vec.h"
#include "mat.h"
//#include "CheckError.h"

static char*
readShaderSource(const char* shaderFile)
{
  FILE* fp = fopen(shaderFile, "rb");
  
  if ( fp == NULL ) { return NULL; }
  
  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  
  fseek(fp, 0L, SEEK_SET);
  char* buf = new char[size + 1];
  fread(buf, 1, size, fp);
  
  buf[size] = '\0';
  fclose(fp);
  
  return buf;
}

static void check_shader_compilation(std::string shader_file, GLuint shader){
  GLint  compiled;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
  if ( !compiled ) {
    std::cerr << shader_file.c_str() << " failed to compile:" << std::endl;
    GLint  logSize;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
    char* logMsg = new char[logSize];
    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
    std::cerr << logMsg << std::endl;
    delete [] logMsg;
    
    exit( EXIT_FAILURE );
  }
}

static void check_program_link(GLuint program){
  
  GLint  linked;
  glGetProgramiv( program, GL_LINK_STATUS, &linked );
  if ( !linked ) {
    std::cerr << "Shader program failed to link" << std::endl;
    GLint  logSize;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
    char* logMsg = new char[logSize];
    glGetProgramInfoLog( program, logSize, NULL, logMsg );
    std::cerr << logMsg << std::endl;
    delete [] logMsg;
    
    exit( EXIT_FAILURE );
  }
  
}


#endif // __ANGEL_H__
