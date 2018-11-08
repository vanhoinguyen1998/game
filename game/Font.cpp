#include "Font.h"



Font::Font()
{
	_texture = new GTexture("Resources\\font\\1.png", 13, 3, 37, 0);
	_sprite = new GSprite(_texture, 0);

}


Font::~Font()
{
	SAFE_DELETE(_texture);
	SAFE_DELETE(_sprite);
}

void Font::Draw(float x, float y, string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			_sprite->SelectIndex(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				_sprite->SelectIndex(s[i] - '0' + 26);
			}
			else
				_sprite->SelectIndex(36);
		_sprite->Draw(x + i * _texture->FrameWidth, y);
	}
}