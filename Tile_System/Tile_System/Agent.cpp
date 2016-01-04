#include "Agent.h"


Agent::Agent(Percept m,int r=0,int c=0)
{
	//local=m;
	currentr=r;
	currentc=c;
	dir=EAST;
	hasGold=false;
	hasarrow=true;
}


Agent::~Agent(void)
{
}
Percept Agent::GetPercept()
{
return local;
}
void Agent::LeftTurn()
{
	switch (dir)
	{
case NORTH:
		dir=WEST;
		break;
case SOUTH:
		dir=EAST;
		break;
case EAST:
		dir=NORTH;
		break;
case WEST:
		dir=SOUTH;
		break;
	default:
		break;
	}
}
void Agent::RightTurn()
{
	switch (dir)
	{
case NORTH:
		dir=EAST;
		break;
case SOUTH:
		dir=WEST;
		break;
case EAST:
		dir=SOUTH;
		break;
case WEST:
		dir=NORTH;
		break;
	default:
		break;
	}
}
void Agent::Forward()
{
	switch (dir)
	{
case NORTH:
		if(currentr<4)
		currentr++;
		break;
case SOUTH:
	if(currentr>0)
		currentr--;
break;
case EAST:
	if(currentc<4)
		currentc++;
break;
case WEST:
	if(currentc>0)
		currentc--;
	break;
	default:
		break;
	}

}
void Agent::Grab(Percept & World)
{
	if(hasGold==false && local.World[currentr][currentc].Glitter==true)
	{
		World.World[currentr][currentc].Gold=false;
		World.World[currentr][currentc].Glitter=false;
		hasGold=true;
		cout<<"Grabbed the Gold"<<endl;
	}

}
void Agent::Release(Percept & World)
{
	if(hasGold==true && currentc==0 && currentr==0)
	{
		World.World[currentr][currentc].Gold=true;
		hasGold=false;
		cout<<"Released the Gold"<<endl;
	}
}
void Agent::Shoot(Percept &World)
{
	if(hasarrow)
	{
		cout<<"Arrow shot"<<endl;

	}

}
void Agent::UpdateLocal(Hucre  current)
{
	local.World[currentr][currentc]=current;	//write the observations on local Percept
	local.World[currentr][currentc].Safe=true;
	local[currentr][currentc].visited=true;

}
void Agent::PrintLocal()
{
	cout<<endl<<"Printing local Percept"<<endl;
		for (int r=local.size-1;r>-1;r--)
		{
			for (int c =0;c<local.size;c++)
			{
				if(r==currentr && c==currentc)
				{
					cout<<" A ";
				}
				else if(local.World[r][c].Safe==true)
				{
					cout<<" O ";
				
				}
				else
				{
					cout<<" X ";
				}
			
			}
				cout<<endl;
		}
}
void Agent::adjacentSafe()
{
	if(currentr-1>-1)
	{
		local.World[currentr-1][currentc].Safe=true;
	
	}
	if(currentr+1<local.size)
	{
		local.World[currentr+1][currentc].Safe=true;
	
		
	}
	if(currentc-1>-1)
	{
		local.World[currentr][currentc-1].Safe=true;
	
	

	}
	if(currentc+1<local.size)
	{
		local.World[currentr][currentc+1].Safe=true;
		
	
	}
}
Hucre Agent::getCurrentCell(Percept m)
{
	return m[currentr][currentc];
}

void Agent::CheckPit(int adj[4][2])
{
	for(int k=0;k<4;k++)
	{
		int newrow=currentr+adj[k][0];
		int newcol=currentc+adj[k][1];
		if(newrow>-1 && newrow<local.size && newcol>-1 && newcol<local.size)
		{
			if(local[newrow][newcol].Safe==false && local[newrow][newcol].absnopit==false)
			{
				local[newrow][newcol].Pit=true;
			}
		
		}
	}
}


void Agent::CheckWumpus(int adj[4][2])	
{
	for(int k=0;k<4;k++)
	{
		int newrow=currentr+adj[k][0];
		int newcol=currentc+adj[k][1];
		if(newrow>-1 && newrow<local.size && newcol>-1 && newcol<local.size)
		{
			if(local[newrow][newcol].Safe==false && local[newrow][newcol].absnowumpus==false)
			{
				local[newrow][newcol].Wumpus=true;
			}
		
		}
	}
}
void Agent::setDirection(direction d)
{
	dir=d;
}
void Agent::setDirection(int d)
{
	switch (d)
	{
	case 0:
		dir=NORTH;
		break;
	case 1:
		dir=SOUTH;
		break;
	case 2:
		dir=EAST;
		break;
	case 3:
		dir=WEST;
		break;
	default:
		break;
	}
}
void Agent::CheckInconsistent()
{
	for(int r=0;r<local.size;r++)
	{
		for (int c=0;c<local.size;c++)
		{
			if(local[r][c].absnopit && local[r][c].absnowumpus)
			{
				local[r][c].Pit=false;
				local[r][c].Wumpus=false;
				local[r][c].Safe=true;
			}
			
		}
	}


}
void Agent::nopitadjacent(int adj[4][2]){

	for(int k=0;k<4;k++)
	{
		int newrow=currentr+adj[k][0];
		int newcol=currentc+adj[k][1];
		if(newrow>-1 && newrow<local.size && newcol>-1 && newcol<local.size)
		{
			local[newrow][newcol].absnopit=true;
		
		}
	}}
void Agent::nowumpusadjacent(int adj[4][2])
{
	for(int k=0;k<4;k++)
	{
		int newrow=currentr+adj[k][0];
		int newcol=currentc+adj[k][1];
		if(newrow>-1 && newrow<local.size && newcol>-1 && newcol<local.size)
		{
			local[newrow][newcol].absnowumpus=true;
		
		}
	}
}
