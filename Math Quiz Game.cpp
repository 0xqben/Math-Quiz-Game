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

string OperationType(enOperationType Type) {
    string arrOpType[4] = { "Add","Sub","Mul","Div" };
    return arrOpType[Type - 1];
}

string QuestionLevel(enDifficulty Level) {
    string arrLevelType[3] = { "Easy","Medium","Hard" };
    return arrLevelType[Level - 1];
}

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

enOperationType ReadOperationType() {
    int OpType = 1;
    do
    {
        cout << "\nEnter Question Level [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? ";
        cin >> OpType;
    } while (OpType > 5 || OpType < 1);
    return (enOperationType)OpType;
}

int ReadPlayerAnswer(stQuestion Question) {
    int Answer;
    cout << Question.Number1 << endl;
    cout << Question.Number2 << " " << OperationType(Question.OpType) << endl;
    cout << "_______________" << endl;
    cin >> Answer;
    return Answer;
}

int RandomNumber(int From , int To) {
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

enOperationType GetRandomOperation() {
    return (enOperationType)RandomNumber(1, 4);
}

enDifficulty GetRandomDifficulty() {
    return (enDifficulty)RandomNumber(1, 3);
}

stQuestion GenerateQuestion(enOperationType OpType , enDifficulty QuestionLevel) {
    stQuestion GeneratedQuestion;
    if (OpType == enOperationType::MixOp)
        GeneratedQuestion.OpType = GetRandomOperation();
    else
        GeneratedQuestion.OpType = OpType;

    if (QuestionLevel == enDifficulty::MixDifficulty)
        GeneratedQuestion.QuestionLevel = GetRandomDifficulty();
    else
        GeneratedQuestion.QuestionLevel = QuestionLevel;

    switch (GeneratedQuestion.QuestionLevel) {
    case enDifficulty::Easy :
        GeneratedQuestion.Number1 = RandomNumber(1, 10);;
        GeneratedQuestion.Number2 = RandomNumber(1, 10);;
        break;
    case enDifficulty::Medium :
        GeneratedQuestion.Number1 = RandomNumber(5, 20);
        GeneratedQuestion.Number2 = RandomNumber(5, 20);
        break;
    case enDifficulty::Hard :
        GeneratedQuestion.Number1 = RandomNumber(10, 100);
        GeneratedQuestion.Number2 = RandomNumber(10, 100);
        break;
    }

    switch (GeneratedQuestion.OpType) {
    case enOperationType::Add :
        GeneratedQuestion.Answer = GeneratedQuestion.Number1 + GeneratedQuestion.Number2;
        break;
    case enOperationType::Sub :
        GeneratedQuestion.Answer = GeneratedQuestion.Number1 - GeneratedQuestion.Number2;
        break;
    case enOperationType::Mul :
        GeneratedQuestion.Answer = GeneratedQuestion.Number1 * GeneratedQuestion.Number2;
        break;
    case enOperationType::Div :
        GeneratedQuestion.Answer = GeneratedQuestion.Number1 / GeneratedQuestion.Number2;
        break;
    }


    return GeneratedQuestion;
}

bool IsRightAnswer(stQuestion Question) {
    return (Question.Answer == Question.PlayerAnswer);
}

void SetScreenColor(bool IsRight) {
    if (IsRight)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
    }
}

void PrintQuestionResult(stQuestion Question) {
    if (IsRightAnswer(Question))
    {
        cout << "\nRight Answer ;-)" << endl;
        SetScreenColor(IsRightAnswer(Question));
    }
    else
    {
        cout << "\nWrong Answer :-(" << endl;
        SetScreenColor(IsRightAnswer(Question));
    }
}

stQuizz FillGameResults(int NumberOfQuestions, int RightAnswers, int WrongAnswers) {
    stQuizz QuizResults;
    QuizResults.NumberOfQuestions = NumberOfQuestions;
    QuizResults.RightAnswers = RightAnswers;
    QuizResults.WrongAnswers = WrongAnswers;

    return QuizResults;
}

stQuizz PlayGame(int NumberOfQuestions ,enOperationType OpType ,enDifficulty QuestionsDiffculty) {
    int RightAnswers = 0, WrongAnswers = 0;
    stQuestion Question;
    for (int QuestionNumber = 1; QuestionNumber <= NumberOfQuestions; QuestionNumber++)
    {
        
        cout << "\nQuestion [" << QuestionNumber << "/" << NumberOfQuestions << "]" << endl;
        Question.OpType = OpType;
        Question.QuestionLevel = QuestionsDiffculty;
        Question = GenerateQuestion(OpType,QuestionsDiffculty);
        Question.PlayerAnswer = ReadPlayerAnswer(Question);

        if (IsRightAnswer(Question))
            RightAnswers++;

        else
            WrongAnswers++;
        PrintQuestionResult(Question);
    }
    return FillGameResults(NumberOfQuestions,RightAnswers , WrongAnswers);
}

stQuizz CreateQuiz() {
    stQuizz QuizInfo;
    QuizInfo.NumberOfQuestions = ReadNumberOfQuestions();
    QuizInfo.OperationType = ReadOperationType();
    QuizInfo.QuestionsLevel = ReadQuestionsLevel();

    QuizInfo = PlayGame(QuizInfo.NumberOfQuestions, QuizInfo.OperationType, QuizInfo.QuestionsLevel);
    return QuizInfo;
       
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
        
        
        Quiz = CreateQuiz();
        //ShowPassFailScreen();
        //ShowGameResult();

        cout << "\nDo you want to play again ? Y / N : " << endl;
        cin >> PlayAgain;


    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    
}


