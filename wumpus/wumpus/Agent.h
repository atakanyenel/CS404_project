#pragma once
#include "Map.h"
		// NORTH SOUTH EAST WEST 
class Agent
{
		
public:
	Agent(Map m,int r,int c);
	Map GetMap();
	~Agent(void);
	void LeftTurn();
	void RightTurn();
	void Forward();
		enum direction{NORTH,SOUTH,EAST,WEST};
	direction dir;
	void Grab(Map&);
	void Release(Map&);
	void Shoot(Map&);
	void UpdateLocal(Cell current);
	void adjacentSafe();
	void setDirection(direction);
	void setDirection(int d);
	void PrintLocal();
	void CheckPit(int adj[4][2]);
	void CheckWumpus(int adj[4][2]);
	Cell getCurrentCell(Map m);
		bool hasGold;

	int currentc;
		int currentr;
private:
	Map local;



	
	
	bool hasarrow;

	
};

