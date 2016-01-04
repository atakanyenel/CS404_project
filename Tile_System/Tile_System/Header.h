struct Cell
{
	bool Breeze;
	bool Glitter;
	bool Smell;
	bool Wumpus;
	bool Pit;
	bool Gold;
	bool Safe;
	bool visited;

	Cell()
	{
		Breeze = false;
		Glitter = false;
		Smell = false;
		Wumpus = false;
		Pit = false;
		Gold = false;
		Safe = false;
		visited = false;
	}
};

struct Map
{
	Cell World[5][5];

	void CreateWorld()
	{
		//-- Enter World Data Here --//
		World[4][0].Gold = true; //World[1][2].Gold=true; World[4][0]
		
		World[0][0].Pit = true;
		World[3][4].Pit=true;

		World[0][2].Wumpus = true;
		setRules();
	}

void setRules()
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
};