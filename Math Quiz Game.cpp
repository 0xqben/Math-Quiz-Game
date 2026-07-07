// Math Quiz Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enDifficulty
{
    Easy = 1,
    Medium =2,
    Hard = 3,
    Mix = 4,
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    Mix = 5,
};

struct stQuizz
{
    int NumberOfQuestions = 0;
    int RightAnswers = 0;
    int WrongAnswers = 0;
    enOperationType OperationType;
    enDifficulty QuestionLevel;

};

void StartGame() {
    char PlayAgain = 'y';

    do
    {
        // ResestScreen();
        stQuizz Quiz; //PlayGame(ReadNumberOfQuestions());
        // ShowPassFailScreen();
        // ShowGameResult();

        cout << "\nDo you want to play again ? Y / N : " << endl;
        cin >> PlayAgain;


    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));


}


