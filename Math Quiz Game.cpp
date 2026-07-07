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
    stQuestion QuestionList[100];
    int NumberOfQuestions = 0;
    int RightAnswers = 0;
    int WrongAnswers = 0;
    enOperationType OperationType;
    enDifficulty QuestionsLevel;
    bool isPass = false;

};

struct stQuestion
{
    enDifficulty QuestionLevel;
    enOperationType OpType;
    int Answer = 0;
    int PlayerAnswer = -1;
    int Number1 = 0;
    int Number2 = 0;
};

string OperationType(enOperationType Type) {
    string arrOpType[5] = { "Add","Sub","Mul","Div", "Mix"};
    return arrOpType[Type - 1];
}

string QuestionLevel(enDifficulty Level) {
    string arrLevelType[4] = { "Easy","Medium","Hard", "Mix"};
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
        cout << "\nThe right answer is : " << Question.Answer << endl;
        SetScreenColor(IsRightAnswer(Question));
    }
}

stQuizz FillGameResults(stQuizz QuizInfo, int RightAnswers, int WrongAnswers) {
    stQuizz QuizResults;

    QuizResults.NumberOfQuestions = QuizInfo.NumberOfQuestions;
    QuizResults.OperationType = QuizInfo.OperationType;
    QuizResults.QuestionsLevel = QuizInfo.QuestionsLevel;
    QuizResults.RightAnswers = RightAnswers;
    QuizResults.WrongAnswers = WrongAnswers;

    return QuizResults;
}

stQuizz PlayGame(stQuizz QuizInfo) {
    int RightAnswers = 0, WrongAnswers = 0;
    stQuestion Question;
    for (int QuestionNumber = 1; QuestionNumber <= QuizInfo.NumberOfQuestions; QuestionNumber++)
    {
        
        cout << "\nQuestion [" << QuestionNumber << "/" << QuizInfo.NumberOfQuestions << "]" << endl;
        Question = GenerateQuestion(QuizInfo.OperationType, QuizInfo.QuestionsLevel);
        Question.PlayerAnswer = ReadPlayerAnswer(Question);

        if (IsRightAnswer(Question))
            RightAnswers++;
        else
            WrongAnswers++;
        PrintQuestionResult(Question);
    }
    return FillGameResults(QuizInfo,RightAnswers , WrongAnswers);
}

stQuizz ReadQuizInfo() {
    stQuizz QuizInfo;
    QuizInfo.NumberOfQuestions = ReadNumberOfQuestions();
    QuizInfo.OperationType = ReadOperationType();
    QuizInfo.QuestionsLevel = ReadQuestionsLevel();
    return QuizInfo;
       
}

void ResestScreen() {
    system("cls");
    system("color 0F");
}

void ShowPassFailScreen(stQuizz Quiz) {
    cout << "\n--------------------------------\n";
    if (Quiz.RightAnswers > Quiz.WrongAnswers)
    {
        cout << " Final Results is PASS :-)";
    }
    else
    {
        cout << " Final Results is FAIL :-(";
    }
    cout << "\n--------------------------------\n";
}


void ShowGameResult(stQuizz Quiz) {
    cout << "Number of questions : " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level : " << QuestionLevel(Quiz.QuestionsLevel) << endl;
    cout << "operation Type : " << OperationType(Quiz.OperationType) << endl;
    cout << "Number of right answers : " << Quiz.RightAnswers << endl;
    cout << "Number of wrong answers : " << Quiz.WrongAnswers << endl;
    cout << "-----------------------------------\n";
}

void PlayMathGame() {
    stQuizz Quiz;
    Quiz.NumberOfQuestions = ReadNumberOfQuestions();
    Quiz.QuestionsLevel = ReadQuestionsLevel();
    Quiz.OperationType = ReadOperationType();

    Quiz = PlayGame(Quiz);
    ShowPassFailScreen(Quiz);
    ShowGameResult(Quiz);
}

void StartGame() {
    char PlayAgain = 'y';

    do
    {
        ResestScreen();
        PlayMathGame();

        cout << "\nDo you want to play again ? Y / N : " << endl;
        cin >> PlayAgain;


    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    
}


