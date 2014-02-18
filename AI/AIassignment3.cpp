#include<iostream>
#include<string>

#include<stdlib.h>
#include<stdio.h>
using namespace std;
int depthlimit;
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define win 10000
#define lose -10000
int maxvalue(char board[8][8],int depth,char player,int alpha,int beta);
int minvalue(char board[8][8],int depth,char player,int alpha,int beta);
struct position
{
	int x;
	int y;
};
position optimalmove[2];
class jumpormove
{
public:position pos[12][5];
	   jumpormove()
	   {
		   for(int i=0;i<12;i++)
			   for(int j=0;j<5;j++)
				   pos[i][j].x=pos[i][j].y=10;
	   }
};

void readboard(char board[8][8])
{
    int c;                 
    int count;
    
    
    char arr[8];
    printf("\nEnter the board config:\n");
    for(int i=0;i<8;i++)
    {
        c = getchar();
        count = 0;
        while ((count < 8) && (c != EOF)) 
        { 
            arr[count] = c;
            ++count;
            c = getchar();  
        }

        for(int j=0;j<8;j++)
        board[i][j]=arr[j];
    
    }     
    printf("\nEnter depth:");
    scanf("%d",&depthlimit);
    /*cout<<"\nBoard and depth read successfully:depth is "<<depthlimit;
    cout<<"\nBoard config is:";
    for(int i=0;i<8;i++)
       {    cout<<endl;
          for(int j=0;j<8;j++)
         cout<<board[i][j];           
         }*/
 }
 
int heuristic(char board[8][8])
{int acount=0,bcount=0;
int diff;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			if(board[i][j]=='o')
				acount++;
			else if(board[i][j]=='k')
				acount+=2;
			else if(board[i][j]=='*')
				bcount++;
			else if(board[i][j]=='K')
				bcount+=2;
		}
		if(bcount==0)
			return win;
		else if(acount==0)
			return lose;
		diff=acount-bcount;
		return diff;
}

void getalljumps(char board[8][8],char player,jumpormove* jmp)
{	int piece=0,mov=0;
int flag=0;
	//Player A	
		if(player=='A')
		{
				for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					flag=mov=0;	
						//a normal piece of Player A
						if(board[i][j]=='o')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=1)//i=0 is not considered coz normal piece shud be changed to king as soon as it reaches i=0
							{	//forward jumps
								if(j!=0 && j!=1)
								{	
									if(board[i-1][j-1]=='*' && board[i-2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i-1][j+1]=='*' && board[i-2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}
					
							}
							//if the piece doesn't have a jump then set its position out of board
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}

							piece++;							
						}
				
						//king piece of player A
						if(board[i][j]=='k')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=1 && i!=0)
							{	//forward jumps
								if(j!=0 && j!=1)
								{
									if(board[i-1][j-1]=='*' && board[i-2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i-1][j+1]=='*' && board[i-2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}
					
							}

							if(i!=6 && i!=7)
							{	//backward jumps
								if(j!=0 && j!=1)
								{
									if(board[i+1][j-1]=='*' && board[i+2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i+1][j+1]=='*' && board[i+2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}							
							}
							//if the king doesn't have a jump then set its position out of board
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}	

							piece++;

						}

				}
		}

		//Player B

		if(player=='B')
		{
				for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					flag=mov=0;	
						//a normal piece of Player B
						if(board[i][j]=='*')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=6)
							{	//backward jumps
								if(j!=0 && j!=1)
								{	
									if(board[i+1][j-1]=='o' && board[i+2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i+1][j+1]=='o' && board[i+2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}
					
							}
							//no jump for B's piece
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}

							piece++;

						}
				
						//king piece of player B
						if(board[i][j]=='K')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=1 && i!=0)
							{	//forward jumps
								if(j!=0 && j!=1)
								{
									if(board[i-1][j-1]=='o' && board[i-2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i-1][j+1]=='o' && board[i-2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i-2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}
					
							}

							if(i!=6 && i!=7)
							{	//backward jumps
								if(j!=0 && j!=1)
								{
									if(board[i+1][j-1]=='o' && board[i+2][j-2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j-2;
										mov++;
										flag=1;
									}
								}
						
								if(j!=6 && j!=7)
								{

									if(board[i+1][j+1]=='o' && board[i+2][j+2]=='.' )
									{
										jmp->pos[piece][mov].y=i+2;
										jmp->pos[piece][mov].x=j+2;
										mov++;
										flag=1;
									}
								}							
							}
							//if no jump for B's king
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}

							piece++;
						}
				

				}
		}

}


void getallmoves(char board[8][8],char player,jumpormove* jmp)
{
	int piece=0,mov=0;
	int flag=0;
	//player A
		if(player=='A')
		{
			for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			{
				flag=mov=0;
				//normal piece of player A
				if(board[i][j]=='o')
				{
					jmp->pos[piece][mov].y=i;
					jmp->pos[piece][mov].x=j;
					mov++;
					if(i!=0)
					{	//forward moves
						if(j!=0)
						{	
							if(board[i-1][j-1]=='.')
							{
								jmp->pos[piece][mov].y=i-1;
								jmp->pos[piece][mov].x=j-1;
								mov++;
								flag=1;
							}
						}
						
						if(j!=7)
						{

							if(board[i-1][j+1]=='.')
							{
								jmp->pos[piece][mov].y=i-1;
								jmp->pos[piece][mov].x=j+1;
								mov++;
								flag=1;
							}
						}			
					}		

					//if the piece doesn't have a mov then set its position out of board
					if(flag==0)
					{
						jmp->pos[piece][0].y=10;
						jmp->pos[piece][0].x=10;
					}
					piece++;									
				}
				
				//king piece of player A
				if(board[i][j]=='k')
				{
					jmp->pos[piece][mov].y=i;
					jmp->pos[piece][mov].x=j;
					mov++;
					if(i!=0)
					{	//forward movess
						if(j!=0)
						{
							if(board[i-1][j-1]=='.')
							{
								jmp->pos[piece][mov].y=i-1;
								jmp->pos[piece][mov].x=j-1;
								mov++;
								flag=1;
							}
						}
						
						if(j!=7)
						{

							if(board[i-1][j+1]=='.')
							{
								jmp->pos[piece][mov].y=i-1;
								jmp->pos[piece][mov].x=j+1;
								mov++;
								flag=1;
							}
						}
					
					}

						if(i!=7)
						{	//backward moves
							if(j!=0)
							{
								if(board[i+1][j-1]=='.')
								{
									jmp->pos[piece][mov].y=i+1;
									jmp->pos[piece][mov].x=j-1;
									mov++;
									flag=1;
								}
							}
						
							if(j!=7)
							{

								if(board[i+1][j+1]=='.')
								{
									jmp->pos[piece][mov].y=i+1;
									jmp->pos[piece][mov].x=j+1;
									mov++;
									flag=1;
								}
							}							
						}
						//if the king doesn't have a move then set its position out of board
						if(flag==0)
						{
							jmp->pos[piece][0].y=10;
							jmp->pos[piece][0].x=10;
						}	
						piece++;
				}
				
			}

		}
	

		//Player B

		if(player=='B')
		{
				for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					flag=mov=0;	
						//a normal piece of Player B
						if(board[i][j]=='*')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=7)
							{	//backward moves
								if(j!=0)
								{	
									if(board[i+1][j-1]=='.')
									{
										jmp->pos[piece][mov].y=i+1;
										jmp->pos[piece][mov].x=j-1;
										mov++;
										flag=1;
									}
								}
						
								if(j!=7)
								{

									if(board[i+1][j+1]=='.')
									{
										jmp->pos[piece][mov].y=i+1;
										jmp->pos[piece][mov].x=j+1;
										mov++;
										flag=1;
									}
								}
					
							}
							//no jump for B's piece
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}

							piece++;
						}
				
						//king piece of player B
						if(board[i][j]=='K')
						{
							jmp->pos[piece][mov].y=i;
							jmp->pos[piece][mov].x=j;
							mov++;
							if(i!=0)
							{	//forward moves
								if(j!=0)
								{
									if(board[i-1][j-1]=='.')
									{
										jmp->pos[piece][mov].y=i-1;
										jmp->pos[piece][mov].x=j-1;
										mov++;
										flag=1;
									}
								}
						
								if(j!=7)
								{

									if(board[i-1][j+1]=='.')
									{
										jmp->pos[piece][mov].y=i-1;
										jmp->pos[piece][mov].x=j+1;
										mov++;
										flag=1;
									}
								}
					
							}

							if(i!=7)
							{	//backward jumps
								if(j!=0)
								{
									if(board[i+1][j-1]=='.')
									{
										jmp->pos[piece][mov].y=i+1;
										jmp->pos[piece][mov].x=j-1;
										mov++;
										flag=1;
									}
								}
						
								if(j!=7)
								{

									if(board[i+1][j+1]=='.')
									{
										jmp->pos[piece][mov].y=i+1;
										jmp->pos[piece][mov].x=j+1;
										mov++;
										flag=1;
									}
								}							
							}
							//if no jump for B's king
							if(flag==0)
							{
								jmp->pos[piece][0].y=10;
								jmp->pos[piece][0].x=10;
							}

							piece++;
						}
				

				}
		}

}


int minvalue(char board[8][8],int depth,char player,int alpha,int beta)
{	
int flag=0;
int jumpi,jumpj,prune,movei,movej;
	int hvalue;
	if(depth==depthlimit)
	{
		
	//	if(heuristic(board)==win)
	//		cout<<"Depth "<<depth<<": Heuristic value of the current board = +INFINITY";
	//	else if(heuristic(board)==lose)
	//		cout<<"Depth "<<depth<<": Heuristic value of the current board = -INFINITY";
		int arbi=heuristic(board);
		
		if(arbi==win)
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board = +INFINITY";
		}
		else if(arbi==lose)
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board = -INFINITY";
		}

		else
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board ="<<heuristic(board);
		}
		return heuristic(board);
	}

	char curgamestate[8][8];
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			curgamestate[i][j]=board[i][j];
	jumpormove* jmpmov=new jumpormove();
	getalljumps(curgamestate,player,jmpmov);
	prune=0;
	int i,j;
	for( i=0;i<12;i++)
	{
		if(jmpmov->pos[i][0].x!=10)
		{
			flag=1;
			for(j=1;j<5;j++)
			{
				if(jmpmov->pos[i][j].x!=10)
				{	int fromx,fromy,tox,toy,captpiecex,captpiecey;
					char childstate[8][8];
					for(int k=0;k<8;k++)
						for(int l=0;l<8;l++)
							childstate[k][l]=curgamestate[k][l];
					fromx=jmpmov->pos[i][0].x;
					fromy=jmpmov->pos[i][0].y;
					tox=jmpmov->pos[i][j].x;
					toy=jmpmov->pos[i][j].y;
					//determine the piece eliminated
					captpiecey=(fromy+toy)/2;
					captpiecex=(fromx+tox)/2;
					//make the move ,eliminate the piece
					childstate[fromy][fromx]='.';
					childstate[toy][tox]='*';
					childstate[captpiecey][captpiecex]='.';
					cout<<"\n";
					for(int i=0;i<depth;i++)
					cout<<"\t";
					cout<<"Depth "<<depth<<":Player B moves from ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
					beta=min(beta,maxvalue(childstate,depth+1,'A',alpha,beta));
					
					if(beta<=alpha)
					{
					/*	if(beta==lose)
						{
						cout<<"\n";
						for(int i=0;i<=depth;i++)
						cout<<"\t";
						cout<<"Depth "<<depth+1<<": Heuristic value of the current board = -INFINITY";
						}
						*/
						prune=1;
						jumpi=i;
						jumpj=j;
						goto prunedjumps;
						//code to chceck A's lose
						//return alpha;
					}
				}

			}
		}
	}


	prunedjumps:
	if(prune==1)
	{ 
		int start=0;
		
		
			int fromx,fromy,tox,toy;
			
			for(;jumpi<12;jumpi++)
			{
				if(jmpmov->pos[jumpi][0].x!=10)
				{
					for(j=jumpj+1;j<5;j++)
					{
						if(jmpmov->pos[jumpi][j].x!=10)
						{
							fromx=jmpmov->pos[jumpi][0].x;
							fromy=jmpmov->pos[jumpi][0].y;
							tox=jmpmov->pos[jumpi][j].x;
							toy=jmpmov->pos[jumpi][j].y;
							if(start==0)
							{
								cout<<"\n Pruning Player B"<<"’"<<"s moves:"<<"("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<") ";
								start=1;
							}
							else
								cout<<", ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
						}
					}


				}
				jumpj=0;
			}
			if(start==1)
		cout<<"; Alpha = "<<alpha<<"; Beta = "<<beta;
		return alpha;
	}





	if(flag==0)
{	jumpormove* jmpmov=new jumpormove();	
	getallmoves(curgamestate,player,jmpmov);
	for(int i=0;i<12;i++)
	{
		if(jmpmov->pos[i][0].x!=10)
		{
			flag=1;
			for(int j=1;j<5;j++)
			{
				if(jmpmov->pos[i][j].x!=10)
				{
					int fromx,fromy,tox,toy;
					char childstate[8][8];
					for(int k=0;k<8;k++)
						for(int l=0;l<8;l++)
							childstate[k][l]=curgamestate[k][l];
					fromx=jmpmov->pos[i][0].x;
					fromy=jmpmov->pos[i][0].y;
					tox=jmpmov->pos[i][j].x;
					toy=jmpmov->pos[i][j].y;
					childstate[fromy][fromx]='.';
					childstate[toy][tox]='*';
					cout<<"\n";
					for(int i=0;i<depth;i++)
					cout<<"\t";
					cout<<"Depth "<<depth<<":Player B moves from ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
					beta=min(beta,maxvalue(childstate,depth+1,'A',alpha,beta));
					
					if(beta<=alpha)
					{
					
						prune=1;
					/*			if(beta==lose)
						{
							cout<<"\n";
						for(int i=0;i<=depth;i++)
						cout<<"\t";
							cout<<"Depth "<<depth+1<<": Heuristic value of the current board = -INFINITY";
							prune=0;
						}
						*/
									movei=i;
									movej=j;
									goto prunemoves;
									//code to check A's lose
						//return alpha;
					}
				}
			}
		}
	}
}
	prunemoves:
		if(prune==1)
	{  
		
		int start=0;
		
		
			int fromx,fromy,tox,toy;
			
			for(;movei<12;movei++)
			{
				if(jmpmov->pos[movei][0].x!=10)
				{
					for(j=movej+1;j<5;j++)
					{
						if(jmpmov->pos[movei][j].x!=10)
						{
							fromx=jmpmov->pos[movei][0].x;
							fromy=jmpmov->pos[movei][0].y;
							tox=jmpmov->pos[movei][j].x;
							toy=jmpmov->pos[movei][j].y;
							if(start==0)
							{
								cout<<"\n Pruning Player B"<<"’"<<"s moves:"<<"("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<") ";
								start=1;
							}
							else
								cout<<", ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
						}
					}


				}
				movej=0;
			}
			if(start==1)
		cout<<"; Alpha = "<<alpha<<"; Beta = "<<beta;
		return alpha;
	}


	if(flag==0)
	{
					
						
							cout<<"\n";
						for(int i=0;i<=depth;i++)
						cout<<"\t";
							cout<<"Depth "<<depth<<": Heuristic value of the current board = +INFINITY";
							
						
		return win;
		cout<<"Game over: Player A wins as Player B cant move";

	}
	return beta;
}

int maxvalue(char board[8][8],int depth,char player,int alpha,int beta)
{	
	
	int flag=0;
	int hvalue;
	int jumpi,jumpj,movei,movej;
	if(depth==depthlimit)
	{
		
	//	if(heuristic(board)==win)
		//	cout<<"Depth "<<depth<<": Heuristic value of the current board = +INFINITY";
		//else if(heuristic(board)==lose)
		//	cout<<"Depth "<<depth<<": Heuristic value of the current board = -INFINITY";
		int arbi=heuristic(board);
		if(arbi==win)
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board = +INFINITY";
		}
		else if(arbi==lose)
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board = -INFINITY";
		}

		else
		{
			cout<<"\n";
			for(int i=0;i<depth;i++)
			cout<<"\t";
			cout<<"Depth "<<depth<<": Heuristic value of the current board ="<<heuristic(board);
		}
		return heuristic(board);
	}

	char curgamestate[8][8];
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			curgamestate[i][j]=board[i][j];
	jumpormove* jmpmov=new jumpormove();
	getalljumps(curgamestate,player,jmpmov);
	int i,j,prune=0;
	for(i=0;i<12;i++)
	{
		if(jmpmov->pos[i][0].x!=10)
		{
			flag=1;
			for(j=1;j<5;j++)
			{
				if(jmpmov->pos[i][j].x!=10)
				{	int fromx,fromy,tox,toy,captpiecex,captpiecey;
					char childstate[8][8];
					int value;
					for(int k=0;k<8;k++)
						for(int l=0;l<8;l++)
							childstate[k][l]=curgamestate[k][l];
					fromx=jmpmov->pos[i][0].x;
					fromy=jmpmov->pos[i][0].y;
					tox=jmpmov->pos[i][j].x;
					toy=jmpmov->pos[i][j].y;
					//determine the piece eliminated
					captpiecey=(fromy+toy)/2;
					captpiecex=(fromx+tox)/2;
					//make the move ,eliminate the piece
					childstate[fromy][fromx]='.';
					childstate[toy][tox]='o';
					childstate[captpiecey][captpiecex]='.';
					cout<<"\n";
					for(int i=0;i<depth;i++)
					cout<<"\t";
					cout<<"Depth "<<depth<<":Player A moves from ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
					value=max(alpha,minvalue(childstate,depth+1,'B',alpha,beta));
                    
					if(value>=alpha)
					{
						if(depth==0)
						{
							optimalmove[0].x=fromx;
							optimalmove[0].y=fromy;
							optimalmove[1].x=tox;
							optimalmove[1].y=toy;
						}
						//code to check win situation
					/*	if(value==win)
						{
							
							cout<<"\n";
						for(int i=0;i<=depth;i++)
						cout<<"\t";
							cout<<"Depth "<<depth+1<<": Heuristic value of the current board = INFINITY";
						}
						*/
						alpha=value;
					}
					if(alpha>=beta)
					{
						prune=1;
						jumpi=i;
						jumpj=j;
						goto prunedjumps;
					//	return beta;

					}
				}

			}
		}
	}
	prunedjumps:
	if(prune==1)
	{ 
		int start=0;
		
		
			int fromx,fromy,tox,toy;
			
			for(;jumpi<12;jumpi++)
			{
				if(jmpmov->pos[jumpi][0].x!=10)
				{
					for(j=jumpj+1;j<5;j++)
					{
						if(jmpmov->pos[jumpi][j].x!=10)
						{
							fromx=jmpmov->pos[jumpi][0].x;
							fromy=jmpmov->pos[jumpi][0].y;
							tox=jmpmov->pos[jumpi][j].x;
							toy=jmpmov->pos[jumpi][j].y;
							if(start==0)
							{
								cout<<"\n Pruning Player A"<<"’"<<"s moves:"<<"("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<") ";
								start=1;
							}
							else
								cout<<", ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
						}
					}


				}
				jumpj=0;
			}
			if(start==1)
		cout<<"; Alpha = "<<alpha<<"; Beta = "<<beta;
		return beta;
	}
	if(flag==0)
	{	jumpormove* jmpmov=new jumpormove();
		getallmoves(curgamestate,player,jmpmov);
				for(int i=0;i<12;i++)
				{
					if(jmpmov->pos[i][0].x!=10)
					{
						flag=1;
						for(int j=1;j<5;j++)
						{
							if(jmpmov->pos[i][j].x!=10)
							{
								int fromx,fromy,tox,toy;
								char childstate[8][8];
								int value;
								for(int k=0;k<8;k++)
									for(int l=0;l<8;l++)
										childstate[k][l]=curgamestate[k][l];
								fromx=jmpmov->pos[i][0].x;
								fromy=jmpmov->pos[i][0].y;
								tox=jmpmov->pos[i][j].x;
								toy=jmpmov->pos[i][j].y;
								childstate[fromy][fromx]='.';
								childstate[toy][tox]='o';
								cout<<"\n";
								for(int i=0;i<depth;i++)
								cout<<"\t";
								cout<<"Depth "<<depth<<":Player A moves from ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
								value=max(alpha,minvalue(childstate,depth+1,'B',alpha,beta));
					
								if(value>alpha)
								{
									if(depth==0)
									{
										optimalmove[0].x=fromx;
										optimalmove[0].y=fromy;
										optimalmove[1].x=tox;
										optimalmove[1].y=toy;
									}
									//code to check win
								/*	if(value==win)
									{
									cout<<"\n";
									for(int i=0;i<=depth;i++)
									cout<<"\t";
										cout<<"Depth "<<depth+1<<": Heuristic value of the current board = INFINITY";
									}
									*/
									alpha=value;
								}
								if(alpha>=beta)
								{
									prune=1;
									movei=i;
									movej=j;
									goto prunemoves;
									//return beta;
								}
							}
						}
					}
				}
	}

prunemoves:
		if(prune==1)
	{  
		
		int start=0;
		
		
			int fromx,fromy,tox,toy;
			
			for(;movei<12;movei++)
			{
				if(jmpmov->pos[movei][0].x!=10)
				{
					for(j=movej+1;j<5;j++)
					{
						if(jmpmov->pos[movei][j].x!=10)
						{
							fromx=jmpmov->pos[movei][0].x;
							fromy=jmpmov->pos[movei][0].y;
							tox=jmpmov->pos[movei][j].x;
							toy=jmpmov->pos[movei][j].y;
							if(start==0)
							{
								cout<<"\n Pruning Player A"<<"'"<<"s moves:"<<"("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<") ";
								start=1;
							}
							else
								cout<<", ("<<fromy+1<<","<<fromx+1<<") to ("<<toy+1<<","<<tox+1<<")";
						}
					}


				}
				movej=0;
			}
			if(start==1)
		cout<<"; Alpha = "<<alpha<<"; Beta = "<<beta;
		return beta;
	}
	if(flag==0)
	{
					
					
							cout<<"\n";
						for(int i=0;i<=depth;i++)
						cout<<"\t";
							cout<<"Depth "<<depth<<": Heuristic value of the current board = -INFINITY";
						
						
		return lose;
		cout<<"Game over: Player B wins as Player A cant move";

	}
	return alpha;
}


void display()
{
	cout<<"\nAnswer:Player A moves from ("<<optimalmove[0].y+1<<","<<optimalmove[0].x+1<<") to ("<<optimalmove[1].y+1<<","<<optimalmove[1].x+1<<")";
}

 void checkers()
 {
		int alpha,beta;
		alpha=-10000;
		beta=10000;
		char board[8][8];
		char player='A';
		int depth =0;
		readboard(board);
		alpha=maxvalue(board,depth,player,alpha,beta);
 }
      
      
int main()
{
    
    
    checkers();
	cout<<"\nExpansions complete\n";
	display();
    getchar();
    getchar();
    return (EXIT_SUCCESS);
}
