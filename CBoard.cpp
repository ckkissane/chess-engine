#include <assert.h>
#include "PieceTables.h"
#include "CBoard.h"

#define YELLOW "[33m"
#define BLUE   "[34m"
#define NORM   "[0m"

std::ostream& operator <<(std::ostream &os, const CBoard &rhs)
{
    static const char pieces[] = "kqrbnp.PNBRQK";

    for (int row=8; row>=1; --row)
    {
        os << NORM << row << " ";
        for (int col=1; col<=8; ++col)
        {
            int idx = (row+1)*10+col;
            int piece = rhs.chess_board[idx];
            if (piece != IV)
            {
                if (piece < 0)
                    os << BLUE;
                else if (piece > 0)
                    os << YELLOW;
                else
                    os << NORM;
                os << pieces[piece+6] << " ";
            }
        }
        os << std::endl;
    }
    os << NORM;
    os << "  a b c d e f g h" << std::endl;
    switch (rhs.side_to_move)
    {
        case  1 : os << "White to move" << std::endl; break;
        case -1 : os << "Black to move" << std::endl; break;
    }

    os << std::endl;
    os << "Material : " << rhs.material << std::endl;
    if (rhs.isKingInCheck())
    {
        os << "You are in check!" << std::endl;
    }
    return os;
} 


void CBoard::newGame()
{
    e_piece initial[120] = {
        IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
        IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
        IV, WR, WN, WB, WQ, WK, WB, WN, WR, IV,
        IV, WP, WP, WP, WP, WP, WP, WP, WP, IV,
        IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
        IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
        IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
        IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
        IV, BP, BP, BP, BP, BP, BP, BP, BP, IV,
        IV, BR, BN, BB, BQ, BK, BB, BN, BR, IV,
        IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
        IV, IV, IV, IV, IV, IV, IV, IV, IV, IV} ;

    chess_board.reserve(120);
    for (int i=0; i<120; ++i)
    {
        chess_board[i] = initial[i];
    }

    side_to_move = 1;
    material = 0;
}

//Returns true if opposite side to move threatens square
bool CBoard::isSquareThreatened(const CSquare& sq) const
{
    if (side_to_move > 0)
    {
        // pawns
        if (chess_board[sq + NW] == BP || chess_board[sq + NE] == BP)
            return true;

        // Knights
        {
            int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

            for (int k=0; k<8; ++k)
            {
                int dir = dirs[k];
                if (chess_board[sq + dir] == BN)
                    return true;
            }
        }

        // Bishops/Queens (Diagonal)
        {
            int dirs[4] = {NW, NE, SW, SE};

            for (int k=0; k<4; ++k)
            {
                int dir = dirs[k];
                int sq2 = sq;
                while (1)
                {
                    sq2 += dir;
                    if (chess_board[sq2] == BB || chess_board[sq2] == BQ)
                        return true;
                    if (chess_board[sq2] != EM)
                        break;
                }

            }
        }

        // Rook/Queens(Horizontal/Vertical)
        {
            int dirs[4] = {N, S, W, E};

            for (int k=0; k<4; ++k)
            {
                int dir = dirs[k];
                int sq2 = sq;
                while (1)
                {
                    sq2 += dir;
                    if (chess_board[sq2] == BR || chess_board[sq2] == BQ)
                        return true;
                    if (chess_board[sq2] != EM)
                        break;
                }

            }
        }

        //King
        {
            int dirs[8] = {NW, NE, SW, SE, N, S, W, E};

            for (int k=0; k<8; ++k)
            {
                int dir = dirs[k];
                if (chess_board[sq + dir] == BK)
                    return true;
            }
        }
    }
    else
    {
        // Same as above, but side to move is black
        //Pawns
        if (chess_board[sq + SW] == WP || chess_board[sq + SE] == WP)
            return true;

        //Knights
        {
            int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

            for (int k=0; k<8; ++k)
            {
                int dir = dirs[k];
                if (chess_board[sq + dir] == WN)
                    return true;
            }
        }

        //Bishops/Queens (Diagonal)
        {
            int dirs[4] = {NW, NE, SW, SE};

            for (int k=0; k<4; ++k)
            {
                int dir = dirs[k];
                int sq2 = sq;
                while (1)
                {
                    sq2 += dir;
                    if (chess_board[sq2] == WB || chess_board[sq2] == WQ)
                        return true;
                    if (chess_board[sq2] != EM)
                        break;
                }

            }
        }

        //Rook/Queen (Horizontal/Vertical)
        {
            int dirs[4] = {N, S, W, E};

            for (int k=0; k<4; ++k)
            {
                int dir = dirs[k];
                int sq2 = sq;
                while (1)
                {
                    sq2 += dir;
                    if (chess_board[sq2] == WR || chess_board[sq2] == WQ)
                        return true;
                    if (chess_board[sq2] != EM)
                        break;
                }

            }
        }

        //King
        {
            int dirs[8] = {NW, NE, SW, SE, N, S, W, E};

            for (int k=0; k<8; ++k)
            {
                int dir = dirs[k];
                if (chess_board[sq + dir] == WK)
                    return true;
            }
        }
    }

    return false;
}


void CBoard::find_legal_moves(CMoveList &moves) const
{
    moves.clear();

    if (side_to_move > 0)
        for (int i=A1; i<=H8; ++i)
        {
            int8_t piece = chess_board[i];
            int j;

            switch (piece)
            {
                case WP :
                    j = i + 10;// One square forward
                    if (chess_board[j] == EM)
                    {
                        if (i > 80) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, EM, WQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, WR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, WB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, WN);
                                moves.push_back(move);
                            }
                        }
                        else // regular pawn move
                        {
                            CMove move(piece, i, j, EM);
                            moves.push_back(move);
                        }

                        j = i + 20; // Two squares forward
                        if (chess_board[j] == EM)
                        {
                            if (i < 40) // Only from second rank (first move)
                            {
                                CMove move(piece, i, j, EM);
                                moves.push_back(move);
                            }
                        }
                    }

                    j = i + 9; // Diagonal capture
                    if ((chess_board[j] != IV && chess_board[j] < 0))
                    {
                        if (i > 80) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, chess_board[j], WQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WN);
                                moves.push_back(move);
                            }
                        }
                        else
                        {
                            CMove move(piece, i, j, chess_board[j]);
                            moves.push_back(move);
                        }
                    }

                    j = i + 11; // Diagonal capture
                    if ((chess_board[j] != IV && chess_board[j] < 0))
                    {
                        if (i > 80) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, chess_board[j], WQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], WN);
                                moves.push_back(move);
                            }
                        }
                        else
                        {
                            CMove move(piece, i, j, chess_board[j]);
                            moves.push_back(move);
                        }
                    }
                    break;

                case WN : // White knight 
                    {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];

                            j = i+dir;
                            if (chess_board[j] != IV) 
                                if (chess_board[j] <= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                }
                        }
                    }

                    break;

                case WB : // White bishop
                    {
                        int dirs[4] = {NE, NW, SE, SW};

                        for (int k=0; k<4; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] <= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] < 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case WR : // White rook
                    {
                        int dirs[4] = {N, E, S, W};

                        for (int k=0; k<4; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] <= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] < 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case WQ : // White queen
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] <= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] < 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case WK : // White king
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];

                            j = i+dir;
                            if (chess_board[j] != IV) 
                                if (chess_board[j] <= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                }
                        }

                    }

                    break;

                default : // Invalid, wrong color, or empty
                    continue;
            }

        }

    else
        for (int i=A1; i<=H8; ++i)
        {
            int8_t piece = chess_board[i];
            int j;

            switch (piece)
            {
                case BP : // Black pawn
                    j = i - 10; // One squre forward
                    if (chess_board[j] == EM)
                    {
                        if (i < 40) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, EM, BQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, BR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, BB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, EM, BN);
                                moves.push_back(move);
                            }
                        }
                        else // Regular pawn move
                        {
                            CMove move(piece, i, j, EM);
                            moves.push_back(move);
                        }

                        j = i - 20; // Two squares forward
                        if (chess_board[j] == EM)
                        {
                            if (i > 80) // Only from seventh rank
                            {
                                CMove move(piece, i, j, EM);
                                moves.push_back(move);
                            }
                        }
                    }

                    j = i - 9; // Diagonal capture
                    if ((chess_board[j] != IV && chess_board[j] > 0))
                    {
                        if (i < 40) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, chess_board[j], BQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BN);
                                moves.push_back(move);
                            }
                        }
                        else
                        {
                            CMove move(piece, i, j, chess_board[j]);
                            moves.push_back(move);
                        }
                    }

                    j = i - 11; // Diagonal capture
                    if ((chess_board[j] != IV && chess_board[j] > 0))
                    {
                        if (i < 40) // Check for promotion
                        {
                            {
                                CMove move(piece, i, j, chess_board[j], BQ);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BR);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BB);
                                moves.push_back(move);
                            }
                            {
                                CMove move(piece, i, j, chess_board[j], BN);
                                moves.push_back(move);
                            }
                        }
                        else
                        {
                            CMove move(piece, i, j, chess_board[j]);
                            moves.push_back(move);
                        }
                    }
                    break;

                case BN : // Black knight
                    {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];

                            j = i+dir;
                            if (chess_board[j] != IV) 
                                if (chess_board[j] >= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                }
                        }
                    }

                    break;

                case BB : // Black bishop
                    {
                        int dirs[4] = {NE, NW, SE, SW};

                        for (int k=0; k<4; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] >= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] > 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case BR : // Black rook
                    {
                        int dirs[4] = {N, E, S, W};

                        for (int k=0; k<4; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] >= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] > 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case BQ : // Black queen
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];
                            j = i;
                            while (1)
                            {
                                j += dir;
                                if (chess_board[j] == IV) break;
                                if (chess_board[j] >= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                    if (chess_board[j] > 0)
                                        break;
                                }
                                else
                                    break;
                            }
                        }
                    }

                    break;

                case BK : // Black king
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k=0; k<8; ++k)
                        {
                            int dir = dirs[k];

                            j = i+dir;
                            if (chess_board[j] != IV) 
                                if (chess_board[j] >= 0)
                                {
                                    CMove move(piece, i, j, chess_board[j]);
                                    moves.push_back(move);
                                }
                        }

                    }

                    break;

                default : // Invalid, wrong color, or empty
                    continue;
            }

        }
} 


//Updates board according to move
void CBoard::make_move(const CMove &move)
{
    switch (move.captured)
    {
        case WP : case BP : material += 1; break;
        case WN : case BN : material += 3; break;
        case WB : case BB : material += 3; break;
        case WR : case BR : material += 5; break;
        case WQ : case BQ : material += 9; break;
        default : break;
    }

    switch (move.promoted)
    {
        case WN : case BN : material += 3-1; break;
        case WB : case BB : material += 3-1; break;
        case WR : case BR : material += 5-1; break;
        case WQ : case BQ : material += 9-1; break;
        default : break;
    }

    chess_board[move.to] = chess_board[move.from];
    if (move.promoted != EM)
        chess_board[move.to] = move.promoted;
    chess_board[move.from] = EM;
    side_to_move = -side_to_move;
    material = -material;
} 


//Reverses "make_move"
void CBoard::undo_move(const CMove &move)
{
    material = -material;
    switch (move.captured)
    {
        case WP : case BP : material -= 1; break;
        case WN : case BN : material -= 3; break;
        case WB : case BB : material -= 3; break;
        case WR : case BR : material -= 5; break;
        case WQ : case BQ : material -= 9; break;
        default : break;
    }

    switch (move.promoted)
    {
        case WN : case BN : material -= 3-1; break;
        case WB : case BB : material -= 3-1; break;
        case WR : case BR : material -= 5-1; break;
        case WQ : case BQ : material -= 9-1; break;
        default : break;
    }

    chess_board[move.from] = move.piece;
    chess_board[move.to] = move.captured;
    side_to_move = -side_to_move;

} 


bool CBoard::IsMoveValid(CMove &move) const
{
    CMoveList moves;
    find_legal_moves(moves);
    for (unsigned int i=0; i<moves.size(); ++i)
    {
        if (moves[i] == move)
        {
            move.piece = chess_board[move.from];
            move.captured = chess_board[move.to];
            return true;
        }
    }
    return false;
}


int CBoard::evaluate_board()
{
    CMoveList moves;
    find_legal_moves(moves);
    int my_moves = moves.size();
    swap_sides();

    find_legal_moves(moves);
    int his_moves = moves.size();
    swap_sides();

    //Evaluate possition (piece square tables)
    int piece_square_val = 0;
    for (int i=A1; i<=H8; ++i)
    {
        int piece = chess_board[i];
        int mirror_idx = (11-i/10)*10 + (i%10);
        if (piece==WP)
            piece_square_val += pawntable[i];
        if (piece==BP)
            piece_square_val -= pawntable[mirror_idx];
        if (piece == WN)
            piece_square_val += knightstable[i];
        if (piece == BN)
            piece_square_val -= knightstable[mirror_idx];
        if (piece == WB)
            piece_square_val += bishopstable[i];
        if (piece == BB)
            piece_square_val -= bishopstable[mirror_idx];
        if (piece == WR)
            piece_square_val += rookstable[i];
        if (piece == BR)
            piece_square_val -= rookstable[mirror_idx];
        if (piece == WQ)
            piece_square_val += queenstable[i];
        if (piece == BQ)
            piece_square_val -= queenstable[mirror_idx];
        if (piece == WK)
            piece_square_val += kingstable[i];
        if (piece == BK)
            piece_square_val -= kingstable[mirror_idx];
    }

    if (side_to_move < 0)
        piece_square_val = -piece_square_val;
    
    //Final eval based on position and material
    return (my_moves-his_moves) + 100*material + piece_square_val;
}


bool CBoard::isKingInCheck() const
{
    e_piece king;
    CSquare kingSquare = 0;

    if (side_to_move == 1)
        king = WK;
    else
        king = BK;

    // Look for our king
    for (int i=A1; i<=H8; ++i)
    {
        if (chess_board[i] == king)
        {
            kingSquare = i;
            break;
        }
    }

    assert (kingSquare != 0); //king must be on board

    return isSquareThreatened(kingSquare);

} 



//Returns true if player not to move is in check.
bool CBoard::isOtherKingInCheck() const
{
    ((CBoard *)this)->side_to_move = -side_to_move;
    bool retval = isKingInCheck();
    ((CBoard *)this)->side_to_move = -side_to_move;
    return retval;
} 

bool CBoard::is_capture(const CMove& move)
{
    return move.captured!=EM;
}