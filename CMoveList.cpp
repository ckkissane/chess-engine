#include "CMoveList.h"

std::ostream& operator <<(std::ostream &os, const CMoveList &rhs)
{
    for (std::vector<CMove>::const_iterator it = rhs.move_list.begin(); it != rhs.move_list.end(); ++it)
    {
        os << (*it).ToShortString() << " ";
    }

    return os;
}