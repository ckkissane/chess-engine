//Piece tables for each piece.
//In general, central squares are valued higher
int pawntable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, 0,  0,  0,  0,  0,  0,  0,  0, -1,
                -1, 5, 10, 10,-20,-20, 10, 10,  5, -1,
                -1, 5, -5,-10,  0,  0,-10, -5,  5, -1,
                -1, 0,  0,  0, 20, 20,  0,  0,  0, -1,
                -1, 5,  5, 10, 25, 25, 10,  5,  5, -1,
                -1, 10, 10, 20, 30, 30, 20, 10, 10, -1,
                -1, 50, 50, 50, 50, 50, 50, 50, 50, -1,
                -1, 0,  0,  0,  0,  0,  0,  0,  0, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int knightstable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1,-50,-40,-30,-30,-30,-30,-40,-50,-1,
                -1,-40,-20,  0,  5,  5,  0,-20,-40,-1,
                -1,-30,  5, 10, 15, 15, 10,  5,-30,-1,
                -1,-30,  0, 15, 20, 20, 15,  0,-30,-1,
                -1,-30,  5, 15, 20, 20, 15,  5,-30,-1,
                -1,-30,  0, 10, 15, 15, 10,  0,-30,-1,
                -1,-40,-20,  0,  0,  0,  0,-20,-40,-1,
                -1,-50,-40,-30,-30,-30,-30,-40,-50,-1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};
    
    int bishopstable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1,-20,-10,-10,-10,-10,-10,-10,-20,-1,
                -1,-10,  5,  0,  0,  0,  0,  5,-10,-1,
                -1,-10, 10, 10, 10, 10, 10, 10,-10,-1,
                -1,-10,  0, 10, 10, 10, 10,  0,-10,-1,
                -1,-10,  5,  5, 10, 10,  5,  5,-10,-1,
                -1,-10,  0,  5, 10, 10,  5,  0,-10,-1,
                -1,-10,  0,  0,  0,  0,  0,  0,-10,-1,
                -1,-20,-10,-10,-10,-10,-10,-10,-20,-1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};
    
    int rookstable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1,0,  0,  0,  5,  5,  0,  0,  0,-1
                -1,-5,  0,  0,  0,  0,  0,  0, -5,-1,
                -1,-5,  0,  0,  0,  0,  0,  0, -5,-1,
                -1,-5,  0,  0,  0,  0,  0,  0, -5,-1,
                -1,-5,  0,  0,  0,  0,  0,  0, -5,-1,
                -1,-5,  0,  0,  0,  0,  0,  0, -5,-1,
                -1,5, 10, 10, 10, 10, 10, 10,  5,-1,
                -1,0,  0,  0,  0,  0,  0,  0,  0,-1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};
    
    int queenstable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1,-20,-10,-10, -5, -5,-10,-10,-20,-1,
                -1,-10,  0,  0,  0,  0,  0,  0,-10,-1,
                -1,-10,  5,  5,  5,  5,  5,  0,-10,-1,
                -1,0,  0,  5,  5,  5,  5,  0, -5,-1,
                -1,-5,  0,  5,  5,  5,  5,  0, -5,-1,
                -1,-10,  0,  5,  5,  5,  5,  0,-10,-1,
                -1,-10,  0,  0,  0,  0,  0,  0,-10,-1,
                -1,-20,-10,-10, -5, -5,-10,-10,-20,-1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};
    
    int kingstable[120] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1,20, 30, 10,  0,  0, 10, 30, 20,-1,
                -1,20, 20,  0,  0,  0,  0, 20, 20,-1,
                -1,-10,-20,-20,-20,-20,-20,-20,-10,-1,
                -1,-20,-30,-30,-40,-40,-30,-30,-20,-1,
                -1,-30,-40,-40,-50,-50,-40,-40,-30,-1,
                -1,-30,-40,-40,-50,-50,-40,-40,-30,-1,
                -1,-30,-40,-40,-50,-50,-40,-40,-30,-1,
                -1,-30,-40,-40,-50,-50,-40,-40,-30,-1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};