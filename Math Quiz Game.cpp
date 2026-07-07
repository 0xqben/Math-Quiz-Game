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
    MixDifficulty = 4,
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5,
};

struct stQuizz
{
    int NumberOfQuestions = 0;
    int RightAnswers = 0;
    int WrongAnswers = 0;
    enOperationType OperationType;
    enDifficulty QuestionsLevel;

};

struct stQuestion
{
    enDifficulty QuestionLevel;
    enOperationType OpType;
    int Answer;
    int PlayerAnswer;
    int Number1;
    int Number2;
};

int ReadNumberOfQuestions() {
    int NumberOfQuestions = 1;
    do
    {
        cout << "Enter Number Of Questions : " << endl;
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions <= 0);
    return NumberOfQuestions;
}

enDifficulty ReadQuestionsLevel() {
    int QuestionLevel = 1;
    do
    {
        cout << "\nEnter Question Level [1] Easy , [2] Medium , [3] Hard , [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel > 4 || QuestionLevel < 1);
    return (enDifficulty)QuestionLevel;
}

int RandomNumber(int From , int To) {
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

enOperationType GetRandomOperation() {
    return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(stQuestion& Question) {
    if (Question.OpType == enOperationType::MixOp)
        Question.OpType = GetRandomOperation();

    if (Question.QuestionLevel == enDifficulty::MixDifficulty)
        Question.QuestionLevel = GetRandomDifficulty();




}

bool IsRightAnswer(stQuestion Question) {
    return (Question.Answer == Question.PlayerAnswer);
}

void PrintQuestionResult(stQuestion Question) {
    if (IsRightAnswer(Question))
    {
        cout << "Right Answer ;-)" << endl;
        //SetScreenColor(IsRightAnswer(Question));
    }
    else
    {
        cout << "Wrong Answer :-(" << endl;
        //SetScreenColor(IsRightAnswer(Question));
    }
}

stQuizz PlayGame(int NumberOfQuestions , enDifficulty QuestionsDiffculty,enOperationType OpType) {
    stQuestion Question;
    int NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

    for (int QuestionNumber = 1; QuestionNumber <= NumberOfQuestions; QuestionNumber++)
    {
        cout << "\nQuestion [" << QuestionNumber << "/" << NumberOfQuestions << "]" << endl;

        Question.QuestionLevel = QuestionsDiffculty;
        Question.OpType = OpType;
        GenerateQuestion(Question);
        Question.PlayerAnswer;// ReadPlayerAnswer(Question);

        if (IsRightAnswer(Question))
            NumberOfRightAnswers++;
            
        else
            NumberOfWrongAnswers++;
            

        PrintQuestionResult(Question);
    }
}

enDifficulty ReadQuestionsLevel() {
    int QuestionLevel = 1;
    do
    {
        cout << "\nEnter Question Level [1] Easy , [2] Medium , [3] Hard , [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel > 4 || QuestionLevel < 1);
    return (enDifficulty)QuestionLevel;
}

void ResestScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'y';

    do
    {
        ResestScreen();
        stQuizz Quiz;
        Quiz.NumberOfQuestions = ReadNumberOfQuestions();
        Quiz.OperationType;// = ReadOpertionType();
        Quiz.QuestionsLevel;// = ReadQuestionLevel();
        //Might change them and move them to playgame func
        
        //PlayGame();
        //ShowPassFailScreen();
        //ShowGameResult();

        cout << "\nDo you want to play again ? Y / N : " << endl;
        cin >> PlayAgain;


    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
   

}


