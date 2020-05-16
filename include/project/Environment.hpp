#pragma once
#include "project/Constants.hpp"
#include "project/Types.hpp"

namespace Reinforcement
{
    class Environment
    {
    public:
        Environment();
        void Initialize();
        std::pair<Board *, int> Update(int move);
        bool IsGameOver();

    private:
        Board mBoard;
        int mCross;
        int mCircle;
        int mGameState;
    };
}; // namespace Reinforcement