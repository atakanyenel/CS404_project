#include "Probability.h"
map<int, int> getFringe(int x, int y){
	map<int, int> f;
	f[x] = y;
	int i = x, j = y;
	while (i - 1 >= 0 && j + 1 <= 4){
		i = i - 1;
		j = j + 1;
		f[i] = j;
	}
	i = x; j = y;
	while (i + 1 <= 4 && j - 1 >= 0){
		i = i + 1;
		j = j - 1;
		f[i] = j;
	}
	return f;
}

void inTheFringeZeros(Map & agentmap, map<int, int> &m){
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = m.begin(); iterator != m.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		int x = iterator->first;
		int y = iterator->second;
		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Breeze) || x - 1 < 0){ //Pitler
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Breeze) || y + 1 > 4){
				agentmap.World[x][y].Pit = 0;
			}
		}

		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Glitter) || x - 1 < 0){
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Glitter) || y + 1 > 4){
				agentmap.World[x][y].Gold = 0;
			}
		}

		if ((x - 1 >= 0 && !agentmap.World[x - 1][y].Smell) || x - 1 < 0){
			if ((y + 1 <= 4 && !agentmap.World[x][y + 1].Smell) || y + 1 > 4){
				agentmap.World[x][y].Wumpus = 0;
			}
		}
	}
}

int Factorial(int val)
{
	int Result = 1;
	for (int i = 1; i <= val; i++)
	{
		Result *= i;
	}
	return Result;
}
int Combination(int N, int R)
{
	return (Factorial(N)) / ((Factorial(N - R)) * Factorial(R));
}

float probSum(float prior, int n){
	float sum = 0;
	for (int i = 1; i <= n; i++){
		int comb = Combination(n, i);
		sum += comb*pow(prior, i)*pow(1 - prior, n - i);
	}
	return sum;
}

float pitProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Pit) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Pit) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter - 1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}

float wumpusProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Smell) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Wumpus) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter - 1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}

float goldProb(int x, int y, Map &agentmap, float prior){
	map<int, int> fringe = getFringe(x, y);
	inTheFringeZeros(agentmap, fringe);
	if (!agentmap.World[x][y].Gold) return 0;
	int counter = 0, zeroCounter = 0;
	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = fringe.begin(); iterator != fringe.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		counter++;
		int x = iterator->first;
		int y = iterator->second;
		if (!agentmap.World[x][y].Gold) zeroCounter++;
	}
	float positive = prior*probSum(prior, counter - zeroCounter - 1);
	float negative = (1 - prior)*probSum(prior, counter - zeroCounter - 1);
	if (x == 0 || y == 4){
		negative -= (1 - prior)*probSum(prior, counter - zeroCounter - 2);
	}

	return positive / (positive + negative);

}