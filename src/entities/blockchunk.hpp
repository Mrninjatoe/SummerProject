#pragma once
#include <memory>
#include "../entity.hpp"
#include "primitivemeshes.hpp"
#include "glm/gtc/matrix_transform.hpp"



class BlockChunk : public Entity {
public:
	BlockChunk(int nrOfBlocks);
	virtual ~BlockChunk();
private:
	int _nrOfBlocks;
	glm::mat4 _modelMatrices;
	std::shared_ptr<PrimitiveMeshes> _mesh;
};