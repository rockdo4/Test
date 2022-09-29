#pragma once
#include "SpriteGameObject.h"
#include <SFML/Graphics.hpp>
#include "Branch.h"
#include "EffectLog.h"
#include <list>

using namespace sf;
using namespace std;

class Player : public SpriteGameObject
{
protected:
	Texture texLog;
	list<EffectLog*> unuseLogs;
	list<EffectLog*> useLogs;

	Texture& texPlayer;
	Texture& texRip;
	Sprite axe;
	Vector2f axePos;

	bool isAlive;
	bool isChopping;

	Sides pos;
	Vector2f centerPos;
	vector<Vector2f> originalPos;


public:
	Player(Texture& player, Texture& rip, Texture& axe);

	void Set(Vector2f center);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPosition(Vector2f pos) override;
	virtual void SetFlipX(bool flip) override;

	void ShowLogEffect();

	bool GetAlive() const;
	Sides GetPos() const;

	void Die();
	void Chop(Sides side);
};

