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
  
  glClearColor(0.44, 0.36, 0.31, 1.0);

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

void check_collision() {
  
  
  vec2 katamari_loc = prince.state.katamari;
  
  vec2 chick_loc = chick.chick_state.a_cur_location;
  vec2 chick2_loc = chick2.chick_state.a_cur_location;
  vec2 chick3_loc = chick3.chick_state.a_cur_location;
  vec2 chick4_loc = chick4.chick_state.a_cur_location;
  vec2 chick5_loc = chick5.chick_state.a_cur_location;
  vec2 chick6_loc = chick6.chick_state.a_cur_location;
  
  vec2 lego_loc = lego.lego_state.a_cur_location;
  vec2 lego2_loc = lego2.lego_state.a_cur_location;
  vec2 lego3_loc = lego3.lego_state.a_cur_location;
  vec2 lego4_loc = lego4.lego_state.a_cur_location;
  vec2 lego5_loc = lego5.lego_state.a_cur_location;
  
  vec2 shark_loc = shark.shark_state.a_cur_location;
  vec2 shark2_loc = shark2.shark_state.a_cur_location;
  vec2 shark3_loc = shark3.shark_state.a_cur_location;
  vec2 shark4_loc = shark4.shark_state.a_cur_location;
  
  vec2 ball_loc = ball.ball_state.a_cur_location;
  vec2 ball2_loc = ball2.ball_state.a_cur_location;
  vec2 ball3_loc = ball3.ball_state.a_cur_location;
  
  vec2 kid_loc = kid.kid_state.a_cur_location;
  vec2 kid2_loc = kid2.kid_state.a_cur_location;
  

  // CHICKS
  if (((katamari_loc.x - chick_loc.x) < 0.025 && (katamari_loc.x - chick_loc.x) > -0.025) && ((katamari_loc.y - chick_loc.y) < 0.025 && (katamari_loc.y - chick_loc.y) > -0.025)) {
      chick.hit = true;
      chick.k_offset = katamari_loc - chick_loc;
  }
  if (((katamari_loc.x - chick2_loc.x) < 0.025 && (katamari_loc.x - chick2_loc.x) > -0.025) && ((katamari_loc.y - chick2_loc.y) < 0.025 && (katamari_loc.y - chick2_loc.y) > -0.025)) {
      chick2.hit = true;
      chick2.k_offset = katamari_loc - chick2_loc;
  }
  if (((katamari_loc.x - chick3_loc.x) < 0.025 && (katamari_loc.x - chick3_loc.x) > -0.025) && ((katamari_loc.y - chick3_loc.y) < 0.025 && (katamari_loc.y - chick3_loc.y) > -0.025)) {
      chick3.hit = true;
      chick3.k_offset = katamari_loc - chick3_loc;
  }
  if (((katamari_loc.x - chick4_loc.x) < 0.025 && (katamari_loc.x - chick4_loc.x) > -0.025) && ((katamari_loc.y - chick4_loc.y) < 0.025 && (katamari_loc.y - chick4_loc.y) > -0.025)) {
      chick4.hit = true;
      chick4.k_offset = katamari_loc - chick4_loc;
  }
  if (((katamari_loc.x - chick5_loc.x) < 0.025 && (katamari_loc.x - chick5_loc.x) > -0.025) && ((katamari_loc.y - chick5_loc.y) < 0.025 && (katamari_loc.y - chick5_loc.y) > -0.025)) {
      chick5.hit = true;
      chick5.k_offset = katamari_loc - chick5_loc;
  }
  if (((katamari_loc.x - chick6_loc.x) < 0.025 && (katamari_loc.x - chick6_loc.x) > -0.025) && ((katamari_loc.y - chick6_loc.y) < 0.025 && (katamari_loc.y - chick6_loc.y) > -0.025)) {
      chick6.hit = true;
      chick6.k_offset = katamari_loc - chick6_loc;
  }
  
  // LEGOS
  if (((katamari_loc.x - lego_loc.x) < 0.025 && (katamari_loc.x - lego_loc.x) > -0.025) && ((katamari_loc.y - lego_loc.y) < 0.025 && (katamari_loc.y - lego_loc.y) > -0.025)) {
    lego.hit = true;
    lego.k_offset = katamari_loc - lego_loc;
  }
  if (((katamari_loc.x - lego2_loc.x) < 0.025 && (katamari_loc.x - lego2_loc.x) > -0.025) && ((katamari_loc.y - lego2_loc.y) < 0.025 && (katamari_loc.y - lego2_loc.y) > -0.025)) {
    lego2.hit = true;
    lego2.k_offset = katamari_loc - lego2_loc;
  }
  if (((katamari_loc.x - lego3_loc.x) < 0.025 && (katamari_loc.x - lego3_loc.x) > -0.025) && ((katamari_loc.y - lego3_loc.y) < 0.025 && (katamari_loc.y - lego3_loc.y) > -0.025)) {
    lego3.hit = true;
    lego3.k_offset = katamari_loc - lego3_loc;
  }
  if (((katamari_loc.x - lego4_loc.x) < 0.025 && (katamari_loc.x - lego4_loc.x) > -0.025) && ((katamari_loc.y - lego4_loc.y) < 0.025 && (katamari_loc.y - lego4_loc.y) > -0.025)) {
    lego4.hit = true;
    lego4.k_offset = katamari_loc - lego4_loc;
  }
  if (((katamari_loc.x - lego5_loc.x) < 0.025 && (katamari_loc.x - lego5_loc.x) > -0.025) && ((katamari_loc.y - lego5_loc.y) < 0.025 && (katamari_loc.y - lego5_loc.y) > -0.025)) {
    lego5.hit = true;
    lego5.k_offset = katamari_loc - lego5_loc;
  }
  
  // SHARK
  if (((katamari_loc.x - shark_loc.x) < 0.029 && (katamari_loc.x - shark_loc.x) > -0.029) && ((katamari_loc.y - shark_loc.y) < 0.029 && (katamari_loc.y - shark_loc.y) > -0.029)) {
    shark.hit = true;
    shark.k_offset = katamari_loc - shark_loc;
  }
  if (((katamari_loc.x - shark2_loc.x) < 0.029 && (katamari_loc.x - shark2_loc.x) > -0.029) && ((katamari_loc.y - shark2_loc.y) < 0.029 && (katamari_loc.y - shark2_loc.y) > -0.029)) {
    shark2.hit = true;
    shark2.k_offset = katamari_loc - shark2_loc;
  }
  if (((katamari_loc.x - shark3_loc.x) < 0.029 && (katamari_loc.x - shark3_loc.x) > -0.029) && ((katamari_loc.y - shark3_loc.y) < 0.029 && (katamari_loc.y - shark3_loc.y) > -0.029)) {
    shark3.hit = true;
    shark3.k_offset = katamari_loc - shark3_loc;
  }
  if (((katamari_loc.x - shark4_loc.x) < 0.029 && (katamari_loc.x - shark4_loc.x) > -0.029) && ((katamari_loc.y - shark4_loc.y) < 0.029 && (katamari_loc.y - shark4_loc.y) > -0.029)) {
    shark4.hit = true;
    shark4.k_offset = katamari_loc - shark4_loc;
  }
  
  // BALL
  if (((katamari_loc.x - ball_loc.x) < 0.029 && (katamari_loc.x - ball_loc.x) > -0.029) && ((katamari_loc.y - ball_loc.y) < 0.09 && (katamari_loc.y - ball_loc.y) > -0.09)) {
    ball.hit = true;
    ball.k_offset = katamari_loc - ball_loc;
  }
  if (((katamari_loc.x - ball2_loc.x) < 0.025 && (katamari_loc.x - ball2_loc.x) > -0.025) && ((katamari_loc.y - ball2_loc.y) < 0.025 && (katamari_loc.y - ball2_loc.y) > -0.025)) {
    ball2.hit = true;
    ball2.k_offset = katamari_loc - ball2_loc;
  }
  if (((katamari_loc.x - ball3_loc.x) < 0.025 && (katamari_loc.x - ball3_loc.x) > -0.025) && ((katamari_loc.y - ball3_loc.y) < 0.025 && (katamari_loc.y - ball3_loc.y) > -0.025)) {
    ball3.hit = true;
    ball3.k_offset = katamari_loc - ball3_loc;
  }
  
  // KID
  if (((katamari_loc.x - kid_loc.x) < 0.025 && (katamari_loc.x - kid_loc.x) > -0.025) && ((katamari_loc.y - kid_loc.y) < 0.025 && (katamari_loc.y - kid_loc.y) > -0.025)) {
    kid.hit = true;
    kid.k_offset = katamari_loc - kid_loc;
  }
  if (((katamari_loc.x - kid2_loc.x) < 0.025 && (katamari_loc.x - kid2_loc.x) > -0.025) && ((katamari_loc.y - kid2_loc.y) < 0.025 && (katamari_loc.y - kid2_loc.y) > -0.025)) {
    kid2.hit = true;
    kid2.k_offset = katamari_loc - kid2_loc;
  }
  
  
}

//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.095){ // was 0.033
    glfwSetTime(0.0);
    
    vec2 ball_loc = ball.ball_state.a_cur_location;
    vec2 shark_loc = shark.shark_state.a_cur_location;
    vec2 kid_loc = kid.kid_state.a_cur_location;
    vec2 katamari_loc = prince.state.katamari;
    
    
    //prince.update_state();
    
    // CHICK updates
    if (chick.hit == false){
        chick.chick_update_state();
    }
    else {
      chick.stuck(prince);
    }
    
    if (chick2.hit == false){
      chick2.chick_update_state();
    }
    else {
      chick2.stuck(prince);
    }
    
    if (chick3.hit == false){
      chick3.chick_update_state();
    }
    else {
      chick3.stuck(prince);
    }
    
    if (chick4.hit == false){
      chick4.chick_update_state();
    }
    else {
      chick4.stuck(prince);
    }
    
    if (chick5.hit == false){
      chick5.chick_update_state();
    }
    else {
      chick5.stuck(prince);
    }
    
    if (chick6.hit == false){
      chick6.chick_update_state();
    }
    else {
      chick6.stuck(prince);
    }

    // LEGO updates
    if (lego.hit == false){
      lego.lego_update_state();
    }
    else {
      lego.stuck(prince);
    }
    
    if (lego2.hit == false){
      lego2.lego_update_state();
    }
    else {
      lego2.stuck(prince);
    }
    
    if (lego3.hit == false){
      lego3.lego_update_state();
    }
    else {
      lego3.stuck(prince);
    }
    
    if (lego4.hit == false){
      lego4.lego_update_state();
    }
    else {
      lego4.stuck(prince);
    }
    
    if (lego5.hit == false){
      lego5.lego_update_state();
    }
    else {
      lego5.stuck(prince);
    }
    
    // SHARK updates
    if (shark.hit == false){
      shark.shark_update_state();
    }
    else {
      shark.stuck(prince);
//      std::cout<< "\nshark" << shark_loc;
//      std::cout<< "\nkatamari" << katamari_loc;
    }
    if (shark2.hit == false){
      shark2.shark_update_state();
    }
    else {
      shark2.stuck(prince);
    }
    
    if (shark3.hit == false){
      shark3.shark_update_state();
    }
    else {
      shark3.stuck(prince);
    }
    
    if (shark4.hit == false){
      shark4.shark_update_state();
    }
    else {
      shark4.stuck(prince);
    }
    
    // BALL updates
    if (ball.hit == false){
      ball.ball_update_state();
      std::cout<< "\nball not hit" << ball_loc;
      std::cout<< "\nkatamari not hit" << katamari_loc;
    }
    else {
      ball.stuck(prince);
      std::cout<< "\nball hit" << ball_loc;
      std::cout<< "\nkatamari hit" << katamari_loc;
    }
    
    if (ball2.hit == false){
      ball2.ball_update_state();
    }
    else {
      ball2.stuck(prince);
    }
    
    if (ball3.hit == false){
      ball3.ball_update_state();
    }
    else {
      ball3.stuck(prince);
    }
    
    // KID updates
    if (kid.hit == false){
      kid.kid_update_state();
      std::cout<<"\nkid not hit" << kid_loc;
      std::cout<<"\nkatamari not" << katamari_loc;
    }
    else {
      kid.stuck(prince);
      std::cout<<"\nkid hit" << kid_loc;
      std::cout<<"\nkatamari hit" << katamari_loc;
    }
    
    if (kid2.hit == false){
      kid2.kid_update_state();
    }
    else {
      kid2.stuck(prince);
    }
    
	check_collision();

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
    prince.draw(proj);

    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
