#define GLFW_INCLUDE_ES2 1
#define GLFW_DLL 1
//#define GLFW_EXPOSE_NATIVE_WIN32 1
//#define GLFW_EXPOSE_NATIVE_EGL 1

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream> 
#include "angle_util/Matrix.h"
#include "angle_util/geometry_utils.h"
#include "bitmap.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

#define TEXTURE_COUNT 6

GLint GprogramID = -1;
GLuint GtextureID[TEXTURE_COUNT];


GLuint Gframebuffer;
GLuint GdepthRenderbuffer;

GLuint GfullscreenTexture;
GLuint GfullscreenTexture2;
GLuint highPassTexture;
GLuint highPassTexture2;

GLFWwindow* window;

Matrix4 gPerspectiveMatrix;
Matrix4 gViewMatrix;

int randNum[20];

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

GLuint LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char infoLog[4096];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error compiling shader:\n%s\n", infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint LoadShaderFromFile(GLenum shaderType, std::string path)
{
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	if (sourceFile)
	{
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		const GLchar* shaderSource = shaderString.c_str();

		return LoadShader(shaderType, shaderSource);
	}
	else
		printf("Unable to open file %s\n", path.c_str());

	return shaderID;
}

void loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

int Init(void)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	//load textures
	glGenTextures(TEXTURE_COUNT, GtextureID);
	loadTexture("../media/rocks.bmp", GtextureID[0]);
	loadTexture("../media/glass.bmp", GtextureID[1]);
	loadTexture("../media/win8.bmp", GtextureID[2]);
	loadTexture("../media/fury_nano2.bmp", GtextureID[3]);
	loadTexture("../media/rainbow.bmp", GtextureID[4]);
	loadTexture("../media/Skybox.bmp", GtextureID[5]);
	//====



	//==================== set up frame buffer, render buffer, and create an empty texture for blurring purpose
	// create a new FBO
	glGenFramebuffers(1, &Gframebuffer);

	// create a new empty texture for rendering original scene (screenshot)
	glGenTextures(1, &GfullscreenTexture);
	glBindTexture(GL_TEXTURE_2D, GfullscreenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// create and bind renderbuffer, and create a 16-bit depth buffer
	glGenRenderbuffers(1, &GdepthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, GdepthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
	//=================================

	glGenTextures(1, &GfullscreenTexture2);
	glBindTexture(GL_TEXTURE_2D, GfullscreenTexture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// create and bind renderbuffer, and create a 16-bit depth buffer
	glGenRenderbuffers(1, &GdepthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, GdepthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);

	//=================================

	glGenTextures(1, &highPassTexture);
	glBindTexture(GL_TEXTURE_2D, highPassTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// create and bind renderbuffer, and create a 16-bit depth buffer
	glGenRenderbuffers(1, &GdepthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, GdepthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
	//=================================
	//=================================

	glGenTextures(1, &highPassTexture2);
	glBindTexture(GL_TEXTURE_2D, highPassTexture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// create and bind renderbuffer, and create a 16-bit depth buffer
	glGenRenderbuffers(1, &GdepthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, GdepthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
	//=================================


	fragmentShader = LoadShaderFromFile(GL_VERTEX_SHADER, "../vertexShader1.vert");
	vertexShader = LoadShaderFromFile(GL_FRAGMENT_SHADER, "../fragmentShader1.frag");

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	glBindAttribLocation(programObject, 0, "vPosition");
	glBindAttribLocation(programObject, 1, "vColor");
	glBindAttribLocation(programObject, 2, "vTexCoord");

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char infoLog[1024];
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);
		}

		glDeleteProgram(programObject);
		return 0;
	}

	// Store the program object
	GprogramID = programObject;


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//initialize matrices
	gPerspectiveMatrix = Matrix4::perspective(60.0f,
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.5f, 3000.0f);

	gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -2.0f));

	// rand number for cube position
	for (int n=0; n<20; n++)
	{
		randNum[n] = rand() % 12 - 6;
	}

	return 1;
}


void UpdateCamera(void)
{
	static float yaw = 0.0f;
	static float pitch = 0.0f;
	static float distance = 2.5f;

	if (glfwGetKey(window, 'A')) pitch -= 1.0f;
	if (glfwGetKey(window, 'D')) pitch += 1.0f;
	if (glfwGetKey(window, 'W')) yaw -= 1.0f;
	if (glfwGetKey(window, 'S')) yaw += 1.0f;

	if (glfwGetKey(window, 'R'))
	{
		distance -= 0.06f;
		if (distance < 1.0f)
			distance = 1.0f;
	}
	if (glfwGetKey(window, 'F')) distance += 0.06f;

	gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -distance)) *
		Matrix4::rotate(yaw, Vector3(1.0f, 0.0f, 0.0f)) *
		Matrix4::rotate(pitch, Vector3(0.0f, 1.0f, 0.0f));
}

void DrawSquare(GLuint texture)
{
	static GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,
								-1.0f, -1.0f, 0.0f,
								1.0f, -1.0f,  0.0f,
								1.0f,  -1.0f, 0.0f,
								1.0f, 1.0f, 0.0f,
								-1.0f, 1.0f,  0.0f };


	static GLfloat vColors[] = { 1.0f,  0.0f, 0.0f, 1.0f,
								 0.0f, 1.0f, 0.0f, 1.0f,
								 0.0f, 0.0f,  1.0f, 1.0f,
								 0.0f,  0.0f, 1.0f, 1.0f,
								 1.0f, 1.0f, 0.0f, 1.0f,
								 1.0f, 0.0f,  0.0f, 1.0f };

	static GLfloat vTexCoords[] = { 0.0f,  1.0f,
									 0.0f, 0.0f,
									 1.0f, 0.0f,
									 1.0f,  0.0f,
									 1.0f, 1.0f,
									 0.0f, 1.0f };


	glBindTexture(GL_TEXTURE_2D, texture);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void DrawPillar(GLuint texture, float size)
{
	float height = size; // 0.02
	float startY = -0.3f;
	int segment = 20;

	static GLfloat pVertices[10000];
	static GLfloat pColors[10000];
	static GLfloat pTexCoords[10000];
	static int p; //vertex count

	for (int c=0; c<10000; c++)
	{
		pColors[c] = 1.0f;
	}

	for (int t = 0; t < 10000; t+=12)
	{
		pTexCoords[t] = 0.0f;
		pTexCoords[t + 1] = 1.0f;
		pTexCoords[t + 2] = 0.0f;
		pTexCoords[t + 3] = 0.0f;
		pTexCoords[t + 4] = 1.0f;
		pTexCoords[t + 5] = 0.0f;
		pTexCoords[t + 6] = 1.0f;
		pTexCoords[t + 7] = 0.0f;
		pTexCoords[t + 8] = 1.0f;
		pTexCoords[t + 9] = 1.0f;
		pTexCoords[t + 10] = 0.0f;
		pTexCoords[t + 11] = 1.0f;
	}

	for (int i = 0; i < segment; i++)
	{
		if (i==0)
		{
			p = 0;
		}

		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;

		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;

		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = -size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;

		pVertices[p] = size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
		pVertices[p] = size; pVertices[p + 1] = -height + startY + i * height*2.0f; pVertices[p + 2] = -size; p += 3;
	}

	glBindTexture(GL_TEXTURE_2D, texture);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, pVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, pColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, pTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// total of vVertices divide by 3 (3 vertices form a triangle)
	glDrawArrays(GL_TRIANGLES, 0, p);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void DrawCube(GLuint texture, float cubeSize)
{
	float boxSize = cubeSize;

	static GLfloat vVertices[] = {
		// toward camera
		-boxSize,  boxSize, boxSize, // left top
		-boxSize, -boxSize, boxSize, // left bottom
		boxSize, -boxSize,  boxSize, // right bottom
		boxSize,  -boxSize, boxSize, // right bottom
		boxSize, boxSize, boxSize, // right top
		-boxSize, boxSize,  boxSize, // left top

		// top
		-boxSize,  boxSize, -boxSize, // top left back
		-boxSize, boxSize, boxSize, // top left front
		boxSize, boxSize,  boxSize, // top right front
		boxSize, boxSize,  boxSize, // top right front
		boxSize, boxSize, -boxSize, // top right back
		-boxSize,  boxSize, -boxSize, // top left back

		// back 
		-boxSize,  boxSize, -boxSize, // top left
		-boxSize, -boxSize, -boxSize, // bottom left
		boxSize, -boxSize,  -boxSize, // bottom right
		boxSize,  -boxSize, -boxSize, // bottom right
		boxSize, boxSize, -boxSize, // top right
		-boxSize, boxSize,  -boxSize, // top left

		// bottom
		-boxSize,  -boxSize, -boxSize, // bottom left back
		-boxSize, -boxSize, boxSize, // bottom left front
		boxSize, -boxSize,  boxSize, // bottom right front
		boxSize, -boxSize,  boxSize, // bottom right front
		boxSize, -boxSize, -boxSize, // bottom right back
		-boxSize,  -boxSize, -boxSize, // bottom left back

		// left
		-boxSize, boxSize, -boxSize, // top left back
		-boxSize,  -boxSize, -boxSize, // bottom left back
		-boxSize, -boxSize, boxSize, // bottom left front
		-boxSize, -boxSize, boxSize, // bottom left front
		-boxSize, boxSize,  boxSize, // top left front
		-boxSize, boxSize, -boxSize, // top left back

		// right
		boxSize, boxSize, -boxSize, // top left back
		boxSize,  -boxSize, -boxSize, // bottom left back
		boxSize, -boxSize, boxSize, // bottom left front
		boxSize, -boxSize, boxSize, // bottom left front
		boxSize, boxSize,  boxSize, // top left front
		boxSize, boxSize, -boxSize, // top left back
	};


	static GLfloat vColors[] = {
								1.0f,  1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f,  1.0f, 1.0f,
								 1.0f,  1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f,  1.0f, 1.0f,

								 // top
								 1.0f,  1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f,  1.0f, 1.0f,
								  1.0f,  1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f,  1.0f, 1.0f,

								  // back
								  1.0f,  1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f,  1.0f, 1.0f,
								   1.0f,  1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f,  1.0f, 1.0f,

								   // bottom
								   1.0f,  1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f, 1.0f,
									1.0f, 1.0f,  1.0f, 1.0f,
									1.0f,  1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f, 1.0f,
									1.0f, 1.0f,  1.0f, 1.0f,

									// left
									1.0f,  1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f,  1.0f, 1.0f,
									 1.0f,  1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f,  1.0f, 1.0f,

									 // right
									 1.0f,  1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f,  1.0f, 1.0f,
									  1.0f,  1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f,  1.0f, 1.0f,

	};

	static GLfloat vTexCoords[] = { // behind initial camera
									0.0f,  1.0f,
									 0.0f, 0.0f,
									 1.0f, 0.0f,
									 1.0f,  0.0f,
									 1.0f, 1.0f,
									 0.0f, 1.0f,

									 // top
									 0.0f,  1.0f,
									 0.0f, 0.0f,
									 1.0f, 0.0f,
									 1.0f,  0.0f,
									 1.0f, 1.0f,
									 0.0f, 1.0f,

									  // back ----> front in scene
									 0.0f,  1.0f,
									 0.0f, 0.0f,
									 1.0f, 0.0f,
									 1.0f,  0.0f,
									 1.0f, 1.0f,
									 0.0f, 1.0f,

									   // bottom
									   0.0f,  1.0f,
									  0.0f, 0.0f,
									  1.0f, 0.0f,
									  1.0f,  0.0f,
									  1.0f, 1.0f,
									  0.0f, 1.0f,

										// left
										0.0f,  1.0f,
									    0.0f, 0.0f,
									    1.0f, 0.0f,
									    1.0f,  0.0f,
									    1.0f, 1.0f,
									    0.0f, 1.0f,

										 // right
										 0.0f,  1.0f,
									    0.0f, 0.0f,
									    1.0f, 0.0f,
									    1.0f,  0.0f,
									    1.0f, 1.0f,
									    0.0f, 1.0f
	};


	glBindTexture(GL_TEXTURE_2D, texture);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// total of vVertices divide by 3 (3 vertices form a triangle)
	// cube = 6 * 6 = 36
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void DrawSkybox(GLuint texture)
{
	static float boxSize = 100.0f;

	static GLfloat vVertices[] = {
		// toward camera
		-boxSize,  boxSize, boxSize, // left top
		-boxSize, -boxSize, boxSize, // left bottom
		boxSize, -boxSize,  boxSize, // right bottom
		boxSize,  -boxSize, boxSize, // right bottom
		boxSize, boxSize, boxSize, // right top
		-boxSize, boxSize,  boxSize, // left top

		// top
		-boxSize,  boxSize, -boxSize, // top left back
		-boxSize, boxSize, boxSize, // top left front
		boxSize, boxSize,  boxSize, // top right front
		boxSize, boxSize,  boxSize, // top right front
		boxSize, boxSize, -boxSize, // top right back
		-boxSize,  boxSize, -boxSize, // top left back

		// back 
		-boxSize,  boxSize, -boxSize, // top left
		-boxSize, -boxSize, -boxSize, // bottom left
		boxSize, -boxSize,  -boxSize, // bottom right
		boxSize,  -boxSize, -boxSize, // bottom right
		boxSize, boxSize, -boxSize, // top right
		-boxSize, boxSize,  -boxSize, // top left

		// bottom
		-boxSize,  -boxSize, -boxSize, // bottom left back
		-boxSize, -boxSize, boxSize, // bottom left front
		boxSize, -boxSize,  boxSize, // bottom right front
		boxSize, -boxSize,  boxSize, // bottom right front
		boxSize, -boxSize, -boxSize, // bottom right back
		-boxSize,  -boxSize, -boxSize, // bottom left back

		// left
		-boxSize, boxSize, -boxSize, // top left back
		-boxSize,  -boxSize, -boxSize, // bottom left back
		-boxSize, -boxSize, boxSize, // bottom left front
		-boxSize, -boxSize, boxSize, // bottom left front
		-boxSize, boxSize,  boxSize, // top left front
		-boxSize, boxSize, -boxSize, // top left back

		// right
		boxSize, boxSize, -boxSize, // top left back
		boxSize,  -boxSize, -boxSize, // bottom left back
		boxSize, -boxSize, boxSize, // bottom left front
		boxSize, -boxSize, boxSize, // bottom left front
		boxSize, boxSize,  boxSize, // top left front
		boxSize, boxSize, -boxSize, // top left back
	};


	static GLfloat vColors[] = {
								1.0f,  1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f,  1.0f, 1.0f,
								 1.0f,  1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f, 1.0f, 1.0f,
								 1.0f, 1.0f,  1.0f, 1.0f,

								 // top
								 1.0f,  1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f,  1.0f, 1.0f,
								  1.0f,  1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f, 1.0f, 1.0f,
								  1.0f, 1.0f,  1.0f, 1.0f,

								  // back
								  1.0f,  1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f,  1.0f, 1.0f,
								   1.0f,  1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f,  1.0f, 1.0f,

								   // bottom
								   1.0f,  1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f, 1.0f,
									1.0f, 1.0f,  1.0f, 1.0f,
									1.0f,  1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f, 1.0f,
									1.0f, 1.0f,  1.0f, 1.0f,

									// left
									1.0f,  1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f,  1.0f, 1.0f,
									 1.0f,  1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f, 1.0f, 1.0f,
									 1.0f, 1.0f,  1.0f, 1.0f,

									 // right
									 1.0f,  1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f,  1.0f, 1.0f,
									  1.0f,  1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f, 1.0f, 1.0f,
									  1.0f, 1.0f,  1.0f, 1.0f,

	};

	static GLfloat vTexCoords[] = { // behind initial camera
									1.0f,  0.655f,
									 1.0f, 0.345f,
									 0.75f, 0.345f,
									 0.75f,  0.345f,
									 0.75f, 0.655f,
									 1.0f, 0.655f,

									 // top
									 0.26f,  0.66f,
									  0.26f, 1.0f,
									  0.49f, 1.0f,
									  0.49f, 1.0f,
									  0.49f, 0.66f,
									  0.26f, 0.66f,

									  // back ----> front in scene
									  0.25f,  0.655f,
									   0.25f, 0.345f,
									   0.5f, 0.345f,
									   0.5f,  0.345f,
									   0.5f, 0.655f,
									   0.25f, 0.655f,

									   // bottom
									   0.26f,  0.33f,
										0.26f, 0.0f,
										0.49f, 0.0f,
										0.49f,  0.0f,
										0.49f, 0.33f,
										0.26f, 0.33f,

										// left
										0.25f,  0.655f,
										 0.25f, 0.345f,
										 0.0f, 0.34f,
										 0.0f,  0.345f,
										 0.0f, 0.655f,
										 0.25f, 0.655f,

										 // right
										 0.5f,  0.655f,
										  0.5f, 0.345f,
										  0.75f, 0.345f,
										  0.75f,  0.345f,
										  0.75f, 0.655f,
										  0.5f, 0.655f
	};


	glBindTexture(GL_TEXTURE_2D, texture);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// total of vVertices divide by 3 (3 vertices form a triangle)
	// cube = 6 * 6 = 36
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Draw(void)
{
	/*
	// Use the program object, it's possible that you have multiple shader programs and switch it accordingly
	glUseProgram(GprogramID);

	// set the sampler2D varying variable to the first texture unit(index 0)
	glUniform1i(glGetUniformLocation(GprogramID, "sampler2d"), 0);
	*/

	//==========================================================================================
	//modify Factor 1 varying variable
	static float factor1 = 0.0f;
	factor1 += 0.01f;
	GLint factor1Loc = glGetUniformLocation(GprogramID, "Factor1");
	if (factor1Loc != -1)
	{
		glUniform1f(factor1Loc, factor1);
	}
	//==========================================================================================


	// Get the uniform variables location. You've probably already done that before...
	GLint Tex1Location = glGetUniformLocation(GprogramID, "Tex1");
	GLint Tex2Location = glGetUniformLocation(GprogramID, "Tex2");

	// Then bind the uniform samplers to texture units:
	glUseProgram(GprogramID);
	glUniform1i(Tex1Location, 0);
	glUniform1i(Tex2Location, 1);

	glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
	glBindTexture(GL_TEXTURE_2D, GfullscreenTexture);

	glActiveTexture(GL_TEXTURE0 + 1); // Texture unit 1
	glBindTexture(GL_TEXTURE_2D, GfullscreenTexture2);

	glActiveTexture(GL_TEXTURE0 + 0);

	// Done! Now you render normally.

	//========pass texture size to shader
	glUniform1f(glGetUniformLocation(GprogramID, "uTextureW"), (GLfloat)WINDOW_WIDTH);
	glUniform1f(glGetUniformLocation(GprogramID, "uTextureH"), (GLfloat)WINDOW_HEIGHT);
	//=========


	UpdateCamera();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//=====================draw 2 rectangles on a texture
	// bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, Gframebuffer);

	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GfullscreenTexture, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);


	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), -1); //set to no blur
		// =====================================================================================
		// one shape
		Matrix4 modelMatrix, mvpMatrix;

		for (int n=0; n<10; n++)
		{
			modelMatrix = Matrix4::translate(Vector3(-1.2f * n/10 + randNum[n], 0.0f, 0.0f + randNum[n*2])) *
				Matrix4::rotate(0, Vector3(0.0f, 1.0f, 0.0f));
			mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
			// mode for vertex shader 
			glUniform1i(glGetUniformLocation(GprogramID, "mode"), 1);

			glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
			DrawCube(GtextureID[1], 0.1); //draw first rectangle
		}
		// =====================================================================================
		// one shape

		modelMatrix = Matrix4::translate(Vector3(1.2f, 0.0f, -5.0f)) *
			Matrix4::rotate(0, Vector3(0.0f, 1.0f, 0.0f));
		mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
		// mode for vertex shader 
		glUniform1i(glGetUniformLocation(GprogramID, "mode"), 2);

		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
		DrawCube(GtextureID[1], 0.1); //draw second rectangle
		// =====================================================================================

		// =====================================================================================
		// one shape
		modelMatrix = Matrix4::translate(Vector3(0.0f, -1.0f, 0.0f)) *
		Matrix4::rotate(0, Vector3(0.0f, 1.0f, 0.0f));
		mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
		// mode for vertex shader 
		glUniform1i(glGetUniformLocation(GprogramID, "mode"), 3);

		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
		DrawPillar(GtextureID[1], 0.1f); //draw second rectangle

		// =====================================================================================

		// skybox
		modelMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, 0.0f)) *
			Matrix4::rotate(0, Vector3(0.0f, 1.0f, 0.0f));
		mvpMatrix = gPerspectiveMatrix * gViewMatrix * modelMatrix;
		// mode for vertex shader 
		glUniform1i(glGetUniformLocation(GprogramID, "mode"), -1);

		glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, mvpMatrix.data);
		DrawSkybox(GtextureID[5]);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	//=============================================

	//=============================================

	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, highPassTexture, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);

	//==============high pass filter================================
	// this time, render first texture to second texture and apply horizontal blur
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

	// draw the texture, apply blurring
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 10);
	DrawSquare(GfullscreenTexture);
	//======================================================


	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, highPassTexture2, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);

	//==============blur the high pass ================================
	// this time, render first texture to second texture and apply horizontal blur
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

	// draw the texture, apply blurring
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 1);
	DrawSquare(highPassTexture);
	//======================================================
	//======================================================

	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GfullscreenTexture2, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);

	//==============blur the high pass2 ================================

	// this time, render second texture directly to window system framebuffer and apply vertical blur
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

	// draw the texture, apply blurring
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 2);
	DrawSquare(highPassTexture2);

	//======================================================
	//======================================================

	// specify texture as color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GfullscreenTexture2, 0);

	// specify depth_renderbufer as depth attachment
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GdepthRenderbuffer);

	//==============apply to GfullscreenTexture ================================

	// this time, render second texture directly to window system framebuffer and apply vertical blur
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset the mvpMatrix to identity matrix so that it renders fully on texture in normalized device coordinates
	glUniformMatrix4fv(glGetUniformLocation(GprogramID, "uMvpMatrix"), 1, GL_FALSE, Matrix4::identity().data);

	// draw the texture, apply blurring
	glUniform1i(glGetUniformLocation(GprogramID, "uBlurDirection"), 100);

	DrawSquare(GfullscreenTexture);

}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	// Initialize GLFW library
	if (!glfwInit())
		return -1;

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Create and open a window
	window = glfwCreateWindow(WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"Hello World",
		NULL,
		NULL);

	if (!window)
	{
		glfwTerminate();
		printf("glfwCreateWindow Error\n");
		exit(1);
	}

	glfwMakeContextCurrent(window);

	Init();

	// Repeat
	while (!glfwWindowShouldClose(window))
	{
		Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
