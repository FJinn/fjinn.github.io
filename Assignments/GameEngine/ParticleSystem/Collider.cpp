#include "Collider.h"

BoxCollider::BoxCollider()
{
	m_positionOffset = Vector(0.0f, 0.0f, 0.0f);
	m_widthOffset = 0.0f;
	m_heightOffset = 0.0f;
}

BoxCollider::BoxCollider(Vector posOffset, float widthOffset, float heightOffset)
{
	m_positionOffset = posOffset;
	m_widthOffset = widthOffset * 0.5f;
	m_heightOffset = heightOffset * 0.5f;
}

void BoxCollider::SetWidthOffset(float widthOffset)
{
	m_widthOffset = widthOffset * 0.5f;
}

float BoxCollider::GetWidthOffset()
{
	return m_widthOffset;
}

void BoxCollider::SetHeightOffset(float heightOffset)
{
	m_heightOffset = heightOffset * 0.5f;
}

float BoxCollider::GetHeightOffset()
{
	return m_heightOffset;
}

void BoxCollider::SetPositionOffset(Vector posOffset)
{
	m_positionOffset = posOffset;
}

Vector BoxCollider::GetPositionOffset()
{
	return m_positionOffset;
}

void BoxCollider::SetVertexPositionsMatrix(Matrix vertexPositionsMatrix)
{
	m_vertexPositionsMatrix = vertexPositionsMatrix;

	// vertextPoint from left bottom in clockwise order
	m_positionMatrix.mVal[0][0] = m_vertexPositionsMatrix.mVal[0][0] + m_positionOffset.mVal[0] - m_widthOffset;
	m_positionMatrix.mVal[0][1] = m_vertexPositionsMatrix.mVal[0][1] + m_positionOffset.mVal[0] - m_widthOffset;
	m_positionMatrix.mVal[0][2] = m_vertexPositionsMatrix.mVal[0][2] + m_positionOffset.mVal[0] + m_widthOffset;
	m_positionMatrix.mVal[0][3] = m_vertexPositionsMatrix.mVal[0][3] + m_positionOffset.mVal[0] + m_widthOffset;

	m_positionMatrix.mVal[1][0] = m_vertexPositionsMatrix.mVal[1][0] + m_positionOffset.mVal[1] + m_heightOffset;
	m_positionMatrix.mVal[1][1] = m_vertexPositionsMatrix.mVal[1][1] + m_positionOffset.mVal[1] - m_heightOffset;
	m_positionMatrix.mVal[1][2] = m_vertexPositionsMatrix.mVal[1][2] + m_positionOffset.mVal[1] - m_heightOffset;
	m_positionMatrix.mVal[1][3] = m_vertexPositionsMatrix.mVal[1][3] + m_positionOffset.mVal[1] + m_heightOffset;

	m_positionMatrix.mVal[2][0] = m_vertexPositionsMatrix.mVal[2][0];
	m_positionMatrix.mVal[2][1] = m_vertexPositionsMatrix.mVal[2][1];
	m_positionMatrix.mVal[2][2] = m_vertexPositionsMatrix.mVal[2][2];
	m_positionMatrix.mVal[2][3] = m_vertexPositionsMatrix.mVal[2][3];

	m_positionMatrix.mVal[3][0] = m_vertexPositionsMatrix.mVal[3][0];
	m_positionMatrix.mVal[3][1] = m_vertexPositionsMatrix.mVal[3][1];
	m_positionMatrix.mVal[3][2] = m_vertexPositionsMatrix.mVal[3][2];
	m_positionMatrix.mVal[3][3] = m_vertexPositionsMatrix.mVal[3][3];
}

Matrix BoxCollider::GetVertexPositionsMatrix()
{
	return m_vertexPositionsMatrix;
}

bool BoxCollider::IsCollided(BoxCollider other)
{ 
	// self
	float x1Min = m_positionMatrix.mVal[0][0];
	float x1Max = m_positionMatrix.mVal[0][3];
	float y1Min = m_positionMatrix.mVal[1][0];
	float y1Max = m_positionMatrix.mVal[1][1];

	// other box collider
	float x2Min = other.m_positionMatrix.mVal[0][0];
	float x2Max = other.m_positionMatrix.mVal[0][3];
	float y2Min = other.m_positionMatrix.mVal[1][0];
	float y2Max = other.m_positionMatrix.mVal[1][1];

	// check if it is smallest/largest among all vertex points
	// for after rotation
	for (int i = 0; i < 4; i++)
	{
		if (m_positionMatrix.mVal[0][i] < x1Min)
		{
			x1Min = m_positionMatrix.mVal[0][i];
		}

		if (m_positionMatrix.mVal[0][i] > x1Max)
		{
			x1Max = m_positionMatrix.mVal[0][i];
		}

		if (m_positionMatrix.mVal[1][i] < y1Min)
		{
			y1Min = m_positionMatrix.mVal[0][i];
		}

		if (m_positionMatrix.mVal[1][i] > y1Max)
		{
			y1Max = m_positionMatrix.mVal[0][i];
		}

		// ===============================================================
		if (other.m_positionMatrix.mVal[0][i] < x2Min)
		{
			x2Min = other.m_positionMatrix.mVal[0][i];
		}

		if (other.m_positionMatrix.mVal[0][i] > x2Max)
		{
			x2Max = other.m_positionMatrix.mVal[0][i];
		}

		if (other.m_positionMatrix.mVal[1][i] < y2Min)
		{
			y2Min = other.m_positionMatrix.mVal[0][i];
		}

		if (other.m_positionMatrix.mVal[1][i] > y2Max)
		{
			y2Max = other.m_positionMatrix.mVal[0][i];
		}
	}

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max)
	{
		return false;
	}
	if (y1Max < y2Min || y1Min > y2Max)
	{
		return false;
	}

	return true;
}

void BoxCollider::Draw()
{
	glBegin(GL_LINES);

	// set color of the box collider
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	//left line
	glVertex2f(m_positionMatrix.mVal[0][0], m_positionMatrix.mVal[1][0]);
	glVertex2f(m_positionMatrix.mVal[0][1], m_positionMatrix.mVal[1][1]);
	//bottom line
	glVertex2f(m_positionMatrix.mVal[0][1], m_positionMatrix.mVal[1][1]);
	glVertex2f(m_positionMatrix.mVal[0][2], m_positionMatrix.mVal[1][2]);
	//right line
	glVertex2f(m_positionMatrix.mVal[0][2], m_positionMatrix.mVal[1][2]);
	glVertex2f(m_positionMatrix.mVal[0][3], m_positionMatrix.mVal[1][3]);
	//top line
	glVertex2f(m_positionMatrix.mVal[0][3], m_positionMatrix.mVal[1][3]);
	glVertex2f(m_positionMatrix.mVal[0][0], m_positionMatrix.mVal[1][0]);

	glEnd();

	glBegin(GL_LINE);

}
