#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

void circle(float startX, float startY, float startZ, float radius)
{
	int sides = 20;
	//float radius = 1.0f;
	//float height = 1.0f;

	for (int k = 0; k < sides; k++)
	{
		for (int i = 0; i < sides; i++)
		{
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			// latitude
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(theta), 0.0f, radius*cos(theta));
			glVertex3f(radius*sin(nextTheta), 0.0f, radius*cos(nextTheta));*/

			// different latitude
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(i* M_PI / 10), radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			glVertex3f(radius*sin((i + 1)* M_PI / 10), radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));*/

			//// latitude degree of one side
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(radius*sin(i* M_PI / 10), radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			//glVertex3f(radius*sin((i + 1)* M_PI / 10), radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));

			//// longtitude 90 degree
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(0.0f, radius*sin(theta), radius*cos(theta));
			//glVertex3f(0.0f, radius*sin(nextTheta), radius*cos(nextTheta));

			//// longtitude 180 degree
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(radius*cos(theta), radius*sin(theta), 0.0f);
			//glVertex3f(radius*cos(nextTheta), radius*sin(nextTheta), 0.0f);

			// longtitude degree of one side
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*sin(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			glVertex3f(radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*sin((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));
*/

			float x1 = radius * sin(k * M_PI / 10)*cos(i* M_PI / 10);
			float y1 = radius * sin(i* M_PI / 10);
			float z1 = radius * cos(i* M_PI / 10)*cos(k * M_PI / 10);

			float x2 = radius * sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y2 = radius * sin((i + 1)* M_PI / 10);
			float z2 = radius * cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10);

			float x3 = radius * sin((k + 1) * M_PI / 10)*cos(i* M_PI / 10);
			float y3 = radius * sin(i* M_PI / 10);
			float z3 = radius * cos(i* M_PI / 10)*cos((k+1) * M_PI / 10);

			float x4 = radius * sin((k + 1) * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y4 = radius * sin((i + 1)* M_PI / 10);
			float z4 = radius * cos((i + 1)* M_PI / 10)*cos((k + 1) * M_PI / 10);

			glVertex3f(x1 + startX, y1 + startY, z1 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

			glVertex3f(x4+ startX, y4 + startY, z4+ startZ);
			glVertex3f(x2+ startX, y2 + startY, z2+ startZ);
			glVertex3f(x3+ startX, y3 + startY, z3+ startZ);

		}
	}
}

void halfCircle(float startX, float startY, float startZ, float radius)
{
	int sides = 20;
//	float radius = 1.0f;
	float height = 1.0f;

	for (int k = 0; k < 20; k++) // 10 is enough, 20 just extra triangles overlap each other
	{
		for (int i = 0; i < sides/2; i++) // divide by 2 for half circle
		{

			float x1 = radius * sin(k * M_PI / 10)*cos(i* M_PI / 10);
			float y1 = radius * sin(i* M_PI / 10);
			float z1 = radius * cos(i* M_PI / 10)*cos(k * M_PI / 10);

			float x2 = radius * sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y2 = radius * sin((i + 1)* M_PI / 10);
			float z2 = radius * cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10);

			float x3 = radius * sin((k + 1) * M_PI / 10)*cos(i* M_PI / 10);
			float y3 = radius * sin(i* M_PI / 10);
			float z3 = radius * cos(i* M_PI / 10)*cos((k + 1) * M_PI / 10);

			float x4 = radius * sin((k + 1) * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y4 = radius * sin((i + 1)* M_PI / 10);
			float z4 = radius * cos((i + 1)* M_PI / 10)*cos((k + 1) * M_PI / 10);

			glVertex3f(x1 + startX, y1 + startY, z1 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

			glVertex3f(x4 + startX, y4 + startY, z4 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

		}
	}
}

void botHalfCircle(float startX, float startY, float startZ, float radius)
{
	int sides = 20;
	//	float radius = 1.0f;
	float height = 1.0f;

	for (int k = 0; k < 20; k++) // 10 is enough, 20 just extra triangles overlap each other
	{
		for (int i = sides / 2; i < sides; i++) // divide by 2 for half circle
		{

			float x1 = radius * sin(k * M_PI / 10)*cos(i* M_PI / 10);
			float y1 = radius * sin(i* M_PI / 10);
			float z1 = radius * cos(i* M_PI / 10)*cos(k * M_PI / 10);

			float x2 = radius * sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y2 = radius * sin((i + 1)* M_PI / 10);
			float z2 = radius * cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10);

			float x3 = radius * sin((k + 1) * M_PI / 10)*cos(i* M_PI / 10);
			float y3 = radius * sin(i* M_PI / 10);
			float z3 = radius * cos(i* M_PI / 10)*cos((k + 1) * M_PI / 10);

			float x4 = radius * sin((k + 1) * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y4 = radius * sin((i + 1)* M_PI / 10);
			float z4 = radius * cos((i + 1)* M_PI / 10)*cos((k + 1) * M_PI / 10);

			glVertex3f(x1 + startX, y1 + startY, z1 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

			glVertex3f(x4 + startX, y4 + startY, z4 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

		}
	}
}

void oval(float startX, float startY, float startZ, float radius, float flatValueX, float flatValueY, float flatValueZ)
{
	int sides = 20;
	//float radius = 1.0f;
	//float height = 1.0f;

	for (int k = 0; k < sides; k++)
	{
		for (int i = 0; i < sides; i++)
		{
			float theta = i * (M_2PI / sides);
			float nextTheta = (i + 1)*(M_2PI / sides);

			// latitude
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(theta), 0.0f, radius*cos(theta));
			glVertex3f(radius*sin(nextTheta), 0.0f, radius*cos(nextTheta));*/

			// different latitude
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(i* M_PI / 10), radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			glVertex3f(radius*sin((i + 1)* M_PI / 10), radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));*/

			//// latitude degree of one side
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(radius*sin(i* M_PI / 10), radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			//glVertex3f(radius*sin((i + 1)* M_PI / 10), radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));

			//// longtitude 90 degree
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(0.0f, radius*sin(theta), radius*cos(theta));
			//glVertex3f(0.0f, radius*sin(nextTheta), radius*cos(nextTheta));

			//// longtitude 180 degree
			//glVertex3f(0.0f, 0.0f, 0.0f);
			//glVertex3f(radius*cos(theta), radius*sin(theta), 0.0f);
			//glVertex3f(radius*cos(nextTheta), radius*sin(nextTheta), 0.0f);

			// longtitude degree of one side
			/*glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(radius*sin(k * M_PI / 10)*cos(i* M_PI / 10), radius*sin(i* M_PI / 10), radius*cos(i* M_PI / 10)*cos(k * M_PI / 10));
			glVertex3f(radius*sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10), radius*sin((i + 1)* M_PI / 10), radius*cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10));
			*/

			float x1 = radius / flatValueX * sin(k * M_PI / 10)*cos(i* M_PI / 10);
			float y1 = radius / flatValueY * sin(i* M_PI / 10);
			float z1 = radius / flatValueZ * cos(i* M_PI / 10)*cos(k * M_PI / 10);

			float x2 = radius / flatValueX * sin(k * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y2 = radius / flatValueY * sin((i + 1)* M_PI / 10);
			float z2 = radius / flatValueZ * cos((i + 1)* M_PI / 10)*cos(k * M_PI / 10);

			float x3 = radius / flatValueX * sin((k + 1) * M_PI / 10)*cos(i* M_PI / 10);
			float y3 = radius / flatValueY * sin(i* M_PI / 10);
			float z3 = radius / flatValueZ * cos(i* M_PI / 10)*cos((k + 1) * M_PI / 10);

			float x4 = radius / flatValueX * sin((k + 1) * M_PI / 10)*cos((i + 1)* M_PI / 10);
			float y4 = radius / flatValueY * sin((i + 1)* M_PI / 10);
			float z4 = radius / flatValueZ * cos((i + 1)* M_PI / 10)*cos((k + 1) * M_PI / 10);


			glColor3f(1.0f, 0.4f, 1.0f);
			if (k <= sides -8 )
			{
				glColor3f(1.0f, 0.35f, 1.0f);
			}
			glVertex3f(x1 + startX, y1 + startY, z1 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

			glVertex3f(x4 + startX, y4 + startY, z4 + startZ);
			glVertex3f(x2 + startX, y2 + startY, z2 + startZ);
			glVertex3f(x3 + startX, y3 + startY, z3 + startZ);

		}
	}
}


#endif
