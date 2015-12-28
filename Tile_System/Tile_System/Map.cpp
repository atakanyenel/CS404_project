#include "Map.h"

Map::Map()
{
	size=4;

}

Map::Map(int s)
{
	size=s;
}

Map::~Map(void)
{
}

void Map::CreateWorld()
{
	//There is 1 wumpus
	World[2][0].Wumpus=true;
	//3 pits
	World[2][2].Pit=true;
	World[3][3].Pit=true;
	World[0][2].Pit=true;
	//1 Gold
	World[2][1].Gold=true;

	setRules();
}
void Map::setRules()
{
	for(int k=0;k<4;k++)
	{
		for(int j=0;j<4;j++)
		{
			if(World[k][j].Pit)
			{
				setAdjBreeze(k,j); //Set adjacent squares to Breeze
			}
			else if(World[k][j].Wumpus)
			{
				setAdjSmell(k,j);	//Set adjacent squares to Smell
			}
			else if(World[k][j].Gold)
			{
				World[k][j].Glitter=true;//Square with Gold glitters
			}

		}
	}
}
void Map::setAdjBreeze(int r,int c)
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
void Map::setAdjSmell(int r,int c)
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
Map Map::operator=(Map other)
{
	Map mymap;
	for(int r=0;r<size;r++)
	{
		for(int c=0;c<size;c++)
		{
			mymap.World[r][c]=other.World[r][c];
		}
	}
	return mymap;

}