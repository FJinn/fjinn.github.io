#ifndef CURVE_H
#define CURVE_H

#include "vector.h"
#include <math.h>

// return new point based on t
inline Vector QuadraticBezierFunction(Vector originalPoint, Vector controlPoint, Vector finalPoint, double t)
{
	Vector resultPoint;

	resultPoint.mVal[0] = pow(1 - t, 2) * originalPoint.mVal[0] + (1 - t) * 2 * t * controlPoint.mVal[0] + t * t * finalPoint.mVal[0];
	resultPoint.mVal[1] = pow(1 - t, 2) * originalPoint.mVal[1] + (1 - t) * 2 * t * controlPoint.mVal[1] + t * t * finalPoint.mVal[1];

	return resultPoint;
}

inline Vector CubicBezierFunction(Vector originalPoint, Vector controlPoint1, Vector controlPoint2, Vector finalPoint, double t)
{
	Vector resultPoint;

	resultPoint.mVal[0] = pow(1 - t, 3) * originalPoint.mVal[0] + pow(1 - t, 2) * 3 * t * controlPoint1.mVal[0] + (1 - t) * 3 * t * t * controlPoint2.mVal[0] + t * t * t * finalPoint.mVal[0];
	resultPoint.mVal[1] = pow(1 - t, 3) * originalPoint.mVal[1] + pow(1 - t, 2) * 3 * t * controlPoint1.mVal[1] + (1 - t) * 3 * t * t * controlPoint2.mVal[1] + t * t * t * finalPoint.mVal[1];

	return resultPoint;
}

inline Vector ControlPointFromPassThroughPoint(Vector originalPoint, Vector passThroughPoint, Vector finalPoint, double t)
{
	Vector controlPoint;
	controlPoint.mVal[0] = passThroughPoint.mVal[0] * 2 - (originalPoint.mVal[0] + finalPoint.mVal[0]) / 2;
	controlPoint.mVal[1] = passThroughPoint.mVal[1] * 2 - (originalPoint.mVal[1] + finalPoint.mVal[1]) / 2;

	return controlPoint;
}

// not done due to time restriction in game jam
inline Vector MultiCurve(Vector points[], double t)
{
	Vector firstControlPoint, secondControlPoint, midPoint;

	static double time = 1 / (points->length() - 1);

	static int index = 0;

	// get mid point as final point for quadratic curve function, and repeat
	if (index <= points->length() - 2)
	{
		firstControlPoint = points[index + 1];
		secondControlPoint = points[index + 2];

		midPoint.mVal[0] = (firstControlPoint.mVal[0] + secondControlPoint.mVal[0]) / 2;
		midPoint.mVal[1] = (firstControlPoint.mVal[1] + secondControlPoint.mVal[1]) / 2;
	}

	return Vector(0,0,0);
}

#endif