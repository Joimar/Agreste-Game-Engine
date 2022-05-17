#include "Physics.h"

Physics::Physics()
{
	gravity = glm::vec3(0.0f, -0.02f, 0.0);
}

bool Physics::broadPhase() // testes com sort and sweep
{
	//Find highest variance of axis for AABBs
	//Sort AABBs by min on highest variance axis
	//Go through the list, test interactions in range
	return false;
}

bool Physics::isCollision(GameObject * obj1, GameObject * obj2) {
	bool flagX = false;
	bool flagY = false;
	bool flagZ = false;
	std::vector<Mesh> mesh1 = obj1->getModel().meshes;
	std::vector<Mesh> mesh2 = obj2->getModel().meshes;

	for (int i = 0; i < mesh1.size(); i++){
		for (int j = 0; j < mesh2.size(); j++){

			if ((mesh1[i].maxX >= mesh2[j].maxX) && (mesh1[i].maxX <= mesh2[j].maxX)) {
				flagX = true;
			}
			if ((mesh1[i].maxY >= mesh2[j].maxY) && (mesh1[i].maxY <= mesh2[j].maxY)) {
				flagY = true;
			}
			if ((mesh1[i].maxZ >= mesh2[j].maxZ) && (mesh1[i].maxZ <= mesh2[j].maxZ)) {
				flagZ = true;
			}
		}
	}

	

	/*if ((obj1->getArestas()[0].x >= obj2->getArestas()[0].x) && (obj1->getArestas()[0].x <= obj2->getArestas()[1].x))
	{
		flagX = true;
	}
	if ((obj1->getArestas()[0].y >= obj2->getArestas()[0].y) && (obj1->getArestas()[0].y <= obj2->getArestas()[1].y))
	{
		flagY = true;
	}
	if ((obj1->getArestas()[0].z >= obj2->getArestas()[0].z) && (obj1->getArestas()[0].z <= obj2->getArestas()[1].z))
	{
		flagZ = true;
	}*/

	if ((flagX == true) && (flagY == true) && (flagZ == true)){ 
		std::cout << "Colidiu" << std::endl;
		return true;
	}

	return false;
}

bool Physics::narrowPhase(GameObject obj1, GameObject obj2)
{
	//calcular o bounding box da mesh do player 
	float planeDistance = 0;
	float radius = 1.5f;
	float x_min, y_min, z_min;
	float x_max, y_max, z_max;
	glm::vec3 point = obj1.getPosition();
	glm::vec3 point2 = obj2.getPosition();
	for (size_t i = 0; i < obj2.getModel().meshes.size(); i++)
	{
		bool breakPlane = false;
		bool inside_sphere = false;
		bool inside_Binding_box = false;
		x_max = obj2.getModel().meshes[i].maxX + point2.x;// operacao entre o position e a mesh
		y_max = obj2.getModel().meshes[i].maxY + point2.y;
		z_max = obj2.getModel().meshes[i].maxZ + point2.z;
		x_min = obj2.getModel().meshes[i].minX + point2.x;
		y_min = obj2.getModel().meshes[i].minY + point2.y;
		z_min = obj2.getModel().meshes[i].minZ + point2.z;
		float boundSphereRadius = distance(point2, glm::vec3(x_min, y_min, z_min));
		if (boundSphereRadius <0)
		{
			boundSphereRadius *= -1;
		}
		boundSphereRadius -= 4.0f;

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
			if (distance_from_center_to_center <0)
			{
				distance_from_center_to_center *= -1;
			}

			if (distance_from_center_to_center < (boundSphereRadius))
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
			//analise de colisão eixo a eixo
			if (x_min < point.x && point.x < x_max)
			{
				if (y_min < point.y && point.y < y_max + 0.5 )
				{
					if (z_min < point.z && point.z < z_max) 
					{
						
							inside_Binding_box = true;
						
					}
				}

			}

			isCollision(&obj1, &obj2);

			if (planeDistance < 0)
				planeDistance *= -1;
			if ((planeDistance < radius))
			{
				breakPlane = true;
			}
			if (inside_sphere && breakPlane && inside_Binding_box)//resposta a colisao
			{
				this->normalResponse = normal;
				return true;
			}
			if (j >= obj2.getModel().meshes[i].indices.size() - 3)//evitar repeticao de vertice
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
