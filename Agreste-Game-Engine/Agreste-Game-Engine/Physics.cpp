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

bool Physics::isCollision(vector<GameObject*> &objList) {
	
	//lista de todos os pares ,lista de pares provaveis fazer comparacao de xmax e xmin
	//std::vector<Mesh> mesh1 = obj1->getModel().meshes;
	//std::vector<Mesh> mesh2 = obj2->getModel().meshes;

	//glm::vec3 point1 = obj1->getPosition();
	//glm::vec3 point2 = obj2->getPosition();

	
	
	vector<vector<int>> allPairs;

	for (int i = 0; i < objList.size(); i++) {
		
		for (int j = i + 1; j < objList.size(); j++) {
			vector<int> vecAux;
			//paiir<int, int> vecAuxPair;
			//cAuxPair.first = i;
	
			vecAux.push_back(i);
			//if (j > i) 
			{
				vecAux.push_back(j);
				allPairs.push_back(vecAux);
			}
			
		}
	}

	for (int i = 0; i < allPairs.size(); i++) 
	{
		/*float x_maxObj1, y_maxObj1, z_maxObj1;
		float x_maxObj2, y_maxObj2, z_maxObj2;

		float x_minObj1, y_minObj1, z_minObj1;
		float x_minObj2, y_minObj2, z_minObj2;*/
	
		bool flagX = false;
		bool flagY = false;
		bool flagZ = false;

		GameObject *obj1, *obj2;
		obj1 = objList[allPairs[i][0]];
		obj2 = objList[allPairs[i][1]];

		glm::vec3 point1 = obj1->getPosition();
		glm::vec3 point2 = obj2->getPosition();

			
		//calculando maximos obj1
		float x_maxObj1 = obj1->getModel().meshes[0].maxX + point1.x;// operacao entre o position e a mesh
		float y_maxObj1 = obj1->getModel().meshes[0].maxY + point1.y;
		float z_maxObj1 = obj1->getModel().meshes[0].maxZ + point1.z;
		//calculando maximos obj2
		float x_maxObj2 = obj2->getModel().meshes[0].maxX + point2.x;// operacao entre o position e a mesh
		float y_maxObj2 = obj2->getModel().meshes[0].maxY + point2.y;
		float z_maxObj2 = obj2->getModel().meshes[0].maxZ + point2.z;
		//calculando mínimos obj1
		float x_minObj1 = obj1->getModel().meshes[0].minX + point1.x;// operacao entre o position e a mesh
		float y_minObj1 = obj1->getModel().meshes[0].minY + point1.y;
		float z_minObj1 = obj1->getModel().meshes[0].minZ + point1.z;
		//calculando mínimos obj2
		float x_minObj2 = obj2->getModel().meshes[0].minX + point2.x;// operacao entre o position e a mesh
		float y_minObj2 = obj2->getModel().meshes[0].minY + point2.y;
		float z_minObj2 = obj2->getModel().meshes[0].minZ + point2.z;

		if ( (x_minObj1 >= x_maxObj2) || (x_maxObj1 <= x_minObj2) ) 
			flagX = true;
		
		if ( (y_minObj1 >= y_maxObj2) || (y_maxObj1 <= y_minObj2) )  
			flagY = true;
		
		if ((z_minObj1 >= z_maxObj2) || (z_maxObj1 <= z_minObj2))
			flagZ = true;
		

		//if ((flagX == false) && (flagY == false) && (flagZ == false) ) {
		if( !(flagX || flagY || flagZ) ){
		//inserir cout aqui para ver os falores das flags e outras variáveis
			//allPairs.erase(allPairs.begin() + i);
			if (!allPairs.empty()) std::cout << "()Colidiu()" << std::endl;
			narrowPhase(*obj1, *obj2);
		} 

		
	}

	//if(!allPairs.empty()) std::cout << "teste" << std::endl;

	/*for (int i = 0; i < mesh1.size(); i++){

		for (int j = 0; j < mesh2.size(); j++){

			x_maxObj1 = obj1->getModel().meshes[i].maxX + point1.x;// operacao entre o position e a mesh
			y_maxObj1 = obj1->getModel().meshes[i].maxY + point1.y;
			z_maxObj1 = obj1->getModel().meshes[i].maxZ + point1.z;

			x_maxObj2 = obj2->getModel().meshes[i].maxX + point2.x;// operacao entre o position e a mesh
			y_maxObj2 = obj2->getModel().meshes[i].maxY + point2.y;
			z_maxObj2 = obj2->getModel().meshes[i].maxZ + point2.z;

			x_minObj1 = obj1->getModel().meshes[i].maxX + point1.x;// operacao entre o position e a mesh
			y_minObj1 = obj1->getModel().meshes[i].maxX + point1.y;
			z_minObj1 = obj1->getModel().meshes[i].maxX + point1.z;

			x_minObj2 = obj1->getModel().meshes[i].maxX + point2.x;// operacao entre o position e a mesh
			y_minObj2 = obj1->getModel().meshes[i].maxX + point2.y;
			z_minObj2 = obj1->getModel().meshes[i].maxX + point2.z;
			
			if ((x_maxObj1 <= x_maxObj2) && (x_minObj1 >= x_minObj2)) {
				flagX = true;
			}
			if ((y_maxObj1 <= y_maxObj2) && (y_minObj1 >= y_minObj2)) {
				flagY = true;
			}
			if ((z_maxObj1 <= z_maxObj2) && (z_minObj1 >= z_minObj2)) {
				flagZ = true;
			}
		}
	}*/

	

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

	/*if ((flagX == true) && (flagY == true) && (flagZ == true)){ 
		std::cout << "Colidiu" << std::endl;

		return true;
	}*/

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
				if (y_min < point.y && point.y < y_max + 0.5)// pq 0.5 no Y?
				{
					if (z_min < point.z && point.z < z_max) 
					{
						
							inside_Binding_box = true;
						
					}
				}

			}

			//isCollision(&obj1, &obj2);

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
