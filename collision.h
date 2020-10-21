#ifndef COLLISION_H
#define COLLISION_H

#include<d3dx9.h>

//円形の当たり判定構造体(未使用)
typedef struct CircleCollision_tag
{

	D3DXVECTOR2 ceneter;
	float radius;


}CircleCollision;





class collision {

private:


public:

	collision();
	~collision();


	//円形の当たり判定関数(未使用)
	bool Collision_CircleAndCircleHit(const CircleCollision* pA, const CircleCollision *pB);

};






#endif // !COLLION_H


