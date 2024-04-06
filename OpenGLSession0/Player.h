#pragma once
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/VAO.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include <cmath>
#include "Table.h"
#include "Pokal.h"
#include "Construct.h"

class Pokal;


using namespace std;
//struct PlayerVertex
//{
//	double x, y, z;
//	float r, g, b;
//
//};
class Player {
private:


public:
std::array<Vertex, 36> mVertecies;
std::array<Vertex, 6> mPlaneVertecies;
std::array<Vertex, 48> mHouseVertecies;
	glm::vec3 position;
	float r, g, b;
	glm::vec3 velocity;
	glm::vec3 PointPosition;
	float sphere_radius = 0;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;
	bool move = true; 

	
	VAO VAO5;
	VBO VBO1;
	Construct con;
	std::array<glm::vec3, 4> planePoints;
	
	
	Player(float scale, const glm::vec3& initialPosition, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float figure = 1.f)
		: a(scale), position(initialPosition), velocity(glm::vec3(0.0f)), r(red), g(green), b(blue), VBO1()
	{
		


		//Cube
		if (figure == 1)
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		
			VAO5.Unbind();
			VBO1.Unbind();
		}
		else if (figure == 2)
		{
			mVertecies = con.Table(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			
			VAO5.Unbind();
			VBO1.Unbind();
		}

		else if (figure == 3)
		{
			mHouseVertecies = con.House(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mHouseVertecies.size() * sizeof(Vertex), mHouseVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
		}
		else if (figure == 4) {

			PointPosition = glm::vec3(10.0f, 0.0f, 0.0f);
			mPlaneVertecies = con.Plane(glm::vec3(red, green, blue), PointPosition);

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mPlaneVertecies.size() * sizeof(Vertex), mPlaneVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3(-scale, scale, scale);
			planePoints[1] = glm::vec3(scale, scale * 1.5, scale);
			planePoints[2] = glm::vec3(scale, scale * 1.5, -scale);
			planePoints[3] = glm::vec3(-scale, scale, -scale);

		}
		else
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
		}
		
		
		//Table
		//mVertecies = con.Table(a, initialPosition, glm::vec3(red, green, blue));

		//collitionSphere
		sphere_radius = a; 


		//flattenVertices();
	}
	float GetA();
	/*std::vector<GLfloat> getFlattenedVertices() const;*/
	/*void ConstructVBO(std::vector<GLfloat> flattenedVertices, bool update);*/
	void DeleteVBOANDVAO();
	void UnbindVAO();
	void BindVAO();
	void UpdateVertices(float Xspeed, float Yspeed, float Zspeed, glm::vec3 velocity);
	VBO GetVBO();
	void inputs(GLFWwindow* window);

	void Patrol(std::vector<double> coefficients);
	
	bool CheckCollision( Player& otherCube);
	


	void flattenVertices();
	glm::vec3 calculateBarycentricCoordinates(glm::vec3& point, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

public:
	float a{ 1.0f };
	double xvalue = 0;
	double xspeed = 0.001;
	bool xPositiveDir = true;


};