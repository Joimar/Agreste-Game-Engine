#include "Physics.h"

Physics::Physics()
{
	gravity = glm::vec3(0.0f, -0.02f, 0.0);
}


bool Physics::narrowPhase(GameObject obj1, GameObject obj2)
{
	float planeDistance = 0;
	float radius = 0.5f;
	float x_min, y_min, z_min;
	float x_max, y_max, z_max;
	glm::vec3 point = obj1.getPosition();
	glm::vec3 point2 = obj2.getPosition();
	for (size_t i = 0; i < obj2.getModel().meshes.size(); i++)
	{
		bool breakPlane = false;
		bool inside_sphere = false;
		bool inside_Binding_box = false;
		x_max = obj2.getModel().meshes[i].maxX + point.x;
		y_max = obj2.getModel().meshes[i].maxY + point.y;
		z_max = obj2.getModel().meshes[i].maxZ + point.z;
		x_min = obj2.getModel().meshes[i].minX + point.x;
		y_min = obj2.getModel().meshes[i].minY + point.y;
		z_min = obj2.getModel().meshes[i].minZ + point.z;
		float boundSphereRadius = distance(point2, glm::vec3(x_min, y_min, z_min));
		if (boundSphereRadius <0)
		{
			boundSphereRadius *= -1;
		}

		int j = 0;
		while (true)
		{
			breakPlane = false;
			inside_sphere = false;
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
			float distance_from_center_to_center = glm::distance(point, point2);

			if (distance_from_center_to_center < (radius+boundSphereRadius))
			{
				inside_sphere = true;
			}
			/*if (normal.y > 0.1f || normal.y<-0.1f)
			{
				if (j >= obj2.getModel().meshes[i].indices.size() - 3)
				{
					break;
				}
				j = j + 3;
				continue;
			}*/
			if (x_min < point.x && point.x < x_max)
			{
				if (y_min < point.y )
				{
					if (z_min < point.z && point.z < z_max) 
					{
						
							inside_Binding_box = true;
						
						
					}
				}

			}

			if (planeDistance < 0)
				planeDistance *= -1;
			if ((planeDistance < radius))
			{
				breakPlane = true;
			}
			if (inside_sphere && breakPlane && inside_Binding_box)
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

void Physics::gravityForce(vector<GameObject*> GameObjects, float deltaTime)
{
	glm::vec3 newPos;
	
	for (size_t i = 0; i < GameObjects.size(); i++)
	{
		if (!(*GameObjects[i]).isFixed() && (*GameObjects[i]).getPosition().y > 0)
		{
			
			(*GameObjects[i]).Move(gravity, deltaTime);

			
		}
	}
}
