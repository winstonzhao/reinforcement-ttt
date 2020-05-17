#include "project/Environment.hpp"
#include "project/Util.hpp"
#include <iostream>

namespace Reinforcement
{
    Environment::Environment() {}

    void Environment::Initialize()
    {
        for (int i = 0; i < mBoard.size(); ++i)
        {
            mBoard[i] = 0;
        }
        mGameState = PLAYING;
        mCross = 0;
        mCircle = 0;
    }

    Board *Environment::GetState()
    {
        return &mBoard;
    }

    std::pair<Board *, int> Environment::Update(int move)
    {
        if (IsGameOver())
        {
            throw "Attemping game update while game is over";
        }
        if (mBoard[move] != 0)
        {
            PrintBoard(mBoard);
            throw "Invalid move attempted";
        }
        bool oTurn = mCross == mCircle;

        mBoard[move] = oTurn ? CIRCLE : CROSS;
        ++(oTurn ? mCircle : mCross);

        mGameState = GetGameState(mBoard);

        if (mGameState == PLAYING)
            return std::make_pair(&mBoard, 0);
        else if (mGameState == CROSS_WIN || mGameState == CIRCLE_WIN)
            return std::make_pair(&mBoard, -100);
        else if (mGameState == DRAW)
            return std::make_pair(&mBoard, 50);

        throw "Invalid gamestate found";
    }

    bool Environment::IsGameOver()
    {
        return mGameState != PLAYING;
    }
}; // namespace Reinforcement