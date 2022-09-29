#include "InputMgr2.h"
#include <iostream>
#include <algorithm>

vector<bool> InputMgr2::downList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::upList(Keyboard::Key::KeyCount);

void InputMgr2::ClearInput()
{
	fill(downList.begin(), downList.end(), false);
	fill(upList.begin(), upList.end(), false);
}

void InputMgr2::UpdateInput(Event& ev)
{
	switch (ev.type)
	{
	case Event::EventType::KeyPressed:
		if (ev.key.code != Keyboard::Key::Unknown && !ingList[ev.key.code])
		{
			downList[ev.key.code] = true;
			ingList[ev.key.code] = true;
		}
		break;
	case Event::EventType::KeyReleased:
		if (ev.key.code != Keyboard::Key::Unknown)
		{
			ingList[ev.key.code] = false;
			upList[ev.key.code] = true;
		}
		break;
	}
}

bool InputMgr2::GetKeyDown(Keyboard::Key key)
{
	return downList[key];
}

bool InputMgr2::GetKey(Keyboard::Key key)
{
	return ingList[key];
}

bool InputMgr2::GetKeyUp(Keyboard::Key key)
{
	return upList[key];
}
