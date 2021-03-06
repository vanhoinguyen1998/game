﻿#ifndef __BAT_H__
#define __BAT_H__

#include "GameObject.h" 

#define BAT_SPEED_X 0.1f 
#define BAT_SPEED_Y 0.05f

#define DeltaY 20 // Biên giao động trục y


class Bat :	public GameObject
{
private:
	float yBackup; // vị trí của y ban dầu
 
public:
	Bat(float X = 0, float Y = 0, int Direction = -1);
	virtual ~Bat();
	  
 	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL); 
	void Render(Camera * camera);
	 
};

#endif