#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Sprite* sprite, Vector position, float rotation, float scale, Color color, enumBlend blendMode)
{
	m_sprite = sprite;
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_color = color;
	m_blendMode = blendMode;

}

GameObject::~GameObject()
{
}

void GameObject::SetPos(Vector pos)
{
	m_position = pos;
}

const Vector & GameObject::GetPos()
{
	return m_position;
}

void GameObject::SetRotation(float rotate)
{
	m_rotation = rotate;
}

float GameObject::GetRotation()
{
	return m_rotation;
}

void GameObject::SetScale(float scale)
{
	m_scale = scale;
}

float GameObject::GetScale()
{
	return m_scale;
}

void GameObject::SetSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

Sprite* GameObject::GetSprite()
{
	return m_sprite;
}

void GameObject::SetColor(Color color)
{
	m_color = color;
}

Color GameObject::GetColor()
{
	return m_color;
}

void GameObject::SetBlendingMode(enumBlend blend)
{
	m_blendMode = blend;
}

enumBlend GameObject::GetBlendingMode()
{
	return m_blendMode;
}

void GameObject::Draw()
{
	// blend
	glEnable(GL_BLEND);

	switch (m_blendMode)
	{
	case ADDITIVE:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		break;
	case MULTIPLY:
		glBlendFunc(GL_DST_COLOR, GL_ZERO); // multiply blend
		break;
	case ALPHA_BLEND:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case TEST:
		glBlendFunc(GL_DST_COLOR, GL_DST_COLOR);
		break;
	case NONE:
		break;
	}

	m_sprite->Draw(m_position.mVal[0], m_position.mVal[1], m_rotation, m_scale, m_color, m_blendMode);

	glDisable(GL_BLEND);
}

void GameObject::Update(double deltaTime)
{
}
