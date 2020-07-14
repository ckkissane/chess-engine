#include <stdlib.h>

#include "ai.h"
#include "CMoveList.h"

/***************************************************************
 * minimax algo with alpha beta pruning
 * The value returned is
 * * positive if side to move is winning
 * * negative if side to move is losing
 * * 900+, if the opponent is check-mated.
 * * -999, if the side to move is check-mated.
 **=************************************************************/
int AI::alphabeta(int alpha, int beta, int level)
{
    if (level == 0)
        return chess_board.evaluate_board();

    CMoveList moves;
    chess_board.find_legal_moves(moves);

    int best_score = -9999;

    
    for (unsigned int i=0; i<moves.size(); ++i)
    {
        if (best_score >= beta)
        {
            break;
        }
        if (best_score > alpha)
        {
            alpha = best_score;
        }
        
        const CMove& move = moves[i];
        if (move.is_captured_piece_a_king())
        {
            return 900 + level;
        }

        // recurse (negamax)
        chess_board.make_move(move);
        int score = -alphabeta(-beta, -alpha, level-1);
        chess_board.undo_move(move);

        if (score > best_score)
        {
            best_score = score;
        }
    }

    return best_score;
} 

//quiesce to avoid horizon effect. Too slow right now
// need move ordering
int AI::quiesce(int alpha,int beta)
{
    int stand_pat = chess_board.evaluate_board();
    if (stand_pat >= beta)
        return beta;
    if (alpha < stand_pat)
        alpha = stand_pat;
    
    CMoveList moves;
    chess_board.find_legal_moves(moves);

    for (int i=0; i<moves.size(); ++i)
    {
        const CMove& move = moves[i];
        if (chess_board.is_capture(move))
        {
            chess_board.make_move(move);
            int score = -quiesce(-beta,-alpha);
            chess_board.undo_move(move);

            if (score>=beta)
                return beta;
            if (score > alpha)
                alpha = score;
        }
    }
    return alpha;
}

/***************************************************************
 * returns what it considers to be the best legal move in the
 * current position.
 ***************************************************************/
CMove AI::selectmove()
{
    // Make a list of all legal moves
    CMoveList moves;
    chess_board.find_legal_moves(moves);

    std::cout << "info string " << moves.size() << " legal moves." << std::endl;

    CMoveList best_moves;
    int best_val = -9999;

    // Search through all legal moves
    for (unsigned int i=0; i<moves.size(); ++i)
    {
        CMove move = moves[i];

        chess_board.make_move(move);
        int val = -alphabeta(-9999, 9999, 4);
        chess_board.undo_move(move);

        std::cout << "info string " << val << " : " << move << std::endl;

        if (val > best_val)
        {
            best_val = val;
            best_moves.clear();
            best_moves.push_back(move);
        }
        else if (val == best_val)
        {
            best_moves.push_back(move);
        }
    }

    if (best_moves.size() == 0)
    {
        std::cout << "BUG: No legal moves!" << std::endl;
        exit(1);
    }

    return best_moves[rand() % best_moves.size()];
} 