#ifndef VISION_RENDERER_H
#define VISION_RENDERER_H

#include "vis_pch.hpp"

struct Shader
{
	GLuint program_id;
	std::unordered_map<const char *, GLuint> uniforms;

	void create(const std::string & shader_name);

	void checkErrors(int shader, int type);

	void bind();
	void unbind();

	inline GLuint getUniformLocation(const char * name);

	bool setFloat(const char * name, float value);

	bool setInt(const char * name, int value);

	bool setMat4(const char * name, glm::mat4 & value);
	bool setVec3(const char * name, glm::vec3 & value);
};

struct Mesh
{
	GLuint vao;
	GLuint vertices;

	void init();
};

struct Texture
{
	GLuint texture_id;

	void init(const char * name);
	void bind();
};

void initFonts();

void initRenderer();

void drawQuad(glm::vec2 position, float rotation, glm::vec2 size, glm::vec3 color);

void drawQuad(const char * texture, glm::vec2 position, float rotation, glm::vec2 size, glm::vec3 color);

void drawText(const char * text, glm::vec2 position, glm::vec2 size, glm::vec3 color);

#endif
