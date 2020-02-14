#ifndef EMITTERSHAPE_H
#define EMITTERSHAPE_H

#include "vector.h"
#include "matrix.h"
#include <vector>

enum EmitterShapeName
{
	// default
	POINT_SHAPE,
	RECTANGLE_SHAPE,
	CIRCLE_SHAPE
};

class EmitterShape
{
protected:
	EmitterShapeName m_emitterShapeName = POINT_SHAPE;

	Vector m_spawnPosition;

	// for checking boundaries
	// generally starts from bottom left and in clockwise order
	std::vector<Vector> m_vertexPoints;

	// size of shape
	float m_size;

public:
	EmitterShape();
	~EmitterShape();

	void SetEmitterShapeName(EmitterShapeName shapeName);
	EmitterShapeName GetEmitterShapeName();

	// randomize a position within emitter shape boundary
	virtual Vector GetParticleEmissionPos(Vector* particleSystemPos) = 0;
};

class PointShape : public EmitterShape
{
public:
	PointShape();
	~PointShape();

	Vector GetParticleEmissionPos(Vector* particleSystemPos);
};

class RectangleShape : public EmitterShape
{
private:
	// width and height of the rectangle box
	float m_width, m_height;

public:
	RectangleShape(float size);
	~RectangleShape();

	void SetRectangleWidth(float width);
	float GetRectangleWidth();
	void SetRectangleHeight(float height);
	float GetRectangleHeight();

	Vector GetParticleEmissionPos(Vector* particleSystemPos);
};

class CircleShape : public EmitterShape
{
private:
	float m_radius;
public:
	CircleShape(float size);
	~CircleShape();

	void SetRadius(float radius);
	float GetRadius();

	Vector GetParticleEmissionPos(Vector* particleSystemPos);
};

#endif