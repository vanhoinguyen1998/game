#include "Board.h"
 
Board::Board(int X, int Y)
{
	_texture = new GTexture("Resources\\blackboard.png");
	_sprite = new GSprite(_texture, 0);
	x = X;
	y = Y;
 
}

void Board::Render(Camera * camera)
{ 
	_sprite->Draw(x,y);
	_font.Draw(x, y+15, "SCORE-");
	_font.Draw(x, y+33, "PLAYER");
	_font.Draw(x, y+51, "ENEMY");


	_font.Draw(x+210, y + 15, "TIME");
	_font.Draw(x + 400, y + 15, "STAGE");

}


Board::~Board()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}