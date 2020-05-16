#pragma once
#include "project/Types.hpp"
#include "project/Constants.hpp"

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

    if (board[0] != BLANK && board[4] != board[0] && board[8] == board[0])
        return board[0] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;

    if (board[2] != BLANK && board[4] == board[2] && board[6] == board[2])
        return board[2] == CIRCLE ? CIRCLE_WIN : CROSS_WIN;

    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i] == 0)
        {
            return DRAW;
        }
    }

    return PLAYING;
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