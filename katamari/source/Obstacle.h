//
//  Obstacle.h
//  KATAMARI
//
//  Created by Ashley Chen on 12/4/20.
//

#ifndef Obstacle_h
#define Obstacle_h

#include "common.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Obstacle {

public:
    
    vec3 yellow = vec3(1.0, 0.85, 0.41);
    vec3 orange = vec3(0.97, 0.44, 0.30);
    vec3 pink = vec3(1.0, 0.38, 0.38);
    vec3 blue = vec3(0.32, 0.57, 0.74);
    vec3 purple = vec3(0.59, 0.24, 0.54);
    vec3 green = vec3(0.56, 0.75, 0.3);
    vec3 dgreen = vec3(0.24, 0.6, 0.24);
    vec3 almond = vec3(0.93, 0.83, 0.74);
    vec3 brown = vec3(0.44, 0.36, 0.31);
    
    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 white = vec3(1.0,1.0, 1.0);
    
    bool hit;
    
    
//    //Record of the chick's state
//    struct {
//        vec2 a_cur_location;   //Current position of the center
//        float a_angle;         //Rotation angle
//        vec2 a_pointing;       //Vector pointing to the front of the ship
//        //This function will be helpful to keep track of the direction the ship
//        //is pointing
//        vec2 a_accel;
//        mat2 a_RotateZ2D(const GLfloat theta) {
//            GLfloat angle = DegreesToRadians * theta;
//            mat2 c;
//            c[0][0] = c[1][1] = cos(angle);
//            c[1][0] = sin(angle);
//            c[0][1] = -c[1][0];
//            return c;
//        }
//        vec2 a_velocity;       //Velocity
//    } obstacle_state;
//
//    //OpenGL variables for a ship
//    struct {
//        GLuint a_vao;           //Vertex array object
//        GLuint a_program;       //shader program
//        GLuint a_buffer;        //Vertex buffer objects
//        GLuint a_vertex_shader, a_fragment_shader;  //Shaders
//        GLint a_vpos_location, a_vcolor_location;   //reference to pos and color in shaders
//        GLint a_M_location;     //Reference to matrix in shader
//    } chick_GLvars;
//
//
//public:
//
//
//    Chicks();
//
//    mat4 chick_move;
//
//    //    inline void rotateLeft() {
//    //        //Do something
//    //          // update geometry here and change direction it's pointing
//    //        //m2 *= RotateZ(-5);
//    //        //state.pointing *= RotateZ2D(-5);
//    //
//    //    }
//    //    inline void rotateRight() {
//    //        //Do something
//    //        //m2 *= RotateZ(5);
//    //        //state.pointing *= RotateZ2D(5);
//    //
//    //    }
//
//    void chick_update_state();
//
//    void chick_gl_init();
//
//    void chick_draw(mat4 proj);
    
};

#endif /* Obstacle_h */
