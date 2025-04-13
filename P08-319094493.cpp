/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture dadoTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;

Model Incredimovil_M;
Model IncredimovilLlantaDer_M;
Model IncredimovilLlantaIzq_M;
Model IncredimovilCofre_M;

Model Alumbrado_M;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights_ej2[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// Cara 1
		0, 1, 2,

		// Cara 5
		3, 4, 5,

		// Cara 7
		6, 7, 8,

		// Cara 3
		9, 10, 11,

		// Cara 4
		12, 13, 14,

		// Cara 6
		15, 16, 17,


		// Cara 8
		18, 19, 20,

		// Cara 2
		21, 22, 23,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat cubo_vertices[] = {
		// Cara 1
		//x		y		z				S		T			NX		NY		NZ
		// Superior
		0.0f, 0.485f,  -0.038f,			0.05f,  0.815f,		0.0f,	1.0f,	0.0f,	//0
		// Izquierdo
		-0.358f, -0.003f,  -0.363f,		0.31f,	0.97f,		-1.0f,	0.0f,	1.0f,	//1
		//Derecho
		0.373f,  0.004f,  -0.337f,		0.31f,	0.71f,		1.0f,	0.0f,	1.0f,	//2


		// Cara 5
		// Superior
		0.0f, 0.485f,  -0.038f,			0.357f,  0.384f,		0.0f,	1.0f,	0.0f,	//3

		// Izquierdo
		0.373f,  0.004f,  -0.337f,		0.628f,	0.291f,		1.0f,	0.0f,	1.0f,	//4

		// Derecho
		0.358f,  -0.004f,  0.363f,		0.359f,	0.156f,		1.0f,	0.0f,	-1.0f,	//5



		// Cara 7
		// Superior
		0.0f, 0.485f,  -0.038f,			0.371f,  0.414f,		0.0f,	1.0f,	0.0f,	//6

		// Izquierdo
		0.358f,  -0.004f,  0.363f,		0.648f,	0.556f,		1.0f,	0.0f,	-1.0f,	//7

		// Derecho
		-0.358f,  -0.004f,  0.363f,		0.648f,	0.314f,		-1.0f,	0.0f,	-1.0f,	//8


		// Cara 3
		// Superior
		0.0f, 0.485f,  -0.038f,			0.359f,  0.445f,		0.0f,	1.0f,	0.0f,	//9

		// Izquierdo
		-0.358f,  -0.004f,  0.363f,		0.359f,	0.677f,		-1.0f,	0.0f,	-1.0f,	//10

		// Derecho
		-0.358f, -0.003f,  -0.363f,		0.625f,	0.578f,		-1.0f,	0.0f,	1.0f,	//11


		// Cara 4
		//x		y		z				S		T			NX		NY		NZ
		// Inferior
		0.0f, -0.5f,  0.004f,			0.351f,  0.974f,		0.0f,	-1.0f,	0.0f,	//12

		// Izquierdo
		-0.358f, -0.003f,  -0.363f,		0.621f,	0.876f,		-1.0f,	0.0f,	1.0f,	//13

		//Derecho
		0.373f,  0.004f,  -0.337f,		0.351f,	0.736f,		1.0f,	0.0f,	1.0f,	//14


		// Cara 6
		// Inferior
		0.0f, -0.5f,  0.004f,			0.65f,  0.0294f,		0.0f,	-1.0f,	0.0f,	//15

		// Izquierdo
		0.373f,  0.004f,  -0.337f,		0.65f,	0.255f,		1.0f,	0.0f,	1.0f,	//16

		// Derecho
		0.358f,  -0.004f,  0.363f,		0.384f,	0.121f,		1.0f,	0.0f,	-1.0f,	//17



		// Cara 8
		// Inferior
		0.0f, -0.5f,  0.004f,			0.675f,  0.853f,		0.0f,	-1.0f,	0.0f,	//18

		// Izquierdo
		0.358f,  -0.004f,  0.363f,		0.976f,	0.757f,		1.0f,	0.0f,	-1.0f,	//19

		// Derecho
		-0.358f,  -0.004f,  0.363f,		0.697f,	0.623f,		-1.0f,	0.0f,	-1.0f,	//20

		// Cara 2
		// Inferior
		0.0f, -0.5f,  0.004f,			0.638f,  0.853f,		0.0f,	-1.0f,	0.0f,	//21

		// Izquierdo
		-0.358f,  -0.004f,  0.363f,		0.648f,	0.609f,		-1.0f,	0.0f,	-1.0f,	//22

		// Derecho
		-0.358f, -0.003f,  -0.363f,		0.371f,	0.705f,		-1.0f,	0.0f,	1.0f,	//23

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 23);
	meshList.push_back(dado);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	bool movimientoCoche = true;

	CreateObjects();
	CreateShaders();
	CrearDado();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado_optimizado.tga");
	dadoTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");


	Incredimovil_M = Model();
	Incredimovil_M.LoadModel("Models/incredimovil_carroceria.obj");
	IncredimovilLlantaDer_M = Model();
	IncredimovilLlantaDer_M.LoadModel("Models/LlantaIzq_texturizada.obj");
	IncredimovilLlantaIzq_M = Model();
	IncredimovilLlantaIzq_M.LoadModel("Models/LlantaDer_texturizada.obj");
	IncredimovilCofre_M = Model();
	IncredimovilCofre_M.LoadModel("Models/incredimovil_cofre.obj");


	Alumbrado_M = Model();
	Alumbrado_M.LoadModel("Models/Alumbrado_D.obj");
	

	
	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.1f, 0.1f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.8f, 2.0f,
		5.0f, 12.0f, 2.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	// Spotlight del cofre
	spotLights[1] = SpotLight(0.368f, 0.129f, 0.16f,
		1.3f, 1.3f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;

	// Spotlight Avanza
	spotLights[2] = SpotLight(1.0f, 0.129f, 0.16f,
		1.3f, 1.3f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;


	// Spotlight Retrocede
	spotLights[3] = SpotLight(1.0f, 0.129f, 0.16f,
		1.3f, 1.3f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	spotLights_ej2[0] = spotLights[0];
	spotLights_ej2[1] = spotLights[1];
	spotLights_ej2[2] = spotLights[3];
	spotLights_ej2[3] = spotLights[2];
	
	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;

		// Spotlight del cofre
		spotLights[1].SetFlash(glm::vec3(-1.55f, 0.2f+ mainWindow.getcofre_arriba() * 0.1, 5.9f + (mainWindow.getmuevex() * 0.5f) + mainWindow.getcofre_arriba() * 0.02), glm::vec3(0.0f, mainWindow.getcofre_arriba() * 0.1, 1.0f));
		spotLights_ej2[1].SetFlash(glm::vec3(-1.55f, 0.2f + mainWindow.getcofre_arriba() * 0.1, 5.9f + (mainWindow.getmuevex() * 0.5f) + mainWindow.getcofre_arriba() * 0.02), glm::vec3(0.0f, mainWindow.getcofre_arriba() * 0.1, 1.0f));

		// Spotlight de avance
		spotLights[2].SetFlash(glm::vec3(-1.55f, 0.2f, 5.9f + (mainWindow.getmuevex() * 0.5f)), glm::vec3(0.0f, 0.0f, 1.0f));
		spotLights_ej2[3].SetFlash(glm::vec3(-1.55f, 0.2f, 5.9f + (mainWindow.getmuevex() * 0.5f)), glm::vec3(0.0f, 0.0f, 1.0f));

		// Spotlight de retrocede
		spotLights[3].SetFlash(glm::vec3(-1.55f, 0.2f, 5.9f + (mainWindow.getmuevex() * 0.5f)), glm::vec3(0.0f, 0.0f, -1.0f));
		spotLights_ej2[2].SetFlash(glm::vec3(-1.55f, 0.2f, -3.0f + (mainWindow.getmuevex() * 0.5f)), glm::vec3(0.0f, 0.0f, -1.0f));


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);

		if (mainWindow.getbandera_movimiento() == 1.0f) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		}
		else {
			shaderList[0].SetSpotLights(spotLights_ej2, spotLightCount - 1);
		}
		



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);


		meshList[2]->RenderMesh();

		// Coche
		{

			//Instancia del coche 
			{
				model = glm::mat4(1.0);
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::translate(model, glm::vec3(-3.0f, 0.5f, mainWindow.getmuevex()));
				modelaux = model;
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Incredimovil_M.RenderModel();
			}

			// Cofre
			{
				modelaux = model;
				model = glm::translate(model, glm::vec3(3.347f, 3.264f, 0.001f));
				model = glm::rotate(model, glm::radians(mainWindow.getcofre_arriba()), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::rotate(model, glm::radians(mainWindow.getcofre_abajo()), glm::vec3(0.0f, 0.0f, -1.0f));
				color = glm::vec3(0.5f, 0.0f, 0.5f);
				glUniform3fv(uniformColor, 1, glm::value_ptr(color));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				IncredimovilCofre_M.RenderModel();
				model = modelaux;
			}

			// Llantas
			{
				// Llanta Derecha Delantera
				{
					modelaux = model;
					model = glm::translate(model, glm::vec3(12.733f, -2.071f, 7.498f));
					model = glm::rotate(model, glm::radians(mainWindow.getllantaDerD()), glm::vec3(0.0f, 0.0f, 1.0f));
					color = glm::vec3(0.5f, 0.0f, 0.3f);
					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					IncredimovilLlantaIzq_M.RenderModel();
					model = modelaux;
				}

				// Llanta Derecha Trasera
				{
					modelaux = model;
					model = glm::translate(model, glm::vec3(-12.148f, -2.071f, 5.488f));
					model = glm::rotate(model, glm::radians(mainWindow.getllantaDerT()), glm::vec3(0.0f, 0.0f, 1.0f));
					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					IncredimovilLlantaIzq_M.RenderModel();
					model = modelaux;
				}

				// Llanta Izquierda Delantera
				{
					modelaux = model;
					model = glm::translate(model, glm::vec3(12.733f, -2.071f, -7.498f));
					model = glm::rotate(model, glm::radians(mainWindow.getllantaIzqD()), glm::vec3(0.0f, 0.0f, 1.0f));
					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					IncredimovilLlantaDer_M.RenderModel();
					model = modelaux;
				}

				// Llanta Izquierda Trasera
				{
					modelaux = model;
					model = glm::translate(model, glm::vec3(-12.148f, -2.071f, -5.488f));
					model = glm::rotate(model, glm::radians(mainWindow.getllantaIzqT()), glm::vec3(0.0f, 0.0f, 1.0f));
					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					IncredimovilLlantaDer_M.RenderModel();
					model = modelaux;
				}
			}

		}

		model = glm::mat4(1.0);


		// Alumbrado
		modelaux = model;
		model = glm::translate(model, glm::vec3(5.0f, -1.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alumbrado_M.RenderModel();
		model = modelaux;

		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmueveHelicoptero(), 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshList[4]->RenderMesh();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
