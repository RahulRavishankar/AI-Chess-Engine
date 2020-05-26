#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <map>
#include <QVector>
using namespace std;
#define PAWN 10   	//P
#define KNIGHT 30	//N
#define BISHOP 30	//B
#define ROOK 50		//R
#define QUEEN 90	//Q
#define KING 900	//K

/*template for all classes in Piece
{
	public:
		bool isValid(const vector<vector<char> >&,int, int, int, int)=0;    
		void allMoves(vector<vector<char> > &board,vector< vector<vector<char> > > &boardStates,int &index, int init_row, int init_col)
};*/
class Piece
{
	class Pawn
	{
		public:
            bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
                if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = dest_row - init_row;
				int diff2 = dest_col - init_col;
                
				//white pieces can't move backwards (Denoted by capital letter)
                if(board[init_row][init_col]>=65 && board[init_row][init_col]<91 && diff1>0)  //>
					return false;
				
				//black pieces can't move backwards (Denoted by small letter)
                if(board[init_row][init_col]>=97 && board[init_row][init_col]<123 && diff1<0)  //<
					return false;
                
				diff1=abs(diff1);
				diff2=abs(diff2);

				//out of bounds
				if (diff1> 2 || diff2 > 1 || (!diff1 && !diff2))
					return false;

				//move one step diagonally
				if (diff1==1 && diff2==1)
				{
					//Killing a piece via a pawn
					if(!isEmpty(board,dest_row,dest_col) && isDifferentColor(board,init_row,init_col,dest_row,dest_col) )
						return true; 
					
					return false;
                }
				//move one or two steps further
				return true;
			}
            void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				//int count_moves=0; cout<<"number of moves=====\n";
				QVector<int> dx;
				if(board[init_row][init_col]=='p')	dx={1,1, 1};
				else								dx={-1,-1,-1};
				QVector<int> dy={0,-1,1};
				/*QVector<int> dx={-1,-1,-1,0,1,1, 1,0};
				QVector<int> dy={-1, 0, 1,1,1,0,-1,1};*/
				for(int di=0;di<dx.size();di++)
				{
					if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
					{
						addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]); //count_moves++;
					}
						
				}
				//cout<<"Number of moves added: "<<count_moves<<"\n";
			}
	};

	class Knight
	{
		public:
            bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
				if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = abs(dest_row - init_row);
				int diff2 = abs(dest_col - init_col);
				
				if ( (diff1 == 2 && diff2 == 1) || (diff1 == 1 && diff2 == 2) ) 
				{
					if(!isEmpty(board,dest_row,dest_col))
					{
						if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
							return true;
						else
							return false;
					}
					return true;
				}
				
				return false;
			}
			void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				//int count_moves=0; cout<<"number of moves(Knight)=====\n";
				QVector<int> dx={-2,-1, 1, 2, 2, 1,-1,-2};
				QVector<int> dy={ 1, 2, 2, 1,-1,-2,-2,-1};
				for(int di=0;di<8;di++)
				{
					if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
					{
						addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]); //count_moves++;
					}
				}
				//cout<<"Number of moves added: "<<count_moves<<"\n";
			}
	};

	class Bishop
	{
		public:
			bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
				if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = abs(dest_row - init_row);
				int diff2 = abs(dest_col - init_col);

				//return false if the movement is not diagonal
				if(diff1!=diff2)
					return false;

				if(isJump(board,init_row,init_col,dest_row,dest_col))
					return false;
				
				if(isEmpty(board,dest_row,dest_col))
					return true;

				if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
					return true;

				return false;
			}
			void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				generateDiagonalMoves(board,boardStates,init_row,init_col);
			}
	};

	class King
	{
		public:
			bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
				if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = abs(dest_row - init_row);
				int diff2 = abs(dest_col - init_col);

				if( (diff1==1 && diff2==1) ||	(diff1==0 && diff2==1) ||	(diff1==1 && diff2==0) )
				{
					if(!isEmpty(board,dest_row,dest_col))
					{
						return isDifferentColor(board,init_row,init_col,dest_row,dest_col);
					}
					return true;
				}
				return false;
			}
			void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				QVector<int> dx={-1,-1,-1, 0, 1, 1, 1, 0};
				QVector<int> dy={-1, 0, 1, 1, 1, 0,-1, 1};
				for(int di=0;di<8;di++)
				{
					if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
					{
						addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]);
					}
				}
			}
	};

	class Queen
	{
		public:
			bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
				if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = abs(dest_row - init_row);
				int diff2 = abs(dest_col - init_col);

				//horizontal or vertical movement
				if( (diff1==0 && diff2>0) || (diff1>0 && diff2==0) )
				{
					if(isJump(board,init_row,init_col,dest_row,dest_col))
						return false;
					
					if(!isEmpty(board,dest_row,dest_col))
					{
						if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
							return true;
						
						return false;
					}
					return true;
				}

				//diagonal movement
				if(diff1==diff2)
				{
					if(isJump(board,init_row,init_col,dest_row,dest_col))
						return false;
					
					if(isEmpty(board,dest_row,dest_col))
						return true;

					if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
						return true;
				}

				return false;
			}
			void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				generateAxialMoves(board,boardStates,init_row,init_col);
				generateDiagonalMoves(board,boardStates,init_row,init_col);
			}
	};

	class Rook
	{
		public:
			bool isValid(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
			{
				//if initial sqauare is empty return false 
				if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
					return false;

				int diff1 = abs(dest_row - init_row);
				int diff2 = abs(dest_col - init_col);

				if( (diff1==0 && diff2>0) || (diff1>0 && diff2==0) )
				{
					if(isJump(board,init_row,init_col,dest_row,dest_col))
						return false;
					
					if(!isEmpty(board,dest_row,dest_col))
					{
						if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
							return true;
						
						return false;
					}
					return true;
				}
                return false;
			}
			void allMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, int init_row, int init_col)
			{
				generateAxialMoves(board,boardStates,init_row,init_col);
			}
	};
	public:
        Pawn pawn; Knight knight; Bishop bishop; Rook rook; Queen queen; King king;
        static bool isJump (const QVector<QVector<char> > &board, int,int,int,int);
        static bool isEmpty(const QVector<QVector<char> > &board, int dest_row, int dest_col);
        static bool isDifferentColor(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col);
        static int calculateScore(const QVector<QVector<char> > &board);
		static bool isOutofRange(int row,int col);
		static void addMove(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, 
							int init_row, int init_col,int dest_row,int dest_col);
		static void generateAxialMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates,
							int init_row, int init_col);
		static void generateDiagonalMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates,
							int init_row, int init_col);
};
#endif
