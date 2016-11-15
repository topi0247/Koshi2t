//
//	@file	Collision.h
//	@brief	�����蔻��Ǘ��N���X
//	@date	2016/11/14
//	@outher�@�g�z��R

#pragma once
#include "./Mesh/CD3DXMESH_ANIM.h"
#include "Origin.h"
#define RAY_DISTANCE 3

class Collision
{
public:
	~Collision();
	Collision();
	bool RayIntersect(CD3DXMESH_ANIM* Mesh_a, CD3DXMESH_ANIM* Mesh_b,float* pfDistance);
};

