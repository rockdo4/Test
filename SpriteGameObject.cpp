#include "SpriteGameObject.h"

SpriteGameObject::SpriteGameObject(Texture& tex, Vector2f pos)
{
	sprite.setTexture(tex);
	sprite.setPosition(pos);

	//Init();
}

SpriteGameObject::~SpriteGameObject()
{
	//Release();
}

void SpriteGameObject::Init()
{
}

void SpriteGameObject::Release()
{
}


SpriteGameObject& SpriteGameObject::operator=(const SpriteGameObject& ref)
{
	return *this;
}


void SpriteGameObject::Update(float dt)
{

}

void SpriteGameObject::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteGameObject::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

Vector2f SpriteGameObject::GetSize() const
{
	FloatRect rect = sprite.getLocalBounds();
	return Vector2f(rect.width, rect.height);
}

Vector2f SpriteGameObject::GetPosition()
{
	return sprite.getPosition();
}

void SpriteGameObject::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

void SpriteGameObject::SetFlipX(bool flip)
{
	Vector2f scale = sprite.getScale();
	scale.x = flip ? -abs(scale.x) : abs(scale.x);
	sprite.setScale(scale);
}

void SpriteGameObject::Translate(Vector2f delta)
{
	Vector2f pos = sprite.getPosition() + delta;
	SetPosition(pos);
}
