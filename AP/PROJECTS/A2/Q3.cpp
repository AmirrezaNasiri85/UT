#include <iostream>
#include <string>
#include <vector>
#include <array>

const int MIN_INDEX = 0;
const int MID_INDEX = 3;
const int MAX_MOVE_INDEX = 3;
const int MAX_ROW = 7;
const int MAX_COLUMN = 7;

struct movementInfo
{
    std::string place;
    std::string movement;
};

struct gameData
{
    const std::array<int, MAX_MOVE_INDEX + 1> UP_MOVEMENT = {0, +2, -2, 0};
    const std::array<int, MAX_MOVE_INDEX + 1> LINE_MOVEMENT = {-2, 0, 0, +2};
    const std::array<std::array<std::string,MAX_COLUMN>,MAX_ROW> namedBoardGame = {{
        {"A1", "A2", "A3", "A4", "A5", "A6", "A7"},
        {"B1", "B2", "B3", "B4", "B5", "B6", "B7"},
        {"C1", "C2", "C3", "C4", "C5", "C6", "C7"},
        {"D1", "D2", "D3", "D4", "D5", "D6", "D7"},
        {"E1", "E2", "E3", "E4", "E5", "E6", "E7"},
        {"F1", "F2", "F3", "F4", "F5", "F6", "F7"},
        {"G1", "G2", "G3", "G4", "G5", "G6", "G7"}}};
};
    
using Board = std::array<std::array<char,MAX_COLUMN>,MAX_ROW>;
using Path = std::vector<movementInfo>;

void printPath(const Path &movementPath, bool resultEndGame, int index = 0)
{
    if (movementPath.empty() && resultEndGame == false)
    {
        std::cout << "Loser";
        return;
    }
    else if(movementPath.empty())
    {
        return;
    }
    else
    {
        if(index == movementPath.size())
        {
            return;
        }
        std::cout << movementPath[index].place << " " << movementPath[index].movement;  
        if(index != movementPath.size() - 1)
        {  
            std::cout << std::endl;
        }
        index += 1;
        printPath(movementPath, resultEndGame, index);
    }
}

void removePath(Path &movementPath)
{
    movementPath.pop_back();
}

void addPath(Path &movementPath, int row, int column, int moveIndex,gameData& gameInfo)
{
    movementInfo movementData;
    movementData.place = gameInfo.namedBoardGame[row][column];

    if (gameInfo.LINE_MOVEMENT[moveIndex] == +2)
    {
        movementData.movement = "RIGHT";
    }
    else if (gameInfo.LINE_MOVEMENT[moveIndex] == -2)
    {
        movementData.movement = "LEFT";
    }
    else
    {
        if (gameInfo.UP_MOVEMENT[moveIndex] == +2)
        {
            movementData.movement = "DOWN";
        }
        else if (gameInfo.UP_MOVEMENT[moveIndex] == -2)
        {
            movementData.movement = "UP";
        }
    }
    movementPath.push_back(movementData);
}

void unDoMove(Board &boardGame, int pieceRow, int pieceColumn, int moveIndex, gameData& gameInfo)
{
    int midPieceRow, midPieceCollum;

    midPieceCollum = pieceColumn + (gameInfo.LINE_MOVEMENT[moveIndex]/2);
    midPieceRow = pieceRow + (gameInfo.UP_MOVEMENT[moveIndex]/2);

    boardGame[midPieceRow][midPieceCollum] = 'N';
    boardGame[pieceRow][pieceColumn] = 'N';
    boardGame[pieceRow + gameInfo.UP_MOVEMENT[moveIndex]][pieceColumn + gameInfo.LINE_MOVEMENT[moveIndex]] = 'O';
}

void doMove(Board &boardGame, int pieceRow, int pieceColumn, int moveIndex, gameData& gameInfo)
{
    int midPieceRow, midPieceCollum;

    midPieceCollum = pieceColumn + (gameInfo.LINE_MOVEMENT[moveIndex]/2);
    midPieceRow = pieceRow + (gameInfo.UP_MOVEMENT[moveIndex]/2);

    boardGame[midPieceRow][midPieceCollum] = 'O';
    boardGame[pieceRow][pieceColumn] = 'O';
    boardGame[pieceRow + gameInfo.UP_MOVEMENT[moveIndex]][pieceColumn + gameInfo.LINE_MOVEMENT[moveIndex]] = 'N';
}

bool canMove(Board &boardGame, int pieceRow, int pieceColumn, int moveIndex, gameData& gameInfo)
{
    if (pieceRow + gameInfo.UP_MOVEMENT[moveIndex] >= MIN_INDEX 
        && pieceRow + gameInfo.UP_MOVEMENT[moveIndex] < MAX_ROW
        && pieceColumn + gameInfo.LINE_MOVEMENT[moveIndex] >= MIN_INDEX 
        && pieceColumn + gameInfo.LINE_MOVEMENT[moveIndex] < MAX_COLUMN)
    {
        int midPieceRow, midPieceCollum;

        midPieceCollum = pieceColumn + (gameInfo.LINE_MOVEMENT[moveIndex]/2);
        midPieceRow = pieceRow + (gameInfo.UP_MOVEMENT[moveIndex]/2);

        if(boardGame[midPieceRow][midPieceCollum] == 'N'
            && boardGame[pieceRow + gameInfo.UP_MOVEMENT[moveIndex]][pieceColumn + gameInfo.LINE_MOVEMENT[moveIndex]] == 'O')
            {
                return true;
            }
        return false;
    }
    return false;
}

void makeBoardGame(Board &boardGame, int& pieceCount)
{
    for(int row = 0;row < MAX_ROW;row++){
        for(int column = 0;column < MAX_COLUMN;column++){
            std::cin >> boardGame[row][column];

            if(boardGame[row][column] == 'N')
            {
                pieceCount++;
            }
        }
    }
}

bool endGame(Board &boardGame,int& pieceCount)
{
    if(pieceCount == 1
        && boardGame[MID_INDEX][MID_INDEX] == 'N')
    {
        return true;
    }
    return false;
}

bool findStrategy(Board &boardGame, Path &movementPath, int& pieceCount, gameData& gameInfo)
{
    if (endGame(boardGame, pieceCount))
    {
        return true;
    }

    for (int row = 0; row < MAX_ROW; row++)
    {
        for (int column = 0; column < MAX_COLUMN; column++)
        {
            if (boardGame[row][column] == 'N')
            {
                for (int moveIndex = 0; moveIndex <= MAX_MOVE_INDEX; moveIndex++)
                {
                    if (canMove(boardGame, row, column, moveIndex, gameInfo))
                    {
                        doMove(boardGame, row, column, moveIndex, gameInfo);

                        pieceCount--;

                        addPath(movementPath, row, column, moveIndex, gameInfo);

                        if (findStrategy(boardGame, movementPath, pieceCount, gameInfo))
                        {
                            return true;
                        }

                        unDoMove(boardGame, row, column, moveIndex, gameInfo);

                        pieceCount++;

                        removePath(movementPath);
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    int pieceCount = 0;

    Board boardGame;
    std::vector<movementInfo> movementPath;

    gameData gameInfo;

    makeBoardGame(boardGame, pieceCount);

    bool resultENdGame = findStrategy(boardGame, movementPath, pieceCount, gameInfo);

    printPath(movementPath, resultENdGame);

    return 0;
}