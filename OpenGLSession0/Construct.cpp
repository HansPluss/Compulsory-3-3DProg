#include "Construct.h"

std::array<Vertex, 36> Construct::Cube(glm::vec3 Color)
{
	std::array<Vertex, 36> CubeArray;
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z };
    Vertex v2{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v4{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v6{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v7{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z };

    CubeArray[0] = v0;
    CubeArray[1] = v1;
    CubeArray[2] = v2;
    CubeArray[3] = v2;
    CubeArray[4] = v3;
    CubeArray[5] = v0;

    // Right face
    CubeArray[6] = v1;
    CubeArray[7] = v5;
    CubeArray[8] = v6;
    CubeArray[9] = v6;
    CubeArray[10] = v2;
    CubeArray[11] = v1;

    // Back face
    CubeArray[12] = v5;
    CubeArray[13] = v4;
    CubeArray[14] = v7;
    CubeArray[15] = v7;
    CubeArray[16] = v6;
    CubeArray[17] = v5;

    // Left face
    CubeArray[18] = v4;
    CubeArray[19] = v0;
    CubeArray[20] = v3;
    CubeArray[21] = v3;
    CubeArray[22] = v7;
    CubeArray[23] = v4;

    // Top face
    CubeArray[24] = v3;
    CubeArray[25] = v2;
    CubeArray[26] = v6;
    CubeArray[27] = v6;
    CubeArray[28] = v7;
    CubeArray[29] = v3;

    // Bottom face
    CubeArray[30] = v0;
    CubeArray[31] = v4;
    CubeArray[32] = v5;
    CubeArray[33] = v5;
    CubeArray[34] = v1;
    CubeArray[35] = v0;

    return CubeArray; 
}

std::array<Vertex, 36> Construct::Table(glm::vec3 Color)
{
    std::array<Vertex, 36> TableArray;
    float size = 1;

    Vertex v0{ -size, -size, size , Color.x, Color.y, Color.z };
    Vertex v1{ size, -size, size, Color.x, Color.y, Color.z };
    Vertex v2{ size, size, size , Color.x, Color.y, Color.z };
    Vertex v3{ -size, size, size ,  Color.x, Color.y, Color.z };
    Vertex v4{ -size, -size, -size ,  Color.x, Color.y, Color.z };
    Vertex v5{ size, -size, -size ,  Color.x, Color.y, Color.z };
    Vertex v6{ size, size, -size ,  Color.x, Color.y, Color.z };
    Vertex v7{ -size, size, -size , Color.x, Color.y, Color.z };

    Vertex v8{(3 * -size),  size, (4 * size) , Color.x, Color.y, Color.z};
    Vertex v9{(3 * size),  size, (4 * size) , Color.x, Color.y, Color.z };
    Vertex v10{ (3 * -size) ,  size,(4 * -size), Color.x, Color.y, Color.z };
    Vertex v11{(3 * size), size,(4 * -size) , Color.x, Color.y, Color.z };

    TableArray = {
        // Front face
        v0, v1, v3,
        v3, v1, v2,

        // Back face
        v4, v5, v7,
        v7, v5, v6,

        // Right face
        v1, v5, v2,
        v2, v5, v6,

        // Left face
        v4, v0, v7,
        v7, v0, v3,

        // Top face
        v8, v9, v10,
        v10, v9, v11,


        // Bottom face
        v4, v5, v0,
        v0, v5, v1
    };

    return TableArray;
}

std::array<Vertex, 48> Construct::House(glm::vec3 Color)
{
    std::array<Vertex, 48> houseArray;
    float size = 1.f; 

    // House
    Vertex v0{ -size, -size, size , Color.x, Color.y, Color.z };
    Vertex v1{ size, -size, size, Color.x, Color.y, Color.z };
    Vertex v2{ size, size, size , Color.x, Color.y, Color.z };
    Vertex v3{ -size, size, size ,  Color.x, Color.y, Color.z };
    Vertex v4{ -size, -size, -size ,  Color.x, Color.y, Color.z };
    Vertex v5{ size, -size, -size ,  Color.x, Color.y, Color.z };
    Vertex v6{ size, size, -size ,  Color.x, Color.y, Color.z };
    Vertex v7{ -size, size, -size , Color.x, Color.y, Color.z };

    // Roof
    Vertex v8{ 0.0f, size + size / 2,  size, Color.x, Color.y, Color.z };
    Vertex v9{ 0.0f, size + size / 2, -size, Color.x, Color.y, Color.z };

    houseArray =
    {
        // Front face
        v0, v1, v3,
        v3, v1, v2,

        // Back face
        v4, v5, v7,
        v7, v5, v6,

        // Right face
        v1, v5, v2,
        v2, v5, v6,

        // Left face
        v4, v0, v7,
        v7, v0, v3,

        // Bottom face
        v4, v5, v0, 
        v0, v5, v1, 

        // Roof faces
        // Front triangle
        v3, v2, v8,
        // Back triangle
        v6, v7, v9,

        // Left roof face
        v3, v7, v8,
        v7, v8, v9,

        // Right roof face
        v2, v6, v8,
        v6, v8, v9
    };

    return houseArray;
}

std::array<Vertex, 6> Construct::Plane(glm::vec3 Color, glm::vec3 PointPosition)
{
    std::array<Vertex, 6> PlaneArray;
    glm::vec3 sizeXYZ = glm::vec3(10.0f, 10.0f, 10.0f);
   
      //  = glm::vec3(sizeXYZ.x / 4, sizeXYZ.x / 2, 0);
    Vertex v2{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v6{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z ,  Color.x, Color.y, Color.z };
    Vertex v7{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z };

    glm::vec<3, float> baryCoords = calculateBarycentricCoordinates(PointPosition, glm::vec3(v3.x, v3.y, v3.z), glm::vec3(v2.x, v2.y, v2.z), glm::vec3(v6.x, v6.y, v6.z));
    glm::vec<3, float> baryCoords2 = calculateBarycentricCoordinates(PointPosition, glm::vec3(v7.x, v7.y, v7.z), glm::vec3(v2.x, v2.y, v2.z), glm::vec3(v3.x, v3.y, v3.z));

    float heightV3 = v3.y * baryCoords.x + v2.y * baryCoords.y + v6.y * (1.0 - baryCoords.x - baryCoords.y);
    float heightV2 = v7.y * baryCoords2.x + v2.y * baryCoords2.y + v3.y * (1.0 - baryCoords2.x - baryCoords2.y);
    float heightV6 = v3.y * (1.0 - baryCoords.x - baryCoords.y) + v2.y * baryCoords.x + v7.y * baryCoords.y;

    v3.y = heightV3;
    v2.y = heightV2;
    v6.y = heightV6;
    currentBaryPosition.x = baryCoords.x;
    currentBaryPosition.y = baryCoords.y;
    currentBaryPosition.z = baryCoords.z;
    std::cout << "x: " << heightV2 << std::endl;
    std::cout << "y: " << baryCoords.y << std::endl;
    std::cout << "z: " << baryCoords.z << std::endl;
    //v7.y = newHeight2;
    PlaneArray[0] = v3;
    PlaneArray[1] = v2;
    PlaneArray[2] = v6;
  /*  PlaneArray[3] = v6;
    PlaneArray[4] = v7;
    PlaneArray[5] = v3;*/

    return PlaneArray;
}

glm::vec3 Construct::calculateBarycentricCoordinates(const glm::vec3& point, const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2)
{
    glm::vec<3, float> u = v0 - point;
    glm::vec<3, float> v = v1 - point;
    glm::vec<3, float> w = v2 - point;
   /* glm::vec3 area;
    area = v1 * v2;*/
    std::cout << "u: " << u.y << std::endl;
    std::cout << "v: " << v.y << std::endl;
    std::cout << "w: " << w.y << std::endl;
    glm::vec3 area = glm::cross(v1 - v0, v2 - v0);

    //float determinant = u.x * v.y - u.y * v.x;
    
    if (area.y == 0) {
        //error
        std::cout << area.y << std::endl;
        std::cout << "ERROR" << std::endl;
        return glm::vec3(0.0f);
    }
    glm::vec3 uv = glm::cross(u, v);
    glm::vec3 vw = glm::cross(v, w);
    float a = glm::dot(uv, vw) / glm::dot(area, area);
    float b = glm::dot(vw, glm::cross(u, w)) / glm::dot(area, area);
    float c = 1.0f - a - b;

    
    return glm::vec3(a, b, c);
}

glm::vec3 Construct::GetCurrentBaryPosition()
{
    return currentBaryPosition;
}

