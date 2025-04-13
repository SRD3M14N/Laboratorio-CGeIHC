#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	GLfloat getcofre_abajo() { return cofre_abajo; }
	GLfloat getcofre_arriba() { return cofre_arriba; }
	GLfloat getllantaIzqD() { return llantaIzqD; }
	GLfloat getllantaDerD() { return llantaDerD; }
	GLfloat getllantaDerT() { return llantaDerT; }
	GLfloat getllantaIzqT() { return llantaIzqT; }

	GLfloat getmueveHelicoptero() { return mueveHelicoptero; }
	
	GLfloat getbandera_movimiento() { return bandera_movimiento; }

	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat cofre_abajo, cofre_arriba,
		llantaIzqD, llantaDerD,
		llantaIzqT, llantaDerT,
		mueveHelicoptero,
		bandera_movimiento;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

