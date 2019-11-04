#ifndef BOIDS_H
#define BOIDS_H

#include "vector.h"
#include "Bitmap.h"
#include <time.h>

double mouseXPos;
double mouseYPos;

// triangle max velocity
int maxVelocity = 3.0;
// radius size for all object
int radiusSize = 100;
int radiusFix = 40;

bool bMouseHold;
// int to control object moving
// 0 = nothing, 1 = attractor, 2 = obstacle, 3 = repeller
int movingCondition = 0;

// total boids
const int totalBoids = 80;
const int totalObstacle = 3;

//  half triangle size
int triangleSize = 5;

//=============================================================================================================
int maxSteering = 1;
int maxAvoid = 1;
int maxRepel = 10;
//=============================================================================================================

//=============================================================================================================

// pre declaration
void Display(GLFWwindow* window);

// attractor
class Attractor
{
public:
	Vector myPosition, myVelocity;
	int xMin, xMax, yMin, yMax, myRadius;

	Attractor(GLFWwindow* window)
	{
		int widthTemp, heightTemp;
		glfwGetFramebufferSize(window, &widthTemp, &heightTemp);

		myPosition.mVal[0] = widthTemp / 2.0;
		myPosition.mVal[1] = heightTemp / 2.0 + 200;

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];


		myRadius = radiusSize;
	}

	~Attractor()
	{
	}

	void DrawAttractor()
	{
		//==========================================================================

		//glEnable(GL_TEXTURE_2D); // enable texturing
		//glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // Bind panel texture

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];

		glColor3f(0.4f, 1.0f, 0.4f);

		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(xMin, yMin);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(xMax, yMin);
		glTexCoord2f(1.0f, -1.0f); glVertex2f(myPosition.mVal[0], yMax);

		glEnd();

		//glDisable(GL_TEXTURE_2D);
	}

};

// obstacle
class Obstacle
{
public:
	Vector myPosition, myVelocity;
	int xMin, xMax, yMin, yMax, myRadius;
	// initialize initial position
	int tempX, tempY;

	Obstacle(GLFWwindow* window)
	{
		tempX = 100 * (rand() % 2 - 1);
		tempY = 100 * (rand() % 2 - 1);

		int widthTemp, heightTemp;
		glfwGetFramebufferSize(window, &widthTemp, &heightTemp);

		myPosition.mVal[0] = widthTemp / 2.0 + tempX;
		myPosition.mVal[1] = heightTemp / 2.0 + tempY;

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];


		myRadius = radiusSize;
	}

	~Obstacle()
	{
	}

	void DrawObstacle()
	{
		//==========================================================================

		//glEnable(GL_TEXTURE_2D); // enable texturing
		//glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // Bind panel texture

		glColor3f(0.7f, 0.4f, 0.7f);

		glBegin(GL_TRIANGLES);

		//	glTexCoord2f(0.0f, 0.0f); glVertex2f(xMin, yMin);
		//	glTexCoord2f(1.0f, 0.0f); glVertex2f(xMax, yMin);
		//	glTexCoord2f(1.0f, -1.0f); glVertex2f(m_position.mVal[0], yMax);

		int sides = 20;
		int centerX = myPosition.mVal[0];
		int centerY = myPosition.mVal[1];
		float radius = myRadius / 2;

		for (int i = 0; i < sides; i++)
		{
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			glVertex2f(centerX, centerY);
			glVertex2f(radius*cos(theta) + centerX, radius*sin(theta) + centerY);
			glVertex2f(radius*cos(nextTheta) + centerX, radius*sin(nextTheta) + centerY);
		}

		glEnd();

		//glDisable(GL_TEXTURE_2D);
	}

};

// repeller
class Repeller
{
public:
	Vector myPosition, myVelocity;
	int xMin, xMax, yMin, yMax, myRadius;

	Repeller(GLFWwindow* window)
	{
		int widthTemp, heightTemp;
		glfwGetFramebufferSize(window, &widthTemp, &heightTemp);

		myPosition.mVal[0] = widthTemp / 2.0 - 200;
		myPosition.mVal[1] = heightTemp / 2.0;

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];


		myRadius = radiusSize;
	}

	~Repeller()
	{
	}

	void DrawRepeller()
	{
		//==========================================================================

		//glEnable(GL_TEXTURE_2D); // enable texturing
		//glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // Bind panel texture

		glColor3f(1.0f, 0.7f, 0.4f);

		glBegin(GL_TRIANGLES);

		int sides = 20;
		int centerX = myPosition.mVal[0];
		int centerY = myPosition.mVal[1];
		float radius = myRadius / 2;

		for (int i = 0; i < sides; i++)
		{
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			glVertex2f(centerX, centerY);
			glVertex2f(radius*cos(theta) + centerX, radius*sin(theta) + centerY);
			glVertex2f(radius*cos(nextTheta) + centerX, radius*sin(nextTheta) + centerY);
		}
		glEnd();

		//glDisable(GL_TEXTURE_2D);
	}

};

class Boid
{
public:
	int myIndex;
	Vector myPosition, initialVelocity, resultVelocity;
	Vector ahead;

	Vector wanderCircleCenter;

	int xMin, xMax, yMin, yMax;

	Boid(GLFWwindow* window)
	{
		int widthTemp, heightTemp;
		glfwGetFramebufferSize(window, &widthTemp, &heightTemp);

		myPosition.mVal[0] = widthTemp / 2.0;
		myPosition.mVal[1] = heightTemp / 2.0;

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];

		// initialize initial velocity
		int tempX, tempY;
		tempX = rand() % 10;
		tempY = rand() % 10;

		initialVelocity.set(tempX, tempY, 0);
		initialVelocity.normalize();
		initialVelocity *= maxVelocity;
	}

	~Boid()
	{
	}

	void rMatrix(Matrix &mat, float angle)
	{
		float s = sin(angle * M_DEG_2_RAD);
		float c = cos(angle * M_DEG_2_RAD);
		/*
		Translate your points such that the center is the new origin:

		xt = x1 - xc;
		yt = y1 - yc;
		Rotate around the origin by the angle a :

		// x' = x cos 0 - y sin 0
		// y' = x sin 0 + y cos 0
		c = cos(a); // compute trig. functions only once
		s = sin(a);
		xr = xt * c - yt * s;
		yr = xt * s + yt * c;
		Translate points back :

		x2 = xr + xc;
		y2 = yr + yc;
*/
		float xt, yt, xc, yc, xr, yr;

		xc = myPosition.mVal[0];
		yc = myPosition.mVal[1];

		for (int i = 0; i < 3; i++)
		{
			xt = mat.mVal[i][0] - xc;
			yt = mat.mVal[i][1] - yc;

			xr = xt * c - yt * s;
			yr = xt * s + yt * c;

			mat.mVal[i][0] = xr + xc;
			mat.mVal[i][1] = yr + yc;
		}
	}

	void DrawBoid()
	{
		//==========================================================================

		if (myPosition.mVal[0] > 800)
		{
			myPosition.mVal[0] = 0;
		}
		else if (myPosition.mVal[0] < 0)
		{
			myPosition.mVal[0] = 800;
		}

		if (myPosition.mVal[1] > 600)
		{
			myPosition.mVal[1] = 0;
		}
		else if (myPosition.mVal[1] < 0)
		{
			myPosition.mVal[1] = 600;
		}

		xMin = myPosition.mVal[0] - triangleSize;
		xMax = myPosition.mVal[0] + triangleSize;
		yMin = myPosition.mVal[1] + triangleSize * 2.0;
		yMax = myPosition.mVal[1];

		Matrix triMat;
		triMat.mVal[0][0] = xMin;
		triMat.mVal[0][1] = yMin;

		triMat.mVal[1][0] = xMax;
		triMat.mVal[1][1] = yMin;

		triMat.mVal[2][0] = myPosition.mVal[0];
		triMat.mVal[2][1] = yMax;

		float theta;
		// rotate toward result velocity
		theta = atan2(resultVelocity.mVal[1], resultVelocity.mVal[0]);
		theta = theta * 180 / M_PI;
		theta += 90;

		rMatrix(triMat, theta);

		glColor3f(0.0f, 0.0f, 0.7f);

		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(triMat.mVal[0][0], triMat.mVal[0][1]);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(triMat.mVal[1][0], triMat.mVal[1][1]);
		glTexCoord2f(1.0f, -1.0f); glVertex2f(triMat.mVal[2][0], triMat.mVal[2][1]);

		glEnd();
	}

};

Vector Seek(Attractor* att, Boid* b)
{
	// target position
	Vector target(att->myPosition.mVal[0], att->myPosition.mVal[1], 0);

	Vector desiredVelocity(target.mVal[0] - b->myPosition.mVal[0], target.mVal[1] - b->myPosition.mVal[1], 0);

	float length = desiredVelocity.length();

	desiredVelocity.normalize();

	desiredVelocity *= maxVelocity;

	Vector steeringForce(desiredVelocity.mVal[0] - b->resultVelocity.mVal[0], desiredVelocity.mVal[1] - b->resultVelocity.mVal[1], 0);
	steeringForce.normalize();
	float i = maxSteering / steeringForce.length();
	i = i < 0.05 ? i : 0.05;
	steeringForce *= i;

	return steeringForce;
}

Vector AvoidObstacle(Obstacle *o, Boid* b)
{
	b->ahead.set(b->resultVelocity.mVal[0], b->resultVelocity.mVal[1], 0);
	b->ahead.normalize();
	b->ahead = b->myPosition + b->ahead;

	float distance = sqrt(pow(b->ahead.mVal[0] - o->myPosition.mVal[0], 2.0) + pow(b->ahead.mVal[1] - o->myPosition.mVal[1], 2.0));
	if (distance < o->myRadius - radiusFix)
	{
		Vector avoidForce(b->ahead.mVal[0] - o->myPosition.mVal[0], b->ahead.mVal[1] - o->myPosition.mVal[1], 0);
		avoidForce.normalize();
		avoidForce *= o->myRadius - distance;

		float i = maxAvoid / avoidForce.length();
		i = i < 0.7 ? i : 0.7;
		avoidForce *= i;

		return avoidForce;
	}
	else
	{
		return Vector(0, 0, 0);
	}
}

Vector AvoidRepeller(Repeller *rep, Boid* b)
{
	b->ahead.set(b->resultVelocity.mVal[0], b->resultVelocity.mVal[1], 0);
	b->ahead.normalize();
	b->ahead *= maxVelocity;
	b->ahead = b->myPosition + b->ahead;

	float distance = sqrt(pow(b->ahead.mVal[0] - rep->myPosition.mVal[0], 2.0) + pow(b->ahead.mVal[1] - rep->myPosition.mVal[1], 2.0));
	if (distance < rep->myRadius - radiusFix)
	{
		Vector repelForce(b->ahead.mVal[0] - rep->myPosition.mVal[0], b->ahead.mVal[1] - rep->myPosition.mVal[1], 0);

		repelForce.normalize();
		repelForce *= maxRepel;

		float i = maxRepel / repelForce.length();
		i = i < 1.0 ? i : 1.0;
		repelForce *= i;

		return repelForce;
	}
	else
	{
		return Vector(0,0,0);
	}
}

// declare triangle pointer
Boid* boid[totalBoids];
// attractor pointer
Attractor* att;
// obstacle pointer
Obstacle* obs[totalObstacle];
// repeller pointer
Repeller * rep;

void init(GLFWwindow* window)
{
	srand(time(NULL));

	for (int i = 0; i < totalBoids; i++)
	{
		boid[i] = new Boid(window);
		boid[i]->myIndex = i;
		boid[i]->resultVelocity = boid[i]->initialVelocity;
	}

	att = new Attractor(window);
	for (int j = 0; j < totalObstacle; j++)
	{
		obs[j] = new Obstacle(window);
	}
	rep = new Repeller(window);
}

void deinit()
{
	for (int i = 0; i < totalBoids; i++)
	{
		delete boid[i];
	}

	delete att;
	for (int j = 0; j < totalObstacle; j++)
	{
		delete obs[j];
	}
	delete rep;
}

// Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
Vector BoidRuleOne(Boid* b)
{
	/*	PROCEDURE rule1(boid bJ)

			Vector pcJ

			FOR EACH BOID b
			IF b != bJ THEN
			pcJ = pcJ + b.position
			END IF
			END

			pcJ = pcJ / N - 1

			//To move it 1% of the way towards the centre (this is about the factor I use) this is given by (pcJ - bJ.position) / 100.
			RETURN(pcJ - bJ.position) / 100

			END PROCEDURE
	*/
	Vector triC(0.0f, 0.0f, 0.0f);
	int neighbourCount = 0;

	for (int i = 0; i < totalBoids; i++)
	{
		if (i != b->myIndex)
		{
			Vector temp;
			temp.set(boid[i]->myPosition.mVal[0] - b->myPosition.mVal[0], boid[i]->myPosition.mVal[1] - b->myPosition.mVal[1], boid[i]->myPosition.mVal[2] - b->myPosition.mVal[2]);

			if (temp.length() > 0 && temp.length() < 50)
			{
				triC = triC + boid[i]->myPosition;
				neighbourCount++;
			}
		}
	}

	if (neighbourCount != 0)
	{
		triC = triC / (neighbourCount);
	}

	triC = (triC - b->myPosition);
	triC.normalize();

	return triC / 100;
}

// Rule 2: Boids try to keep a small distance away from other objects (including other boids).
Vector BoidRuleTwo(Boid* b)
{
	/*  PROCEDURE rule2(boid bJ)

		Vector c = 0;

		FOR EACH BOID b
			IF b != bJ THEN
				IF |b.position - bJ.position| < 100 THEN
					c = c - (b.position - bJ.position)
				END IF
			END IF
		END

		RETURN c
	*/

	Vector c(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < totalBoids; i++)
	{
		if (i != b->myIndex)
		{
			Vector temp;
			temp.set(boid[i]->myPosition.mVal[0] - b->myPosition.mVal[0], boid[i]->myPosition.mVal[1] - b->myPosition.mVal[1], boid[i]->myPosition.mVal[2] - b->myPosition.mVal[2]);

			if (temp.length() > 0 && temp.length() < 15)
			{
				c = c - temp;
			}
		}
	}

	return c;
}

// Rule 3: Boids try to match velocity with near boids.
Vector BoidRuleThree(Boid* b)
{
	/*  PROCEDURE rule3(boid bJ)

		Vector pvJ

		FOR EACH BOID b
			IF b != bJ THEN
				pvJ = pvJ + b.velocity
			END IF
		END

		pvJ = pvJ / N-1

		RETURN (pvJ - bJ.velocity) / 8

		END PROCEDURE
	*/

	Vector pvJ(0.0f, 0.0f, 0.0f);

	int neighbourCount = 0;

	for (int i = 0; i < totalBoids; i++)
	{
		if (i != b->myIndex)
		{
			Vector temp;
			temp.set(boid[i]->myPosition.mVal[0] - b->myPosition.mVal[0], boid[i]->myPosition.mVal[1] - b->myPosition.mVal[1], boid[i]->myPosition.mVal[2] - b->myPosition.mVal[2]);

			if (temp.length() > 0 && temp.length() < 50)
			{
				pvJ = pvJ + boid[i]->resultVelocity;
				neighbourCount++;
			}
		}
	}

	if (neighbourCount == 0)
	{
		return pvJ;
	}

	pvJ = pvJ / (neighbourCount);

	return pvJ / 8;
}

void Display(GLFWwindow* window)
{
	//
	//  Clear the window.
	//
	glClear(GL_COLOR_BUFFER_BIT);
	//
	//  Draw each triangle.
	//

	att->DrawAttractor();

	for (int i = 0; i < totalBoids; i++)
	{
		boid[i]->resultVelocity += BoidRuleOne(boid[i]) + BoidRuleTwo(boid[i]) + BoidRuleThree(boid[i]);
		boid[i]->resultVelocity += Seek(att, boid[i]) + AvoidRepeller(rep, boid[i]);

		for (int n=0; n<totalObstacle; n++)
		{
			boid[i]->resultVelocity += AvoidObstacle(obs[n], boid[i]);
		}

		float j = maxVelocity / boid[i]->resultVelocity.length();
		j = j < 1.0 ? j : 1.0;
		boid[i]->resultVelocity *= j;

		boid[i]->myPosition += boid[i]->resultVelocity;
		boid[i]->DrawBoid();
	}

	for (int j = 0; j < totalObstacle; j++)
	{
		obs[j]->DrawObstacle();
	}
	rep->DrawRepeller();
}

// ===============================================================================================
// ===============================================================================================
// ===============================================================================================

void Key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	int widthTemp, heightTemp;
	glfwGetFramebufferSize(window, &widthTemp, &heightTemp);

	/*
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS) && viewportOffsetY - viewportMoveSpeed > -HEIGHT + heightTemp + 1000)
	{
		viewportOffsetY -= viewportMoveSpeed;
	}
	else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS) && HEIGHT + viewportOffsetY + viewportMoveSpeed < HEIGHT + boardOffsetY)
	{
		viewportOffsetY += viewportMoveSpeed;
	}

	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS) && viewportOffsetX + viewportMoveSpeed < 100)
	{
		viewportOffsetX += viewportMoveSpeed;
	}
	else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS) && map_width*box_size - viewportOffsetX - viewportMoveSpeed < map_width*box_size)
	{
		viewportOffsetX -= viewportMoveSpeed;
	}
	*/


}

void OnMouseClick(GLFWwindow* window, int button, int mouse_state, int mods)
{
	glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

	if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_state == GLFW_PRESS)
	{
		// turn mouse hold bool on
		bMouseHold = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_state == GLFW_RELEASE)
	{
		// turn bool mouse hold off
		bMouseHold = false;
		movingCondition = 0;
	}
}

void MouseDrag(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

	static int obsNum = 0;

	if (bMouseHold)
	{
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

		// move attractor
		if (mouseXPos >= att->myPosition.mVal[0] - att->myRadius && mouseXPos <= att->myPosition.mVal[0] + att->myRadius
			&& mouseYPos >= att->myPosition.mVal[1] - att->myRadius && mouseYPos <= att->myPosition.mVal[1] + att->myRadius
			&& movingCondition == 0)
		{
			movingCondition = 1;
		}
		// move obstacle
		for (int i = 0; i < totalObstacle; i++)
		{
			if (mouseXPos >= obs[i]->myPosition.mVal[0] - obs[i]->myRadius && mouseXPos <= obs[i]->myPosition.mVal[0] + obs[i]->myRadius
				&& mouseYPos >= obs[i]->myPosition.mVal[1] - obs[i]->myRadius && mouseYPos <= obs[i]->myPosition.mVal[1] + obs[i]->myRadius
				&& movingCondition == 0)
			{
				movingCondition = 2;
				obsNum = i;
			}
		}
		// move repeller
		if (mouseXPos >= rep->myPosition.mVal[0] - rep->myRadius && mouseXPos <= rep->myPosition.mVal[0] + rep->myRadius
			&& mouseYPos >= rep->myPosition.mVal[1] - rep->myRadius && mouseYPos <= rep->myPosition.mVal[1] + rep->myRadius
			&& movingCondition == 0)
		{
			movingCondition = 3;
		}

		if (movingCondition == 1)
		{
			att->myPosition.set(mouseXPos, mouseYPos, 0);
		}
		else if (movingCondition == 2)
		{
			obs[obsNum]->myPosition.set(mouseXPos, mouseYPos, 0);
		}
		else if (movingCondition == 3)
		{
			rep->myPosition.set(mouseXPos, mouseYPos, 0);
		}
	}
}

#endif // !BOIDS_H
