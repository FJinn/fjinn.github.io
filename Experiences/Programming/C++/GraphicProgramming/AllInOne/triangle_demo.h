#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include "pokemon.h"
#include "Bitmap.h"
#include <fmod.hpp>
#include <fmod_errors.h>

#define TEXTURE_COUNT 2

// must be power of 2
#define SPECTRUM_SIZE 128

// fmod error checking function
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! : " << FMOD_ErrorString(result) << std::endl;
	}
}

// commented out in main.cpp

class TriangleDemo : public DemoBase
{
private:
	float m_rotation;
	float m_value1;
	
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;
	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];

	GLuint mTextureID[TEXTURE_COUNT];

	void loadTexture(const char* path, GLuint textureID)
	{
		CBitmap bitmap(path);

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // apply texture wrapping along horizontal part
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // apply texture wrapping along vertical part

		//// old school (minecraft) filtering
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // near filtering. (For when texture needs to scale up)
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // far filtering. (For when texture needs to scale down)
	
		
		//bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when texture needs to scale up)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when texture needs to scale down)
		

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	}

public:
	void initFmod()
	{
		FMOD_RESULT result;
		unsigned int version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRCHECK(result);

		result = m_fmodSystem->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
		{
			std::cout << "FMOD Error! You are using an old version of FMOD." << std::endl;
		}

		// initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);

		// load and set up music 
		result = m_fmodSystem->createStream("../media/SomethingJustLikeThis.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		// play the loaded music
		//result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);
	}

	void init()
	{
		m_rotation = 0;
		m_value1 = 0;

		// openGL generate texture id 
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/glass.bmp", mTextureID[0]);
		loadTexture("../media/rocks.bmp", mTextureID[1]);

		initFmod();
	}

	void deinit()
	{
	}

	void UpdateFmod()
	{
		m_fmodSystem->update();

		// Get spectrum for left and right stereo channels
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);

		// test and print first frequency range volume
		std::cout <<"Left : " << m_spectrumLeft[0] <<" , right: " << m_spectrumRight[0] << std::endl;
	}

	void drawAxis(const Matrix& viewMatrix)
	{
		// ============draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.3f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		glColor3f(0.3f, 1.0f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.3f, 0.3f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		// ============================
	}


	void drawTriangle(void)
	{
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);

		// square

		glColor3f(2.0f, 0.0f, 2.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 2.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);

		glEnd();
	}

	void drawCube(void)
	{
		glBegin(GL_TRIANGLES);

		// cube
		//first
		glColor3f(1.0f, 0.4f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		//second (right)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		//third (left)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		//forth (back)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.6f, 1.0f, 0.6f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		//fifth (up)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		//sixth (down)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glEnd();
	}

	void drawPyramid(void)
	{
		glBegin(GL_TRIANGLES);

		// pyramid
		//first
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.0f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.0f, -0.5f, 0.5f);

		//second (right)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.0f);

		//third (left)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.0f);

		//forth (back)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.0f, -0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.0f, -0.5f, -0.5f);

		//sixth (down)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glEnd();
	}

	void drawCylinder(void)
	{
		glBegin(GL_TRIANGLES);

		for (double i = -180; i <= 180; i += 0.01)
		{
			double a, b, c;
			// a/|v| = cos 0;
			// b/|v| = sin 0;
			a = cos(i* M_PI / 180);
			b = sin(i* M_PI / 180);

			// c = next a position for cylinder body
			c = cos((i + 1)* M_PI / 180);

			// first circle
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(a, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(a, 0.0f, b);

			// second circle
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(a, 4.0f, 0.0f);
			glVertex3f(0.0f, 4.0f, 0.0f);
			glVertex3f(a, 4.0f, b);

			// first body
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(a, 4.0f, b);
			glVertex3f(c, 4.0f, b);
			glVertex3f(a, 0.0f, b);

			// second body
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(a, 0.0f, b);
			glVertex3f(c, 0.0f, b);
			glVertex3f(a, 4.0f, b);
		}

		glEnd();
	}
	
	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);

		//	// ==================== set transformation matrix and upload to GPU
		//	m_rotation += 0.05f;
		//	m_value1 += 0.05f;
		//	Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 0.0f, 1.0f));
		//	Matrix translate1 = Matrix::makeTranslationMatrix(cosf(m_rotation)*3.0f, 0.0f, sin(m_rotation)*8.0f);
		//	Matrix scale1 = Matrix::makeScaleMatrix(4.0f, 4.0f, 4.0f);

		//	// NOTE on OpenGL Matrix model:
		//	// Screen = Proj * View * Model
		//	// Model = TransformA(3rd) * TranformB(2nd) * TransformC(1st) (Transform could be Rotate, Scale, Translate etc)

		//	// perform model transformation
		//	Matrix modelMatrix = translate1;

		//	// convert model space to view space
		//	Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		//	
		//	glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		//	//glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//	//enable wireframe mode
		//	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		//	//glColor3f(1.0f, 1.0f, 1.0f);
		//	
		////	drawTriangle();
		//	drawCube();
		////	drawPyramid();
		////	drawCylinder();


		//	// object2
		//	m_value1 += 1.0f;
		//	rotate1 = Matrix::makeRotateMatrix(m_value1, Vector(0.0f, 1.0f, 0.0f));

		//	Matrix modelMatrix2 = rotate1;

		//	Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix2;

		//	glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);

		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//	drawCube();
	//	snakeBoxes(viewMatrix);

		//glColor3f(1.0f, 0.4f, 1.0f);
		//drawPokemon(viewMatrix);
		//headAnimation(viewMatrix);
		//glColor3f(1.0f, 0.4f, 0.9f);
		//footAnimation(viewMatrix);


		// texture*******************

	//		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
			glColor3f(1.0f, 1.0f, 1.0f);
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


			glEnable(GL_TEXTURE_2D); // enable texturing
			glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture

		Rectangle(viewMatrix);
			//RectangleArray();
		//	WaveRectangle();

		//	UpdateFmod();

	//		AudioVisualizer();
	}
	
	void AudioVisualizer()
	{
		static float x, y, z;
		static float deltaX, deltaZ = 0;
		x = 1.0f;
		y = 1.0f;
		z = 1.0f;

		static GLfloat vertices1[720];
		static GLfloat textCoords1[480];
		static GLubyte colors1[720];

		deltaX = x;
		deltaZ = z;

		float height = 50;
		int count = 0;
		int countText = 0;
		int num = 0;
		int audioNum = 0;
		int audioNum2 = 0;
		float curValue = 0;

		for (int k = 0; k<720; k++)
		{
			if (k < 360)
			{
				curValue = (m_spectrumLeft[audioNum] * height);
			}
			else
			{
				curValue = (m_spectrumRight[audioNum2] * height);
			}

			if (count < 19)
			{
				count++;
			}
			else if (count == 19)
			{
				count = 1;
			}

			if (count == 1)
			{
				vertices1[num] = deltaX - 1;
			}
			else if (count == 2)
			{
				vertices1[num] = y;
			}
			else if (count == 3)
			{
				vertices1[num] = z + curValue;
			}
			else if (count == 4)
			{
				vertices1[num] = deltaX;
			}
			else if (count == 5) // cur y
			{
				vertices1[num] = y ;
			}
			else if (count == 6)
			{
				vertices1[num] = z + curValue;
			}
			else if (count == 7)
			{
				vertices1[num] = deltaX;
			}
			else if (count == 8) // cur y
			{
				vertices1[num] = y;
			}
			else if (count == 9)
			{
				vertices1[num] = z;
			}
			else if (count == 10)
			{
				vertices1[num] = deltaX;
			}
			else if (count == 11) // cur y
			{
				vertices1[num] = y ;
			}
			else if (count == 12)
			{
				vertices1[num] = z;
			}
			else if (count == 13)
			{
				vertices1[num] = deltaX - 1;
			}
			else if (count == 14)
			{
				vertices1[num] = y;
			}
			else if (count == 15)
			{
				vertices1[num] = z;
			}
			else if (count == 16)
			{
				vertices1[num] = deltaX - 1;
			}
			else if (count == 17)
			{
				vertices1[num] = y;
			}
			else if (count == 18)
			{
				vertices1[num] = z + curValue;

				deltaX += x;
				count = 0;
				if (k < 360)
				{
					audioNum++;
				}
				else
				{
					audioNum2++;
				}

			}

			colors1[num] = 200;

			num++;
		}

		for (int j = 0; j<480; j++)
		{
			if (countText < 13)
			{
				countText++;
			}
			else if (countText == 13)
			{
				countText = 1;
			}

			if (countText == 1 || countText == 2 || countText == 4 || countText == 9 || countText == 11 || countText == 12)
			{
				textCoords1[j] = 0.0f;
			}
			else if (countText == 3 || countText == 5 || countText == 6 || countText == 7 || countText == 8 || countText == 10)
			{
				textCoords1[j] = 1.0f;
			}
		}

		//	glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture

		glEnableClientState(GL_VERTEX_ARRAY);
		//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices1);
		//	glTexCoordPointer(2, GL_FLOAT, 0, textCoords1);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors1);

		glDrawArrays(GL_TRIANGLES, 0, 240);

		glDisableClientState(GL_VERTEX_ARRAY);
		//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	float deltaY = 0;
	void WaveRectangle()
	{
		static float x, y, z;
		static float deltaX, deltaZ = 0;
		x = 1.0f;
		y = 1.0f;
		z = 1.0f;

		static GLfloat vertices1[45000];
		static GLfloat textCoords1[30000];
		static GLubyte colors1[45000];

		deltaX = x;
		deltaZ = z;
		// speed
		deltaY += 0.05f;

		float height = 1;
		int count = 0;
		int countText = 0;
		int num = 0;

		float prevY = sinf((deltaY - 1)) * height;
		float curY = sinf(deltaY) * height;

		for (int i = 0; i< 50; i++ )
		{
			prevY = sinf(deltaY - 1) * height;
			curY = sinf(deltaY) * height;

			for (int k = 0; k<900; k++)
			{
				if (count < 19)
				{
					count++;
				}
				else if (count == 19)
				{
					count = 1;
				}

				if (count == 1)
				{
					vertices1[num] = deltaX - 1;
				}
				else if (count == 2)
				{
					vertices1[num] = prevY;
				}
				else if (count == 3)
				{
					vertices1[num] = deltaZ - 1;
				}
				else if (count == 4)
				{
					vertices1[num] = deltaX;
				}
				else if (count == 5) // cur y
				{
					vertices1[num] = curY;
				}
				else if (count == 6)
				{
					vertices1[num] = deltaZ - 1;
				}
				else if (count == 7)
				{
					vertices1[num] = deltaX;
				}
				else if (count == 8) // cur y
				{
					vertices1[num] = curY;
				}
				else if (count == 9)
				{
					vertices1[num] = deltaZ;
				}
				else if (count == 10)
				{
					vertices1[num] = deltaX;
				}
				else if (count == 11) // cur y
				{
					vertices1[num] = curY;
				}
				else if (count == 12)
				{
					vertices1[num] = deltaZ;
				}
				else if (count == 13)
				{
					vertices1[num] = deltaX - 1;
				}
				else if (count == 14)
				{
					vertices1[num] = prevY;
				}
				else if (count == 15)
				{
					vertices1[num] = deltaZ;
				}
				else if (count == 16)
				{
					vertices1[num] = deltaX - 1;
				}
				else if (count == 17)
				{
					vertices1[num] = prevY;
				}
				else if (count == 18)
				{
					vertices1[num] = deltaZ - 1;

					deltaX += x;
					count = 0;

					prevY = curY;
					curY = sinf(deltaY - k) * height;
				}

				num++;
				if ( count % 3 == 0)
				{
					colors1[num] = 255;
				}
				else
				{
					colors1[num] = 100;
				}
			}

			deltaX = x;
			deltaZ += z;
		}

		for (int j = 0; j<30000; j++)
		{
			if (countText < 13)
			{
				countText++;
			}
			else if (countText == 13)
			{
				countText = 1;
			}

			if (countText == 1 || countText == 2 || countText == 4 || countText == 9 || countText == 11 || countText == 12)
			{
				textCoords1[j] = 0.0f;
			}
			else if (countText == 3 || countText == 5 || countText == 6 || countText == 7 || countText == 8 || countText == 10)
			{
				textCoords1[j] = 1.0f;
			}
		}
/*
		static GLfloat vertices[] = {
			-x, -y, z,
			x, -y, z,
			x, y, z,
			x, y, z,
			-x, y, z,
			-x, -y, z,
		};

		static GLfloat textCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		};

		static GLubyte colors[] = {
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255
		};
*/
	//	glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture

		glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices1);
	//	glTexCoordPointer(2, GL_FLOAT, 0, textCoords1);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors1);

		glDrawArrays(GL_TRIANGLES, 0, 15000);

		glDisableClientState(GL_VERTEX_ARRAY);
	//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void RectangleArray()
	{
		static GLfloat vertices[] = {
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f
		};

		static GLfloat textCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		};

		static GLubyte colors[] = {
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255
		};

		glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, textCoords);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	// texture cube
	void TextureCube()
	{
		static float uShift = 0.0f; // UV's u
		//uShift += 0.01f;
		//if (uShift > 1.0f)
		//{
		//	uShift -= 1.0f;
		//}

		glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture
		glBegin(GL_TRIANGLES);
		//			u			  ,   v
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

		glEnd();


		glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f + uShift, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f + uShift, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

		glEnd();
	}

	// blending rectangle ---- exmaple effect of adding glow
	void Rectangle(const Matrix& viewMatrix)
	{
		// drawing opaque object first
		glDisable(GL_BLEND);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]); // Bind panel texture

		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -4.0f, -2.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -4.0f, -2.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f,  4.0f, -2.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f,  4.0f, -2.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,  4.0f, -2.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -4.0f, -2.0f);

		glEnd();

		// drawing transparent objects here
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		//glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend

		TextureCube();

		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // Bind panel texture
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0f , 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f , 0.0f); glVertex3f( 2.0f, -2.0f, 2.0f);
		glTexCoord2f(1.0f , 1.0f); glVertex3f( 2.0f,  2.0f, 2.0f);
		glTexCoord2f(1.0f , 1.0f); glVertex3f( 2.0f,  2.0f, 2.0f);
		glTexCoord2f(0.0f , 1.0f); glVertex3f(-2.0f,  2.0f, 2.0f);
		glTexCoord2f(0.0f , 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);

		glEnd();

		glDepthMask(true);
	}
/*
	void snakeBoxes(const Matrix& viewMatrix)
	{
		m_rotation += 0.1f;
		for (float i = 0; i < 20; i += 0.45)
		{
			Matrix snakeRotation = Matrix::makeTranslationMatrix(cosf(m_rotation - i)*4.0f, 0.0f + i, sinf(m_rotation - i)*4.0f);

			m_value1 += 0.05f;
			Matrix rotate1 = Matrix::makeRotateMatrix(m_value1, Vector(0.0f, 1.0f, 0.0f));

			Matrix modelMatrix = snakeRotation * rotate1;

			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			drawCube();
		}

		
		//lecturer's code
		//float entityRotation = m_rotation =0.5f*(float)i;

		//// 1st animation
		//Matrix modelMatrix = Metrix::makeTranslationMatrix(cosf(entityRotation)*3.0f, i*0.5f, sinf(entityRotation*3.0f);

		//// 2nd animation
		//Matirx modelMatrix = Matrix::makeTranslationMatrix(0.0f, i*0.5f, 0.0f) *
		//					 Matrix::maleRotateMatrix(entityRotation*180.0/M_PI, Vector(0.0f, 1.0f, 0.0f)) *
		//					 Matirx::makeTranslationMatrix(3.0f, 0.0f, 0.0f);

		//Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		//glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//drawCube();

		
	}

	// Pokemon Assignmnet Animation Part
	// + Matrix Transformation

	void drawPokemon(const Matrix& viewMatrix)
	{
		body();
		glColor3f(1.0f, 0.35f, 1.0f);
		waist();
		glColor3f(1.0f, 0.35f, 1.0f);
		drawLeftHand(viewMatrix);
		glColor3f(1.0f, 0.4f, 1.0f);
		drawRightHand(viewMatrix);
		drawTail(viewMatrix);
		//drawTailEnd(viewMatrix);
	}

	float rotationValue = 0.0f;
	float temp = 1.0f;

	void headAnimation(const Matrix& viewMatrix)
	{
		rotationValue += temp;

		if (rotationValue < -20)
		{
			temp = 1.0f;
		}
		else if (rotationValue > 20)
		{
			temp = -1.0f;
		}

		for (float i = 0; i < 20; i ++)
		{
			Matrix rotate1 = Matrix::makeRotateMatrix(rotationValue, Vector(0.0f, 0.0f, 1.0f));

			Matrix modelMatrix = rotate1;

			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

			glColor3f(0.9f, 0.3f, 1.0f);
			drawHead(viewSpaceMatrix);
			drawMouth(viewSpaceMatrix);
			drawLeftEye(viewSpaceMatrix);
			drawRightEye(viewSpaceMatrix);
			glColor3f(0.9f, 0.3f, 1.0f);
			drawLeftEar(viewSpaceMatrix);
			drawRightEar(viewSpaceMatrix);
		}

	}

	float rotationFootValue= 0.0f;
	float tempFoot = 1.0f;

	void footAnimation(const Matrix& viewMatrix)
	{
		rotationFootValue += tempFoot;

		if (rotationFootValue < 0)
		{
			tempFoot = 1.0f;
		}
		else if (rotationFootValue > 15)
		{
			tempFoot = -1.0f;
		}

		for (float i = 0; i < 10; i++)
		{
			Matrix rotate1 = Matrix::makeRotateMatrix(-rotationFootValue, Vector(1.0f, 0.0f, 0.0f));
			
			Matrix modelMatrix = rotate1;

			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

			glColor3f(1.0f, 0.35f, 1.0f);
			leftThigh();
			glColor3f(1.0f, 0.4f, 1.0f);
			rightThigh();
			glColor3f(1.0f, 0.35f, 1.0f);
			leftKnee();
			glColor3f(1.0f, 0.4f, 1.0f);
			rightKnee();
			glColor3f(1.0f, 0.35f, 1.0f);
			waistLeft();
			glColor3f(1.0f, 0.4f, 1.0f);
			waistRight();

			glColor3f(1.0f, 0.35f, 1.0f);
			leftFoot();
			glColor3f(1.0f, 0.4f, 1.0f);
			rightFoot();
			glColor3f(1.0f, 0.35f, 1.0f);
			leftFootToe();
			glColor3f(1.0f, 0.4f, 1.0f);
			rightFootToe();
		}
	}

	float rotationValue2 = 0.0f;

	void drawLeftEar(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(25, Vector(0.0f, 0.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(-1.0f, -2.6f, 0.0f);
		Matrix translate2 = Matrix::makeTranslationMatrix(1.0f, 2.6f, 0.0f);

		Matrix modelMatrix = translate2 * rotate1 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		leftEar();
	}
	void drawRightEar(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(-25, Vector(0.0f, 0.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(1.0f, -2.6f, 0.0f);
		Matrix translate2 = Matrix::makeTranslationMatrix(-1.0f, 2.6f, 0.0f);

		Matrix modelMatrix = translate2 * rotate1 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		rightEar();
	}

	float rotationValue3 = 0.0f;
	float temp2 = 3.0f;

	void drawLeftHand(const Matrix& viewMatrix)
	{
		rotationValue3 += temp2;

		if (rotationValue3 < 0)
		{
			temp2 = 3.0f;
		}
		else if (rotationValue3 > 70)
		{
			temp2 = -3.0f;
		}

		Matrix rotate1 = Matrix::makeRotateMatrix(45, Vector(0.0f, 0.0f, 1.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(rotationValue3, Vector(0.0f, 1.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(-1.2f, 1.0f, 0.0f);
		Matrix translate2 = Matrix::makeTranslationMatrix(1.2f, -1.0f, 0.0f);

		Matrix modelMatrix = translate2 * rotate1 * rotate2 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		leftHand();
	}

	void drawRightHand(const Matrix& viewMatrix)
	{
		rotationValue3 += temp2;

		if (rotationValue3 < 0)
		{
			temp2 = 4.0f;
		}
		else if (rotationValue3 > 70)
		{
			temp2 = -4.0f;
		}

		Matrix rotate1 = Matrix::makeRotateMatrix(-45, Vector(0.0f, 0.0f, 1.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(-rotationValue3, Vector(0.0f, 1.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(1.2f, 1.0f, 0.0f);
		Matrix translate2 = Matrix::makeTranslationMatrix(-1.2f, -1.0f, 0.0f);

		Matrix modelMatrix = translate2 * rotate1 * rotate2  * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		rightHand();
	}

	float y = -2.0f;
	float deltaY = 0.1f;
	float z = -2.0f;
	float deltaZ = 0.1f;

	void drawTail(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(-90, Vector(0.0f, 1.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(1.3f, -4.0f, 0.0f);

		Matrix modelMatrix = rotate1 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		y += deltaY;
		z += deltaZ;

		if (y < -2)
		{
			deltaY = 0.1;
		}
		else if (y > 2)
		{
			deltaY = -0.1;
		}

		if (z < -2)
		{
			deltaZ = 0.1;
		}
		else if (z > 2)
		{
			deltaZ = -0.1;
		}

		tail(y, z);
	}

	void drawTailEnd(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(90, Vector(0.0f, 1.0f, 0.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(60, Vector(1.0f, 0.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(-7.0f, -9.0f, -5.25f);

		Matrix modelMatrix = rotate1 * rotate2 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		tailEnd();
	}

	void drawHead(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(-25, Vector(1.0f, 0.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, -1.4f, 0.0f);
		Matrix translate2 = Matrix::makeTranslationMatrix(0.0f, 1.2f, 0.0f);

		Matrix modelMatrix = translate2 * rotate1 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		head();
	}

	void drawLeftEye(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(35, Vector(0.0f, 1.0f, 0.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(-15, Vector(0.0f, 0.0f, 1.0f));
		Matrix rotate3 = Matrix::makeRotateMatrix(-35, Vector(1.0f, 0.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(2.3f, 0.5f, 0.2f);

		Matrix modelMatrix = rotate1 * rotate2 * rotate3 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		leftEye();
	}

	void drawRightEye(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(-35, Vector(0.0f, 1.0f, 0.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(15, Vector(0.0f, 0.0f, 1.0f));
		Matrix rotate3 = Matrix::makeRotateMatrix(-35, Vector(1.0f, 0.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(-2.3f, 0.5f, 0.2f);

		Matrix modelMatrix = rotate1 * rotate2 * rotate3 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		rightEye();
	}

	void drawMouth(const Matrix& viewMatrix)
	{
		Matrix rotate1 = Matrix::makeRotateMatrix(-35, Vector(1.0f, 0.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, -0.3f, -1.5f);
		Matrix translate2 = Matrix::makeTranslationMatrix(0.0f, 0.0f, 2.0f);

		Matrix modelMatrix = translate2 * rotate1 * translate1;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		mouth();
	}
	*/
};


#endif
