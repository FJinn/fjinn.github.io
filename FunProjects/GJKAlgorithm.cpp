#include "GJK.h"

bool OriginInSimplex(Vector(&simplex)[3], Vector &direction) 
{	
	Vector A = simplex[0];
	Vector B = simplex[1];
	Vector C = simplex[2];

	Vector AB = B - A;
	Vector BC = C - B;
	Vector CA = A - C;

	Vector AO = Vector(0, 0, 0) - A;
	Vector BO = Vector(0, 0, 0) - B;
	Vector CO = Vector(0, 0, 0) - C;

	// get perpendicular toward origin
	Vector AB_Perp_O = (AB.cross(AO)).cross(AB);
	Vector BC_Perp_O = (BC.cross(BO)).cross(BC);
	Vector CA_Perp_O = (CA.cross(CO)).cross(CA);

	// check if it is more than 0 => origin is inside the region
	// if not, means no collision
	if (C.dot(AB_Perp_O) < 0)
	{
		goto RemoveFurthest;

		return false;
	}

	if (A.dot(BC_Perp_O) < 0)
	{
		goto RemoveFurthest;

		return false;
	}

	if (B.dot(CA_Perp_O) < 0)
	{
		goto RemoveFurthest;

		return false;
	}

	return true;

RemoveFurthest:
	float furthest = simplex[2].squaredLength();

	for (int i=0; i<3; ++i)
	{
		float distance = simplex[i].squaredLength();

		if (distance > furthest)
		{
			furthest = distance;

			Vector temp = simplex[i];
			simplex[i] = simplex[2];
			simplex[2] = temp;
		}
	}
	// remove/reset/ignore simplex[2], then search direction based on the line
	Vector line01 = simplex[1] - simplex[0];
	Vector refPoint = Vector(0,0,0) - simplex[0];
	direction = (line01.cross(refPoint)).cross(line01);

	return false;
}

bool GJK_CollisionCheck(Collider a, Collider b)
{
	Vector direction = Vector(1.0, 0.0, 0.0);
	Vector pointA = a.Support(direction) - b.Support(direction * -1);

	Vector simplex[3];
	simplex[0] = pointA;

	direction = Vector(0, 0, 0) - pointA;

	Vector pointB = a.Support(direction) - b.Support(direction * -1);
	Vector AO = Vector(0, 0, 0) - pointA;

	Vector AB = pointB - pointA;
	Vector pointC;

	if (AO.dot(pointB) > 0) // test if point B is beyond Origin as seen from point A
	{
		simplex[1] = pointB;

	}
	else
	{
		return false;
	}

	// toward origin from AB
	direction = (AB.cross(AO)).cross(AB);

LoopForSimplex:

	pointC = a.Support(direction) - b.Support(direction * -1);

	if (simplex[2].mVal[0] == pointC.mVal[0] && simplex[2].mVal[1] == pointC.mVal[1])
	{
		return false;
	}
	else
	{
		simplex[2] = pointC;

		if (direction.dot(pointC) < 0) // test if point C is beyond Origin as seen from line AB
		{
			return false;
		}

		if (OriginInSimplex(simplex, direction))
		{
			return true;
		}
		else
		{
			goto LoopForSimplex;
		}
	}
}



