#pragma once
#ifndef __AISpaceship_H__
#define __AISpaceship_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"
#include <cstdlib>

class AISpaceship : public GameObject
{
public:
	AISpaceship();
	AISpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	AISpaceship(const AISpaceship& s);
	virtual ~AISpaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetAISpaceshipShape(shared_ptr<Shape> AISpaceship_shape) { mAISpaceshipShape = AISpaceship_shape; }
	void SetThrusterShape(shared_ptr<Shape> thruster_shape) { mThrusterShape = thruster_shape; }
	void SetBulletShape(shared_ptr<Shape> bullet_shape) { mBulletShape = bullet_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

private:
	float mThrust;

	shared_ptr<Shape> mAISpaceshipShape;
	shared_ptr<Shape> mThrusterShape;
	shared_ptr<Shape> mBulletShape;
};

#endif