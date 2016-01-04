#include "Percept.h"

Percept::Percept()
{
	size=5;

}

Percept::Percept(int s)
{
	size=s;
}

Percept::~Percept()
{
}

void Percept::CreateWorld()
{
	//There is 1 wumpus
	World[2][0].Wumpus=true;

	//3 pits
	World[2][3].Pit=true;
	World[3][3].Pit=true;
	World[0][2].Pit=true;
	//1 Gold
	World[4][4].Gold=true;		//World[2][1].Gold=true;	World[4][4].Gold

	setRules();
}

	void Percept::setRules()
	{
		for (int k = 0; k < 5; k++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (World[k][j].Pit)
				{
					if(k<4)
					World[k + 1][j].Breeze = true;
					if(k>0)
					World[k - 1][j].Breeze = true;
					if(j<4)
					World[k][j + 1].Breeze = true;
					if(j>0)
					World[k][j - 1].Breeze = true;
				}
				else if (World[k][j].Wumpus)
				{
					if(k<4)
					World[k + 1][j].Smell = true;
					if(k>0)
					World[k - 1][j].Smell = true;
					if(j<4)
					World[k][j + 1].Smell = true;
					if(j>0)
					World[k][j - 1].Smell = true;
				}
				else if (World[k][j].Gold)
				{
					World[k][j].Glitter = true;
				}
			}
		}
	}
void Percept::setAdjBreeze(int r,int c)
{
		if(r-1>-1)
		{
			World[r-1][c].Breeze=true;
		}
		if(r+1<size)
		{
			World[r+1][c].Breeze=true;
		}
		if(c+1<size)
		{
			World[r][c+1].Breeze=true;
		}
		if(c-1>-1)
		{
			World[r][c-1].Breeze=true;
		}
}
void Percept::setAdjSmell(int r,int c)
{
	if(r-1>-1)
		{
			World[r-1][c].Smell=true;
		}
		if(r+1<size)
		{
			World[r+1][c].Smell=true;
		}
		if(c+1<size)
		{
			World[r][c+1].Smell=true;
		}
		if(c-1>-1)
		{
			World[r][c-1].Smell=true;
		}
}
Percept Percept::operator=(Percept other)
{
	Percept myPercept;
	for(int r=0;r<size;r++)
	{
		for(int c=0;c<size;c++)
		{
			myPercept.World[r][c]=other.World[r][c];
		}
	}
	return myPercept;
}