#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <ctime> 
#include <stb/stb_image.h>

#include "Resources/Shaders/shaderClass.h"
#include "Resources/Shaders/VAO.h"
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/EBO.h"
#include "Camera.h"
#include "Pokal.h"
#include "Player.h"
#include "LSM.h"
#include "SphereCollition.h"

#include<filesystem>



const unsigned int width = 800;
const unsigned int height = 800;
using namespace std;

void processInput(GLFWwindow* window);


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLProject", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800

	
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	
	
	
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	

	Player myPlayer(1.0f, glm::vec3(0,0,20), 0.1f, 0.0f, 0.5f, 1);

	Player floor(20.0f, glm::vec3(5, -27, -10), 0.1f, 0.8f, 0.9f, 4);
	
	Player AI(1.0f, glm::vec3(0, 0, -5), 0.1f, 0.5f, 0.0f, 1);

	
	// Unbind all to prevent accidentally modifying them
	
	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	float scaleValue = 100.0f;
	
	
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	
	
	//Camera object
	Camera camera(width, height, glm::vec3(0.0f, 10.0f, 40.0f));
	
	//speed of cube
	float translationSpeed = 0.05f;
	
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	//std::string texPath = "/Resources/Textures/";

	//// Texture
	//Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//brickTex.texUnit(shaderProgram, "tex0", 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("brick.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(true);
	//shaderProgram.Activate();
	shaderProgram.setInt("tex0", 0);
	//std::cout << parentDir + texPath + "brick.png" << endl;

	std::vector<double> patrolPoints = { -1 , 2, 1, -2, 2, 2 }; // points for patrolling
	LSM PatrolPath(patrolPoints, 2); // the degree of the function, f.exa x^2

	//SphereCollition sc(myPlayer, NPC);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		
		processInput(window);
		myPlayer.inputs(window);
		camera.Inputs(window);
		AI.Patrol(PatrolPath.getCoefficients());
		//Set render distance and FOV
		glm::mat4 viewproj= camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, myPlayer.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj*model));
		myPlayer.BindVAO();
		myPlayer.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, myPlayer.mVertecies.size());
		myPlayer.UnbindVAO();
		
		//collision for player for plane
		floor.calculateBarycentricCoordinates(myPlayer.position, floor.planePoints[0], floor.planePoints[1], floor.planePoints[2],true);
		floor.calculateBarycentricCoordinates(myPlayer.position, floor.planePoints[2], floor.planePoints[3], floor.planePoints[0],true);
		//collision for player for plane
		floor.calculateBarycentricCoordinates(AI.position, floor.planePoints[0], floor.planePoints[1], floor.planePoints[2],true);
		floor.calculateBarycentricCoordinates(AI.position, floor.planePoints[2], floor.planePoints[3], floor.planePoints[0],true);
		
		AI.calculateBarycentricCoordinates(myPlayer.position, AI.planePoints[0], AI.planePoints[1], AI.planePoints[2],false);
		AI.calculateBarycentricCoordinates(myPlayer.position, AI.planePoints[2], AI.planePoints[3], AI.planePoints[0],false);
		//brickTex.Bind();
		glm::mat4 FloorModel = glm::mat4(1.0f);
		FloorModel = glm::translate(FloorModel, floor.position);
		FloorModel = glm::scale(FloorModel, glm::vec3(20.0f,20.f,20.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * FloorModel));
		
		floor.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, floor.mVertecies.size());
		floor.UnbindVAO();
		

		glm::mat4 NPCmodel = glm::mat4(1.0f);
		NPCmodel = glm::translate(NPCmodel, AI.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * NPCmodel));
		
		AI.BindVAO();
		AI.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, AI.mVertecies.size());
		AI.UnbindVAO();
		

		
		
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	
	
	
	
	// Delete all the objects we've created
	
	myPlayer.VAO5.Delete();
	
	
	shaderProgram.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	

}