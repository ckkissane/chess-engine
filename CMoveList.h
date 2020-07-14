#ifndef _C_MOVELIST_H_
#define _C_MOVELIST_H_

#include <iostream>
#include <vector>

#include "CMove.h"

// Object that contains array of CMoves
class CMoveList
{
    public:
        CMoveList()
        {
            move_list.reserve(100);
        }

        friend std::ostream& operator <<(std::ostream &os, const CMoveList &rhs);

        void push_back(const CMove& move)
        {
            move_list.push_back(move);
        }

        void clear()
        {
            move_list.clear();
        }

        unsigned int size() const
        {
            return move_list.size();
        }

        const CMove & operator [] (unsigned int ix) const { return move_list[ix]; }

    private:
        std::vector<CMove> move_list;

};

#endif