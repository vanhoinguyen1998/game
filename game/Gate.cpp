#include "Gate.h"



Gate::Gate(int X, int Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::GATE);
	_sprite = new GSprite(_texture, 200);
	type = eID::GATE;
	Health = 1;
	isStart = 0;
	x = X;
	y = Y;
}


Gate::~Gate()
{
}

void Gate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void Gate::Update(DWORD dt, vector<LPOBJECT>* coObjects)
{
	GameObject::Update(dt); // update dt
}

void Gate::Render(Camera * camera)
{
	if (isStart != 0)
	{

		int index = _sprite->GetIndex();
		switch (isStart)
		{
		case 1:
		{
			_sprite->_timeLocal += dt;
			if (_sprite->_timeLocal >= 1000)
			{
				_sprite->_timeLocal = 0;
				_sprite->Next();
				isStart++;
			}
			break;
		}
		case 2:
		{
			_sprite->_timeLocal += dt;
			if (_sprite->_timeLocal >= 500)
			{
				_sprite->_timeLocal = 0;
				_sprite->Next();
				isStart++;
			}
			break;
		}
		case 3:
		{
			_sprite->_timeLocal += dt;
			if (_sprite->_timeLocal >= 500)
			{
				_sprite->_timeLocal = 0;
				_sprite->Next();
				isStart++;
			}
			break;
		}
		default:
			break;
		}

		
	}


	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);


	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}

void Gate::Start()
{
	isStart = 1;
}

int Gate::GetStart()
{
	return isStart;
}
