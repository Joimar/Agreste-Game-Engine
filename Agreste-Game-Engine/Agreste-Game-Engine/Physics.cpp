#include "Physics.h"

Physics::Physics()
{
	gravity = glm::vec3(0.0f, -0.02f, 0.0);
}


bool Physics::detectCollision(GameObject obj1, GameObject obj2)
{
	float planeDistance = 0;
	float radius = 0.5f;
	glm::vec3 point = obj1.getPosition();
	for (size_t i = 0; i < obj2.getModel().meshes.size(); i++)
	{
		bool awayFromFace = false;
		bool awayFromVertices =false;
		bool awayFromEdges =false;
		int j = 0;
		while (true)
		{
			awayFromFace = false;
			awayFromVertices = false;
			awayFromEdges = false;
			int index = obj2.getModel().meshes[i].indices[j];
			glm::vec3 vertex1 = obj2.getModel().meshes[i].vertices[index].Position + obj2.getPosition();
			glm::vec3 vertex2 = obj2.getModel().meshes[i].vertices[index+1].Position + obj2.getPosition();
			glm::vec3 vertex3 = obj2.getModel().meshes[i].vertices[index+2].Position + obj2.getPosition();
			glm::vec3 vertex_ab = vertex2 - vertex1;
			glm::vec3 vertex_ac = vertex3 - vertex1;
			glm::vec3 normal = glm::cross(vertex_ab, vertex_ac);
			float d = -1*glm::dot(normal ,vertex1);
			float div = sqrt((normal.x*normal.x) + (normal.y*normal.y) + (normal.z*normal.z));
			planeDistance = (glm::dot(normal, point) + d) / div;
			float vd1, vd2, vd3;
			vd1 = glm::distance(point, vertex1);
			if (vd1 < 0)
				vd1 *= -1;
			vd2 = glm::distance(point, vertex2);
			if (vd2 < 0)
				vd2 *= -1;
			vd3 = glm::distance(point, vertex3);
			if (vd3 < 0)
				vd3 *= -1;
			float ld1, ld2, ld3;
			//edge formed by vertices 1,2
			float numerator = glm::length(glm::cross((point - vertex1), (point - vertex2)));
			float denominator = glm::length(vertex_ab);
			ld1 = numerator / denominator;
			if (ld1 < 0)
				ld1 *= -1;
			//edge formed by vertices 1,2
			numerator = glm::length(glm::cross((point - vertex1), (point - vertex3)));
			denominator = glm::length(vertex_ac);
			ld2 = numerator / denominator;
			if (ld2 < 0)
				ld2 *= -1;
			//edge formed by vertices 2,3
			numerator = glm::length(glm::cross((point - vertex2), (point - vertex3)));
			denominator = glm::length(vertex3-vertex2);
			ld3 = numerator / denominator;
			if (ld3 < 0)
				ld3 *= -1;
			/*if (normal.y > 0.1f || normal.y<-0.1f)
			{
				if (j >= obj2.getModel().meshes[i].indices.size() - 3)
				{
					break;
				}
				j = j + 3;
				continue;
			}/**/
			if (ld1 > radius &&
				ld2 > radius &&
				ld3 > radius)
			{
				awayFromEdges = true;
			}

			if (vd1 > radius &&
				vd2 > radius &&
				vd3 > radius)
			{
				awayFromVertices = true;
			}

			if (planeDistance < 0)
				planeDistance *= -1;
			if ((planeDistance > radius))
			{
				awayFromFace = true;
			}
			if (!(awayFromFace || awayFromVertices && awayFromEdges))
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

void Physics::gravityForce(vector<GameObject*> GameObjects)
{
	glm::vec3 newPos;
	
	for (size_t i = 0; i < GameObjects.size(); i++)
	{
		if (!(*GameObjects[i]).isFixed() && (*GameObjects[i]).getPosition().y > 0)
		{
			
			newPos = (*GameObjects[i]).getPosition() + gravity ;
			(*GameObjects[i]).setPosition(newPos);
			
		}
	}
}
