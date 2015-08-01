//
// Created by James on 30/07/15.
//

#include <iostream>
#include "../hexGraph.h"
#include "../board.h"

static void printBoard_(const HexBoard & board);
static void test_white_win(const HexBoard & board, const HexGraph & hg);
static void test_black_win(const HexBoard & board, const HexGraph & hg);
static int test_number = 0;

int main()
{
    std::cout << "LOLOL" << std::endl;

    HexBoard board(5);
    HexGraph hg;

    /* Test board configuration.
            1  2  3  4  5
        1   W  -  -  -  B   1
         2   W  -  B  B  -   2
          3   W  W  W  B  W   3
           4   B  B  B  W  B   4
            5   W  -  -  -  -   5
                 1  2  3  4  5
       Black has won this board.
     */

    // fill board up
    board[0] = TileColour::WHITE;
    board[5] = TileColour::WHITE;
    board[10] = TileColour::WHITE;
    board[11] = TileColour::WHITE;
    board[12] = TileColour::WHITE;
    board[14] = TileColour::WHITE;
    board[18] = TileColour::WHITE;
    board[20] = TileColour::WHITE;
    board[4] = TileColour::BLACK;
    board[7] = TileColour::BLACK;
    board[8] = TileColour::BLACK;
    board[13] = TileColour::BLACK;
    board[15] = TileColour::BLACK;
    board[16] = TileColour::BLACK;
    board[17] = TileColour::BLACK;
    board[19] = TileColour::BLACK;

    test_black_win(board, hg);

    // fill board up
    board = HexBoard(5);
    //board[3] = TileColour::BLACK;
    //board[4] = TileColour::BLACK;
    board[8] = TileColour::BLACK;
    //board[9] = TileColour::BLACK;
    board[13] = TileColour::BLACK;
    board[15] = TileColour::BLACK;
    board[16] = TileColour::BLACK;
    board[17] = TileColour::BLACK;
    board[18] = TileColour::BLACK;
    board[19] = TileColour::BLACK;

    test_black_win(board, hg);

    // fill board up
    board = HexBoard(5);
    int i = 4;
    board[i*5+0] = TileColour::BLACK;
    board[i*5+1] = TileColour::BLACK;
    board[i*5+2] = TileColour::BLACK;
    board[i*5+3] = TileColour::BLACK;
    board[i*5+4] = TileColour::BLACK;

    test_black_win(board, hg);

    // fill board up
    board = HexBoard(5);
    //board[3] = TileColour::BLACK;
    //board[4] = TileColour::BLACK;
    board[7] = TileColour::BLACK;
    board[8] = TileColour::BLACK;
    board[9] = TileColour::BLACK;
    board[12] = TileColour::BLACK;
    board[17] = TileColour::BLACK;
    board[20] = TileColour::BLACK;
    board[21] = TileColour::BLACK;
    board[22] = TileColour::BLACK;
    board[22] = TileColour::BLACK;

    test_black_win(board, hg);

    // fill board up
    board = HexBoard(5);
    //board[3] = TileColour::BLACK;
    //board[4] = TileColour::BLACK;
    board[4] = TileColour::WHITE;
    board[9] = TileColour::WHITE;
    board[10] = TileColour::WHITE;
    board[11] = TileColour::WHITE;
    board[12] = TileColour::WHITE;
    board[13] = TileColour::WHITE;
    board[14] = TileColour::WHITE;
    board[15] = TileColour::WHITE;
    board[20] = TileColour::WHITE;

    test_white_win(board, hg);
    return 0;
}

static void test_black_win(const HexBoard & board, const HexGraph & hg)
{
    printBoard_(board);

    bool whiteWon = hg.whiteWon(board);
    bool blackWon = hg.blackWon(board);
    TileColour winner = hg.fullBoardWinner(board);

    std::cout << "Test " << test_number++ << std::endl;
    std::cout << (whiteWon == false) << std::endl;
    std::cout << (blackWon == true) << std::endl;
    std::cout << (winner == TileColour::BLACK) << std::endl;
    std::cout << std::endl;
}

static void test_white_win(const HexBoard & board, const HexGraph & hg)
{
    printBoard_(board);

    bool whiteWon = hg.whiteWon(board);
    bool blackWon = hg.blackWon(board);
    TileColour winner = hg.fullBoardWinner(board);

    std::cout << "Test " << test_number++ << std::endl;
    std::cout << (whiteWon == true) << std::endl;
    std::cout << (blackWon == false) << std::endl;
    std::cout << (winner == TileColour::WHITE) << std::endl;
    std::cout << std::endl;
}

static void printBoard_(const HexBoard & board)
{

    int board_side_ = board.side();
    std::cout << "   ";
    for (int col = 0; col < board_side_; ++col)
        std::cout << col+1 << "  ";
    std::cout << std::endl;

    for (int row=0; row < board_side_; ++row)
    {
        std::cout << row+1 << "   ";
        for (int col=0; col < board_side_; ++col)
        {
            TileColour tile = board[row*board_side_+col];
            if (tile == TileColour::WHITE)
                std::cout << "W  ";
            else if (tile == TileColour::BLACK)
                std::cout << "B  ";
            else
                std::cout << "-  ";
        }
        std::cout << " " << row+1 << std::endl;
        std::cout << std::string(row+1,' ');	// indent next row
    }
    std::cout << "    ";
    for (int col = 0; col < board_side_; ++col)
        std::cout << col+1 << "  ";
    std::cout << std::endl;
}
