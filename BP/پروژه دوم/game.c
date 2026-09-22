#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pi 3.14159265358
#define g 0.4
#define max_life 100
#define max_x_range_player1 33
#define min_x_range_player1 1
#define min_x_range_player2 85
#define max_x_range_player2 121
#define max_angle 180
#define min_angle 0

typedef struct BombLocation
{
    double x;
    double y;
} BombLocation;

typedef struct Tank
{
    int LifeCount;
    int begginPos;
} Tank;

typedef struct data
{
    double shotAngle;
    double power;
    char movement;
    int ShiftRL;
} DataShot;

typedef struct gamedata
{
    char grid[24][123];
    Tank *player1;
    Tank *player2;
    DataShot *Shot;
    BombLocation *Bomb;
    int gamePlayTurn;
} gamedata;

void MergeScreen(gamedata *game);
void RandomPlacement(gamedata *game);
void printStatus(gamedata *game);
void PrintGet(gamedata *game, char gridCopy[24][123]);
void printField(gamedata *game, char gridCopy[24][123]);
int CheckMovement(gamedata *game);
int CheckFireAngle(gamedata *game);
int CheckRLShifts(gamedata *game);
int CheckPower(gamedata *game);
int GetOrders(gamedata *game,char gridCopy[24][123]);
void placeBombP1(gamedata *game, double time);
void placeBombP2(gamedata *game, double time);
void printBomb(gamedata *game, char gridCopy[24][123]);
void DrawShape(gamedata *game);
void SleepCannonShot();
void ClearScreen();
void SleepTime();
void ChangeAngle(gamedata *game);
void ChangePower(gamedata *game);
void ShotCannon(gamedata *game, char gridCopy[24][123]);
int DetrmineBomb(gamedata *game);
int EndGame(gamedata *game);

int main()
{
    // for random numbers.
    srand(time(NULL));

    // definng the the parts
    Tank player1;
    Tank player2;

    BombLocation bomb;
    DataShot shot;
    gamedata game;

    game.Bomb = &bomb;
    game.player1 = &player1;
    game.player2 = &player2;
    game.Shot = &shot;
    game.gamePlayTurn = 0;

    game.player1->LifeCount = max_life;
    game.player2->LifeCount = max_life;

    MergeScreen(&game);
}

void MergeScreen(gamedata *game)
{ // A function to get merge the funcitons of the game parts.

    char gridCopy[24][123] = {
        "-------------------------------------------------------------------------------------------------------------------------|",
        "|                  ^                                                                                                     |",
        "|                 ^^^                                                                            ^                       |",
        "|                ^^^^^                                                                          ^^^                      |",
        "|                                                                                              ^^^^^                     |",
        "|                                                                                                                        |",
        "|                                                                                                                        |",
        "|                      ^^                                                                                                |",
        "|                     ^^^^                                                                                               |",
        "|                    ^^^^^^                                                                                    ^         |",
        "|                                                                                                             ^^^        |",
        "|                                                                                                                        |",
        "|                                                                                                                        |",
        "|                                                          ^                                                             |",
        "|                                                         ^^^         ^^                                                 |",
        "|                                                        ^^^^^       ^^^^                                                |",
        "|                                               ^       ^^^^^^^^    ^^^^^^                                               |",
        "|                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        |",
        "|                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       |",
        "|                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      |",
        "|                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    |",
        "|########################################################################################################################|",
        "|########################################################################################################################|",
        "--------------------------------------------------------------------------------------------------------------------------",
    };

    memcpy(game->grid, gridCopy, sizeof(gridCopy));

    PrintGet(game, gridCopy);
}

void PrintGet(gamedata *game, char gridCopy[24][123])
{
    // Start of the game.
    RandomPlacement(game);

    // svaing the Prev moves.
    int copytimeP1 = 0;
    int copytimeP2 = 0;
    Tank *player1saveP1 = malloc(sizeof(Tank));
    Tank *player1saveP2 = malloc(sizeof(Tank));
    Tank *player2saveP1 = malloc(sizeof(Tank));
    Tank *player2saveP2 = malloc(sizeof(Tank));
    int savingTime1 = 0;
    int savingTime2 = 0;

    while (game->player1->LifeCount > 0 && game->player2->LifeCount > 0)
    {
        ClearScreen();
        // incease the turn.
        game->gamePlayTurn++;

        // printing the field.
        printField(game, gridCopy);
        
        // Saving the moves.
        if (copytimeP1 == 0 && game->gamePlayTurn % 2 == 1 && savingTime1 == 0)
        {
            memcpy(player1saveP1, game->player1, sizeof(Tank));
            memcpy(player1saveP2, game->player2, sizeof(Tank));
            copytimeP1++;
            if (copytimeP1 == 2)
            {
                copytimeP1 = 0;
            }
        }
        if (copytimeP2 == 0 && game->gamePlayTurn % 2 == 0 && savingTime2 == 0)
        {
            memcpy(player2saveP1, game->player1, sizeof(Tank));
            memcpy(player2saveP2, game->player2, sizeof(Tank));
            copytimeP2++;
            if (copytimeP1 == 2)
            {
                copytimeP2 = 0;
            }
        }

        if (GetOrders(game,gridCopy) == 1)
        {

            if(game->Shot->movement == 'R' || game->Shot->movement == 'L'){
                ShotCannon(game,gridCopy);
            }

            else if (game->Shot->movement == 'Q')
            {
                break;
            }
            else if (game->Shot->movement == 'N')
            {
                game->gamePlayTurn = 0;

                // reseting the lives.
                game->player1->LifeCount = max_life;
                game->player2->LifeCount = max_life;

                // reseting the times of saving.
                savingTime1 = 0;
                savingTime2 = 0;

                // creating the new poses.
                RandomPlacement(game);
            }
            else if (game->Shot->movement == 'S')
            {
            }
            else if (game->Shot->movement == 'B')
            {
                if (game->gamePlayTurn % 2 == 1)
                {
                    if (savingTime1 == 1)
                    {
                        printf("Ability Is Already Used - Your Turn Is Lost!\n");
                        SleepTime();
                    }
                    else
                    {
                        savingTime1 = 1;
                        memcpy(game->player1, player1saveP1, sizeof(Tank));
                        memcpy(game->player2, player1saveP2, sizeof(Tank));
                    }
                }
                else if (game->gamePlayTurn % 2 == 0)
                {
                    if (savingTime2 == 1)
                    {
                        printf("Ability Is Already Used - Your Turn Is Lost!\n");
                        SleepTime();
                    }
                    else
                    {
                        savingTime2 = 1;
                        memcpy(game->player2, player2saveP2, sizeof(Tank));
                        memcpy(game->player1, player2saveP1, sizeof(Tank));
                    }
                }
            }
        }
        else
        {
            SleepTime();
        }
    }

    // freeing the allocting memory.
    free(player1saveP1);
    free(player1saveP2);
    free(player2saveP1);
    free(player2saveP2);
}

void printField(gamedata *game, char gridCopy[24][123])
{ // A function to handle printing of th field.
    // Drawing the Tanks.
    DrawShape(game);

    // printing the status.
    printStatus(game);

    // print the field.
    for (int i = 0; i < 24; i++)
    {
        printf("\n%s", game->grid[i]);
    }

    memcpy(game->grid, gridCopy, sizeof(char) * 24 * 123);
}

void RandomPlacement(gamedata *game)
{ // A funciton to get the random positions for the first play.

    int posPlayer1 = (rand() % 25) + 1;
    int posPlayer2 = (rand() % 27) + 86;

    game->player1->begginPos = posPlayer1;
    game->player2->begginPos = posPlayer2;
}

void printStatus(gamedata *game)
{ // Printing the status of the life of the players.
    printf("=========================================================================================================================\n");
    printf("|                          [P1] TANK ALPHA  |  HEALTH: %d%%   ||   [P2] TANK BETA  |  HEALTH: %d%%                       |\n", game->player1->LifeCount, game->player2->LifeCount);
    printf("=========================================================================================================================");
}

void DrawShape(gamedata *game)
{ // function to draw a tanks on the grid.
    int IndexPlayer1 = game->player1->begginPos;
    int IndexPlayer2 = game->player2->begginPos;

    /// player1 draw.
    game->grid[20][IndexPlayer1 + 0] = '|';
    game->grid[20][IndexPlayer1 + 1] = '_';
    game->grid[20][IndexPlayer1 + 2] = '_';
    game->grid[20][IndexPlayer1 + 3] = '_';
    game->grid[20][IndexPlayer1 + 4] = '_';
    game->grid[20][IndexPlayer1 + 5] = '_';
    game->grid[20][IndexPlayer1 + 6] = '_';
    game->grid[20][IndexPlayer1 + 7] = '_';
    game->grid[20][IndexPlayer1 + 8] = '|';
    game->grid[19][IndexPlayer1 + 1] = '_';
    game->grid[19][IndexPlayer1 + 2] = '|';
    game->grid[19][IndexPlayer1 + 3] = '_';
    game->grid[19][IndexPlayer1 + 4] = '_';
    game->grid[19][IndexPlayer1 + 5] = '|';
    game->grid[19][IndexPlayer1 + 6] = '_';
    game->grid[19][IndexPlayer1 + 7] = '/';
    game->grid[19][IndexPlayer1 + 8] = '/';
    game->grid[18][IndexPlayer1 + 3] = '_';
    game->grid[18][IndexPlayer1 + 4] = '_';

    // player2 draw
    game->grid[20][IndexPlayer2 + 0] = '|';
    game->grid[20][IndexPlayer2 + 1] = '_';
    game->grid[20][IndexPlayer2 + 2] = '_';
    game->grid[20][IndexPlayer2 + 3] = '_';
    game->grid[20][IndexPlayer2 + 4] = '_';
    game->grid[20][IndexPlayer2 + 5] = '_';
    game->grid[20][IndexPlayer2 + 6] = '_';
    game->grid[20][IndexPlayer2 + 7] = '_';
    game->grid[20][IndexPlayer2 + 8] = '|';
    game->grid[19][IndexPlayer2 + 0] = '\\';
    game->grid[19][IndexPlayer2 + 1] = '\\';
    game->grid[19][IndexPlayer2 + 2] = '_';
    game->grid[19][IndexPlayer2 + 3] = '|';
    game->grid[19][IndexPlayer2 + 4] = '_';
    game->grid[19][IndexPlayer2 + 5] = '_';
    game->grid[19][IndexPlayer2 + 6] = '|';
    game->grid[19][IndexPlayer2 + 7] = '_';
    game->grid[18][IndexPlayer2 + 4] = '_';
    game->grid[18][IndexPlayer2 + 5] = '_';
}

int GetOrders(gamedata *game,char gridCopy[24][123])
{
    // find the Turn.
    int Turn = game->gamePlayTurn % 2 == 0 ? 2 : 1;

    // Start getting the orders.
    printf("\n(Player %d) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game ,B=Back: ", Turn);
    scanf(" %c", &game->Shot->movement);
    if (CheckMovement(game) == 1)
    {
        if (game->Shot->movement == 'R' || game->Shot->movement == 'L')
        {
            scanf("%d", &game->Shot->ShiftRL);
            if (CheckRLShifts(game) == 0)
            {
                printf("Illegal Move - Your Turn Is Lost!\n");
                return 0;
            }else{

                if (game->gamePlayTurn % 2 == 1)
                {
                    if (game->Shot->movement == 'L')
                    {
                        game->player1->begginPos -= game->Shot->ShiftRL;

                    }
                    else if (game->Shot->movement == 'R')
                    {
                        game->player1->begginPos += game->Shot->ShiftRL;

                    }
                }
                else if (game->gamePlayTurn % 2 == 0)
                {
                    if (game->Shot->movement == 'L')
                    {
                        game->player2->begginPos -= game->Shot->ShiftRL;

                    }
                    else if (game->Shot->movement == 'R')
                    {
                        game->player2->begginPos += game->Shot->ShiftRL;

                    }
                }
                ClearScreen();
                printField(game,gridCopy);
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("Invalid Command - Your Turn Is Lost!\n");
        return 0;
    }

    printf("\n(Player %d) Enter Firing Angle [0-180]: ", Turn);
    scanf("%lf", &game->Shot->shotAngle);
    if (CheckFireAngle(game) == 0)
    {
        printf("Angle Out Of Range - Your Turn Is Lost!\n");
        return 0;
    }

    printf("(Player %d) Enter Shot Power [1-100]: ", Turn);
    scanf("%lf", &game->Shot->power);
    if (CheckPower(game) == 0)
    {
        printf("Power Out Of Range - Your Turn Is Lost!\n");
        return 0;
    }

    return 1;
}

int CheckMovement(gamedata *game)
{ // A function to check the movement validation.
    switch (game->Shot->movement)
    {
    case ('R'):
    case ('L'):
    case ('S'):
    case ('N'):
    case ('Q'):
    case ('B'):
        return 1;
    default:
        return 0;
    }
}

int CheckRLShifts(gamedata *game)
{ // checking the limitations of the shifts.
    int Turn = game->gamePlayTurn % 2 == 0 ? 2 : 1;

    if (Turn == 1)
    {
        if (game->Shot->movement == 'L')
        {
            if (game->player1->begginPos - game->Shot->ShiftRL < min_x_range_player1)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (game->Shot->movement == 'R')
        {
            if (game->player1->begginPos + game->Shot->ShiftRL + 8 > max_x_range_player1)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    else
    {
        if (game->Shot->movement == 'L')
        {
            if (game->player2->begginPos - game->Shot->ShiftRL < min_x_range_player2)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (game->Shot->movement == 'R')
        {
            if (game->player2->begginPos + 9 + game->Shot->ShiftRL > max_x_range_player2)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}

void SleepTime()
{ // Creating the 3 second delay.
#ifdef _WIN32
    Sleep(3000);
#else
    usleep(3000 * 1000);
#endif
}

void SleepCannonShot()
{ // Creating the 0.75 second delay.
    #ifdef _WIN32
        Sleep(750);
    #else
        usleep(750 * 1000);
    #endif
}

void ClearScreen()
{ // Clearing rhe console.
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int CheckFireAngle(gamedata *game)
{ // A function to check the firing angle.
    if (game->Shot->shotAngle <= min_angle || game->Shot->shotAngle >= max_angle)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int CheckPower(gamedata *game)
{ // A functino to check the Power validation.
    if (game->Shot->power <= 1 || game->Shot->power >= 100)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void ShotCannon(gamedata *game, char gridCopy[24][123])
{ // simulating the shot.
    double time = 0.1;
    int count = 0;

    // changing the values to the standards.
    ChangeAngle(game);
    ChangePower(game);

    while (1)
    {
        ClearScreen();

        if (game->gamePlayTurn % 2 == 1)
        {
            placeBombP1(game, time);
        }
        else if (game->gamePlayTurn % 2 == 0)
        {
            placeBombP2(game, time);
        }

        if (game->Bomb->y < 0)
        {
            break;
        }

        int row = 22 - (int)round(game->Bomb->y);
        int cullum = (int)round(game->Bomb->x);

        // Detreminig the hint.
        int hint = DetrmineBomb(game);

        if (row > 20 || row <= 0 || cullum > 120 || cullum < 1)
        {
            time -= 0.1;

            // changing the locations of the bomb.
            if (game->gamePlayTurn % 2 == 1)
            {
                placeBombP1(game, time);
            }
            else if (game->gamePlayTurn % 2 == 0)
            {
                placeBombP2(game, time);
            }

            //printing the bomb.
            printBomb(game,gridCopy);
            printf("Shot Terminated!\n");
            SleepTime();
            break;
        }
        if (hint > 0)
        {
            // decreasing the time.
            time -= 0.1;

            // changing the locations of the bomb.
            if (game->gamePlayTurn % 2 == 1)
            {
                placeBombP1(game, time);
            }
            else if (game->gamePlayTurn % 2 == 0)
            {
                placeBombP2(game, time);
            }

            // printing the screen before the collision.
            printBomb(game, gridCopy);
            if (hint == 1)
            {
                printf("BOOM!!! Friendly Fire\n");
            }
            else if (hint == 2)
            {
                printf("BOOM!!! Clean Hit On The Enemy\n");
            }
            else if (hint == 3)
            {
                printf("Shot Terminated!\n");
            }
            // printing the end games.
            if (EndGame(game) == 1)
            {
                SleepTime();
                break;
            }
            else if(EndGame(game) != 1)
            {
                // Dealy and clearing the screen.
                SleepTime();
                ClearScreen();
                break;
            }
        }
        else
        {
            if (count == 0)
            {
                printBomb(game, gridCopy);
                SleepCannonShot();
            }
        }

        count++;
        if (count == 6)
        {
            count = 0;
        }
        time += 0.1;
    }
}

void ChangeAngle(gamedata *game)
{ // Change the angle to radian.
    game->Shot->shotAngle = (pi * game->Shot->shotAngle) / 180;
}

void ChangePower(gamedata *game)
{ // Change the power for the formula.
    game->Shot->power = 2 + 7 * pow(game->Shot->power / 100, 1.5);
}

void placeBombP1(gamedata *game, double time)
{ // A function to calculate the place of the player1.
    double Vx = game->Shot->power * cos(game->Shot->shotAngle);
    double Vy = game->Shot->power * sin(game->Shot->shotAngle);

    game->Bomb->x = Vx * time + game->player1->begginPos + 8;
    game->Bomb->y = -(0.5) * g * time * time + Vy * time + 4;
}

void placeBombP2(gamedata *game, double time)
{ // A function to calculate the place of the player2.
    double Vx = game->Shot->power * cos(pi - game->Shot->shotAngle);
    double Vy = game->Shot->power * sin(game->Shot->shotAngle);

    game->Bomb->x = Vx * time + game->player2->begginPos;
    game->Bomb->y = -(0.5) * g * time * time + Vy * time + 4;
}

void printBomb(gamedata *game, char gridCopy[24][123])
{ // A function to handle printing of th field with bomb.
    // Drawing the Tanks.
    DrawShape(game);

    // definfing the bomb.
    int row = 22 - (int)round(game->Bomb->y);
    int cullum = (int)round(game->Bomb->x);
    game->grid[row][cullum] = '*';

    // print the field.
    for (int i = 0; i < 24; i++)
    {
        printf("%s\n", game->grid[i]);
    }

    memcpy(game->grid, gridCopy, sizeof(char) * 24 * 123);
}

int DetrmineBomb(gamedata *game)
{ // Dtermineing the shot

    int x = round(game->Bomb->x);
    int y = round(22 - game->Bomb->y);

    if (game->gamePlayTurn % 2 == 1)
    {
        if (x >= game->player1->begginPos + 3 && x <= game->player1->begginPos + 4 && y >= 18 && y <= 20)
        {
            game->player1->LifeCount -= 20;
            return 1;
        }
        if ((x >= game->player1->begginPos && x < game->player1->begginPos + 3 || x >= game->player1->begginPos + 5 && x <= game->player1->begginPos + 8) && y >= 19 && y <= 20)
        {
            game->player1->LifeCount -= 20;
            return 1;
        }
        else if (x >= game->player2->begginPos + 4 && x <= game->player2->begginPos + 5 && y >= 18 && y <= 20)
        {
            game->player2->LifeCount -= 20;
            return 2;
        }
        else if ((x >= game->player2->begginPos && x < game->player2->begginPos + 4 || x >= game->player2->begginPos + 6 && x <= game->player2->begginPos + 8) && y >= 19 && y <= 20)
        {
            game->player2->LifeCount -= 20;
            return 2;
        }
        else if (game->grid[y][x] == '^' || game->grid[y][x] == '#')
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
    else if (game->gamePlayTurn % 2 == 0)
    {
        if (x >= game->player2->begginPos + 5 && x <= game->player2->begginPos + 5 && y >= 18 && y <= 20)
        {
            game->player2->LifeCount -= 20;
            return 1;
        }
        if ((x >= game->player2->begginPos && x < game->player2->begginPos + 4 || x >= game->player2->begginPos + 6 && x <= game->player2->begginPos + 8) && y >= 19 && y <= 20)
        {
            game->player2->LifeCount -= 20;
            return 1;
        }
        else if (x >= game->player1->begginPos + 3 && x <= game->player1->begginPos + 4 && y >= 18 && y <= 20)
        {
            game->player2->begginPos -= 20;
            return 2;
        }
        else if ((x >= game->player1->begginPos && x < game->player1->begginPos + 4 || x >= game->player1->begginPos + 5 && x <= game->player1->begginPos + 8) && y >= 19 && y <= 20)
        {
            game->player1->begginPos -= 20;
            return 2;
        }
        else if (game->grid[y][x] == '^' || game->grid[y][x] == '#')
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
}

int EndGame(gamedata *game)
{ // A funciton to print the massages of the end game.
    if (game->player1->LifeCount == 0)
    {
        printf("--------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------\n");
        return 1;
    }
    else if (game->player2->LifeCount == 0)
    {
        printf("--------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------\n");
        return 1;
    }
    else
    {
        return 0;
    }
}