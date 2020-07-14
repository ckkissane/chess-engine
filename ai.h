#ifndef _AI_H_
#define _AI_H_

#include "CBoard.h"

class AI
{
    public:
        AI(CBoard& board) : chess_board(board) { }

        CMove selectmove();

    private:
        int alphabeta(int alpha, int beta, int level);
        int quiesce(int alpha, int beta);

        CBoard& chess_board;
};

#endif