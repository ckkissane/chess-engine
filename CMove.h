#ifndef _C_MOVE_H_
#define _C_MOVE_H_

#include "CSquare.h"

typedef enum {
    EM = 0,   // Empty
    WP = 1,   // White Pawn
    WN = 2,   // White Knight
    WB = 3,   // White Bishop
    WR = 4,   // White Rook
    WQ = 5,   // White Queen
    WK = 6,   // White King
    BP = -1,  // Black Pawn
    BN = -2,  // Black Knight
    BB = -3,  // Black Bishop
    BR = -4,  // Black Rook
    BQ = -5,  // Black Queen
    BK = -6,  // Black King
    IV = 99   // INVALID
} e_piece;


class CMove
{
    public:
        friend class CBoard;

        friend std::ostream& operator <<(std::ostream &os, const CMove &rhs);

        // Constructors
        CMove() : piece(IV), captured(IV) {}

        CMove(const char *str) : captured(IV) { FromString(str); }

        CMove(int8_t piece, const CSquare& from, const CSquare& to, int8_t captured = EM, int8_t promoted=EM) :
            from(from), to(to), piece(piece), captured(captured), promoted(promoted) {}

        const char * FromString(const char *s); // Returns NULL if error

        std::string ToShortString() const;
        std::string ToLongString() const;

        CSquare     From(void) const {return from;}
        CSquare     To(void) const {return to;}
        bool        Valid(void) const { return captured != IV; } 
        bool        is_captured_piece_a_king(void) const { return (captured == WK || captured == BK); } 
        bool        is_it_a_capture(void) const { return (captured != EM); } 
        bool        operator==(const CMove& rhs) const
        {
            if (rhs.From() != From())
                return false;
            if (rhs.To() != To())
                return false;
            return true;
        }

    private:
        CSquare     from;
        CSquare     to;
        int8_t      piece;
        int8_t      captured;
        int8_t      promoted;

};

#endif