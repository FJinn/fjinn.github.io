#ifndef COLLIDER_H
#define COLLIDER_H

#include "vector.h"
#include "matrix.h"
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_W = 640;
const int WINDOW_H = 480;

class BoxCollider
{
private:
	Vector m_positionOffset;
	float m_widthOffset;
	float m_heightOffset;

	Matrix m_vertexPositionsMatrix;
	Matrix m_positionMatrix;

public:
	BoxCollider();
	BoxCollider(Vector posOffset, float widthOffset, float heightOffset);

	void SetWidthOffset(float widthOffset);
	float GetWidthOffset();
	void SetHeightOffset(float heightOffset);
	float GetHeightOffset();
	void SetPositionOffset(Vector posOffset);
	Vector GetPositionOffset();
	void SetVertexPositionsMatrix(Matrix vertexPositionsMatrix);
	Matrix GetVertexPositionsMatrix();
	bool IsCollided(BoxCollider other);

	void Draw();
};

#endif
