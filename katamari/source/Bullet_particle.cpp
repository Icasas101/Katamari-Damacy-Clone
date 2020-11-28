

#include "common.h"



class Bullet_particle {
public:
	Bullet_particle() {
		//Code changes here
		double random_x = 0.5 - rand() / (float)RAND_MAX;
		double random_y = 0.5 - rand() / (float)RAND_MAX;
		double random_m = rand() % 100;
		loc = vec2(0.0, 0.0);
		color = vec3(1.0, 1.0, 1.0);
		accel = vec2(0.0, -9.8);
		vel = normalize(vec2(random_x, random_y)) * random_m;
	};
	vec2 loc;
	vec2 vel;
	vec2 accel;
	vec3 color;
};


class Particle_System {
public:

	Particle_System() {};
	~Particle_System() {
		for (unsigned int i = 0; i < particles.size(); i++)
			delete particles[i];
		particles.clear();
	}

	GLuint vao;
	GLuint program;
	GLuint buffer;
	GLuint vertex_shader, fragment_shader;
	GLint vpos_location, vcolor_location;
	GLint PM_location;

	std::vector < Bullet_particle* > particles;

	void init() {
		std::string vshader = shader_path + "vshader.glsl";
		std::string fshader = shader_path + "fshader.glsl";

		GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
		GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
		glCompileShader(vertex_shader);
		check_shader_compilation(vshader, vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
		glCompileShader(fragment_shader);
		check_shader_compilation(fshader, fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		check_program_link(program);

		glBindFragDataLocation(program, 0, "fragColor");

		vpos_location = glGetAttribLocation(program, "vPos");
		vcolor_location = glGetAttribLocation(program, "vColor");
		PM_location = glGetUniformLocation(program, "ProjectionModelview");

		// Create a vertex array object
		glGenVertexArrays(1, &vao);
		//Set GL state to use vertex array object
		glBindVertexArray(vao);

		//Generate buffer to hold our vertex data
		glGenBuffers(1, &buffer);

		glEnableVertexAttribArray(vpos_location);
		glEnableVertexAttribArray(vcolor_location);

		glBindVertexArray(0);

	};

	void update() {

		vec2* pos = new vec2[particles.size()];
		vec3* col = new vec3[particles.size()];

		for (unsigned int i = 0; i < particles.size(); i++) {
			pos[i] = particles[i]->loc;
			col[i] = particles[i]->color;
		}

		//Set GL state to use this buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		//Create GPU buffer to hold vertices and color
		glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(vec2) + particles.size() * sizeof(vec3), NULL, GL_STATIC_DRAW);
		//First part of array holds vertices
		glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * sizeof(vec2), pos);
		//Second part of array hold colors (offset by sizeof(triangle))
		glBufferSubData(GL_ARRAY_BUFFER, particles.size() * sizeof(vec2), particles.size() * sizeof(vec3), col);

		glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(particles.size() * sizeof(vec2)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		delete[] pos;
		delete[] col;

	};

	void emit() {
		particles.push_back(new Bullet_particle());
	};

	void step(float dt) {
		//Code changes here
		for (std::vector< Bullet_particle* >::iterator it = particles.begin(); it != particles.end(); ++it) {
			(*it)->vel += (*it)->accel * dt;
			(*it)->loc += (*it)->vel * dt;
			if ((*it)->loc[0] >= 5.0 || (*it)->loc[0] <= -5.0 || (*it)->loc[1] >= 5.0 || (*it)->loc[1] <= -4.0) {
				(*it)->vel = ((*it)->vel * -0.8) - 0.1;
				//(*it)->loc += (*it)->vel * dt;
			}
		}
	};
};


void animate(Particle_System* particles) {
	//Do 30 times per second
	if (glfwGetTime() > (1.0 / 60.0)) {
		particles->step((1.0 / 60.0));
		particles->emit();
		glfwSetTime(0.0);
	}
}

