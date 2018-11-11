#include "Brick.h"
 

Brick::Brick(int X, int Y, int W, int H)
{
	type = eID::BRICK; 
	_texture = TextureManager::GetInstance()->GetTexture(eID::BRICK);
	_sprite = new GSprite(_texture, 1000);
	this->x = (float)X;
	this->y = (float)Y;
	this->width = W;
	this->height = H;
}

void Brick::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);

	 
	for (int i = 0; i < (int)ceil(width / BRICK_FRAME_WIDTH); i++)
		for (int j = 0; j < (int)ceil(height / BRICK_FRAME_HEIGHT); j++)
			_sprite->Draw( (int) pos.x + i * BRICK_FRAME_WIDTH, (int)pos.y + j * BRICK_FRAME_HEIGHT);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / BRICK_FRAME_WIDTH)*BRICK_FRAME_WIDTH;
	b = y + (float)ceil(height / BRICK_FRAME_HEIGHT)*BRICK_FRAME_HEIGHT;
}