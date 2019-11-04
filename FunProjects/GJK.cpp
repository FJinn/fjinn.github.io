#include "GJK.h"

bool GJKTest(Collider a, Collider b)
{
	
	Vector startDirection = Vector(1.0, 0.0, 0.0);
	Vector pointA = a.Support(startDirection) - b.Support(startDirection * -1);

	std::stack<Vector> simplex;
	simplex.push(pointA);

	Vector d_AO = Vector(0, 0, 0) - pointA;

	bool intersection = false;

	Vector pointB = a.Support(d_AO) - b.Support(d_AO * -1);
	Vector AO = Vector(0, 0, 0) - pointA;

	Vector AB = pointB - pointA;
	Vector pointC;

	if (AO.dot(pointB) > 0) // test if point B is beyond Origin as seen from point A
	{
		simplex.push(pointB);

		// toward origin from AB
		Vector newDirection = (AB.cross(AO)).cross(AB);

		pointC = a.Support(newDirection) - b.Support(newDirection * -1);

		simplex.push(pointC);
		//std::cout << "A: " << pointA.mVal[0] << ", " << pointA.mVal[1] << " B: " << pointB.mVal[0] << ", " << pointB.mVal[1] << " C: " << pointC.mVal[0] << ", " << pointC.mVal[1] << std::endl;
	}
	else
	{
		intersection = false;

		return intersection;
	}
	
	// get perpendicular toward origin
	Vector AB_Perp_O = (AB.cross(AO)).cross(AB);
	// check if it is more than 0 => origin is inside the region
	// if not, means no collision
	if (pointC.dot(AB_Perp_O) < 0)
	{
		intersection = false;

		return intersection;
	}

	Vector BC = pointC - pointB;
	Vector BO = Vector(0, 0, 0) - pointB;
	Vector BC_Perp_O = (BC.cross(BO)).cross(BC);
	if (pointA.dot(BC_Perp_O) < 0)
	{
		intersection = false;

		return intersection;
	}

	Vector CA = pointA - pointC;
	Vector CO = Vector(0, 0, 0) - pointC;
	Vector CA_Perp_O = (CA.cross(CO)).cross(CA);
	if (pointB.dot(CA_Perp_O) < 0)
	{
		intersection = false;

		return intersection;
	}

	intersection = true;

	return intersection;


}

//problem
bool DoSimplex(Vector (&simplex)[3], Vector &direction, int &index)
{
	if (index < 2)
	{
		// A = new added point, B = previous point
		// AB = B - A
		Vector AB = simplex[index] - simplex[index - 1];
		// AO = O -A
		Vector AO = Vector(0, 0, 0) - simplex[index];

		// AB closer to origin
		if (AB.dot(direction) > 0)
		{
			// simplex [B , A] = no change
			// direction ab toward origin
			direction = (AB.cross(AO)).cross(AB);

			return false;
		}
		// A closer to origin
		else
		{
			// remove simplex B and A become B
			--index;
			simplex[index] = simplex[index + 1];

			direction = AO;

			return false;
		}
	}
	else if (index == 2)
	{
		// simplex [C, B, A] : A is always new point, C used to be B and B used to be A
		Vector A = simplex[2];
		Vector B = simplex[1];
		Vector C = simplex[0];

		Vector AB = B - A;
		Vector AC = C - A;

		Vector ABC = AB.cross(AC);
		Vector AO = Vector(0, 0, 0) - A;

		if ((ABC.cross(AC)).dot(AO) > 0)
		{
			if (AC.dot(AO) > 0)
			{
				// simplex [C, A], direction = ac x ao x ac
				--index;
				simplex[index] = A;

				direction = (AC.cross(AO)).cross(AC);

				return false;
			}
			else
			{
				if (AB.dot(AO) > 0)
				{
					// simplex [B, A]
					index = 0;
					simplex[index] = B;
					++index;
					simplex[index] = A;

					direction = (AB.cross(AO)).cross(AB);

					return false;
				}
				else
				{
					// simplex [A]
					index = 0;
					simplex[0] = A;

					direction = AO;

					return false;
				}
			}
		}
		else
		{
			if (AB.cross(ABC).dot(AO) > 0)
			{
				if (AB.dot(AO) > 0)
				{
					// simplex [B, A]
					index = 0;
					simplex[index] = B;
					++index;
					simplex[index] = A;

					direction = (AB.cross(AO)).cross(AB);

					return false;
				}
				else
				{
					// simplex [A]
					index = 0;
					simplex[0] = A;

					direction = AO;

					return false;
				}
			}
			else
			{
				if (ABC.dot(AO) > 0)
				{
					// simplex no change
					direction = ABC;
				}
				else
				{
					// simplex [B, C, A]
					simplex[0] = B;
					simplex[1] = C;
					simplex[2] = A;

					direction = Vector(0, 0, 0) - ABC;
				}
			}
		}

	}

	// check if origin inside simplex
	// get perpendicular toward origin
	// simplex[C, B, A]
	Vector A = simplex[0];
	Vector B = simplex[1];
	Vector C = simplex[2];
	Vector AB = B - A;
	Vector BC = C - B;
	Vector CA = A - C;
	Vector AO = Vector(0, 0, 0) - A;
	Vector BO = Vector(0, 0, 0) - B;
	Vector CO = Vector(0, 0, 0) - C;

	Vector AB_Perp_O = (AB.cross(AO)).cross(AB);
	// check if it is more than 0 => origin is inside the region
	// if not, means no collision
	if (C.dot(AB_Perp_O) < 0)
	{
		return false;
	}

	Vector BC_Perp_O = (BC.cross(BO)).cross(BC);
	if (A.dot(BC_Perp_O) < 0)
	{
		return false;
	}

	Vector CA_Perp_O = (CA.cross(CO)).cross(CA);
	if (B.dot(CA_Perp_O) < 0)
	{
		return false;
	}

	return true;
}
//problem
bool GJK_CM(Collider a, Collider b)
{
	Vector simplex[3];

	int index = 0;

	Vector direction = Vector(1.0, 0.0, 0.0);
	Vector first = a.Support(direction) - b.Support(direction);

	simplex[index] = first;

	direction = Vector(0.0, 0.0, 0.0) - first;

	while (true)
	{
		Vector pointA = a.Support(direction) - b.Support(direction);

		// no intersection
		if (pointA.dot(direction) < 0)
		{
			return false;
		}

		++index;
		simplex[index] = pointA;

		if (DoSimplex(simplex, direction, index)) // true = intersection
		{
			return true;
		}
	}
}

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

bool GJK_Updated(Collider a, Collider b)
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



