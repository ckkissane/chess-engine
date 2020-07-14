#include <sstream>
#include <assert.h>

#include "CMove.h"

std::ostream& operator <<(std::ostream &os, const CMove &rhs)
{
    return os << rhs.ToShortString();
} 

static char pieces[] = "kqrbnp.PNBRQK";

std::string CMove::ToShortString() const
{
    std::stringstream ss;
    assert (captured != IV);

    ss << from;
    ss << to;

    if (promoted != EM)
    {
        ss << (char) tolower(pieces[promoted+6]); 
    }
    return ss.str();
}

std::string CMove::ToLongString() const
{
    std::stringstream ss;
    assert (captured != IV);

    ss << pieces[piece+6];
    ss << from;
    if (captured != EM)
        ss << "*";
    else
        ss << "-";

    ss << to;

    if (promoted != EM)
    {
        ss << "=";
        ss << (char) tolower(pieces[promoted+6]); 
    }
    return ss.str();
}

// Returns NULL if error
const char * CMove::FromString(const char *s)
{ 
    if (from.FromString(s) || to.FromString(s+2))
        return NULL;

    s += 4;

    piece = EM;
    captured = EM;
    promoted = EM;

    if (to.row() == 1)
    {
        switch (tolower(s[0]))
        {
            case 'q' : promoted = BQ; s++; break;
            case 'r' : promoted = BR; s++; break;
            case 'b' : promoted = BB; s++; break;
            case 'n' : promoted = BN; s++; break;
            case ' ' : break;
            case '\0': break;
            default  : return NULL;
        }
    }
    else if (to.row() == 8)
    {
        switch (tolower(s[0]))
        {
            case 'q' : promoted = WQ; s++; break;
            case 'r' : promoted = WR; s++; break;
            case 'b' : promoted = WB; s++; break;
            case 'n' : promoted = WN; s++; break;
            case ' ' : break;
            case '\0': break;
            default  : return NULL;
        }
    }

    while (s[0] == ' ')
        s++;

    return s;
} 