#include "Physics.h"

Physics::Physics()
{
	gravity = glm::vec3(0.0f, -0.01f, 0.0);
}


bool Physics::detectCollision(GameObject obj1, GameObject obj2)
{
	float distance = 0;
	float radius = 1.0f;
	glm::vec3 point = obj1.getPosition();
	for (size_t i = 0; i < obj2.getModel().meshes.size(); i++)
	{
		int aux = obj2.getModel().meshes[i].vertices.size();
		int j = 0;
		while (true)
		{
			int index = obj2.getModel().meshes[i].indices[j];
			glm::vec3 vertex1 = obj2.getModel().meshes[i].vertices[index].Position + obj2.getPosition();
			glm::vec3 vertex2 = obj2.getModel().meshes[i].vertices[index+1].Position + obj2.getPosition();
			glm::vec3 vertex3 = obj2.getModel().meshes[i].vertices[index+2].Position + obj2.getPosition();
			glm::vec3 vertex_ab = vertex2 - vertex1;
			glm::vec3 vertex_ac = vertex3 - vertex1;
			glm::vec3 normal = glm::cross(vertex_ab, vertex_ac);
			//std:: cout << "(" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
			float d = -1*glm::dot(normal ,vertex1);
			float div = sqrt((normal.x*normal.x) + (normal.y*normal.y) + (normal.z*normal.z));
			distance = (glm::dot(normal, point) + d) / div;
			if (distance < 0)
				distance *= -1;
			if (normal.y==0.0f && distance < radius)
			{
				this->normalResponse = normal;
				return true;
			}
			if (j >= obj2.getModel().meshes[i].indices.size() - 3)
			{
				break;
			}
			j = j + 3;
		}

	}
	return false;
}
