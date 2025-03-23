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
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }

	GLfloat getincredimovil() { return incredimovil; }
	
	GLfloat getllantaIzqD() { return llantaIzqD; }
	GLfloat getllantaDerD() { return llantaDerD; }
	GLfloat getllantaDerT() { return llantaDerT; }
	GLfloat getllantaIzqT() { return llantaIzqT; }


	GLfloat getcofre_abajo() { return cofre_abajo; }
	GLfloat getcofre_arriba() { return cofre_arriba; }
	

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, 
		llantaIzqD, llantaDerD,
		llantaIzqT, llantaDerT,
		cofre_abajo, cofre_arriba,
		incredimovil;

	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

