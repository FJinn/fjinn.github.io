#ifndef SPRITE_H
#define SPRITE_H

#include <GLFW/glfw3.h>
#include <string>
#include "bitmap.h"
#include "matrix.h"

enum enumBlend
{
	ADDITIVE,
	MULTIPLY,
	ALPHA_BLEND,
	TEST,
	NONE
};

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

class Sprite
{
private: 
	unsigned int m_width = 0;
	unsigned int m_height = 0;
	unsigned int m_textureID;

	// box collider
	float m_scale;
	Matrix m_positionMatrix;

public:
	Sprite();
	Sprite(const std::string& file);

	~Sprite();

	void Draw(float x, float y);
	void Draw(Vector position);
	void Draw(float &x, float &y, float rotation, float scale, const Color& color, enumBlend blendMode);

	unsigned int GetWidth();
	unsigned int GetHeight();
	Matrix GetPositionMatrix();
};

#endif