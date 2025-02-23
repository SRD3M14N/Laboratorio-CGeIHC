//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShader_rojo = "shaders/shader_rojo.vert";

static const char* vShader_verde = "shaders/shader_verde.vert";

static const char* vShader_azul = "shaders/shader_azul.vert";

static const char* vShader_cafe = "shaders/shader_cafe.vert";

static const char* vShader_verdeOsc = "shaders/shader_verdeOsc.vert";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramideArbol()
{

	unsigned int indices[] = {
		1, 4, 5,
		2, 1, 4,


		2, 0, 1,
		1, 0, 5,


		2, 0, 3,
		0, 3, 5,

		2, 3, 4,
		3, 4, 5

	};
	GLfloat vertices[] = {
		-0.25f, -0.25f, -0.25f,	//0
		-0.25f, -0.25f,0.25f,	//1
		0.0f, 0.25f, 0.0f,	//2 Punta
		0.25f, -0.25f, -0.25f,	//3
		0.25f, -0.25f, 0.25f, // 4
		0.0f, -0.25f, 0.0f // 5 - Centro (Base)

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 36, 36);
	meshList.push_back(obj1);
}

void CreaArcoLetra()
{
	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2,
		3, 4, 2,
		4, 5, 2,
		5, 6, 2,
		6, 7, 2,
		7, 8, 2,
		8, 9, 2,
		9, 10, 2,
		10, 11, 2,
		11, 12, 2,
		12, 13, 2,
		13, 14, 2,
		14, 15, 2,
		15, 16, 2,
		16, 17, 2,
		17, 18, 2,
		18, 19, 2,
		19, 20, 2,
		20, 21, 2
	};

	GLfloat vertices[] = {
		0.00000000f, 0.20000000f, 0.00000000f,
		0.01569182f, 0.19938347f, 0.00000000f,
		0.00000000f, 0.00000000f, 0.00000000f,
		0.03128690f, 0.19753768f, 0.00000000f,
		0.04668907f, 0.19447398f, 0.00000000f,
		0.06180340f, 0.19021131f, 0.00000000f,
		0.07653669f, 0.18477590f, 0.00000000f,
		0.09079810f, 0.17820130f, 0.00000000f,
		0.10449971f, 0.17052804f, 0.00000000f,
		0.11755705f, 0.16180339f, 0.00000000f,
		0.12988961f, 0.15208119f, 0.00000000f,
		0.14142136f, 0.14142136f, 0.00000000f,
		0.15208119f, 0.12988961f, 0.00000000f,
		0.16180339f, 0.11755705f, 0.00000000f,
		0.17052804f, 0.10449971f, 0.00000000f,
		0.17820130f, 0.09079810f, 0.00000000f,
		0.18477590f, 0.07653669f, 0.00000000f,
		0.19021131f, 0.06180340f, 0.00000000f,
		0.19447398f, 0.04668907f, 0.00000000f,
		0.19753768f, 0.03128690f, 0.00000000f,
		0.19938347f, 0.01569182f, 0.00000000f,
		0.20000000f, 0.00000000f, 0.00000000f,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 64, 60);
	meshList.push_back(obj1);
}

void CrearRectanguloLargoLetra()
{
	unsigned int cubo_indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	GLfloat cubo_vertices[] = {
		-0.1f, 0.6f, 0.0f, // 0
		-0.1f, -0.6f, 0.0f, // 1
		0.1f, 0.6f, 0.0f, // 2
		0.1f, -0.6f, 0.0f // 3
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearRectanguloMedianoLetra()
{
	unsigned int cubo_indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	GLfloat cubo_vertices[] = {
		-0.1f, 0.5f, 0.0f, // 0
		-0.1f, -0.5f, 0.0f, // 1
		0.1f, 0.5f, 0.0f, // 2
		0.1f, -0.5f, 0.0f // 3
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearRectanguloCortoLetra()
{
	unsigned int cubo_indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	GLfloat cubo_vertices[] = {
		-0.1f, 0.4f, 0.0f, // 0
		-0.1f, -0.4f, 0.0f, // 1
		0.1f, 0.4f, 0.0f, // 2
		0.1f, -0.4f, 0.0f // 3
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearRectanguloMiniLetra()
{
	unsigned int cubo_indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	GLfloat cubo_vertices[] = {
		-0.1f, 0.15f, 0.0f, // 0
		-0.1f, -0.15f, 0.0f, // 1
		0.1f, 0.15f, 0.0f, // 2
		0.1f, -0.15f, 0.0f // 3
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearCuadradoLetra()
{
	unsigned int cubo_indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	GLfloat cubo_vertices[] = {
		-0.1f, 0.1f, 0.0f, // 0
		-0.1f, -0.1f, 0.0f, // 1
		0.1f, 0.1f, 0.0f, // 2
		0.1f, -0.1f, 0.0f // 3
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CreaPiramideCasa()
{
	unsigned int indices[] = {
		1, 4, 5,
		2, 1, 4,

		2, 0, 1,
		1, 0, 5,

		2, 0, 3,
		0, 3, 5,

		2, 3, 4,
		3, 4, 5

	};
	GLfloat vertices[] = {
		-0.6f, -0.3f, -0.6f,	//0
		-0.6f, -0.3f,0.6f,	//1
		0.0f, 0.3f, 0.0f,	//2 Punta
		0.6f, -0.3f, -0.6f,	//3
		0.6f, -0.3f, 0.6f, // 4
		0.0f, -0.3f, 0.0f // 5 - Centro (Base)

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 36, 36);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCuboArbol()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.1f, -0.1f,  0.1f,
		0.1f, -0.1f,  0.1f,
		0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		// back
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f,  0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearCuboCasa()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.6f,  0.5f,
		-0.5f,  0.6f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.6f, -0.5f,
		-0.5f,  0.6f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearCuboVentana()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.15f, -0.15f,  0.15f,
		0.15f, -0.15f,  0.15f,
		0.15f,  0.15f,  0.15f,
		-0.15f,  0.15f,  0.15f,
		// back
		-0.15f, -0.15f, -0.15f,
		0.15f, -0.15f, -0.15f,
		0.15f,  0.15f, -0.15f,
		-0.15f,  0.15f, -0.15f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	1.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	1.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			0.0f,	1.0f,	1.0f,
		/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 18);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


}






void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader3->CreateFromFiles(vShader_rojo, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader4->CreateFromFiles(vShader_verde, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader5->CreateFromFiles(vShader_azul, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader6->CreateFromFiles(vShader_cafe, fShader);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader7->CreateFromFiles(vShader_verdeOsc, fShader);
	shaderList.push_back(*shader7);


}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaArcoLetra();
	CrearRectanguloLargoLetra();
	CrearCuadradoLetra();
	CrearRectanguloMiniLetra();
	CrearRectanguloCortoLetra();
	CrearRectanguloMedianoLetra();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		// Letra R
		{
			// Arco 1 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.6f, 0.3f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();

			// Arco 2 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.6f, 0.0f, -2.0f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();

			// Arco 3 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.6f, -0.2f, -2.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();

			// Arco 4 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.6f, -0.4f, -2.0f));
			//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();


			// Rectangulo Largo R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.9f, -0.1f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[1]->RenderMesh();

			//Cuadrado 1 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.7f, 0.4f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();

			// Cuadrado 2 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.7f, -0.1f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();

			// Rectangulo Mini 1 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.5f, 0.15f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[3]->RenderMesh();

			// Rectangulo Mini 2 R
			shaderList[6].useShader();
			uniformModel = shaderList[6].getModelLocation();
			uniformProjection = shaderList[6].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.5f, -0.55f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[3]->RenderMesh();
		}


		// Letra D
		
		{
			// Arco 1 D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.1f, 0.3f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();

			// Arco 2 D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.1f, -0.5f, -2.0f));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();


			// Rectangulo Largo D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.2f, -0.1f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[1]->RenderMesh();

			// Rectangulo Corto D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.2f, -0.1f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[4]->RenderMesh();

			// Cuadrado 1 D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, 0.4f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();

			// Cuadrado 2 D
			shaderList[5].useShader();
			uniformModel = shaderList[5].getModelLocation();
			uniformProjection = shaderList[5].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.6f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();
		}


		// Letra A
	
		{
			// Arco 1 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.6f, 0.3f, -2.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();


			// Arco 2 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.8f, 0.3f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[0]->RenderMesh();

			// Rectangulo Mediano 1 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.5f, -0.2f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[5]->RenderMesh();

			// Rectangulo Mediano 2 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.9f, -0.2f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[5]->RenderMesh();

			// Cuadrado 1 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.7f, 0.4f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();

			// Cuadrado 2 A
			shaderList[4].useShader();
			uniformModel = shaderList[4].getModelLocation();
			uniformProjection = shaderList[4].getProjectLocation();
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.7f, -0.2f, -2.0f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//gira en el eje z
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			meshList[2]->RenderMesh();
		}




		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/