#ifndef POKEMON_H
#define POKEMON_H

#include <cmath>
#include "sphere.h"

float handLength = 1.2f;
float handStartingX = 1.2f;
float handStartingY = -1.0f;

float thighLength = 3.0f;
float thighStartingX = 2.0f;
float thighStartingY = -4.0f;

float footStartingY = -thighLength + thighStartingY - 0.5f;
float footStartingX = thighStartingX - 0.5f;
float footLength = 4.0f;

float earStartingX = 1.0f;
float earStartingY = 2.6f;

void body()
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 1.0f;
	float height = -4.0f;

	for (int i = 0; i < sides; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		if ( i <= sides/4)
		{
			glColor3f(1.0f, 0.35f, 1.0f);
		}
		else if (i >= sides/4 *3)
		{
			glColor3f(1.0f, 0.4f, 1.0f);
		}

		glVertex3f(radius* sin(theta) *2, height, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(theta), 0.0f, radius* cos(theta) );
		glVertex3f(radius* sin(nextTheta), 0.0f, radius* cos(nextTheta) );

		glVertex3f(radius* sin(nextTheta),0.0f, radius* cos(nextTheta) );
		glVertex3f(radius* sin(theta) * 2, height, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(nextTheta) * 2, height, radius* cos(nextTheta) * 2); // next triangle in cylinder point
	}

	glEnd();
}

void leftHand()
{
	glBegin(GL_TRIANGLES);

	circle(handStartingX, handStartingY, 0.0f, 0.4f);

	int sides = 20;
	float radius = 1/2.5f;
	float height = -4.0f;

	for (int i = 0; i < sides; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		// first body
		glVertex3f(handLength + handStartingX, radius* sin(theta)  + handStartingY, radius* cos(theta));  // next triangle in cylinder point
		glVertex3f(handStartingX, radius* sin(theta) + handStartingY, radius* cos(theta));
		glVertex3f(handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta));

		// second body
		glVertex3f(handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta));
		glVertex3f(handLength + handStartingX, radius* sin(theta) + handStartingY, radius* cos(theta)); // next triangle in cylinder point
		glVertex3f(handLength + handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta)); // next triangle in cylinder point
	}
		
	// fingers

	for (double i = -180; i <= 180; i += 1) // change increment for less edgy, if i<= 0 means half the cylinder
	{
		double a, b;
		// a/|v| = cos 0;
		// b/|v| = sin 0;
		a = cos(i* M_PI / 180);
		b = sin(i* M_PI / 180);

		// smaller hand size
		b /= 2.5;
		a /= 2.5;

		//// first circle
		//glVertex3f(0.0f, a, 0.0f);
		//glVertex3f(0.0f, 0.0f, 0.0f);
		//glVertex3f(0.0f, a, b);

		// body
		// first finger
		glVertex3f(handLength + handStartingX + 1, -0.3f + handStartingY, 0.0f); // tip // + 1 is finger length
		glVertex3f(handLength + handStartingX, -0.3f + handStartingY, 0.0f); // origin point
		glVertex3f(handLength + handStartingX, a + handStartingY, b); // from origin point

		// second finger
		glVertex3f(handLength + handStartingX + 1, handStartingY, 0.0f); // tip // + 1 is finger length
		glVertex3f(handLength + handStartingX, handStartingY, 0.0f); // origin point
		glVertex3f(handLength + handStartingX, a + handStartingY, b); // from origin point

		// third finger
		glVertex3f(handLength + handStartingX + 1, 0.3f + handStartingY, 0.0f); // tip // + 1 is finger length
		glVertex3f(handLength + handStartingX, 0.3f + handStartingY, 0.0f); // origin point
		glVertex3f(handLength + handStartingX, a + handStartingY, b); // from origin point
	}


	glEnd();
}

void rightHand()
{
	glBegin(GL_TRIANGLES);

	circle(-handStartingX, handStartingY, 0.0f, 0.4f);

	int sides = 20;
	float radius = 1 / 2.5f;
	float height = -4.0f;

	for (int i = 0; i < sides; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		// first body
		glVertex3f(-handLength - handStartingX, radius* sin(theta) + handStartingY, radius* cos(theta));  // next triangle in cylinder point
		glVertex3f(-handStartingX, radius* sin(theta) + handStartingY, radius* cos(theta));
		glVertex3f(-handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta));

		// second body
		glVertex3f(-handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta));
		glVertex3f(-handLength - handStartingX, radius* sin(theta) + handStartingY, radius* cos(theta)); // next triangle in cylinder point
		glVertex3f(-handLength - handStartingX, radius* sin(nextTheta) + handStartingY, radius* cos(nextTheta)); // next triangle in cylinder point
	}

	// fingers

	for (double i = -180; i <= 180; i += 1) // change increment for less edgy, if i<= 0 means half the cylinder
	{
		double a, b;
		// a/|v| = cos 0;
		// b/|v| = sin 0;
		a = cos(i* M_PI / 180);
		b = sin(i* M_PI / 180);

		// smaller hand size
		b /= 2.5;
		a /= 2.5;

		//// first circle
		//glVertex3f(0.0f, a, 0.0f);
		//glVertex3f(0.0f, 0.0f, 0.0f);
		//glVertex3f(0.0f, a, b);

		// body
		// first finger
		glVertex3f(-handLength - handStartingX -1, -0.3f + handStartingY, 0.0f); // tip // - 1 is finger length
		glVertex3f(-handLength - handStartingX, -0.3f + handStartingY, 0.0f); // origin point
		glVertex3f(-handLength - handStartingX, a + handStartingY, b); // from origin point

		// second finger
		glVertex3f(-handLength - handStartingX - 1, handStartingY, 0.0f); // tip // - 1 is finger length
		glVertex3f(-handLength - handStartingX, handStartingY, 0.0f); // origin point
		glVertex3f(-handLength - handStartingX, a + handStartingY, b ); // from origin point

		// third finger
		glVertex3f(-handLength - handStartingX - 1, 0.3f + handStartingY, 0.0f); // tip // - 1 is finger length
		glVertex3f(-handLength - handStartingX, 0.3f + handStartingY, 0.0f); // origin point
		glVertex3f(-handLength - handStartingX, a + handStartingY, b); // from origin point
	}

	glEnd();
}

void leftThigh()
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 1.0f / 2;
	float height = -4.0f;

	for (int i = 0; i < sides; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		glVertex3f(radius* sin(theta) * 2 + thighStartingX, thighStartingY, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(nextTheta) * 2 + thighStartingX, thighStartingY, radius* cos(nextTheta) * 2);
		glVertex3f(radius* sin(nextTheta)+ thighStartingX, -thighLength + thighStartingY, radius* cos(nextTheta));

		glVertex3f(radius* sin(nextTheta)+ thighStartingX, -thighLength + thighStartingY, radius* cos(nextTheta));
		glVertex3f(radius* sin(theta) * 2 + thighStartingX,thighStartingY, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(theta)+ thighStartingX, -thighLength + thighStartingY, radius* cos(theta)); // next triangle in cylinder point
	}

	glEnd();
}

void rightThigh()
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 1.0f / 2;
	float height = -4.0f;

	for (int i = 0; i < sides; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		glVertex3f(radius* sin(theta) * 2 - thighStartingX, thighStartingY, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(nextTheta) * 2 - thighStartingX, thighStartingY, radius* cos(nextTheta) * 2);
		glVertex3f(radius* sin(nextTheta) - thighStartingX, -thighLength + thighStartingY, radius* cos(nextTheta));

		glVertex3f(radius* sin(nextTheta) - thighStartingX, -thighLength + thighStartingY, radius* cos(nextTheta));
		glVertex3f(radius* sin(theta) * 2 - thighStartingX, thighStartingY, radius* cos(theta) * 2); // next triangle in cylinder point
		glVertex3f(radius* sin(theta) - thighStartingX, -thighLength + thighStartingY, radius* cos(theta)); // next triangle in cylinder point
	}

	glEnd();
}

void leftFoot()
{
	glBegin(GL_TRIANGLES);

	// rectangle: one side bigger than another side
	// base rectangle
	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f); // intersect point
	glVertex3f(0.6f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f + footStartingX - 0.5f, footStartingY + 0.0f, footLength); // intersect point

	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f + footStartingX + 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f + footStartingX - 0.5f, footStartingY + 0.0f, footLength);

	// top rectangle
	glVertex3f(0.0f + footStartingX, footStartingY + 1.0f -0.5f, 0.0f);
	glVertex3f(1.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(0.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(-1.0f + footStartingX + 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	// small rectangle
	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(0.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(1.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);

	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(0.6f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);

	// left rectangle
	glVertex3f(1.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(0.6f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(0.6f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f + footStartingX - 0.5f, footStartingY + 0.0f, footLength);

	// right rectangle
	glVertex3f(0.0f + footStartingX, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f + footStartingX + 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(0.4f + footStartingX, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f + footStartingX + 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(-1.0f + footStartingX + 0.5f, footStartingY + 0.0f, footLength);

	// big rectangle
	glVertex3f(-1.0f + footStartingX + 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(-1.0f + footStartingX + 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(-1.0f + footStartingX + 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f + footStartingX - 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f + footStartingX - 0.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glEnd();
}

void rightFoot()
{
	glBegin(GL_TRIANGLES);

	// rectangle: one side bigger than another side
	// base rectangle
	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f); // intersect point
	glVertex3f(0.6f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f - footStartingX - 1.5f, footStartingY + 0.0f, footLength); // intersect point

	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f - footStartingX - 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f - footStartingX - 1.5f, footStartingY + 0.0f, footLength);

	// top rectangle
	glVertex3f(0.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(1.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength);// top part

	glVertex3f(0.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(-1.0f - footStartingX - 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	// small rectangle
	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(0.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(1.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);

	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(0.6f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);

	// left rectangle
	glVertex3f(1.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(0.6f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(0.6f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f - footStartingX - 1.5f, footStartingY + 0.0f, footLength);

	// right rectangle
	glVertex3f(0.0f - footStartingX - 1.0f, footStartingY + 1.0f - 0.5f, 0.0f);
	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f - footStartingX - 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(0.4f - footStartingX - 1.0f, footStartingY + 0.0f, 0.0f);
	glVertex3f(-1.0f - footStartingX - 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(-1.0f - footStartingX - 0.5f, footStartingY + 0.0f, footLength);

	// big rectangle
	glVertex3f(-1.0f - footStartingX - 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(-1.0f - footStartingX - 0.5f + 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glVertex3f(-1.0f - footStartingX - 0.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f - footStartingX - 1.5f, footStartingY + 0.0f, footLength);
	glVertex3f(1.2f - footStartingX - 1.5f - 0.4f, footStartingY + 1.2f - 0.6f, footLength); // top part

	glEnd();
}

void head()
{
	glBegin(GL_TRIANGLES);

	oval(0.0f, 1.4f, 0.0f, 2.0, 1.0f, 1.3f, 0.8f);

	glEnd();
}

void leftEye()
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 1.0f;
	//float height = 1.0f;

	for (int i = -sides / 4; i < sides/4; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		if (i >= 0)
		{
			// blue
			glColor3f(0.4f, 0.4f, 1.0f);
		}
		else
		{
			// white
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, cos(i* M_PI / 10) * 0.9f, radius*sin(i* M_PI / 10));
		glVertex3f(0.0f,cos((i + 1)* M_PI / 10) * 0.9f, radius*sin((i + 1)* M_PI / 10));


	}

	glEnd();
	glColor3f(1.0f, 0.3f, 1.0f);
}

void rightEye()
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 1.0f;
	//float height = 1.0f;

	for (int i = -sides / 4; i < sides / 4; i++)
	{
		float theta = i * (M_2PI / sides);
		float nextTheta = (i + 1)*(M_2PI / sides);

		if (i >= 0)
		{
			// blue
			glColor3f(0.4f, 0.4f, 1.0f);
		}
		else
		{
			// white
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, cos(i* M_PI / 10) * 0.9f, radius*sin(i* M_PI / 10));
		glVertex3f(0.0f, cos((i + 1)* M_PI / 10) * 0.9f, radius*sin((i + 1)* M_PI / 10));


	}

	glEnd();
	glColor3f(1.0f, 0.3f, 1.0f);
}

void mouth()
{
	glBegin(GL_TRIANGLES);

	oval(0.0f, 0.3f, 0.3f, 1.0f, 1.2f, 1.5f, 0.6f);

	glEnd();
}

void leftEar()
{
	glBegin(GL_TRIANGLES);

	// (right)
	glVertex3f(0.0f + earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, -0.5f);

	// (left)
	glVertex3f(0.0f + earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, -0.5f);

	// (front)
	glVertex3f(0.0f + earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, 0.0f);

	// (back)
	glVertex3f(0.0f + earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, -0.5f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, -0.5f);

	// (down)
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, -0.5);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, 0.0f);

	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(-0.5f + earStartingX, 0.0f + earStartingY, -0.5f);
	glVertex3f(0.5f + earStartingX, 0.0f + earStartingY, -0.5f);

	glEnd();
}

void rightEar()
{
	glBegin(GL_TRIANGLES);

	// (right)
	glVertex3f(0.0f - earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, -0.5f);

	// (left)
	glVertex3f(0.0f - earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, -0.5f);

	// (front)
	glVertex3f(0.0f - earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, 0.0f);

	// (back)
	glVertex3f(0.0f - earStartingX, 0.8f + earStartingY, 0.0f);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, -0.5f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, -0.5f);

	// (down)
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, -0.5);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, 0.0f);

	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, 0.0f);
	glVertex3f(-0.5f - earStartingX, 0.0f + earStartingY, -0.5f);
	glVertex3f(0.5f - earStartingX, 0.0f + earStartingY, -0.5f);

	glEnd();
}

float tailX = 0.0f;
float tailY = 0.0f;
float tailZ = 0.0f;

void tail(float y, float z)
{
	glBegin(GL_TRIANGLES);

	int sides = 20;
	float radius = 0.3f;

	float prevDeltaX = 0.0f;
	float prevDeltaY = 0.0f;
	float prevDeltaZ = 0.0f;

	float curDeltaX = 0.0f;
	float curDeltaY = 0.0f;
	float curDeltaZ = 0.0f;

	float deltaLength = 0.0f;
	float previousRadius = 0.0f;

	for (float k = 0; k < sides; k += 0.2f)
	{
		float theta = 0.0f;
		float nextTheta = 0.0f;

		prevDeltaX = curDeltaX;
		prevDeltaY = curDeltaY;
		prevDeltaZ = curDeltaZ;
		deltaLength += 0.1f;
		curDeltaX = sin(k * (M_2PI / sides)) + deltaLength;
		curDeltaY = sin(k * (M_2PI / sides));
		curDeltaZ = sin(k * (M_2PI / sides));

		curDeltaY *= y;
		curDeltaZ *= z;

		previousRadius = radius;
		
		/*if (k > sides - 4.0f && k<= sides -2.0f )
		{
			radius += 0.01f;
		}
		else if (k > sides - 2.0f)
		{
			radius -= 0.05f;
		}*/

		for (int i = 0; i < sides; i++)
		{
			theta = i * (M_2PI / sides);
			nextTheta = (i + 1)*(M_2PI / sides);
			
			glVertex3f(curDeltaX, radius* sin(theta) + curDeltaY, radius* cos(theta) + curDeltaZ); // next triangle in cylinder point
			glVertex3f(prevDeltaX , previousRadius* sin(theta) + prevDeltaY, previousRadius* cos(theta) + prevDeltaZ);
			glVertex3f(prevDeltaX, previousRadius* sin(nextTheta) + prevDeltaY, previousRadius* cos(nextTheta) + prevDeltaZ);

			glVertex3f(0.0f + prevDeltaX, previousRadius* sin(nextTheta) + prevDeltaY, previousRadius* cos(nextTheta) + prevDeltaZ);
			glVertex3f(curDeltaX, radius* sin(theta) + curDeltaY, radius* cos(theta) + curDeltaZ); // next triangle in cylinder point
			glVertex3f(curDeltaX, radius* sin(nextTheta) + curDeltaY, radius* cos(nextTheta) + curDeltaZ); // next triangle in cylinder point
		}

	}

	oval(curDeltaX + 1.2f, curDeltaY, curDeltaZ, 1.0f, 0.6f, 2.0f, 1.0f);
	tailX = curDeltaX;
	tailY = curDeltaY;
	tailZ = curDeltaZ;
	
	glEnd();
}

void tailEnd()
{
	glBegin(GL_TRIANGLES);
/*
	oval(tailX + 1.2f, tailY, tailZ, 1.0f, 0.6f, 2.0f, 1.0f);*/
	oval(0.0f, 0.0f, 0.0f, 1.0f, 0.6f, 2.0f, 1.0f);

	glEnd();

}

void waist()
{
	glBegin(GL_TRIANGLES);

	botHalfCircle(0.0f, -4.0f, 0.0f, 2.0f);

	glEnd();
}

void waistLeft()
{
	glBegin(GL_TRIANGLES);

	circle(footStartingX + 0.5f, -4.0f, 0.0f, 1.0);

	glEnd();
}

void waistRight()
{
	glBegin(GL_TRIANGLES);

	circle(-1.0f - footStartingX + 0.5f, -4.0f, 0.0f, 1.0);

	glEnd();
}

void leftKnee()
{
	glBegin(GL_TRIANGLES);

	circle(footStartingX + 0.5f, -thighLength + thighStartingY, 0.0f, 0.5f);

	glEnd();
}

void rightKnee()
{
	glBegin(GL_TRIANGLES);

	circle(-1.0f - footStartingX + 0.5f, -thighLength + thighStartingY, 0.0f, 0.5f);

	glEnd();
}

void leftFootToe()
{
	glBegin(GL_TRIANGLES);

	halfCircle(footStartingX + 0.1f, footStartingY, footLength, 0.6f);

	glEnd();
}

void rightFootToe()
{
	glBegin(GL_TRIANGLES);

	halfCircle(-1.0f - footStartingX + 0.1f, footStartingY, footLength, 0.6f);

	glEnd();
}

#endif