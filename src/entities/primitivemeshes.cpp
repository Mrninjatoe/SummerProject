#include "primitivemeshes.hpp"

// Going to have to make a hierarchy of meshes, primtives being a subclass for mesh.

PrimitiveMeshes::PrimitiveMeshes(PrimitiveMeshes::Primitives type) {
	switch (type) {
	case Primitives::TRIANGLE:
		_createTriangle();
		break;
	case Primitives::QUAD:
		_createQuad();
		break;
	default:
		break;
	}
}

PrimitiveMeshes::PrimitiveMeshes(const std::string& name) {
	_loadMesh(name);
}

PrimitiveMeshes::~PrimitiveMeshes() {
	
}

void PrimitiveMeshes::_createTriangle() {
	_vertices.push_back(
		Vertex{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(1.0f, -1.0f, 0.0f),
			glm::vec3(1.0f, 0.f, 0.f),
			glm::vec2(0.0f, 0.0f)
		}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 1.f, 0.f),
		glm::vec2(0.0f, 0.0f)
		}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(.0f, 1.f, 1.f),
		glm::vec2(0.0f, 0.0f)
		}
	);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_fixBuffers();
}

void PrimitiveMeshes::_createQuad() {
	{
		_vertices.push_back(
			Vertex{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(0, 0, -1.f),
			glm::vec3(1.0f, 0.f, 0.f),
			glm::vec2(0.0f, 0.0f)
		}
		);
		_vertices.push_back(
			Vertex{
			glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec3(0, 0, -1.f),
			glm::vec3(1.0f, 1.f, 0.f),
			glm::vec2(0.0f, 0.0f)
		}
		);
		_vertices.push_back(
			Vertex{
			glm::vec3(0.5f, 0.5f, 0.0f),
			glm::vec3(0, 0, -1.f),
			glm::vec3(.0f, 1.f, 1.f),
			glm::vec2(0.0f, 0.0f)
		}
		);
		_vertices.push_back(
			Vertex{
			glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec3(0, 0, -1.f),
			glm::vec3(.0f, 1.f, 1.f),
			glm::vec2(0.0f, 0.0f)
		}
		);
	}

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(3);

	_fixBuffers();
}

void PrimitiveMeshes::_createPrism() {
	_vertices.push_back(
		Vertex{
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 0.f, 0.f),
		glm::vec2(0.0f, 0.0f)
	}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(1.0f, 1.f, 0.f),
		glm::vec2(0.0f, 0.0f)
	}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(.0f, 1.f, 1.f),
		glm::vec2(0.0f, 0.0f)
	}
	);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_fixBuffers();
}

void PrimitiveMeshes::_loadMesh(const std::string& fileName) {
	std::vector<int> vIndicies, uvIndicies, nIndicies;
	std::vector<glm::vec3> tmp_vertices;
	std::vector<glm::vec2> tmp_uvs;
	std::vector<glm::vec3> tmp_normal;
	char material_Name[80];
	char material_Filename[80];
	bool materials_Loaded = false;
	FILE* file = fopen(fileName.c_str(), "r");
	if (file == nullptr) {
		printf("Unable to load file!: %s\n", fileName.c_str());
	}
	else {
		while (true) {
			char line[256]; // Not sure how long a line can be in a .obj file.
			int errorCheck = fscanf(file, "%s", line);
			if (errorCheck == EOF)
				break;
			else {
				if (strcmp(line, "mtllib") == 0) {
					fscanf(file, "%s\n", material_Filename);
				}
				else if (strcmp(line, "v") == 0) {
					glm::vec3 vertex;
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					tmp_vertices.push_back(vertex);
				}
				else if (strcmp(line, "vt") == 0) {
					glm::vec2 uv;
					fscanf(file, "%f %f\n", &uv.x, &uv.y);
					tmp_uvs.push_back(uv);
				}
				else if (strcmp(line, "vn") == 0) {
					glm::vec3 normal;
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					tmp_normal.push_back(normal);
				}
				else if (strcmp(line, "f") == 0) {
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
					int worked = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1],
						&normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (worked != 9) {
						printf("File can't be read by this pleb loader lmao");
						break;
					}
					// Sends them in 0 -> 2 -> 1 wise because openGL is CW.
					vIndicies.push_back(vertexIndex[0]);
					vIndicies.push_back(vertexIndex[1]);
					vIndicies.push_back(vertexIndex[2]);

					uvIndicies.push_back(uvIndex[0]);
					uvIndicies.push_back(uvIndex[1]);
					uvIndicies.push_back(uvIndex[2]);

					nIndicies.push_back(normalIndex[0]);
					nIndicies.push_back(normalIndex[1]);
					nIndicies.push_back(normalIndex[2]);
				}
			}
		}
		Vertex tmp;
		for (int i = 0; i < vIndicies.size(); i++) {
			unsigned int vertexIndex = vIndicies[i];
			unsigned int uvIndex = uvIndicies[i];
			unsigned int normalIndex = nIndicies[i];
			glm::vec3 vertex = tmp_vertices[vertexIndex - 1]; // Because obj starts at 1
			glm::vec2 uv = tmp_uvs[uvIndex - 1];
			glm::vec3 normal = tmp_normal[normalIndex - 1];
			tmp.position = vertex;
			tmp.texCoords = uv;
			tmp.normal = normal;
			// colors.
			if (i % 2 == 0)
				tmp.color = glm::vec3(0.5, 0.1, 0.7);
			else if (i % 3 == 0)
				tmp.color = glm::vec3(0.9, 0.5, 0.9);
			else if (i % 4 == 0)
				tmp.color = glm::vec3(0.2, 0.5, 0.4);
			else
				tmp.color = glm::vec3(0.2f, 0.5f, 0.2f);
			_vertices.push_back(tmp);
			_indices.push_back(i);
		}
	}
	_fixBuffers();
}

void PrimitiveMeshes::_fixBuffers() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
		&_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::color));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::texCoords));

	glBindVertexArray(0);
}