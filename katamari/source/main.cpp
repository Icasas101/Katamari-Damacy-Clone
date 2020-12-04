#include "common.h"

using namespace Angel;

typedef vec4 color4;

// Initialize shader lighting parameters
vec4 light(0.0, 0.0, 10.0, 1.0);
color4 light_ambient(0.1, 0.1, 0.1, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

// Initialize shader material parameters
color4 material_ambient(0.1, 0.1, 0.1, 1.0);
color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
color4 material_specular(0.8, 0.8, 0.8, 1.0);
float material_shininess = 10;

Prince prince;
Chicks chick;
Rooms room;
Kids kid;
Legos lego;
Sharks shark;
Balls ball;

enum { _FRAME, _TOTAL_MODELS};
std::string files[_TOTAL_MODELS] = { "/models/frame.obj"};

std::vector < Mesh > mesh;
std::vector < GLuint > buffer;
std::vector < GLuint > vao;
GLuint ModelView_loc, NormalMatrix_loc, Projection_loc;
int current_draw;

GLuint program;

//==========Trackball Variables==========
static float curquat[4], lastquat[4];
/* current transformation matrix */
static float curmat[4][4];
mat4 curmat_a;
/* actual operation  */
bool scaling;
bool moving;
bool panning;
/* starting "moving" coordinates */
static int beginx, beginy;
/* ortho */
float ortho_x, ortho_y;
/* current scale factor */
static float scalefactor;
bool lbutton_down;


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    prince.rotateLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    prince.rotateRight();
  if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	prince.moveForward();
}

void init(){

	std::string vshader = shader_path + "/shaders/vshader.glsl";
	std::string fshader = shader_path + "/shaders/fshader.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	check_shader_compilation(vshader, vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	check_shader_compilation(fshader, fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	check_program_link(program);

	glUseProgram(program);

	glBindFragDataLocation(program, 0, "fragColor");

	//Per vertex attributes
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vNormal = glGetAttribLocation(program, "vNormal");

	//Compute ambient, diffuse, and specular terms


	//Retrieve and set uniform variables
	glUniform4fv(glGetUniformLocation(program, "Light"), 1, light);


	//Matrix uniform variable locations
	ModelView_loc = glGetUniformLocation(program, "ModelView");
	NormalMatrix_loc = glGetUniformLocation(program, "NormalMatrix");
	Projection_loc = glGetUniformLocation(program, "Projection");

	//===== Send data to GPU ======
	vao.resize(_TOTAL_MODELS);
	glGenVertexArrays(_TOTAL_MODELS, &vao[0]);

	buffer.resize(_TOTAL_MODELS);
	glGenBuffers(_TOTAL_MODELS, &buffer[0]);

	for (unsigned int i = 0; i < _TOTAL_MODELS; i++) {
		mesh.push_back((shader_path + files[i]).c_str());

		glBindVertexArray(vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		unsigned int vertices_bytes = mesh[i].vertices.size() * sizeof(vec4);
		unsigned int normals_bytes = mesh[i].normals.size() * sizeof(vec3);

		glBufferData(GL_ARRAY_BUFFER, vertices_bytes + normals_bytes, NULL, GL_STATIC_DRAW);
		unsigned int offset = 0;
		glBufferSubData(GL_ARRAY_BUFFER, offset, vertices_bytes, &mesh[i].vertices[0]);
		offset += vertices_bytes;
		glBufferSubData(GL_ARRAY_BUFFER, offset, normals_bytes, &mesh[i].normals[0]);

		glEnableVertexAttribArray(vNormal);
		glEnableVertexAttribArray(vPosition);

		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(mesh[i].vertices.size() * sizeof(vec4)));

	}

	//===== End: Send data to GPU ======


	// ====== Enable some opengl capabilitions ======
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
  
  glClearColor(0.824, 0.706, 0.549, 1.0);

  current_draw = 0;

  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  prince.gl_init();
  chick.chick_gl_init();
  room.room_gl_init();

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

	GLfloat aspect = GLfloat(width) / height;

	//Projection matrix
	mat4  projection = Perspective(45.0, aspect, 0.5, 5.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//"Camera" position
	const vec3 viewer_pos(0.0, 0.0, 2.0);

	//Track_ball rotation matrix
	mat4 track_ball = mat4(curmat[0][0], curmat[1][0], curmat[2][0], curmat[3][0],
		curmat[0][1], curmat[1][1], curmat[2][1], curmat[3][1],
		curmat[0][2], curmat[1][2], curmat[2][2], curmat[3][2],
		curmat[0][3], curmat[1][3], curmat[2][3], curmat[3][3]);

	//Modelview based on user interaction
	mat4 user_MV = Translate(-viewer_pos) *                    //Move Camera Back to -viewer_pos
		Translate(ortho_x, ortho_y, 0.0) *            //Pan Camera
		track_ball *                                  //Rotate Camera
		Scale(scalefactor, scalefactor, scalefactor);   //User Scale


	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, current_draw * ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, current_draw * diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, current_draw * specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	// ====== Draw ======
	glBindVertexArray(vao[current_draw]);
	//glBindBuffer( GL_ARRAY_BUFFER, buffer[current_draw] );

	glUniformMatrix4fv(ModelView_loc, 1, GL_TRUE, user_MV * mesh[current_draw].model_view);
	glUniformMatrix4fv(Projection_loc, 1, GL_TRUE, projection);
	glUniformMatrix4fv(NormalMatrix_loc, 1, GL_TRUE, transpose(invert(user_MV * mesh[current_draw].model_view)));

	glDrawArrays(GL_TRIANGLES, 0, mesh[current_draw].vertices.size());
	// ====== End: Draw ======

    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-1.0, 1.0, 1.0, -1.0);
    
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    prince.draw(proj);
	chick.chick_draw(proj);
	room.room_draw(proj);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
