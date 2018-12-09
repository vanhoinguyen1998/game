#ifndef __BOARD_H__
#define __BOARD_H__

#include "GSprite.h"
#include "GTexture.h"
#include "Camera.h"
#include "define.h"
#include "Font.h"
#include "Simon.h"
#include "BoardHealth.h"
#include "TextureManager.h"
#include "Dagger.h"

#define BOARD_DEFAULT_POSITION_X 10
#define BOARD_DEFAULT_POSITION_Y 0

class Board
{
private:
	Font _font;
	BoardHealth _boardHealth;
	
	GTexture *_texture;
	GSprite * _sprite;
	int x, y;

	string FillNumber(string s, UINT MaxNumber);

 public:
	Board(int X, int Y);
	void Render(Camera * camera, Simon * simon, int state, Weapon * weaponSub, int RemainingTime, GameObject * boss);
	~Board();

	void SetTexture(GTexture * tex);
};





#endif 


