#pragma once

#include "../CommonInclude/CommonRender.hpp"
#include <string>
#include "glm/glm.hpp"

class Sprite
{
public:
	Sprite(const char* _fileName, float _pixelsPerUnit);
	~Sprite();

public:
	inline GLuint getTexID() const { return texId; }
	inline glm::vec2 getSize() const { return glm::vec2(width, height); }

public:
	float pixelsPerUnit;

private:
	GLuint texId;
	std::string fileName;
	int width, height;
};