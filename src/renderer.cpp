#include "vis_pch.hpp"
#include "renderer.hpp"
#include "font.hpp"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Shader * shader_2d;
Mesh * quad;
BMFont * font_config;

std::unordered_map<const char *, Texture *> texture_cache;


void Shader::create(const std::string & shader_name)

{
	// Read the file

	std::ifstream file;
	std::string line, f_source, v_source;
	std::stringstream ss;

	int type = 0;

	file.open(shader_name);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line == "(vertex)")
			{
				type = 0;
				printf("Reading vertex shader \n");
				continue;
			}
			else if (line == "(fragment)")
			{
				type = 1;
				printf("Reading fragment shader \n");
				continue;
			}

			switch (type)
			{
			case 0:
				v_source.append(line);
				v_source.append("\n");
				break;
			case 1:
				f_source.append(line);
				f_source.append("\n");
				break;
			default:
				break;
			}
		}
	}

	// printf("Vertex Shader \n%s\n", v_source.c_str());
	// printf("Fragment Shader \n%s\n", f_source.c_str());

	// Compile the shader
	const char * vSource = v_source.c_str();
	const char * fSource = f_source.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSource, NULL);
	glCompileShader(vertexShader);
	checkErrors(vertexShader, GL_VERTEX_SHADER);

	// Check compile errors
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSource, NULL);
	glCompileShader(fragmentShader);
	checkErrors(fragmentShader, GL_FRAGMENT_SHADER);

	// Shader Program
	program_id = glCreateProgram();
	glAttachShader(program_id, vertexShader);
	glAttachShader(program_id, fragmentShader);
	glLinkProgram(program_id);
	checkErrors(program_id, GL_SHADER);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkErrors(int shader, int type)

{
	GLint status;
	if (type != GL_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			char info_log[512];
			glGetShaderInfoLog(shader, 512, NULL, info_log);

			printf("Error : type %d Shader %s\n", type, info_log);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &status);

		if (!status)
		{
			char info_log[512];
			glGetProgramInfoLog(shader, 512, NULL, info_log);

			printf("Error : Shader %s\n", info_log);
		}
	}

}

void Shader::bind()
{
	glUseProgram(program_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

inline GLuint Shader::getUniformLocation(const char * name)

{
	auto & q = uniforms.find(name);
	if (q != uniforms.end())
	{
		return q->second;
	}
	else {
		GLuint index = glGetUniformLocation(program_id, name);
		if (index == -1)
			return -1;

		uniforms.insert({ name, index });
		return index;
	}
}

bool Shader::setFloat(const char * name, float value)

{
	GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform1f(location, value);

	return true;
}

bool Shader::setInt(const char * name, int value)

{
	GLint location = getUniformLocation(name);
	if (location == -1)
	{
		return false;
	}

	glUniform1i(location, value);

	return true;
}
bool Shader::setMat4(const char * name, glm::mat4 & value)

{
	GLint location = getUniformLocation(name);

	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);

	return true;
}

bool Shader::setVec3(const char * name, glm::vec3 & value)
{
	GLint location = getUniformLocation(name);

	if (location == -1)
	{
		return false;
	}

	glUniform3fv(location, 1, &value[0]);

	return true;
}

void Texture::init(const char * name)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;

	// stbi_set_flip_vertically_on_load(true);

	unsigned char * data = stbi_load(name, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLint in_format = GL_RGB;
		GLint i_format = GL_RGB;

		if (nrChannels == 4) { in_format = GL_RGBA; i_format = GL_RGBA; }
	

		glTexImage2D(GL_TEXTURE_2D, 0, in_format, width, height, 0, in_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Error : Failed to load %s texture !", name);
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Add to cache
	if (texture_cache.find(name) == texture_cache.end())
	{
		texture_cache.insert({name, this });
	}

	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << __FILE__ << " (" << __LINE__ << ")" << std::endl;
	}

}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Mesh::init()
{
	GLfloat verts[] = {
		-1.0f, 1.0f, 1.0f, // Top left
		1.0f, 1.0f, 1.0f, // Top right
		1.0f, -1.0f, 1.0f, // Bottom right
		-1.0f, -1.0f, 1.0f, // Bottom left
	};

	vertices = 6;

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat tex_coords[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	GLuint vbo, tbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << __FILE__ << " (" << __LINE__ << ")" << std::endl;
	}
}

void initRenderer()
{
	shader_2d = new Shader();
	shader_2d->create("res/shader.glsl");

	glm::mat4 p_mat = glm::ortho(0.0f, 680.0f, 720.0f, 0.0f, -1.0f, 10.0f);
	shader_2d->bind();
	shader_2d->setMat4("p_mat", p_mat);

	quad = new Mesh();
	quad->init();

	// Load Textures
	Texture * logo = new Texture();
	logo->init("res/logo.png");

	Texture * container = new Texture();
	container->init("res/consolas.png");

	Texture * vision = new Texture();
	vision->init("res/vision.png");

	initFonts();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initFonts()
{
	font_config = new BMFont();

	font_config->cols = 8;
	font_config->rows = 8;
	font_config->width = 8;
	font_config->height = 8;
	font_config->start_index = 65;
	font_config->texture_name = "res/consolas.png";
}

void drawQuad(glm::vec2 position, float rotation, glm::vec2 size, glm::vec3 color)
{
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));
		// Rotation
		model = glm::translate(model, glm::vec3(size.x / 2, size.y / 2, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-(size.x / 2), -(size.y / 2), 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		shader_2d->bind();
		shader_2d->setMat4("m_mat", model);
		shader_2d->setVec3("vert_color", color);
		shader_2d->setInt("is_textured", 0);
	}

	glBindVertexArray(quad->vao);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, quad->vertices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawQuad(const char * texture, glm::vec2 position, float rotation, glm::vec2 size, glm::vec3 color)
{
	auto t = texture_cache[texture];

	// assert(t != nullptr, "Texture not found");

	t->bind();

	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));
		// Rotation
		model = glm::translate(model, glm::vec3(size.x / 2, size.y / 2, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-(size.x / 2), -(size.y / 2), 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		shader_2d->bind();
		shader_2d->setMat4("m_mat", model);
		shader_2d->setVec3("vert_color", color);
		shader_2d->setInt("is_textured", 1);


	}


	glBindVertexArray(quad->vao);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, quad->vertices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawQuad(const char * texture, int index, glm::vec2 position, float rotation, glm::vec2 size, glm::vec2 color)
{

}

void drawText(const char * text, glm::vec2 position, glm::vec2 size, glm::vec3 color)
{
	auto t = texture_cache["res/consolas.png"];
	for (size_t i = 0; i < strlen(text); i++)
	{
		if (text[i] == ' ')
		{
			position.x += size.x;
			continue;
		}
		int t_pos = text[i] - 65;

		int col = t_pos % font_config->cols;
		int row = t_pos / font_config->rows;

		float tx_offset = (float)col / (float)font_config->cols;
		float ty_offset = (float)row / (float)font_config->rows;


		// assert(t != nullptr, "Texture not found");

		t->bind();

		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(position, 0.0f));
			model = glm::scale(model, glm::vec3(size, 1.0f));

			position.x += size.x;

			shader_2d->bind();
			shader_2d->setMat4("m_mat", model);
			shader_2d->setFloat("tx_offset", tx_offset);
			shader_2d->setFloat("ty_offset", ty_offset);
			shader_2d->setInt("numCols", font_config->cols);
			shader_2d->setInt("numRows", font_config->rows);
			shader_2d->setInt("is_textured", 1);
			shader_2d->setVec3("vert_color", color);



		}


		glBindVertexArray(quad->vao);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, quad->vertices, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}