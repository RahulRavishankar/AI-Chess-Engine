#include<iostream>
#include<QVector>
#include "pieces.h"
/*bool Piece::isJump (const vector<vector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
{
  int diff1 = dest_row - init_row;
  int diff2 = dest_col - init_col;

  if (diff1 == 0) {
    while (diff2-1) {
      Position pc(init_row, ++init_col);
      if (!pc.getPiece())
        return true;
    }
  } else if (diff2 == 0) {
    while (diff1-1) {
      Position pc(++init_row, init_col);
      if (!pc.getPiece())
        return true;
    }
  } else if (abs(diff1) == abs(diff2)) {
    if (diff1 < 0) {
      if (diff2 < 0) {
        for (int i = init_row-1, j = init_col-1; i > (init_row + diff1), j > (init_col + diff2); i--, j--) {
          Position pc(init_row, init_col);
          if (!pc.getPiece())
            return true;
          else
            return false;
        }
      } else {
        for (int i = init_row-1, j = init_col+1; i > (init_row + diff1), j < (init_col + diff2); i--, j++) {
          Position pc(init_row, init_col);
          if (!pc.getPiece())
            return true;
          else
            return false;
        }
      }
    } else {
      if (diff2 < 0) {
        for (int i = init_row+1, j = init_col-1; i < (init_row + diff1), j > (init_col + diff2); i++, j--) {
          Position pc(init_row, init_col);
          if (!pc.getPiece())
            return true;
          else
            return false;
        }
      } else {
        for (int i = init_row+1, j = init_col+1; i < (init_row + diff1), j < (init_col + diff2); i++, j++) {
          Position pc(init_row, init_col);
          if (!pc.getPiece())
            return true;
          else
            return false;
          }
      }
    }
  }
}*/
bool Piece::isJump(const QVector<QVector<char> > &board, int init_row, int init_col, int dest_row , int dest_col)
{
    return false;
}
bool Piece::isEmpty(const QVector<QVector<char> > &board, int row, int col)
{
    return board[row][col]==' ';
}
bool Piece::isDifferentColor(const QVector<QVector<char> > &board,int init_row, int init_col, int dest_row, int dest_col)
{
    return abs(int(board[dest_row][dest_col]) - int(board[init_row][init_col]) )>=8 ;
}
bool Piece::isOutofRange(int row,int col)
{
  return !(row>=0 && row<8 && col>=0 && col<8);
}
int Piece::calculateScore(const QVector<QVector<char> > &board)
{
    int score=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            switch(board[i][j])
            {
                //White pieces - Denoted by Capital letters - Minimise the score
                case 'P': score+=-PAWN; break;
                case 'N': score+=-KNIGHT; break;
                case 'B': score+=-BISHOP; break;
                case 'R': score+=-ROOK; break;
                case 'Q': score+=-QUEEN; break;
                case 'K': score+=-KING; break;
                //Black pieces - Denoted by Small letters - Maximise the score 
                case 'p': score+=PAWN; break;
                case 'n': score+=KNIGHT; break;
                case 'b': score+=BISHOP; break;
                case 'r': score+=ROOK; break;
                case 'q': score+=QUEEN; break;
                case 'k': score+=KING; break;
            }
        }
    }
    return score;
}
void Piece::addMove(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates, 
			int init_row, int init_col,int dest_row,int dest_col)
{
	//move the piece
	board[dest_row][dest_col]=board[init_row][init_col];	board[init_row][init_col]=' ';
	//store the current board state
    boardStates.push_back(board);		 
	//move the piece back
	board[init_row][init_col]=board[dest_row][dest_col]; 	board[dest_row][dest_col]=' ';
}
void Piece::generateAxialMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates,
						int init_row, int init_col)
{
	int row,col;
	
	row=init_row; col=init_col+1;		//movement to the right
	while(col<8 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		col++;
	}
	row=init_row+1; col=init_col;		//downward movement
	while(row<8 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row++;
	}
	row=init_row; col=init_col-1;		//movement to the left
	while(col>=0 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		col--;
	}
	row=init_row-1; col=init_col;		//upward movement
	while(row>=0 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row--;
	}
}
void Piece::generateDiagonalMoves(QVector<QVector<char> > &board,QVector< QVector<QVector<char> > > &boardStates,
						int init_row, int init_col)
{
	int row,col;

	row=init_row-1; col=init_col+1; 	//diagonal Right-Up
	while(row>=0 && col<8 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row--; col++;
	}
	row=init_row+1; col=init_col+1;		//diagonal Right-Down	
	while(row<8 && col<8 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row++; col++;
	}
	row=init_row+1; col=init_col-1;		//diagonal Left-Down
	while(row<8 && col>=0 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row++; col--;
	}
	row=init_row-1; col=init_col-1; 	//diagonal Left-Up
	while(row>=0 && col>=0 && board[row][col]==' ')
	{
		addMove(board,boardStates,init_row,init_col,row,col);
		row--; col--;
	}
}