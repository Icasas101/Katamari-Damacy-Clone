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
    
    bool hit = false;
    vec2 k_offset;
    
    vec2 cur_location;
    
    
    mat2 zoom(GLfloat x_scale, GLfloat y_scale) {
        return mat2( x_scale, 0.0, 0.0, y_scale );
    }
    

    
};

#endif /* Obstacle_h */
