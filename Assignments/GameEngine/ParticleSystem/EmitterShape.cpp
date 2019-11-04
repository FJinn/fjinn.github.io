#include "EmitterShape.h"

EmitterShape::EmitterShape()
{
	// clear all vertex points of boundaries
	m_vertexPoints.clear();
}

EmitterShape::~EmitterShape()
{
}

void EmitterShape::SetEmitterShapeName(EmitterShapeName shapeName)
{
	m_emitterShapeName = shapeName;
}

EmitterShapeName EmitterShape::GetEmitterShapeName()
{
	return m_emitterShapeName;
}

Vector EmitterShape::GetParticleEmissionPos(Vector * particleSystemPos)
{
	return Vector();
}

//==============================================================================================
// point
PointShape::PointShape() : EmitterShape()
{
	// clear all vertex points of boundaries
	m_vertexPoints.clear();
}

PointShape::~PointShape()
{
}

Vector PointShape::GetParticleEmissionPos(Vector * particleSystemPos)
{
	m_spawnPosition = *particleSystemPos;
	return m_spawnPosition;
}

//==============================================================================================
// rectangle

RectangleShape::RectangleShape(float size) : EmitterShape()
{
	m_size = size;

	// default rectangle width and height
	m_width = m_size;
	m_height = m_size;

	SetEmitterShapeName(RECTANGLE_SHAPE);
}

RectangleShape::~RectangleShape()
{
}

void RectangleShape::SetRectangleWidth(float width)
{
	m_width = width;
}

float RectangleShape::GetRectangleWidth()
{
	return m_width;
}

void RectangleShape::SetRectangleHeight(float height)
{
	m_height = height;
}

float RectangleShape::GetRectangleHeight()
{
	return m_height;
}

Vector RectangleShape::GetParticleEmissionPos(Vector * particleSystemPos)
{
	Vector resultVector = Vector(0.0f, 0.0f, 0.0f);

	//std::vector<Vector> temp;

	float x = particleSystemPos->mVal[0];
	float y = particleSystemPos->mVal[1];

	// vertextPoint from left bottom in clockwise order
	Vector vertexPoint1, vertexPoint2, vertexPoint3, vertexPoint4;
	vertexPoint1.set(x - m_width * 0.5f, y - m_height * 0.5f, 0.0f);
	vertexPoint2.set(x - m_width * 0.5f, y + m_height * 0.5f, 0.0f);
	vertexPoint3.set(x + m_width * 0.5f, y + m_height * 0.5f, 0.0f);
	vertexPoint4.set(x + m_width * 0.5f, y - m_height * 0.5f, 0.0f);

	static float xMin = vertexPoint1.mVal[0];
	static float xMax = vertexPoint3.mVal[0];
	static float yMin = vertexPoint1.mVal[1];
	static float yMax = vertexPoint2.mVal[1];

	/*
	temp.push_back(vertexPoint1);
	temp.push_back(vertexPoint2);
	temp.push_back(vertexPoint3);
	temp.push_back(vertexPoint4);

	// boundaries position
	static float xMin = 9999;
	static float xMax = -9999;
	static float yMin = 9999;
	static float yMax = -9999;

	for (int i = 0; i < temp.size(); i++)
	{
		// set min and max of boundaries
		if (temp[i].mVal[0] < xMin)
		{
			xMin = temp[i].mVal[0];
		}
		if (temp[i].mVal[0] > xMax)
		{
			xMax = temp[i].mVal[0];
		}
		if (temp[i].mVal[1] < yMin)
		{
			yMin = temp[i].mVal[1];
		}
		if (temp[i].mVal[1] > yMax)
		{
			yMax = temp[i].mVal[1];
		}
	}
*/
	// randomize a position based on boundaries
	resultVector.mVal[0] = rand() % ((int)xMax - (int)xMin + 1) + (int)xMin;
	resultVector.mVal[1] = rand() % ((int)yMax - (int)yMin + 1) + (int)yMin;

	m_spawnPosition = resultVector;

	return m_spawnPosition;
}

//==============================================================================================
// circle
CircleShape::CircleShape(float size) : EmitterShape()
{
	m_size = size;

	m_radius = m_size;

	SetEmitterShapeName(CIRCLE_SHAPE);
}

CircleShape::~CircleShape()
{
}

void CircleShape::SetRadius(float radius)
{
	m_radius = radius;
}

float CircleShape::GetRadius()
{
	return m_radius;
}

Vector CircleShape::GetParticleEmissionPos(Vector * particleSystemPos)
{
	Vector resultVector = Vector(0.0f, 0.0f, 0.0f);

	float radius = m_size;

	// start with a point
	resultVector = *particleSystemPos;
	// randomize a degree
	float degree = rand() % 360;
	// randomize a displacement
	float displacement = rand() % (int)radius;
	// calculate the position
	resultVector.mVal[0] += displacement * cos(degree);
	resultVector.mVal[1] += displacement * sin(degree);

/*
	// rectangle boundaries position
	static float xMin = particleSystemPos->mVal[0] - m_size;
	static float xMax = particleSystemPos->mVal[0] + m_size;
	static float yMin = particleSystemPos->mVal[1] - m_size;
	static float yMax = particleSystemPos->mVal[1] + m_size;

	// for caching randomize position length
	float magnitude = 0;
	// circle radius
	float radius = m_size;

	
	do
	{
		// randomize a position based on boundaries
		resultVector.mVal[0] = (rand() % (2 * (int)xMax + 1)) - (int)xMin;
		resultVector.mVal[1] = (rand() % (2 * (int)yMax + 1)) - (int)yMin;

		Vector centerToPoint = resultVector - *particleSystemPos;

		// magnitude of the centerToPoint vector 
		magnitude = centerToPoint.length();

		// if bigger than size/radius, randomize position again
	} while (magnitude > radius);
*/

	m_spawnPosition = resultVector;

	return m_spawnPosition;
}
