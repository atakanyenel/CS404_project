#ifndef PROBABILTY_H
#define PROBABILTY_H
#include <map>
#include "Header.h"
using namespace std;

//static struct Map;
typedef std::map<int, int>::iterator it_type;

//probability functionlarý buraya gelecek

map<int, int> getFringe(int x, int y);
void inTheFringeZeros(Map & agentmap, map<int, int> &m);
int Factorial(int val);
int Combination(int N, int R);
float probSum(float prior, int n);
float pitProb(int x, int y, Map &agentmap, float prior);
float wumpusProb(int x, int y, Map &agentmap, float prior);
float goldProb(int x, int y, Map &agentmap, float prior);

#endif