#include "GameUtil.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "AISpaceship.h"
#include "BoundingSphere.h"
#include <cstdlib>

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
AISpaceship::AISpaceship()
	: GameObject("AISpaceship"), mThrust(0)
{
}

/** Construct a AISpaceship with given position, velocity, acceleration, angle, and rotation. */
AISpaceship::AISpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("AISpaceship", p, v, a, h, r), mThrust(0)
{
}

/** Copy constructor. */
AISpaceship::AISpaceship(const AISpaceship& s)
	: GameObject(s), mThrust(0)
{
}

/** Destructor. */
AISpaceship::~AISpaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this AISpaceship. */
void AISpaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this AISpaceship. */
void AISpaceship::Render(void)
{
	if (mAISpaceshipShape.get() != NULL) mAISpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}

/** Fire the rockets. */
void AISpaceship::Thrust(float t)
{
	mThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust * cos(DEG2RAD * mAngle);
	mAcceleration.y = mThrust * sin(DEG2RAD * mAngle);
}

/** Set the rotation. */
void AISpaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void AISpaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the AISpaceship is headed
	GLVector3f AISpaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
	AISpaceship_heading.normalize();
	// Calculate the point at the node of the AISpaceship from position and heading
	GLVector3f bullet_position = mPosition + (AISpaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + AISpaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> bullet
	(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

}

bool AISpaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void AISpaceship::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}