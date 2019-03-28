#include "scene.h"

Scene::Scene(void) {
}

Scene::~Scene(void) {
}

bool Scene::intersect(const Ray &ray,
	IntersectionRecord &intersection_record) const {
	bool intersection_result = false;
	IntersectionRecord tmp_intersection_record;
	std::size_t num_primitives = primitives_.size();

	// Loops over the list of primitives, testing the intersection of each primitive against the given ray 
	for (std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++)
		if (primitives_[primitive_id]->intersect(ray, tmp_intersection_record))
			if ((tmp_intersection_record.t_ < intersection_record.t_) && (tmp_intersection_record.t_ > 0.0)) {
				intersection_record = tmp_intersection_record;
				intersection_result = true; // the ray intersects a primitive!
			}

	return intersection_result;
}

void Scene::load(void) {
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_BONEWEIGHTS |
		aiComponent_CAMERAS |
		aiComponent_LIGHTS);
	/*
	Objects in the folder:
	Lowpoly_tree_sample
	cube
	monkey
	monkey2
	*/
	const aiScene *scene = importer.ReadFile("objts/quarto.obj",
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_RemoveComponent |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (scene == nullptr || !scene->HasMeshes()) std::exit(-10);

	float r, g, b;
	for (unsigned int j = 0; j < scene->mNumMeshes; j++) {
		aiMesh *mesh = scene->mMeshes[j];

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			aiVector3D vert1 = mesh->mVertices[face.mIndices[0]];
			aiVector3D vert2 = mesh->mVertices[face.mIndices[1]];
			aiVector3D vert3 = mesh->mVertices[face.mIndices[2]];

			glm::vec3 p1 = glm::vec3{ vert1.x, -vert1.y, vert1.z };
			glm::vec3 p2 = glm::vec3{ vert2.x, -vert2.y, vert2.z };
			glm::vec3 p3 = glm::vec3{ vert3.x, -vert3.y, vert3.z };

			b = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);

			primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{ p2, p1, p3, new DiffuseMaterial(glm::vec3(1, 1, 1)) }));
		}
	}
	//Luz da cena
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  0.0f, -1.0f,  0.0f }, 0.1f , new LightMaterial(glm::vec3(0, 0, 0) , 80.0f) }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  0.0f, 0.75f,  -0.5f }, 0.1f , new DiffuseMaterial(glm::vec3(0, 0, 1)) }));
	/*primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  2.0f, 0.0f,  0.0f }, 0.8f ,new DiffuseMaterial(glm::vec3(1, 1, 0)) }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{ 3.0f, 1.0f, 3.0f }, glm::vec3{ -3.0f, 1.0f, 3.0f }, glm::vec3{ 3.0f,  1.0f, -3.0f }, new DiffuseMaterial(glm::vec3(1, 0, 0)))));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{ -3.0f, 1.0f, 3.0f }, glm::vec3{ -3.0f, 1.0f, -3.0f }, glm::vec3{ 3.0f,  1.0f, -3.0f }, new DiffuseMaterial(glm::vec3(1, 0, 0)))));*/


	//This lines import 4 spheres and one triangle to test the program

	/*primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  0.0f, -1.0f, -2.0f }, 0.2f }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  0.0f, 1.0f,  -2.0f }, 0.2f }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  1.0f, 0.0f,  -2.0f }, 0.2f }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{ glm::vec3{  -1.0f, 0.0f, -2.0f }, 0.2f }));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{glm::vec3{ 0.5f, 0.0f, -1.0f }, glm::vec3{0.0f, 0.5f, -1.0f }, glm::vec3{ 0.0f,  0.0f, -1.0f } }));*/
}