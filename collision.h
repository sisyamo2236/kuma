#ifndef COLLISION_H
#define COLLISION_H

#include<d3dx9.h>

//�~�`�̓����蔻��\����(���g�p)
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


	//�~�`�̓����蔻��֐�(���g�p)
	bool Collision_CircleAndCircleHit(const CircleCollision* pA, const CircleCollision *pB);

};






#endif // !COLLION_H


