#pragma once
#include "project/Types.hpp"
#include "project/Constants.hpp"

inline char NumToPiece(int num)
{
    if (num == BLANK)
        return ' ';
    else if (num == CIRCLE)
        return 'O';
    else if (num == CROSS)
        return 'X';
    throw "Invalid number to attempt to convert to a piece";
}

inline void PrintBoard(const Board &board)
{
    printf("_____\n");
    printf("|%c%c%c|\n", NumToPiece(board[0]), NumToPiece(board[1]), NumToPiece(board[2]));
    printf("|%c%c%c|\n", NumToPiece(board[3]), NumToPiece(board[4]), NumToPiece(board[5]));
    printf("|%c%c%c|\n", NumToPiece(board[6]), NumToPiece(board[7]), NumToPiece(board[8]));
    printf("-----\n");
}

int inline GetGameState(Board &board)
{
    for (int i = 0; i < board.size(); i += 3)
    {
        if (board[i] != BLANK && board[i + 1] == board[i] && board[i + 2] == board[i])
            return board[i] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (board[i] != BLANK && board[i + 3] == board[i] && board[i + 6] == board[i])
            return board[i] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;
    }

    if (board[0] != BLANK && board[4] == board[0] && board[8] == board[0])
        return board[0] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;

    if (board[2] != BLANK && board[4] == board[2] && board[6] == board[2])
        return board[2] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;

    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i] == 0)
        {
            return PLAYING;
        }
    }

    return DRAW;
}

double inline RandDouble(double fMin = 0, double fMax = 1)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int inline RandInt(int max)
{
    return rand() % max;
}
