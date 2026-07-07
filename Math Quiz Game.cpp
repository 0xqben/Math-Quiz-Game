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

struct stQuestion
{
    enDifficulty QuestionLevel;
    enOperationType OpType;
    int Answer = 0;
    int PlayerAnswer = 0;
    int Number1 = 0;
    int Number2 = 0;
    bool AnswerResult = false;
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

int ReadPlayerAnswer() {
    int Answer;
    cin >> Answer;
    return Answer;
}
//Refactored

void PrintTheQuestion(stQuizz& Quizz, int QuestionNumber) {
    
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << OperationType(Quizz.QuestionList[QuestionNumber].OpType) << endl;
    cout << "_______________" << endl;
}
// New

int RandomNumber(int From , int To) {
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mul:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default :
        return Number1 + Number2;
    }
}

enOperationType GetRandomOperation() {
    return (enOperationType)RandomNumber(1, 4);
}

enDifficulty GetRandomDifficulty() {
    return (enDifficulty)RandomNumber(1, 3);
}

stQuestion GenerateQuestion(enOperationType OpType , enDifficulty QuestionLevel) {
    stQuestion GeneratedQuestion;
    
    if (QuestionLevel == enDifficulty::MixDifficulty)
        QuestionLevel = GetRandomDifficulty();

    GeneratedQuestion.QuestionLevel = QuestionLevel;

    

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperation();


    GeneratedQuestion.OpType = OpType;
    
switch (QuestionLevel) {
    case enDifficulty::Easy :
        GeneratedQuestion.Number1 = RandomNumber(1, 10);;
        GeneratedQuestion.Number2 = RandomNumber(1, 10);;

        GeneratedQuestion.Answer = SimpleCalculator(GeneratedQuestion.Number1, GeneratedQuestion.Number2, GeneratedQuestion.OpType);
        GeneratedQuestion.QuestionLevel = QuestionLevel;
        return GeneratedQuestion;
    case enDifficulty::Medium :
        GeneratedQuestion.Number1 = RandomNumber(10, 50);;
        GeneratedQuestion.Number2 = RandomNumber(10, 50);;

        GeneratedQuestion.Answer = SimpleCalculator(GeneratedQuestion.Number1, GeneratedQuestion.Number2, GeneratedQuestion.OpType);
        GeneratedQuestion.QuestionLevel = QuestionLevel;
        return GeneratedQuestion;
    case enDifficulty::Hard :
        GeneratedQuestion.Number1 = RandomNumber(10, 100);;
        GeneratedQuestion.Number2 = RandomNumber(10, 100);;

        GeneratedQuestion.Answer = SimpleCalculator(GeneratedQuestion.Number1, GeneratedQuestion.Number2, GeneratedQuestion.OpType);
        GeneratedQuestion.QuestionLevel = QuestionLevel;
        return GeneratedQuestion;
    }
    return GeneratedQuestion;
}
// Refactored
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

void CorrectTheQuestionAnswer(stQuizz& Quizz, int QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].Answer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.WrongAnswers++;

        cout << "\nWrong Answer :-(" << endl;
        cout << "\nThe right answer is : " << Quizz.QuestionList[QuestionNumber].Answer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.RightAnswers++;
        cout << "\nRight Answer ;-)" << endl;
    }
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);

}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {
    for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.RightAnswers >= Quizz.WrongAnswers);
}
// New 
stQuizz FillGameResults(stQuizz QuizInfo, int RightAnswers, int WrongAnswers) {
    stQuizz QuizResults;

    QuizResults.NumberOfQuestions = QuizInfo.NumberOfQuestions;
    QuizResults.OperationType = QuizInfo.OperationType;
    QuizResults.QuestionsLevel = QuizInfo.QuestionsLevel;
    QuizResults.RightAnswers = RightAnswers;
    QuizResults.WrongAnswers = WrongAnswers;

    return QuizResults;
}

void GenerateQuizzQuestions(stQuizz& Quizz) {
    for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.OperationType, Quizz.QuestionsLevel);
    }
}
// New 
stQuizz PlayGame(stQuizz QuizInfo) {
    int RightAnswers = 0, WrongAnswers = 0;
    stQuestion Question;
    for (int QuestionNumber = 1; QuestionNumber <= QuizInfo.NumberOfQuestions; QuestionNumber++)
    {
        
        cout << "\nQuestion [" << QuestionNumber << "/" << QuizInfo.NumberOfQuestions << "]" << endl;
        Question = GenerateQuestion(QuizInfo.OperationType, QuizInfo.QuestionsLevel);
        //Question.PlayerAnswer = ReadPlayerAnswer(Question);

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

void ShowPassFailScreen(bool IsPass) {
    cout << "\n--------------------------------\n";
    if (IsPass)
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
 
void PrintQuizResults(stQuizz Quiz) {
    ShowPassFailScreen(Quiz.isPass);
    ShowGameResult(Quiz);

}

void PlayMathGame() {
    stQuizz Quiz;
    Quiz.NumberOfQuestions = ReadNumberOfQuestions();
    Quiz.QuestionsLevel = ReadQuestionsLevel();
    Quiz.OperationType = ReadOperationType();


    GenerateQuizzQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResults(Quiz);
}
// New


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
// Refactored
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    
}


