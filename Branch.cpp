#include "Branch.h"
#include "Utils.h"

Branch::Branch(Texture& tex, SpriteGameObject* tree)
	: SpriteGameObject(tex), tree(tree)
{

}

void Branch::Init()
{
	Vector2f treeSize = tree->GetSize();
	Vector2f branchSize = GetSize();
	sprite.setOrigin(-treeSize.x * 0.5f, branchSize.y * 0.5f);
	SetPosition(tree->GetPosition());
}

void Branch::SetSide(Sides side)
{
	switch (side)
	{
	case Sides::Left:
		sprite.setScale(-1, 1);
		break;
	case Sides::Right:
		sprite.setScale(1, 1);
		break;
	}
}
