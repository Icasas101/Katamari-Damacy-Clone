#include "common.h"

enum { _FRAME, _TOTAL_MODELS };
std::string files[_TOTAL_MODELS] = { "/models/frame.obj" };

std::vector < Mesh > mesh;
std::vector < GLuint > buffer;
std::vector < GLuint > vao;

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

GLuint ModelView_loc, NormalMatrix_loc, Projection_loc;

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

bool Mesh::loadOBJ(const char* path) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< vec3 > temp_vertices;
	std::vector< vec2 > temp_uvs;
	std::vector< vec3 > temp_normals;

	hasUV = true;

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	char* line = new char[128];
	char* lineHeader = new char[128];

	while (true) {
		memset(line, 0, 128);
		memset(lineHeader, 0, 128);

		if (fgets(line, 128, file) == NULL) { break; }
		sscanf(line, "%s ", lineHeader);

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			sscanf(&line[2], "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
			if (vertex.x < box_min.x) { box_min.x = vertex.x; }
			if (vertex.y < box_min.y) { box_min.y = vertex.y; }
			if (vertex.z < box_min.z) { box_min.z = vertex.z; }
			if (vertex.x > box_max.x) { box_max.x = vertex.x; }
			if (vertex.y > box_max.y) { box_max.y = vertex.y; }
			if (vertex.z > box_max.z) { box_max.z = vertex.z; }
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			sscanf(&line[3], "%f %f", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			sscanf(&line[3], "%f %f %f", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = sscanf(&line[2], "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				int matches = sscanf(&line[2], "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0],
					&vertexIndex[1], &normalIndex[1],
					&vertexIndex[2], &normalIndex[2]);
				if (matches == 6) {
					hasUV = false;
				}
				else {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
			}

			/* handle negative indices */
			/* (adjust for size during processing of each face, as per the old
			 *  OBJ specification, instead of after the end of the file) */
			for (int negati = 0; negati < 3; negati++) {
				if (vertexIndex[negati] < 0) {
					vertexIndex[negati] += temp_vertices.size();
					vertexIndex[negati]++; /* <- OBJ indices are one-based */
				}
				if (uvIndex[negati] < 0) {
					uvIndex[negati] += temp_uvs.size();
					uvIndex[negati]++;
				}
				if (normalIndex[negati] < 0) {
					normalIndex[negati] += temp_normals.size();
					normalIndex[negati]++;
				}
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			if (hasUV) {
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			}
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	delete[] line;
	delete[] lineHeader;

	//    std::cout << "Read " << temp_vertices.size() << " vertices\n";
	//    std::cout << "Read " << temp_normals.size() << " normals\n";
	//    std::cout << "Read " << vertexIndices.size()/3 << " faces\n";
	//

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vec4 vertex = vec4(temp_vertices[vertexIndex - 1], 1.0);
		vertices.push_back(vertex);
	}

	if (hasUV) {
		for (unsigned int i = 0; i < uvIndices.size(); i++) {
			unsigned int uvIndex = uvIndices[i];
			vec2 uv = temp_uvs[uvIndex - 1];
			uvs.push_back(uv);
		}
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = temp_normals[normalIndex - 1];
		normals.push_back(normal);
	}

	//    std::cout << "Total " << vertices.size() << " vertices\n";
	//    std::cout << "Total " << normals.size() << " normals\n";


	center = box_min + (box_max - box_min) / 2.0;
	scale = (std::max)(box_max.x - box_min.x, box_max.y - box_min.y);

	model_view = Scale(1.0 / scale,           //Make the extents 0-1
		1.0 / scale,
		1.0 / scale) *
		Translate(-center);  //Orient Model About Center


	return true;
}

//Initialize the gl state and variables
void Mesh::mesh_gl_init() {

	std::string vshader = shader_path + "vshader_Prince.glsl";
	std::string fshader = shader_path + "fshader_Prince.glsl";

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

	current_draw = 0;

}

void Mesh::mesh_draw(int width, int height) {


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
}
