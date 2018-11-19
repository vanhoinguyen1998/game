#ifndef __GATE_H__
#define __GATE_H__

#include "GameObject.h"
class Gate :
	public GameObject
{
	private:
		int isStart;

public:
	Gate(int X, int Y);
	virtual ~Gate();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void Start();
	int GetStart();

};


#endif
