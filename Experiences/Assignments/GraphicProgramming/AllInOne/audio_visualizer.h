#ifndef _AUDIO_VISUALIZER_H
#define _AUDIO_VISUALIZER_H

#include "demo_base.h"
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>
#include "Bitmap.h"
#include <iostream>
#include <time.h>

#define RECT_VERTICE_W 50
#define RECT_VERTICE_D 50
#define RECT_VERTICE_H 1

#define TEXTURE_COUNT 2

// must be power of 2
#define SPECTRUM_SIZE 128

//every quad has 6 vertices
const int RECT_VERTEX_COUNT = (RECT_VERTICE_W - 1)*(RECT_VERTICE_D - 1) * 6;

//every cube has 6 quad
const int CUBE_VERTEX_COUNT = RECT_VERTEX_COUNT * 6;

//every vertex has 3 components(x, y z)
const int RECT_VERTEX_ARRAY_SIZE = CUBE_VERTEX_COUNT * 3;

// every donut has 50 * 50 rect 
const int DONUT_RECT_COUNT = (RECT_VERTICE_W)*(RECT_VERTICE_D);
// every rect has 6 vertices
const int DONUT_VERTEX_COUNT = DONUT_RECT_COUNT * 6;
// every vertex has 3 components
const int DONUT_VERTEX_ARRAY_SIZE = DONUT_VERTEX_COUNT * 3;

// every box has 6 * 6 vertices
const int BOX_VERTEX_COUNT = 36;
// every vertext has 3 components
const int BOX_VERTEX_ARRAY_SIZE = BOX_VERTEX_COUNT * 3;

// fmod error checking function
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! : " << FMOD_ErrorString(result) << std::endl;
	}
}

class AudioVisualizer : public DemoBase
{
private:
	GLfloat mRectVertices[RECT_VERTEX_ARRAY_SIZE];
	GLfloat mRectTexture[CUBE_VERTEX_COUNT * 2];
	GLfloat mDonutVertices[DONUT_VERTEX_ARRAY_SIZE];
	GLfloat mDonutTexture[DONUT_VERTEX_COUNT * 2];
	GLfloat mBoxVertices[BOX_VERTEX_ARRAY_SIZE];
	GLfloat mBoxTexture[BOX_VERTEX_COUNT * 2];

	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;
	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];

	float m_rotation;
	float donut_rotation;
	float donut_rotation2;
	float donut_rotation3;
	float box_rotation;
	float texMul;

	float translateValueX;
	float translateValueY;
	float translateValueZ;

	float boxX;
	float boxY;
	float boxZ;

	int a[12];
	int aCounter;

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
		result = m_fmodSystem->createStream("../media/GoT.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		// play the loaded music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);
	}

	void init()
	{
		initFmod();	
		m_rotation = 0;

		// openGL generate texture id 
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/fire.bmp", mTextureID[0]);
		loadTexture("../media/water.bmp", mTextureID[1]);

		for (int i=0; i<12; i++)
		{
			a[i] = i;
		}
		aCounter = 0;
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
//		std::cout << "Left : " << m_spectrumLeft[0] << " , right: " << m_spectrumRight[0] << std::endl;
	}

	void ACount(int num)
	{
		int temp = 0;
		for (int i = 0; i < num; i++)
		{
			temp = a[i];
			a[i] = a[i + 1];
			a[i + 1] = temp;
		}
	}

	void genPlane()
	{
		const float width = 5.0f;
		const float depth = 5.0f;
		const float halfWidth = width * 0.5f;
		const float halfDepth = depth * 0.5f;
		float height = 1 / (float)RECT_VERTICE_W * width;
		float base = 0.0f;

		const int spectrumHeight = 5;

		if (texMul < 50)
		{
			texMul += m_spectrumLeft[0];
		}
		else
		{
			texMul -= 50;
		}

		int currentVert = -1;
		int currentIndex = -1;
		
		for (int d = 0; d < RECT_VERTICE_D - 1; d++)
		{
			for (int w = 0; w < RECT_VERTICE_W - 1; w++)
			{
				if (d == 2 || d == RECT_VERTICE_D - 4 || w == 0 || w == RECT_VERTICE_W - 2)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[11] * spectrumHeight;
					base =  - m_spectrumRight[a[11]] * spectrumHeight/2;
				}
				else if(d == 4 || d == RECT_VERTICE_D - 6 || w == 2 || w == RECT_VERTICE_W - 4)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[10] * spectrumHeight;
					base = - m_spectrumRight[a[10]] * spectrumHeight/2;
				}
				else if (d == 6 || d == RECT_VERTICE_D - 8 || w == 4 || w == RECT_VERTICE_W - 6)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[9] * spectrumHeight;
					base = - m_spectrumRight[a[9]] * spectrumHeight/2;
				}
				else if (d == 8 || d == RECT_VERTICE_D - 10 || w == 6 || w == RECT_VERTICE_W - 8)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[8] * spectrumHeight;
					base = - m_spectrumRight[a[8]] * spectrumHeight/2;
				}
				else if (d == 10 || d == RECT_VERTICE_D - 12 || w == 8 || w == RECT_VERTICE_W - 10)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[7] * spectrumHeight;
					base = - m_spectrumRight[a[7]] * spectrumHeight/2;
				}
				else if (d == 12 || d == RECT_VERTICE_D - 14 || w == 10 || w == RECT_VERTICE_W - 12)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[6] * spectrumHeight;
					base = - m_spectrumRight[a[6]] * spectrumHeight/2;
				}
				else if (d == 14 || d == RECT_VERTICE_D - 16 || w == 12 || w == RECT_VERTICE_W - 14)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[5] * spectrumHeight;
					base = - m_spectrumRight[a[5]] * spectrumHeight/2;
				}
				else if (d == 16 || d == RECT_VERTICE_D - 18 || w == 14 || w == RECT_VERTICE_W - 16)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[4] * spectrumHeight;
					base = - m_spectrumRight[a[4]] * spectrumHeight/2;
				}
				else if (d == 18 || d == RECT_VERTICE_D - 20 || w == 16 || w == RECT_VERTICE_W - 18)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[3] * spectrumHeight;
					base = - m_spectrumRight[a[3]] * spectrumHeight/2;
				}
				else if (d == 20 || d == RECT_VERTICE_D - 22 || w == 18 || w == RECT_VERTICE_W - 20)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[2] * spectrumHeight;
					base = - m_spectrumRight[a[2]] * spectrumHeight/2;
				}
				else if (d == 22 || d == RECT_VERTICE_D - 24 || w == 20 || w == RECT_VERTICE_W - 22)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[1] * spectrumHeight;
					base = - m_spectrumRight[a[1]] * spectrumHeight/2;
				}
				else if (d == 24 || d == RECT_VERTICE_D - 26 || w == 22 || w == RECT_VERTICE_W - 24)
				{
					height = 1 / (float)RECT_VERTICE_W * width + m_spectrumLeft[0] * spectrumHeight;
					base = - m_spectrumRight[a[0]] * spectrumHeight/2;
				}

				if ((d > 0 && d < RECT_VERTICE_D - 2 && d%2 == 0) && (w%2 == 0))
				{
					//========= 6 vertices to form one sub-rectangle
					//base rectangle
					//1st vertex
					int vertex1 = ++currentVert;
					mRectTexture[vertex1 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex1 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex1 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex1 * 3 + 1] = base;
					mRectVertices[vertex1 * 3 + 2] = -halfDepth + (float)(d) / (float)RECT_VERTICE_D * depth;

					//2nd vertex
					int vertex2 = ++currentVert;
					mRectTexture[vertex2 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex2 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex2 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex2 * 3 + 1] = base;
					mRectVertices[vertex2 * 3 + 2] = -halfDepth + (float)(d + 1) / (float)RECT_VERTICE_D * depth;

					//3rd vertex
					int vertex3 = ++currentVert;
					mRectTexture[vertex3 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex3 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex3 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex3 * 3 + 1] = base;
					mRectVertices[vertex3 * 3 + 2] = -halfDepth + (float)(d + 1) / (float)RECT_VERTICE_D * depth;

					//4th vertex
					int vertex4 = ++currentVert;
					mRectTexture[vertex4 * 2] = mRectTexture[vertex3 * 2];
					mRectTexture[vertex4 * 2 + 1] = mRectTexture[vertex3 * 2 + 1];
					mRectVertices[vertex4 * 3] = mRectVertices[vertex3 * 3];
					mRectVertices[vertex4 * 3 + 1] = mRectVertices[vertex3 * 3 + 1];
					mRectVertices[vertex4 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];

					//5th vertex
					int vertex5 = ++currentVert;
					mRectTexture[vertex5 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex5 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex5 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex5 * 3 + 1] = base;
					mRectVertices[vertex5 * 3 + 2] = -halfDepth + (float)(d) / (float)RECT_VERTICE_D * depth;

					//6th vertex
					int vertex6 = ++currentVert;
					mRectTexture[vertex6 * 2] = mRectTexture[vertex1 * 2];
					mRectTexture[vertex6 * 2 + 1] = mRectTexture[vertex1 * 2 + 1];
					mRectVertices[vertex6 * 3] = mRectVertices[vertex1 * 3];
					mRectVertices[vertex6 * 3 + 1] = mRectVertices[vertex1 * 3 + 1];
					mRectVertices[vertex6 * 3 + 2] = mRectVertices[vertex1 * 3 + 2];

					//top rectangle
					//1st vertex
					int vertex7 = ++currentVert;
					mRectTexture[vertex7 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex7 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex7 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex7 * 3 + 1] = height;
					mRectVertices[vertex7 * 3 + 2] = -halfDepth + (float)(d) / (float)RECT_VERTICE_D * depth;

					//2nd vertex
					int vertex8 = ++currentVert;
					mRectTexture[vertex8 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex8 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex8 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex8 * 3 + 1] = height;
					mRectVertices[vertex8 * 3 + 2] = -halfDepth + (float)(d + 1) / (float)RECT_VERTICE_D * depth;

					//3rd vertex
					int vertex9 = ++currentVert;
					mRectTexture[vertex9 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex9 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex9 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex9 * 3 + 1] = height;
					mRectVertices[vertex9 * 3 + 2] = -halfDepth + (float)(d + 1) / (float)RECT_VERTICE_D * depth;

					//4th vertex
					int vertex10 = ++currentVert;
					mRectTexture[vertex10 * 2] = mRectTexture[vertex9 * 2];
					mRectTexture[vertex10 * 2 + 1] = mRectTexture[vertex9 * 2 + 1];
					mRectVertices[vertex10 * 3] = mRectVertices[vertex9 * 3];
					mRectVertices[vertex10 * 3 + 1] = mRectVertices[vertex9 * 3 + 1];
					mRectVertices[vertex10 * 3 + 2] = mRectVertices[vertex9 * 3 + 2];

					//5th vertex
					int vertex11 = ++currentVert;
					mRectTexture[vertex11 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex11 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex11 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
					mRectVertices[vertex11 * 3 + 1] = height;
					mRectVertices[vertex11 * 3 + 2] = -halfDepth + (float)(d) / (float)RECT_VERTICE_D * depth;

					//6th vertex
					int vertex12 = ++currentVert;
					mRectTexture[vertex12 * 2] = mRectTexture[vertex7 * 2];
					mRectTexture[vertex12 * 2 + 1] = mRectTexture[vertex7 * 2 + 1];
					mRectVertices[vertex12 * 3] = mRectVertices[vertex7 * 3];
					mRectVertices[vertex12 * 3 + 1] = mRectVertices[vertex7 * 3 + 1];
					mRectVertices[vertex12 * 3 + 2] = mRectVertices[vertex7 * 3 + 2];

					//front rectangle
					//1st vertex
					int vertex13 = ++currentVert;
					mRectTexture[vertex13 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex13 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex13 * 3] = mRectVertices[vertex1 * 3];
					mRectVertices[vertex13 * 3 + 1] = base;
					mRectVertices[vertex13 * 3 + 2] = mRectVertices[vertex1 * 3 + 2];

					//2nd vertex
					int vertex14 = ++currentVert;
					mRectTexture[vertex14 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex14 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex14 * 3] = mRectVertices[vertex7 * 3];
					mRectVertices[vertex14 * 3 + 1] = height;
					mRectVertices[vertex14 * 3 + 2] = mRectVertices[vertex7 * 3 + 2];

					//3rd vertex
					int vertex15 = ++currentVert;
					mRectTexture[vertex15 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex15 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex15 * 3] = mRectVertices[vertex11 * 3];
					mRectVertices[vertex15 * 3 + 1] = height;
					mRectVertices[vertex15 * 3 + 2] = mRectVertices[vertex11 * 3 + 2];

					//4th vertex
					int vertex16 = ++currentVert;
					mRectTexture[vertex16 * 2] = mRectTexture[vertex15 * 2];
					mRectTexture[vertex16 * 2 + 1] = mRectTexture[vertex15 * 2 + 1];
					mRectVertices[vertex16 * 3] = mRectVertices[vertex15 * 3];
					mRectVertices[vertex16 * 3 + 1] = mRectVertices[vertex15 * 3 + 1];
					mRectVertices[vertex16 * 3 + 2] = mRectVertices[vertex15 * 3 + 2];

					//5th vertex
					int vertex17 = ++currentVert;
					mRectTexture[vertex17 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex17 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex17 * 3] = mRectVertices[vertex5 * 3];
					mRectVertices[vertex17 * 3 + 1] = base;
					mRectVertices[vertex17 * 3 + 2] = mRectVertices[vertex5 * 3 + 2];

					//6th vertex
					int vertex18 = ++currentVert;
					mRectTexture[vertex18 * 2] = mRectTexture[vertex13 * 2];
					mRectTexture[vertex18 * 2 + 1] = mRectTexture[vertex13 * 2 + 1];
					mRectVertices[vertex18 * 3] = mRectVertices[vertex13 * 3];
					mRectVertices[vertex18 * 3 + 1] = mRectVertices[vertex13 * 3 + 1];
					mRectVertices[vertex18 * 3 + 2] = mRectVertices[vertex13 * 3 + 2];

					//back rectangle
					//1st vertex
					int vertex19 = ++currentVert;
					mRectTexture[vertex19 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex19 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex19 * 3] = mRectVertices[vertex2 * 3];
					mRectVertices[vertex19 * 3 + 1] = base;
					mRectVertices[vertex19 * 3 + 2] = mRectVertices[vertex2 * 3 + 2];

					//2nd vertex
					int vertex20 = ++currentVert;
					mRectTexture[vertex20 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex20 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex20 * 3] = mRectVertices[vertex8 * 3];
					mRectVertices[vertex20 * 3 + 1] = height;
					mRectVertices[vertex20 * 3 + 2] = mRectVertices[vertex8 * 3 + 2];

					//3rd vertex
					int vertex21 = ++currentVert;
					mRectTexture[vertex21 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex21 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex21 * 3] = mRectVertices[vertex9 * 3];
					mRectVertices[vertex21 * 3 + 1] = height;
					mRectVertices[vertex21 * 3 + 2] = mRectVertices[vertex9 * 3 + 2];

					//4th vertex
					int vertex22 = ++currentVert;
					mRectTexture[vertex22 * 2] = mRectTexture[vertex21 * 2];
					mRectTexture[vertex22 * 2 + 1] = mRectTexture[vertex21 * 2 + 1];
					mRectVertices[vertex22 * 3] = mRectVertices[vertex21 * 3];
					mRectVertices[vertex22 * 3 + 1] = mRectVertices[vertex21 * 3 + 1];
					mRectVertices[vertex22 * 3 + 2] = mRectVertices[vertex21 * 3 + 2];

					//5th vertex
					int vertex23 = ++currentVert;
					mRectTexture[vertex23 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex23 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex23 * 3] = mRectVertices[vertex3 * 3];
					mRectVertices[vertex23 * 3 + 1] = base;
					mRectVertices[vertex23 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];

					//6th vertex
					int vertex24 = ++currentVert;
					mRectTexture[vertex24 * 2] = mRectTexture[vertex19 * 2];
					mRectTexture[vertex24 * 2 + 1] = mRectTexture[vertex19 * 2 + 1];
					mRectVertices[vertex24 * 3] = mRectVertices[vertex19 * 3];
					mRectVertices[vertex24 * 3 + 1] = mRectVertices[vertex19 * 3 + 1];
					mRectVertices[vertex24 * 3 + 2] = mRectVertices[vertex19 * 3 + 2];

					//left rectangle
					//1st vertex
					int vertex25 = ++currentVert;
					mRectTexture[vertex25 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex25 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex25 * 3] = mRectVertices[vertex2 * 3];
					mRectVertices[vertex25 * 3 + 1] = base;
					mRectVertices[vertex25 * 3 + 2] = mRectVertices[vertex2 * 3 + 2];

					//2nd vertex
					int vertex26 = ++currentVert;
					mRectTexture[vertex26 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex26 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex26 * 3] = mRectVertices[vertex8 * 3];
					mRectVertices[vertex26 * 3 + 1] = height;
					mRectVertices[vertex26 * 3 + 2] = mRectVertices[vertex8 * 3 + 2];

					//3rd vertex
					int vertex27 = ++currentVert;
					mRectTexture[vertex27 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex27 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex27 * 3] = mRectVertices[vertex7 * 3];
					mRectVertices[vertex27 * 3 + 1] = height;
					mRectVertices[vertex27 * 3 + 2] = mRectVertices[vertex7 * 3 + 2];

					//4th vertex
					int vertex28 = ++currentVert;
					mRectTexture[vertex28 * 2] = mRectTexture[vertex27 * 2];
					mRectTexture[vertex28 * 2 + 1] = mRectTexture[vertex27 * 2 + 1];
					mRectVertices[vertex28 * 3] = mRectVertices[vertex27 * 3];
					mRectVertices[vertex28 * 3 + 1] = mRectVertices[vertex27 * 3 + 1];
					mRectVertices[vertex28 * 3 + 2] = mRectVertices[vertex27 * 3 + 2];

					//5th vertex
					int vertex29 = ++currentVert;
					mRectTexture[vertex29 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex29 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex29 * 3] = mRectVertices[vertex1 * 3];
					mRectVertices[vertex29 * 3 + 1] = base;
					mRectVertices[vertex29 * 3 + 2] = mRectVertices[vertex1 * 3 + 2];

					//6th vertex
					int vertex30 = ++currentVert;
					mRectTexture[vertex30 * 2] = mRectTexture[vertex25 * 2];
					mRectTexture[vertex30 * 2 + 1] = mRectTexture[vertex25 * 2 + 1];
					mRectVertices[vertex30 * 3] = mRectVertices[vertex25 * 3];
					mRectVertices[vertex30 * 3 + 1] = mRectVertices[vertex25 * 3 + 1];
					mRectVertices[vertex30 * 3 + 2] = mRectVertices[vertex25 * 3 + 2];

					//right rectangle
					//1st vertex
					int vertex31 = ++currentVert;
					mRectTexture[vertex31 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex31 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex31 * 3] = mRectVertices[vertex5 * 3];
					mRectVertices[vertex31 * 3 + 1] = base;
					mRectVertices[vertex31 * 3 + 2] = mRectVertices[vertex5 * 3 + 2];

					//2nd vertex
					int vertex32 = ++currentVert;
					mRectTexture[vertex32 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex32 * 2 + 1] = (float)(d) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex32 * 3] = mRectVertices[vertex11 * 3];
					mRectVertices[vertex32 * 3 + 1] = height;
					mRectVertices[vertex32 * 3 + 2] = mRectVertices[vertex11 * 3 + 2];

					//3rd vertex
					int vertex33 = ++currentVert;
					mRectTexture[vertex33 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex33 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex33 * 3] = mRectVertices[vertex9 * 3];
					mRectVertices[vertex33 * 3 + 1] = height;
					mRectVertices[vertex33 * 3 + 2] = mRectVertices[vertex9 * 3 + 2];

					//4th vertex
					int vertex34 = ++currentVert;
					mRectTexture[vertex34 * 2] = mRectTexture[vertex33 * 2];
					mRectTexture[vertex34 * 2 + 1] = mRectTexture[vertex33 * 2 + 1];
					mRectVertices[vertex34 * 3] = mRectVertices[vertex33 * 3];
					mRectVertices[vertex34 * 3 + 1] = mRectVertices[vertex33 * 3 + 1];
					mRectVertices[vertex34 * 3 + 2] = mRectVertices[vertex33 * 3 + 2];

					//5th vertex
					int vertex35 = ++currentVert;
					mRectTexture[vertex35 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;
					mRectTexture[vertex35 * 2 + 1] = (float)(d + 1) / (float)RECT_VERTICE_D * texMul;
					mRectVertices[vertex35 * 3] = mRectVertices[vertex3 * 3];
					mRectVertices[vertex35 * 3 + 1] = base;
					mRectVertices[vertex35 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];

					//6th vertex
					int vertex36 = ++currentVert;
					mRectTexture[vertex36 * 2] = mRectTexture[vertex31 * 2];
					mRectTexture[vertex36 * 2 + 1] = mRectTexture[vertex31 * 2 + 1];
					mRectVertices[vertex36 * 3] = mRectVertices[vertex31 * 3];
					mRectVertices[vertex36 * 3 + 1] = mRectVertices[vertex31 * 3 + 1];
					mRectVertices[vertex36 * 3 + 2] = mRectVertices[vertex31 * 3 + 2];
				}
			}
		}
	}

	void genDonut(float x, float y, float z)
	{
		glBegin(GL_TRIANGLES);

		int sides = 50;
		float radius = 0.3f;

		float prevDeltaX = 0.0f;
		float prevDeltaY = 0.0f;
		float prevDeltaZ = 0.0f;

		float curDeltaX = sin(0 * (M_2PI / sides)) * 4;
		float curDeltaY = 0.0f;
		float curDeltaZ = cos(0 * (M_2PI / sides)) * 4;

		float theta = 0.0f;
		float nextTheta = 0.0f;

		int donutCurrentVertex = -1;

		for (int k = 1; k <= sides; k++)
		{
			prevDeltaX = curDeltaX;
			prevDeltaY = curDeltaY;
			prevDeltaZ = curDeltaZ;
			curDeltaX = sin(k * (M_2PI / sides)) * 4;
			curDeltaY = 0;// sin(k * (M_2PI / sides));
			curDeltaZ = cos(k * (M_2PI / sides)) * 4;

			curDeltaX *= x;
			curDeltaY *= y;
			curDeltaZ *= z;

			for (int i = 0; i < sides; i++)
			{
				theta = i * (M_2PI / sides);
				nextTheta = (i + 1)*(M_2PI / sides);

				//1st vertex
				int vertex1 = ++donutCurrentVertex;
				mDonutTexture[vertex1 * 2] = (float)(i) / (float)RECT_VERTICE_W * texMul;
				mDonutTexture[vertex1 * 2 + 1] = (float)(k) / (float)RECT_VERTICE_D * texMul;
				mDonutVertices[vertex1 * 3] = curDeltaX;
				mDonutVertices[vertex1 * 3 + 1] = radius * sin(theta) + curDeltaY;
				mDonutVertices[vertex1 * 3 + 2] = radius * cos(theta) + curDeltaZ;

				//2nd vertex
				int vertex2 = ++donutCurrentVertex;
				mDonutTexture[vertex2 * 2] = (float)(i + 1) / (float)RECT_VERTICE_W * texMul;
				mDonutTexture[vertex2 * 2 + 1] = (float)(k) / (float)RECT_VERTICE_D * texMul;
				mDonutVertices[vertex2 * 3] = prevDeltaX;
				mDonutVertices[vertex2 * 3 + 1] = radius * sin(theta) + prevDeltaY;
				mDonutVertices[vertex2 * 3 + 2] = radius * cos(theta) + prevDeltaZ;

				//3rd vertex
				int vertex3 = ++donutCurrentVertex;
				mDonutTexture[vertex3 * 2] = (float)(i + 1) / (float)RECT_VERTICE_W * texMul;
				mDonutTexture[vertex3 * 2 + 1] = (float)(k + 1) / (float)RECT_VERTICE_D * texMul;
				mDonutVertices[vertex3 * 3] = prevDeltaX;
				mDonutVertices[vertex3 * 3 + 1] = radius * sin(nextTheta) + prevDeltaY;
				mDonutVertices[vertex3 * 3 + 2] = radius * cos(nextTheta) + prevDeltaZ;

				//4th vertex
				int vertex4 = ++donutCurrentVertex;
				mDonutTexture[vertex4 * 2] = mDonutTexture[vertex3 * 2];
				mDonutTexture[vertex4 * 2 + 1] = mDonutTexture[vertex3 * 2 + 1];
				mDonutVertices[vertex4 * 3] = prevDeltaX;
				mDonutVertices[vertex4 * 3 + 1] = radius * sin(nextTheta) + prevDeltaY;
				mDonutVertices[vertex4 * 3 + 2] = radius * cos(nextTheta) + prevDeltaZ;

				//5th vertex
				int vertex5 = ++donutCurrentVertex;
				mDonutTexture[vertex5 * 2] = (float)(i) / (float)RECT_VERTICE_W * texMul;
				mDonutTexture[vertex5 * 2 + 1] = (float)(k + 1) / (float)RECT_VERTICE_D * texMul;
				mDonutVertices[vertex5 * 3] = curDeltaX;
				mDonutVertices[vertex5 * 3 + 1] = radius * sin(theta) + curDeltaY;
				mDonutVertices[vertex5 * 3 + 2] = radius * cos(theta) + curDeltaZ;

				//6th vertex
				int vertex6 = ++donutCurrentVertex;
				mDonutTexture[vertex6 * 2] = mDonutTexture[vertex1 * 2];
				mDonutTexture[vertex6 * 2 + 1] = mDonutTexture[vertex1 * 2 + 1];
				mDonutVertices[vertex6 * 3] = curDeltaX;
				mDonutVertices[vertex6 * 3 + 1] = radius * sin(nextTheta) + curDeltaY;
				mDonutVertices[vertex6 * 3 + 2] = radius * cos(nextTheta) + curDeltaZ;

			}

		}

		glEnd();
	}

	// not using yet
	void genBox(float startingY)
	{
		const float width = 5.0f;
		const float depth = 5.0f;
		const float halfWidth = 0;
		const float halfDepth = 0;
		float height = 1 / (float)RECT_VERTICE_W * width;
		float base = startingY;

		int currentVert = -1;

		// ======== 6 vertices to form one sub - rectangle
			//base rectangle
			//1st vertex
		int vertex1 = ++currentVert;
		mBoxTexture[vertex1 * 2] = 0 * texMul;
		mBoxTexture[vertex1 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex1 * 3] = -halfWidth + 0 * width;
		mBoxVertices[vertex1 * 3 + 1] = base;
		mBoxVertices[vertex1 * 3 + 2] = -halfDepth + 0 * depth;

		//2nd vertex
		int vertex2 = ++currentVert;
		mBoxTexture[vertex2 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex2 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex2 * 3] = -halfWidth + 0 * width;
		mBoxVertices[vertex2 * 3 + 1] = base;
		mBoxVertices[vertex2 * 3 + 2] = -halfDepth + 1 / (float)RECT_VERTICE_D * depth;

		//3rd vertex
		int vertex3 = ++currentVert;
		mBoxTexture[vertex3 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex3 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex3 * 3] = -halfWidth + 1 / (float)RECT_VERTICE_W * width;
		mBoxVertices[vertex3 * 3 + 1] = base;
		mBoxVertices[vertex3 * 3 + 2] = -halfDepth + 1 / (float)RECT_VERTICE_D * depth;

		//4th vertex
		int vertex4 = ++currentVert;
		mBoxTexture[vertex4 * 2] = mBoxTexture[vertex3 * 2];
		mBoxTexture[vertex4 * 2 + 1] = mBoxTexture[vertex3 * 2 + 1];
		mBoxVertices[vertex4 * 3] = mBoxVertices[vertex3 * 3];
		mBoxVertices[vertex4 * 3 + 1] = mBoxVertices[vertex3 * 3 + 1];
		mBoxVertices[vertex4 * 3 + 2] = mBoxVertices[vertex3 * 3 + 2];

		//5th vertex
		int vertex5 = ++currentVert;
		mBoxTexture[vertex5 * 2] = 0* texMul;
		mBoxTexture[vertex5 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex5 * 3] = -halfWidth + 1 / (float)RECT_VERTICE_W * width;
		mBoxVertices[vertex5 * 3 + 1] = base;
		mBoxVertices[vertex5 * 3 + 2] = -halfDepth + 0 * depth;

		//6th vertex
		int vertex6 = ++currentVert;
		mBoxTexture[vertex6 * 2] = mBoxTexture[vertex1 * 2];
		mBoxTexture[vertex6 * 2 + 1] = mBoxTexture[vertex1 * 2 + 1];
		mBoxVertices[vertex6 * 3] = mBoxVertices[vertex1 * 3];
		mBoxVertices[vertex6 * 3 + 1] = mBoxVertices[vertex1 * 3 + 1];
		mBoxVertices[vertex6 * 3 + 2] = mBoxVertices[vertex1 * 3 + 2];

		//top rectangle
		//1st vertex
		int vertex7 = ++currentVert;
		mBoxTexture[vertex7 * 2] = 0 * texMul;
		mBoxTexture[vertex7 * 2 + 1] = 0* texMul;
		mBoxVertices[vertex7 * 3] = -halfWidth + 0 * width;
		mBoxVertices[vertex7 * 3 + 1] = height;
		mBoxVertices[vertex7 * 3 + 2] = -halfDepth + 0 * depth;

		//2nd vertex
		int vertex8 = ++currentVert;
		mBoxTexture[vertex8 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex8 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex8 * 3] = -halfWidth + 0 * width;
		mBoxVertices[vertex8 * 3 + 1] = height;
		mBoxVertices[vertex8 * 3 + 2] = -halfDepth + 1 / (float)RECT_VERTICE_D * depth;

		//3rd vertex
		int vertex9 = ++currentVert;
		mBoxTexture[vertex9 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex9 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex9 * 3] = -halfWidth + 1 / (float)RECT_VERTICE_W * width;
		mBoxVertices[vertex9 * 3 + 1] = height;
		mBoxVertices[vertex9 * 3 + 2] = -halfDepth + 1 / (float)RECT_VERTICE_D * depth;

		//4th vertex
		int vertex10 = ++currentVert;
		mBoxTexture[vertex10 * 2] = mBoxTexture[vertex9 * 2];
		mBoxTexture[vertex10 * 2 + 1] = mBoxTexture[vertex9 * 2 + 1];
		mBoxVertices[vertex10 * 3] = mBoxVertices[vertex9 * 3];
		mBoxVertices[vertex10 * 3 + 1] = mBoxVertices[vertex9 * 3 + 1];
		mBoxVertices[vertex10 * 3 + 2] = mBoxVertices[vertex9 * 3 + 2];

		//5th vertex
		int vertex11 = ++currentVert;
		mBoxTexture[vertex11 * 2] = 0* texMul;
		mBoxTexture[vertex11 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex11 * 3] = -halfWidth + 1 / (float)RECT_VERTICE_W * width;
		mBoxVertices[vertex11 * 3 + 1] = height;
		mBoxVertices[vertex11 * 3 + 2] = -halfDepth + 0 * depth;

		//6th vertex
		int vertex12 = ++currentVert;
		mBoxTexture[vertex12 * 2] = mBoxTexture[vertex7 * 2];
		mBoxTexture[vertex12 * 2 + 1] = mBoxTexture[vertex7 * 2 + 1];
		mBoxVertices[vertex12 * 3] = mBoxVertices[vertex7 * 3];
		mBoxVertices[vertex12 * 3 + 1] = mBoxVertices[vertex7 * 3 + 1];
		mBoxVertices[vertex12 * 3 + 2] = mBoxVertices[vertex7 * 3 + 2];

		//front rectangle
		//1st vertex
		int vertex13 = ++currentVert;
		mBoxTexture[vertex13 * 2] = 0 * texMul;
		mBoxTexture[vertex13 * 2 + 1] = 0* texMul;
		mBoxVertices[vertex13 * 3] = mBoxVertices[vertex1 * 3];
		mBoxVertices[vertex13 * 3 + 1] = base;
		mBoxVertices[vertex13 * 3 + 2] = mBoxVertices[vertex1 * 3 + 2];

		//2nd vertex
		int vertex14 = ++currentVert;
		mBoxTexture[vertex14 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex14 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex14 * 3] = mBoxVertices[vertex7 * 3];
		mBoxVertices[vertex14 * 3 + 1] = height;
		mBoxVertices[vertex14 * 3 + 2] = mBoxVertices[vertex7 * 3 + 2];

		//3rd vertex
		int vertex15 = ++currentVert;
		mBoxTexture[vertex15 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex15 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex15 * 3] = mBoxVertices[vertex11 * 3];
		mBoxVertices[vertex15 * 3 + 1] = height;
		mBoxVertices[vertex15 * 3 + 2] = mBoxVertices[vertex11 * 3 + 2];

		//4th vertex
		int vertex16 = ++currentVert;
		mBoxTexture[vertex16 * 2] = mBoxTexture[vertex15 * 2];
		mBoxTexture[vertex16 * 2 + 1] = mBoxTexture[vertex15 * 2 + 1];
		mBoxVertices[vertex16 * 3] = mBoxVertices[vertex15 * 3];
		mBoxVertices[vertex16 * 3 + 1] = mBoxVertices[vertex15 * 3 + 1];
		mBoxVertices[vertex16 * 3 + 2] = mBoxVertices[vertex15 * 3 + 2];

		//5th vertex
		int vertex17 = ++currentVert;
		mBoxTexture[vertex17 * 2] = 0 * texMul;
		mBoxTexture[vertex17 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex17 * 3] = mBoxVertices[vertex5 * 3];
		mBoxVertices[vertex17 * 3 + 1] = base;
		mBoxVertices[vertex17 * 3 + 2] = mBoxVertices[vertex5 * 3 + 2];

		//6th vertex
		int vertex18 = ++currentVert;
		mBoxTexture[vertex18 * 2] = mBoxTexture[vertex13 * 2];
		mBoxTexture[vertex18 * 2 + 1] = mBoxTexture[vertex13 * 2 + 1];
		mBoxVertices[vertex18 * 3] = mBoxVertices[vertex13 * 3];
		mBoxVertices[vertex18 * 3 + 1] = mBoxVertices[vertex13 * 3 + 1];
		mBoxVertices[vertex18 * 3 + 2] = mBoxVertices[vertex13 * 3 + 2];

		//back rectangle
		//1st vertex
		int vertex19 = ++currentVert;
		mBoxTexture[vertex19 * 2] = 0 * texMul;
		mBoxTexture[vertex19 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex19 * 3] = mBoxVertices[vertex2 * 3];
		mBoxVertices[vertex19 * 3 + 1] = base;
		mBoxVertices[vertex19 * 3 + 2] = mBoxVertices[vertex2 * 3 + 2];

		//2nd vertex
		int vertex20 = ++currentVert;
		mBoxTexture[vertex20 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex20 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex20 * 3] = mBoxVertices[vertex8 * 3];
		mBoxVertices[vertex20 * 3 + 1] = height;
		mBoxVertices[vertex20 * 3 + 2] = mBoxVertices[vertex8 * 3 + 2];

		//3rd vertex
		int vertex21 = ++currentVert;
		mBoxTexture[vertex21 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex21 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex21 * 3] = mBoxVertices[vertex9 * 3];
		mBoxVertices[vertex21 * 3 + 1] = height;
		mBoxVertices[vertex21 * 3 + 2] = mBoxVertices[vertex9 * 3 + 2];

		//4th vertex
		int vertex22 = ++currentVert;
		mBoxTexture[vertex22 * 2] = mBoxTexture[vertex21 * 2];
		mBoxTexture[vertex22 * 2 + 1] = mBoxTexture[vertex21 * 2 + 1];
		mBoxVertices[vertex22 * 3] = mBoxVertices[vertex21 * 3];
		mBoxVertices[vertex22 * 3 + 1] = mBoxVertices[vertex21 * 3 + 1];
		mBoxVertices[vertex22 * 3 + 2] = mBoxVertices[vertex21 * 3 + 2];

		//5th vertex
		int vertex23 = ++currentVert;
		mBoxTexture[vertex23 * 2] = 0 * texMul;
		mBoxTexture[vertex23 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex23 * 3] = mBoxVertices[vertex3 * 3];
		mBoxVertices[vertex23 * 3 + 1] = base;
		mBoxVertices[vertex23 * 3 + 2] = mBoxVertices[vertex3 * 3 + 2];

		//6th vertex
		int vertex24 = ++currentVert;
		mBoxTexture[vertex24 * 2] = mBoxTexture[vertex19 * 2];
		mBoxTexture[vertex24 * 2 + 1] = mBoxTexture[vertex19 * 2 + 1];
		mBoxVertices[vertex24 * 3] = mBoxVertices[vertex19 * 3];
		mBoxVertices[vertex24 * 3 + 1] = mBoxVertices[vertex19 * 3 + 1];
		mBoxVertices[vertex24 * 3 + 2] = mBoxVertices[vertex19 * 3 + 2];

		//left rectangle
		//1st vertex
		int vertex25 = ++currentVert;
		mBoxTexture[vertex25 * 2] = 0 * texMul;
		mBoxTexture[vertex25 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex25 * 3] = mBoxVertices[vertex2 * 3];
		mBoxVertices[vertex25 * 3 + 1] = base;
		mBoxVertices[vertex25 * 3 + 2] = mBoxVertices[vertex2 * 3 + 2];

		//2nd vertex
		int vertex26 = ++currentVert;
		mBoxTexture[vertex26 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex26 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex26 * 3] = mBoxVertices[vertex8 * 3];
		mBoxVertices[vertex26 * 3 + 1] = height;
		mBoxVertices[vertex26 * 3 + 2] = mBoxVertices[vertex8 * 3 + 2];

		//3rd vertex
		int vertex27 = ++currentVert;
		mBoxTexture[vertex27 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex27 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex27 * 3] = mBoxVertices[vertex7 * 3];
		mBoxVertices[vertex27 * 3 + 1] = height;
		mBoxVertices[vertex27 * 3 + 2] = mBoxVertices[vertex7 * 3 + 2];

		//4th vertex
		int vertex28 = ++currentVert;
		mBoxTexture[vertex28 * 2] = mBoxTexture[vertex27 * 2];
		mBoxTexture[vertex28 * 2 + 1] = mBoxTexture[vertex27 * 2 + 1];
		mBoxVertices[vertex28 * 3] = mBoxVertices[vertex27 * 3];
		mBoxVertices[vertex28 * 3 + 1] = mBoxVertices[vertex27 * 3 + 1];
		mBoxVertices[vertex28 * 3 + 2] = mBoxVertices[vertex27 * 3 + 2];

		//5th vertex
		int vertex29 = ++currentVert;
		mBoxTexture[vertex29 * 2] = 0 * texMul;
		mBoxTexture[vertex29 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex29 * 3] = mBoxVertices[vertex1 * 3];
		mBoxVertices[vertex29 * 3 + 1] = base;
		mBoxVertices[vertex29 * 3 + 2] = mBoxVertices[vertex1 * 3 + 2];

		//6th vertex
		int vertex30 = ++currentVert;
		mBoxTexture[vertex30 * 2] = mBoxTexture[vertex25 * 2];
		mBoxTexture[vertex30 * 2 + 1] = mBoxTexture[vertex25 * 2 + 1];
		mBoxVertices[vertex30 * 3] = mBoxVertices[vertex25 * 3];
		mBoxVertices[vertex30 * 3 + 1] = mBoxVertices[vertex25 * 3 + 1];
		mBoxVertices[vertex30 * 3 + 2] = mBoxVertices[vertex25 * 3 + 2];

		//right rectangle
		//1st vertex
		int vertex31 = ++currentVert;
		mBoxTexture[vertex31 * 2] = 0 * texMul;
		mBoxTexture[vertex31 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex31 * 3] = mBoxVertices[vertex5 * 3];
		mBoxVertices[vertex31 * 3 + 1] = base;
		mBoxVertices[vertex31 * 3 + 2] = mBoxVertices[vertex5 * 3 + 2];

		//2nd vertex
		int vertex32 = ++currentVert;
		mBoxTexture[vertex32 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex32 * 2 + 1] = 0 * texMul;
		mBoxVertices[vertex32 * 3] = mBoxVertices[vertex11 * 3];
		mBoxVertices[vertex32 * 3 + 1] = height;
		mBoxVertices[vertex32 * 3 + 2] = mBoxVertices[vertex11 * 3 + 2];

		//3rd vertex
		int vertex33 = ++currentVert;
		mBoxTexture[vertex33 * 2] = 1 / (float)RECT_VERTICE_W * texMul;
		mBoxTexture[vertex33 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex33 * 3] = mBoxVertices[vertex9 * 3];
		mBoxVertices[vertex33 * 3 + 1] = height;
		mBoxVertices[vertex33 * 3 + 2] = mBoxVertices[vertex9 * 3 + 2];

		//4th vertex
		int vertex34 = ++currentVert;
		mBoxTexture[vertex34 * 2] = mBoxTexture[vertex33 * 2];
		mBoxTexture[vertex34 * 2 + 1] = mBoxTexture[vertex33 * 2 + 1];
		mBoxVertices[vertex34 * 3] = mBoxVertices[vertex33 * 3];
		mBoxVertices[vertex34 * 3 + 1] = mBoxVertices[vertex33 * 3 + 1];
		mBoxVertices[vertex34 * 3 + 2] = mBoxVertices[vertex33 * 3 + 2];

		//5th vertex
		int vertex35 = ++currentVert;
		mBoxTexture[vertex35 * 2] = 0 * texMul;
		mBoxTexture[vertex35 * 2 + 1] = 1 / (float)RECT_VERTICE_D * texMul;
		mBoxVertices[vertex35 * 3] = mBoxVertices[vertex3 * 3];
		mBoxVertices[vertex35 * 3 + 1] = base;
		mBoxVertices[vertex35 * 3 + 2] = mBoxVertices[vertex3 * 3 + 2];

		//6th vertex
		int vertex36 = ++currentVert;
		mBoxTexture[vertex36 * 2] = mBoxTexture[vertex31 * 2];
		mBoxTexture[vertex36 * 2 + 1] = mBoxTexture[vertex31 * 2 + 1];
		mBoxVertices[vertex36 * 3] = mBoxVertices[vertex31 * 3];
		mBoxVertices[vertex36 * 3 + 1] = mBoxVertices[vertex31 * 3 + 1];
		mBoxVertices[vertex36 * 3 + 2] = mBoxVertices[vertex31 * 3 + 2];
	}

	void drawWorldOriginLines(const Matrix& viewMatrix)
	{
		// draw axis.
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
	}

	void drawCastle()
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
		// drawing transparent objects here
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		//glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		genPlane();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, mRectTexture);
		glVertexPointer(3, GL_FLOAT, 0, mRectVertices);
		glDrawArrays(GL_TRIANGLES, 0, CUBE_VERTEX_COUNT);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDepthMask(true);
		glDisable(GL_TEXTURE_2D);
	//	glDisable(GL_BLEND);
	}

	void drawDonut()
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
		// drawing transparent objects here
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		//glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		genDonut(1, 1, 1);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, mDonutTexture);
		glVertexPointer(3, GL_FLOAT, 0, mDonutVertices);
		glDrawArrays(GL_TRIANGLES, 0, DONUT_VERTEX_COUNT);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDepthMask(true);
		glDisable(GL_TEXTURE_2D);
	}

	// not using yet
	void drawBox()
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
		// drawing transparent objects here
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		//glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		genBox(0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, mBoxTexture);
		glVertexPointer(3, GL_FLOAT, 0, mBoxVertices);
		glDrawArrays(GL_TRIANGLES, 0, BOX_VERTEX_COUNT);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDepthMask(true);
		glDisable(GL_TEXTURE_2D);
	}

	void draw(const Matrix& viewMatrix)
	{
		// draw axis.
		drawWorldOriginLines(viewMatrix);
		m_rotation += 0.1f;
		Matrix rotate1 = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, 0.0f, 0.0f);

		// NOTE on OpenGL Matrix model:
		// Screen = Proj * View * Model
		// Model = TransformA(3rd) * TransformB(2nd) * TransformC(1st) (Trasnform could be Rotate, Scale, Translate, etc)

		// perform model transformation
		Matrix modelMatrix = translate1 * rotate1;

		// convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		UpdateFmod();
		drawCastle();

		donut_rotation += 0.2f;

		if (donut_rotation >= 360)
		{
			donut_rotation = 0;
		}

		Matrix rotate2 = Matrix::makeRotateMatrix(donut_rotation, Vector(1.0f, 0.0, 1.0f));

		// perform model transformation
		Matrix modelMatrix2 = rotate2;

		// convert model space to view space
		viewSpaceMatrix = viewMatrix * modelMatrix2;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		drawDonut();

		donut_rotation2 -= 0.2f;
		if (donut_rotation2 <= -360)
		{
			donut_rotation2 = 0;
		}

		Matrix rotate3 = Matrix::makeRotateMatrix(donut_rotation2, Vector(1.0f, 0.0, 1.0f));
		// perform model transformation
		Matrix modelMatrix3 = rotate3;
		// convert model space to view space
		viewSpaceMatrix = viewMatrix * modelMatrix3;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		drawDonut();

		donut_rotation3 += 0.5f + m_spectrumLeft[0];
		if (donut_rotation3 >= 360)
		{
			donut_rotation3 = 0;
		}

		Matrix rotate4 = Matrix::makeRotateMatrix(donut_rotation3, Vector(1.0f, 0.0, 0.0f));
		// perform model transformation
		Matrix modelMatrix4 = rotate4;
		// convert model space to view space
		viewSpaceMatrix = viewMatrix * modelMatrix4;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

		drawDonut();

		if (aCounter >= 11)
		{
			aCounter = 0;
		}

		if (aCounter == 0)
		{
			ACount(1); 
			aCounter++;
		}
		else if (aCounter == 1)
		{
			ACount(2);
			aCounter++;
		}
		else if (aCounter == 2)
		{
			ACount(3);
			aCounter++;
		}
		else if (aCounter == 3)
		{
			ACount(4);
			aCounter++;
		}
		else if (aCounter == 4)
		{
			ACount(5);
			aCounter++;
		}
		else if (aCounter == 5)
		{
			ACount(6);
			aCounter++;
		}
		else if (aCounter == 6)
		{
			ACount(7);
			aCounter++;
		}
		else if (aCounter == 7)
		{
			ACount(8);
			aCounter++;
		}
		else if (aCounter == 8)
		{
			ACount(9);
			aCounter++;
		}
		else if (aCounter == 9)
		{
			ACount(10);
			aCounter++;
		}
		else if (aCounter == 10)
		{
			ACount(11);
			aCounter++;
		}
		else if (aCounter == 11)
		{
			ACount(12);
			aCounter++;
		}

		srand(time(NULL));

		box_rotation += 0.1;

		if (box_rotation >= 360)
		{
			box_rotation = 0;
		}

		for (int i=0; i<1000; i++)
		{
			translateValueX = rand() % 100 - 100/2;
			translateValueY = rand() % 100 - 100/2;
			translateValueZ = rand() % 100 - 100/2;

			Matrix translate2 = Matrix::makeTranslationMatrix(translateValueX, translateValueY, translateValueZ);
			Matrix boxRotate = Matrix::makeRotateMatrix(box_rotation, Vector(1.0f, 1.0, 1.0f));
			// perform model transformation
			Matrix modelMatrix5 = boxRotate * rotate1 * translate2;
			// convert model space to view space
			viewSpaceMatrix = viewMatrix * modelMatrix5;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

			drawBox();
		}
	}
};

#endif
