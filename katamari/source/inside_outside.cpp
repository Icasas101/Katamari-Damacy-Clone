//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include "common.h"
//#include "shader.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>
//
//using namespace Angel;
//
////Globals there is a way to avoid this, but for now let's do the bad thing.
//int current_object = 0;
//int num_obj = 4;
//std::vector < GLuint > vao;
//std::vector < GLuint > buffer;
//std::vector < vec2* > objects;
//std::vector < unsigned int > num_points;
//
//GLuint x_vao;
//GLuint x_buffer;
//GLuint check_vao;
//GLuint check_buffer;
//
//bool inside;
//
////TODO: Inside outside test
//void inside_outside_test(vec2 point) {
//
//	// # of vertices == # of edges
//	int num_edges = num_points[current_object];
//	int in_strip = 0;
//	double x_cross;
//
//	vec2 p1 = objects[current_object][0];
//	for (int i = 1; i <= num_edges; i++) {
//		vec2 p2 = objects[current_object][i % num_edges];
//
//		//Checking if y of cursor is within bounds of y of edge
//		if (point.y > (p1.y < p2.y ? p1.y : p2.y) && (point.y <= (p1.y > p2.y ? p1.y : p2.y))) {
//
//			//Checking if x of cursor is less than max of x of edge and if edge is not horizontal
//			if (point.x <= (p1.x > p2.x ? p1.x : p2.x) && (p1.y != p2.y)) {
//				x_cross = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
//				if ((p1.x == p2.x) || (point.x <= x_cross)) {
//					in_strip++;
//				}
//			}
//		}
//		//swap
//		else {
//			p1 = p2;
//		}
//	}
//
//	if (in_strip % 2 == 0) {
//		inside = false; // even number of in_strip means it's outside of the polygon
//	}
//	else {
//		inside = true;
//	}
//}
//
//
////GLFW error callback
//static void error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Error: %s\n", description);
//}
//
////GLFW keypress callback
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//		current_object = (current_object + 1) % num_obj;
//}
//
//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	//Assuming the default frustrum with extents from -1 to 1, this converts
//	//the screen cursor position to world coordinates
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	xpos = xpos / width * 2.0 - 1.0;
//	ypos = -(ypos / height * 2.0 - 1.0);
//
//	inside_outside_test(vec2(xpos, ypos));
//}
//
////Initialize everything
//void init(GLuint& glShaderProgram) {
//
//	GLuint vertex_shader, fragment_shader;
//	GLint vpos_location, vcolor_location;
//
//	//String with absolute paths to our shaders, shader_path set by CMAKE hack
//	std::string vshader = shader_path + "vshader.glsl";
//	std::string fshader = shader_path + "fshader.glsl";
//
//	//Read in shader code to a character array
//	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
//	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
//
//	//Create and compile vertex shader
//	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
//	glCompileShader(vertex_shader);
//	check_shader_compilation(vshader, vertex_shader);
//
//	//Create and compile fragment shader
//	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
//	glCompileShader(fragment_shader);
//	check_shader_compilation(fshader, fragment_shader);
//
//	//Create shader program from the 2 shaders
//	glShaderProgram = glCreateProgram();
//	glAttachShader(glShaderProgram, vertex_shader);
//	glAttachShader(glShaderProgram, fragment_shader);
//	glLinkProgram(glShaderProgram);
//	check_program_link(glShaderProgram);
//
//	//bind or find the numerical location for shader variables
//	glBindFragDataLocation(glShaderProgram, 0, "fragColor");
//	vpos_location = glGetAttribLocation(glShaderProgram, "vPos");
//	vcolor_location = glGetAttribLocation(glShaderProgram, "vColor");
//
//
//	objects.resize(num_obj);
//	vao.resize(num_obj);
//	buffer.resize(num_obj);
//	num_points.resize(num_obj);
//
//	objects[0] = new vec2[3];
//	objects[0][0] = vec2(-1.0, -1.0);
//	objects[0][1] = vec2(0.0, 1.0);
//	objects[0][2] = vec2(1.0, -1.0);
//	num_points[0] = 3;
//
//	objects[1] = new vec2[4];
//	objects[1][0] = vec2(-0.5, -0.5);
//	objects[1][1] = vec2(-0.5, 0.5);
//	objects[1][2] = vec2(0.5, 0.5);
//	objects[1][3] = vec2(0.5, -0.5);
//	num_points[1] = 4;
//
//	objects[2] = new vec2[8];
//	objects[2][0] = vec2(-0.8, -0.8);
//	objects[2][1] = vec2(-0.8, 0.8);
//	objects[2][2] = vec2(0.8, 0.8);
//	objects[2][3] = vec2(0.8, -0.8);
//	objects[2][4] = vec2(0.4, -0.8);
//	objects[2][5] = vec2(0.4, 0.2);
//	objects[2][6] = vec2(-0.4, 0.2);
//	objects[2][7] = vec2(-0.4, -0.8);
//	num_points[2] = 8;
//
//
//	vec3* colors = new vec3[8];
//	colors[0] = vec3(1.0, 0.0, 1.0);
//	colors[1] = vec3(1.0, 0.0, 1.0);
//	colors[2] = vec3(1.0, 0.0, 1.0);
//	colors[3] = vec3(1.0, 0.0, 1.0);
//	colors[4] = vec3(1.0, 0.0, 1.0);
//	colors[5] = vec3(1.0, 0.0, 1.0);
//	colors[6] = vec3(1.0, 0.0, 1.0);
//	colors[7] = vec3(1.0, 0.0, 1.0);
//
//
//	for (unsigned int i = 0; i < num_obj; i++) {
//
//		// Create a vertex array object
//		glGenVertexArrays(1, &vao[i]);
//		//Set GL state to use vertex array object
//		glBindVertexArray(vao[i]);
//
//		//Generate buffer to hold our vertex data
//		glGenBuffers(1, &buffer[i]);
//		//Set GL state to use this buffer
//		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
//
//		//Create GPU buffer to hold vertices and color
//		glBufferData(GL_ARRAY_BUFFER, num_points[i] * sizeof(vec2) * num_points[i] * sizeof(vec3), NULL, GL_STATIC_DRAW);
//		//First part of array holds vertices
//		glBufferSubData(GL_ARRAY_BUFFER, 0, num_points[i] * sizeof(vec2), objects[i]);
//		//Second part of array hold colors (offset by sizeof(triangle))
//		glBufferSubData(GL_ARRAY_BUFFER, num_points[i] * sizeof(vec2), num_points[i] * sizeof(vec3), colors);
//
//		glEnableVertexAttribArray(vpos_location);
//		glEnableVertexAttribArray(vcolor_location);
//
//		glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//		glVertexAttribPointer(vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(num_points[i] * sizeof(vec2)));
//
//		glBindVertexArray(0);
//	}
//
//
//
//	vec2* x = new vec2[4];
//	x[0] = vec2(-0.9, -0.9);
//	x[1] = vec2(-0.8, -0.8);
//	x[2] = vec2(-0.8, -0.9);
//	x[3] = vec2(-0.9, -0.8);
//	size_t x_bytes = 4 * sizeof(vec2);
//
//	vec3* x_colors = new vec3[4];
//	x_colors[0] = vec3(1.0, 0.0, 0.0);
//	x_colors[1] = vec3(1.0, 0.0, 0.0);
//	x_colors[2] = vec3(1.0, 0.0, 0.0);
//	x_colors[3] = vec3(1.0, 0.0, 0.0);
//	size_t x_color_bytes = 4 * sizeof(vec3);
//
//	glGenVertexArrays(1, &x_vao);
//	glBindVertexArray(x_vao);
//	glGenBuffers(1, &x_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, x_buffer);
//	glBufferData(GL_ARRAY_BUFFER, x_bytes * x_color_bytes, NULL, GL_STATIC_DRAW);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, x_bytes, x);
//	glBufferSubData(GL_ARRAY_BUFFER, x_bytes, x_color_bytes, x_colors);
//
//	glEnableVertexAttribArray(vpos_location);
//	glEnableVertexAttribArray(vcolor_location);
//
//	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//	glVertexAttribPointer(vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(x_bytes));
//
//	glBindVertexArray(0);
//
//	vec2* check = new vec2[3];
//	check[0] = vec2(-0.9, -0.85);
//	check[1] = vec2(-0.85, -0.9);
//	check[2] = vec2(-0.8, -0.8);
//	size_t check_bytes = 3 * sizeof(vec2);
//
//	vec3* check_colors = new vec3[3];
//	check_colors[0] = vec3(0.0, 1.0, 0.0);
//	check_colors[1] = vec3(0.0, 1.0, 0.0);
//	check_colors[2] = vec3(0.0, 1.0, 0.0);
//	size_t check_color_bytes = 3 * sizeof(vec3);
//
//	glGenVertexArrays(1, &check_vao);
//	glBindVertexArray(check_vao);
//	glGenBuffers(1, &check_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, check_buffer);
//	glBufferData(GL_ARRAY_BUFFER, check_bytes * check_color_bytes, NULL, GL_STATIC_DRAW);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, check_bytes, check);
//	glBufferSubData(GL_ARRAY_BUFFER, check_bytes, check_color_bytes, check_colors);
//
//	glEnableVertexAttribArray(vpos_location);
//	glEnableVertexAttribArray(vcolor_location);
//
//	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//	glVertexAttribPointer(vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(check_bytes));
//
//	glBindVertexArray(0);
//
//	delete[] colors;
//	delete[] x;
//	delete[] x_colors;
//	delete[] check;
//	delete[] check_colors;
//}
//
////Main
//int main(void)
//{
//	//Init the geomerty and shaders
//	init(glShaderProgram);
//
//	//set the background/clear color
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	
//
//		switch (inside) {
//		case true:
//			glBindVertexArray(check_vao);
//			glDrawArrays(GL_LINE_STRIP, 0, 3);
//			break;
//		case false:
//			glBindVertexArray(x_vao);
//			glDrawArrays(GL_LINES, 0, 4);
//			break;
//		}
//
//
//	}
//}
