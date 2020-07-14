#include <iostream>
#include <stdlib.h>

#include "CBoard.h"
#include "ai.h"


int main()
{
    CBoard board;
    AI ai(board);

    while (true) 
    {
        
        std::cout << board;
        std::cout << "Input command (ex: move e2e4, go, quit) :";

        
        std::string str;
        getline(std::cin, str);
        std::cout << std::endl;

        if (std::cin.eof() || str == "quit")
        {
            exit(1);
        }

        if (str.compare(0, 5, "move ") == 0)
        {
            CMove move;

            if (move.FromString(str.c_str()+5) == NULL)
            {
                
                std::cout << "Error. Use long notation (ex: e2e4)" << std::endl;
                continue;
            }

            if (board.IsMoveValid(move))
            {
                board.make_move(move);
                bool check = board.isOtherKingInCheck();
                board.undo_move(move);
                if (check)
                {
                    std::cout << "Illegal, you are in check." << std::endl;
                    continue;
                }

                std::cout << "You move : " << move << std::endl;
                board.make_move(move);
            }
            else 
            {
                std::cout << "Move " << move << " is not legal." << std::endl;
                continue;
            }
        } 

        else if (str.compare(0, 2, "go") == 0)
        {
            CMove best_move = ai.selectmove();
            std::cout << "bestmove " << best_move << std::endl;
            board.make_move(best_move);
        }

        else 
        {
            std::cout << "Unknown command" << std::endl;
            std::cout << "Valid commands are: quit, move, go" << std::endl;
        }
    } 

    return 0;
}