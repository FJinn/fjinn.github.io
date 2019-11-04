#include "Sprite.h"

Sprite::Sprite()
{
	m_width = 100;
	m_height = 100;
	// collider 
	m_scale = 1.0f;
}

Sprite::Sprite(const std::string& file)
{
	m_width = 100;
	m_height = 100;
	// collider 
	m_scale = 1.0f;

	glGenTextures(1, &m_textureID);

	const char* path = file.c_str();

	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

Sprite::~Sprite()
{

}

void Sprite::Draw(float x, float y)
{
	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// blend
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
	//glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend

	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - m_width * 0.5f, y - m_height * 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + m_width * 0.5f, y - m_height * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x - m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - m_width * 0.5f, y - m_height * 0.5f);


	glEnd();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
}

void Sprite::Draw(Vector position)
{
	static float x = position.mVal[0];
	static float y = position.mVal[1];

	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// blend
	glEnable(GL_BLEND);

	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - m_width * 0.5f, y - m_height * 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + m_width * 0.5f, y - m_height * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x - m_width * 0.5f, y + m_height * 0.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - m_width * 0.5f, y - m_height * 0.5f);


	glEnd();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
}

void Sprite::Draw(float &x, float &y, float rotation, float scale, const Color& color, enumBlend blendMode)
{
	float tempWidth = m_width * scale;
	float tempHeight = m_height * scale;

	m_scale = scale;

	// vertextPoint from left bottom in clockwise order
	Vector vertexPoint1, vertexPoint2, vertexPoint3, vertexPoint4;
	vertexPoint1.set(x - tempWidth * 0.5f, y - tempHeight * 0.5f, 0.0f);
	vertexPoint2.set(x - tempWidth * 0.5f, y + tempHeight * 0.5f, 0.0f);
	vertexPoint3.set(x + tempWidth * 0.5f, y + tempHeight * 0.5f, 0.0f);
	vertexPoint4.set(x + tempWidth * 0.5f, y - tempHeight * 0.5f, 0.0f);

	// column matrix
	// insert all vertexPoint into matrix
	Matrix tempMatrix;
	tempMatrix.mVal[0][0] = vertexPoint1.mVal[0];
	tempMatrix.mVal[0][1] = vertexPoint2.mVal[0];
	tempMatrix.mVal[0][2] = vertexPoint3.mVal[0];
	tempMatrix.mVal[0][3] = vertexPoint4.mVal[0];

	tempMatrix.mVal[1][0] = vertexPoint1.mVal[1];
	tempMatrix.mVal[1][1] = vertexPoint2.mVal[1];
	tempMatrix.mVal[1][2] = vertexPoint3.mVal[1];
	tempMatrix.mVal[1][3] = vertexPoint4.mVal[1];

	tempMatrix.mVal[2][0] = 0.0f;
	tempMatrix.mVal[2][1] = 0.0f;
	tempMatrix.mVal[2][2] = 0.0f;
	tempMatrix.mVal[2][3] = 0.0f;

	tempMatrix.mVal[3][0] = 1.0f;
	tempMatrix.mVal[3][1] = 1.0f;
	tempMatrix.mVal[3][2] = 1.0f;
	tempMatrix.mVal[3][3] = 1.0f;

	// translate vertexPoints to origin point to do rotation around origin point
	Matrix translateMatrixToOrigin;
	translateMatrixToOrigin = translateMatrixToOrigin.makeTranslationMatrix(-x, -y, 0.0f);
	// make translation matrix code provided is row matrix base, so need to transpose it to column matrix
	translateMatrixToOrigin = translateMatrixToOrigin.transpose();

	// translate vertexPoints back to its own position
	Matrix translateMatrixToOwnPosition;
	translateMatrixToOwnPosition = translateMatrixToOwnPosition.makeTranslationMatrix(x, y, 0.0f);
	// make translation matrix code provided is row matrix base, so need to transpose it to column matrix
	translateMatrixToOwnPosition = translateMatrixToOwnPosition.transpose();

	// create a rotation matrix
	Matrix rotateMatrix;
	rotateMatrix = rotateMatrix.makeRotateMatrix(rotation, Vector(0.0f, 0.0f, 1.0f));

/*	
	// set the matrix to origin before rotation
	tempMatrix.mVal[0][0] = vertexPoint1.mVal[0] - x;
	tempMatrix.mVal[0][1] = vertexPoint2.mVal[0] - x;
	tempMatrix.mVal[0][2] = vertexPoint3.mVal[0] - x;
	tempMatrix.mVal[0][3] = vertexPoint4.mVal[0] - x;

	tempMatrix.mVal[1][0] = vertexPoint1.mVal[1] - y;
	tempMatrix.mVal[1][1] = vertexPoint2.mVal[1] - y;
	tempMatrix.mVal[1][2] = vertexPoint3.mVal[1] - y;
	tempMatrix.mVal[1][3] = vertexPoint4.mVal[1] - y;
*/
	// rotate vertexPoint matrix at origin and translate back to its own position
	tempMatrix = tempMatrix * translateMatrixToOrigin * rotateMatrix * translateMatrixToOwnPosition;
/*
	// set the matrix back to its original position after rotation
	tempMatrix.mVal[0][0] += x;
	tempMatrix.mVal[0][1] += x;
	tempMatrix.mVal[0][2] += x;
	tempMatrix.mVal[0][3] += x;

	tempMatrix.mVal[1][0] += y;
	tempMatrix.mVal[1][1] += y;
	tempMatrix.mVal[1][2] += y;
	tempMatrix.mVal[1][3] += y;
*/
	Matrix resultMatrix = tempMatrix;

	// set vertexPoint to new value
	vertexPoint1.mVal[0] = resultMatrix.mVal[0][0];
	vertexPoint2.mVal[0] = resultMatrix.mVal[0][1];
	vertexPoint3.mVal[0] = resultMatrix.mVal[0][2];
	vertexPoint4.mVal[0] = resultMatrix.mVal[0][3];

	vertexPoint1.mVal[1] = resultMatrix.mVal[1][0];
	vertexPoint2.mVal[1] = resultMatrix.mVal[1][1];
	vertexPoint3.mVal[1] = resultMatrix.mVal[1][2];
	vertexPoint4.mVal[1] = resultMatrix.mVal[1][3];

	// for box collider
	m_positionMatrix = resultMatrix;

#pragma region Draw Region

	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glBegin(GL_TRIANGLES);

	// set color of the sprite
	glColor4f(color.r, color.g, color.b, color.a);

	// vertextPoint from left bottom in clockwise order
	glTexCoord2f(0.0f, 0.0f); glVertex2f(vertexPoint1.mVal[0], vertexPoint1.mVal[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(vertexPoint2.mVal[0], vertexPoint2.mVal[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(vertexPoint3.mVal[0], vertexPoint3.mVal[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(vertexPoint3.mVal[0], vertexPoint3.mVal[1]);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(vertexPoint4.mVal[0], vertexPoint4.mVal[1]);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(vertexPoint1.mVal[0], vertexPoint1.mVal[1]);

// previous triangle draw code
/*
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - tempWidth * 0.5f, y - tempHeight * 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + tempWidth * 0.5f, y - tempHeight * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + tempWidth * 0.5f, y + tempHeight * 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + tempWidth * 0.5f, y + tempHeight * 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x - tempWidth * 0.5f, y + tempHeight * 0.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x - tempWidth * 0.5f, y - tempHeight * 0.5f);
*/
	glEnd();

	glDisable(GL_TEXTURE_2D);

#pragma endregion

}

unsigned int Sprite::GetWidth()
{
	return m_width * m_scale;
}

unsigned int Sprite::GetHeight()
{
	return m_height * m_scale;
}

Matrix Sprite::GetPositionMatrix()
{
	return m_positionMatrix;
}


