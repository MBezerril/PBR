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
	int childs[2] = { 0 , 0 };
	std::shared_ptr<bvhNode> leftChild, rightChild;
	BoxVolume boudingBox{ glm::vec3{0,0,0}, glm::vec3{ 0,0,0 } };
private:
};

#endif
