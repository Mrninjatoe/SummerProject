#include "blockchunk.hpp"

BlockChunk::BlockChunk(int nrOfBlocks) {
	_mesh = std::make_shared<PrimitiveMeshes>("assets/model/cube.obj");
	_nrOfBlocks = nrOfBlocks;
}

BlockChunk::~BlockChunk() {
	
}