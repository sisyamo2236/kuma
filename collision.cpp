#include "collision.h"

collision::collision() {



}

collision::~collision() {



}

bool collision::Collision_CircleAndCircleHit(const CircleCollision* pA, const CircleCollision *pB)
{
	D3DXVECTOR2 vec = pA->ceneter - pB->ceneter;
	return D3DXVec2LengthSq(&vec) < (pA->radius + pB->radius)*(pA->radius + pB->radius);
}