#include "common.h"
#include "lodepng.h"

using namespace Angel;

Prince prince;
Chicks chick;
Chicks chick2;
Chicks chick3;
Chicks chick4;
Chicks chick5;
Chicks chick6;
//Rooms room;
Kids kid;
Kids kid2;
Legos lego;
Legos lego2;
Legos lego3;
Legos lego4;
Legos lego5;
Sharks shark;
Sharks shark2;
Sharks shark3;
Sharks shark4;
Balls ball;
Balls ball2;
Balls ball3;
//Mesh frame;

/* -------------------------------------------------------------------------- */
void loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex){
    
    std::vector<unsigned char> image;
    unsigned int width;
    unsigned int height;
    //decode
    unsigned error = lodepng::decode(image, width, height, lpszPathName, LCT_RGBA, 8);
    
    //if there's an error, display it
    if(error){
        std::cout << "decoder error " << error;
        std::cout << ": " << lodepng_error_text(error) << std::endl;
        return;
    }
    
    /* the image "shall" be in RGBA_U8 format */
    
    std::cout << "Image loaded: " << width << " x " << height << std::endl;
    std::cout << image.size() << " pixels.\n";
    std::cout << "Image has " << image.size()/(width*height) << "color values per pixel.\n";
    
    GLint GL_format = GL_RGBA;
    
    glActiveTexture( GLtex );
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_format, width, height, 0, GL_format, GL_UNSIGNED_BYTE, &image[0] );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //Put things away and free memory
    image.clear();
}


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
  
  //room.room_gl_init();
  //frame.mesh_gl_init();
  prince.gl_init();
  chick.chick_gl_init();
  chick2.chick_gl_init();
  chick3.chick_gl_init();
  chick4.chick_gl_init();
  chick5.chick_gl_init();
  chick6.chick_gl_init();
  shark.shark_gl_init();
  shark2.shark_gl_init();
  shark3.shark_gl_init();
  shark4.shark_gl_init();
  ball.ball_gl_init();
  ball2.ball_gl_init();
  ball3.ball_gl_init();
  lego.lego_gl_init();
  lego2.lego_gl_init();
  lego3.lego_gl_init();
  lego4.lego_gl_init();
  lego5.lego_gl_init();
  kid.kid_gl_init();
  kid2.kid_gl_init();
  


}

//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
	  glfwSetTime(0.0);

	chick.chick_update_state();
	chick2.chick_update_state();
	chick3.chick_update_state();
	chick4.chick_update_state();
	chick5.chick_update_state();
	chick6.chick_update_state();

	lego.lego_update_state();
	lego2.lego_update_state();
	lego3.lego_update_state();
	lego4.lego_update_state();
	lego5.lego_update_state();

	shark.shark_update_state();
	shark2.shark_update_state();
	shark3.shark_update_state();
	shark4.shark_update_state();

	ball.ball_update_state();
	ball2.ball_update_state();
	ball3.ball_update_state();
	
	kid.kid_update_state();
	kid2.kid_update_state();
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
    
    //room.room_draw(proj);
    //frame.mesh_draw(width, height);
    prince.draw(proj);
	chick.chick_draw(proj);
	chick2.chick_draw(proj);
	chick3.chick_draw(proj);
	chick4.chick_draw(proj);
	chick5.chick_draw(proj);
	chick6.chick_draw(proj);
    shark.shark_draw(proj);
	shark2.shark_draw(proj);
	shark3.shark_draw(proj);
	shark4.shark_draw(proj);
    ball.ball_draw(proj);
	ball2.ball_draw(proj);
	ball3.ball_draw(proj);
    lego.lego_draw(proj);
	lego2.lego_draw(proj);
	lego3.lego_draw(proj);
	lego4.lego_draw(proj);
	lego5.lego_draw(proj);
    kid.kid_draw(proj);
	kid2.kid_draw(proj);
	
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
