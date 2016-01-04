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
		World[4][0].Gold = true;
		World[2][2].Pit = true;

		World[3][1].Pit = true;
		World[2][4].Pit = true;

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
					World[k + 1][j].Breeze = true;
					World[k - 1][j].Breeze = true;
					World[k][j + 1].Breeze = true;
					World[k][j - 1].Breeze = true;
				}
				else if (World[k][j].Wumpus)
				{
					World[k + 1][j].Smell = true;
					World[k - 1][j].Smell = true;
					World[k][j + 1].Smell = true;
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