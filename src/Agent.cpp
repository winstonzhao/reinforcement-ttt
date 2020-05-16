#include "project/Agent.hpp"
#include "project/Util.hpp"
#include <cstdio>
#include <cassert>

static int x = 0;

namespace Reinforcement
{
    Agent::Agent(bool side) : mSide{side},
                              mStateActionPairs{20},
                              mEligibility{20},
                              mPolicy{20}
    {
    }

    void Agent::Initialize()
    {
        Board board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        RecursePossibleBoardStates(board, 0, 0);
        for (const auto &saPair : mStateActionPairs)
        {
            mEligibility.insert({saPair, 0});
            if (mPolicy.find(saPair.first) == mPolicy.end())
            {
                mPolicy.insert({saPair.first, {}});
            }
            const auto &avPairs = mPolicy.find(saPair.first);
            avPairs->second.push_back({saPair.second, 0});
        }
    }

    int Agent::GetAction(Board *board)
    {
        int nextMove = -1;
        const auto &moves = mPolicy.find(*board)->second;

        auto rand = RandDouble();

        if (rand > mEpsilon)
        {
            nextMove = RandInt(moves.size());
        }
        else
        {
            double bestMoveValue = -1000;
            std::vector<int> bestMoves;
            for (const auto &move : moves)
            {
                if (move.second >= bestMoveValue)
                {
                    // bestMoves.push_back()
                    bestMoveValue = move.second;
                }
            }
        }

        return nextMove;
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
            newBoard[i] = oTurn ? CIRCLE : CROSS;
            if (oTurn == mSide)
            {
                mStateActionPairs.insert({board, i});
            }
            RecursePossibleBoardStates(newBoard, oTurn ? numO + 1 : numO, oTurn ? numX : numX + 1);
        }
    }

    void Agent::PrintBoard(Board &board)
    {
        printf("_____\n");
        printf("|%c%c%c|\n", NumToPiece(board[0]), NumToPiece(board[1]), NumToPiece(board[2]));
        printf("|%c%c%c|\n", NumToPiece(board[3]), NumToPiece(board[4]), NumToPiece(board[5]));
        printf("|%c%c%c|\n", NumToPiece(board[6]), NumToPiece(board[7]), NumToPiece(board[8]));
        printf("-----\n");
    }

} // namespace Reinforcement