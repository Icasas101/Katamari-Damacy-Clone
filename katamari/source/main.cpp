#include "common.h"

using namespace Angel;

Prince prince;
Chicks chick;
Rooms room;
Kids kid;
Legos lego;
Sharks shark;
Balls ball;
//Mesh frame;


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    prince.moveLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    prince.moveRight();
  if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	prince.moveForward();
  if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	prince.moveDown();
}

void init(){
  
  glClearColor(0.824, 0.706, 0.549, 1.0);

  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  
  room.room_gl_init();
  //frame.mesh_gl_init();
  prince.gl_init();
  chick.chick_gl_init();
  shark.shark_gl_init();
  ball.ball_gl_init();
  lego.lego_gl_init();
  kid.kid_gl_init();
  


}

//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
	  glfwSetTime(0.0);

	chick.chick_update_state();

  }
}

int main(void)

{
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  
  window = glfwCreateWindow(1024, 768, "Katamari Damacy", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();
  
  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-1.0, 1.0, 1.0, -1.0);
    
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    room.room_draw(proj);
    //frame.mesh_draw(width, height);
    prince.draw(proj);
	  chick.chick_draw(proj);
    shark.shark_draw(proj);
    ball.ball_draw(proj);
    lego.lego_draw(proj);
    kid.kid_draw(proj);
	
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
