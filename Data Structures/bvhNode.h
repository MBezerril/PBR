#pragma once
#ifndef BVHNODE_H_
#define BVHNODE_H_
#include "boxVolume.h"
class bvhNode
{
public:
	bvhNode() {
		leftChild = nullptr;
		rightChild = nullptr;
	};
	~bvhNode() {};
	bool isLeaf = false;
	int child = -1;
	std::shared_ptr<bvhNode> leftChild, rightChild;
	BoxVolume boudingBox{ glm::vec3{0,0,0}, glm::vec3{ 0,0,0 } };
private:
};

#endif
