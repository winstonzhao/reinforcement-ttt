#include "project/Agent.hpp"
#include "project/Util.hpp"
#include <cstdio>
#include <cassert>
#include <algorithm>

static int x = 0;

namespace Reinforcement
{
    Agent::Agent(bool side) : mSide{side},
                              mStateActionPairs{20},
                              mEligibility{},
                              mPolicy{20}
    {
    }

    void Agent::Initialize()
    {
        Board board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        RecursePossibleBoardStates(board, 0, 0);

        for (const auto &saPair : mStateActionPairs)
        {
            if (mPolicy.find(saPair.first) == mPolicy.end())
            {
                mPolicy.insert({saPair.first, {}});
            }
            const auto &avPairs = mPolicy.find(saPair.first);
            auto exists = std::find_if(avPairs->second.begin(), avPairs->second.end(), [&](std::pair<int, double> a) -> bool {
                              return a.first == saPair.second;
                          }) != avPairs->second.end();
            if (!exists)
            {
                avPairs->second.push_back({saPair.second, 0});
            }
        }
    }

    std::pair<int, double> *Agent::GetEpsilonGreedyAction(const Board *board)
    {
        assert(mPolicy.find(*board) != mPolicy.end());

        auto &moves = mPolicy.find(*board)->second;
        assert(moves.size() != 0);

        auto rand = RandDouble();

        std::pair<int, double> *nextMove = nullptr;

        if (rand < mEpsilon)
        {
            nextMove = &moves.at(RandInt(moves.size()));
        }
        else
        {
            double bestMoveValue = -100000;
            std::vector<std::pair<int, double> *> bestMoves;
            // printf("--------------------\n");
            for (auto &move : moves)
            {
                // printf("move: %d, value: %f\n", move.first, move.second);
                if (move.second > bestMoveValue)
                {
                    bestMoveValue = move.second;
                    bestMoves.clear();
                }
                if (move.second == bestMoveValue)
                {
                    bestMoves.push_back(&move);
                }
            }
            // printf("\n");

            assert(bestMoves.size() != 0);
            nextMove = bestMoves.at(RandInt(bestMoves.size()));
        }

        mPrevMove = nextMove;

        assert(nextMove != nullptr);

        const auto &eligibility = std::find_if(mEligibility.begin(), mEligibility.end(), [=](std::pair<std::pair<Board, int>, double> a) -> bool {
            return a.first == std::make_pair(*board, nextMove->first);
        });
        if (eligibility == mEligibility.end())
        {
            mEligibility.push_back(std::make_pair(std::make_pair(*board, nextMove->first), 1.0));
        }
        else
        {
            eligibility->second++;
        }

        return nextMove;
    }

    std::pair<int, double> &Agent::GetAction(const Board *board, int action)
    {
        assert(mPolicy.find(*board) != mPolicy.end());

        auto &moves = mPolicy.find(*board)->second;
        assert(moves.size() != 0);

        for (auto &move : moves)
        {
            if (move.first == action)
            {
                return move;
            }
        }

        throw "Move not found.";
    }

    int Agent::Observe(const Board *board, int reward)
    {
        auto futureMove = GetEpsilonGreedyAction(board);
        // printf("side: %d, move: %d\n", mSide, futureMove->first);
        double delta = reward + mGamma * futureMove->second - mPrevMove->second;

        mSteps++;
        mSumError += delta;

        if ((mSteps % 100000) == 0)
        {
            printf("Iteration: %d, error: %f\n", mSteps, mSumError / 100000);
            mEpsilon *= mEpsilonDecayRate;
            mSumError = 0;
        }

        for (auto &el : mEligibility)
        {
            auto &action = GetAction(&(el.first.first), el.first.second);
            action.second += mAlpha * delta * el.second;
            el.second *= (mGamma * mLambda);
        }

        return futureMove->first;
    }

    void Agent::GameOver(bool win)
    {
        double delta = (win ? 100 : -100) - mPrevMove->second;

        mSteps++;
        mSumError += delta;

        if ((mSteps % 100000) == 0)
        {
            printf("Iteration: %d, error: %f\n", mSteps, mSumError / 100000);
            mEpsilon *= mEpsilonDecayRate;
            mSumError = 0;
        }

        for (auto &el : mEligibility)
        {
            auto &action = GetAction(&(el.first.first), el.first.second);
            action.second += mAlpha * delta * el.second;
        }

        mEligibility.clear();
    }

    bool Agent::GetSide()
    {
        return mSide;
    }

    void Agent::RecursePossibleBoardStates(Board board, int numO, int numX)
    {
        if (GetGameState(board) != PLAYING)
        {
            return;
        }

        bool oTurn = numO == numX;

        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i] != BLANK)
                continue;
            auto newBoard = board;
            if (oTurn == mSide)
            {
                mStateActionPairs.insert({board, i});
            }
            newBoard[i] = oTurn ? CIRCLE : CROSS;

            RecursePossibleBoardStates(newBoard, oTurn ? numO + 1 : numO, oTurn ? numX : numX + 1);
        }
    }

} // namespace Reinforcement