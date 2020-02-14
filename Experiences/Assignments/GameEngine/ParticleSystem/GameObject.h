#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector.h"
#include "Sprite.h"
#include "Collider.h"

class GameObject
{
protected:
	Sprite* m_sprite;
	Vector m_position;
	float m_rotation;
	float m_scale;
	Color m_color;
	enumBlend m_blendMode;
	// box collider
	BoxCollider boxCollider;

public:
	GameObject();
	GameObject(Sprite* sprite, Vector position, float rotation, float scale, Color color, enumBlend blendMode);

	~GameObject();

	void SetPos(Vector pos);
	const Vector& GetPos();
	void SetRotation(float rotate);
	float GetRotation();
	void SetScale(float scale);
	float GetScale();
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite();
	void SetColor(Color color);
	Color GetColor();
	void SetBlendingMode(enumBlend blend);
	enumBlend GetBlendingMode();

	void Draw();
	virtual void Update(double deltaTime);

	// extra
	void SetBoxColliderSize(Matrix locationMatrix);
	void DrawBoxCollider();
	BoxCollider GetBoxCollider();
};

#endif

