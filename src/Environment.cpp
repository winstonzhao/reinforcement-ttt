#include "project/Environment.hpp"
#include "project/Util.hpp"

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
    }

    std::pair<Board *, int> Environment::Update(int move)
    {
        if (IsGameOver())
            return std::make_pair(&mBoard, mGameState == DRAW ? 50 : 100);
        if (mBoard[move] != 0)
            throw "Move attempted at invalid position";

        bool oTurn = mCross == mCircle;

        mBoard[move] = oTurn ? CIRCLE : CROSS;
        ++(oTurn ? mCircle : mCross);

        mGameState = GetGameState(mBoard);

        if (mGameState == PLAYING)
            return std::make_pair(&mBoard, 1);
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