#pragma once
#include <array>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vertex
{
	float x, y, z;
	float r, g, b;

};
class Construct
{
public:
	std::array<Vertex, 36> Cube(glm::vec3 Color);
	std::array<Vertex, 36> Table(glm::vec3 Color);
	std::array<Vertex, 48> House( glm::vec3 Color);
	std::array<Vertex, 6> Plane(glm::vec3 Color, glm::vec3 PointPosition);
	glm::vec3 currentBaryPosition;
	glm::vec3 calculateBarycentricCoordinates(const glm::vec3& point, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
	glm::vec3 GetCurrentBaryPosition();
};

