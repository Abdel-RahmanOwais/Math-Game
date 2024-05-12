#include <iostream>
#include <Windows.h>
using namespace std;

enum enQuestionLevel { Easy = 1, Medime = 2, Hard = 3, MixLevel = 4 };
enum enOpType { Add = 1, Subtract = 2, Divide = 3, Multiply = 4, MixOp = 5 };

struct stQuizInfo {
	int NumberOfQuest = 0;
	enQuestionLevel QuestLevel;
	string strQuestLevel;
	enOpType OpType;
	char chOpType;
	int NumOfRightAnswer = 0;
	int NumOfWrongAnswer = 0;
};

int ReadHowManyQuestions() {
	int HowManyQuestions;

	do {
		cout << "\nHow Many Questions Do You Want To Answer ";
		cin >> HowManyQuestions;
	} while (HowManyQuestions < 1 || HowManyQuestions > 100);

	return HowManyQuestions;
}

enQuestionLevel ReadQuestionLevel() {
	short QuestLevel = 0;

	do{
		cout << "\nEnter Question Level [1] Easy, [2] Medium, [3] Hard, [4] Mix ";
		cin >> QuestLevel;
	} while (QuestLevel < 1 || QuestLevel > 4);

	return (enQuestionLevel)QuestLevel;
}

enOpType ReadOpType() {

	short OpType = 0;

	do {
		cout << "Enter Operation Type [1] Add, [2] Subtract, [3] Divide, [4] Multiplay, [5] Mix : ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOpType)OpType;
}

int RandomNumber(int From, int To) {

	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

string QuestionChoiceNmae(enQuestionLevel& QesLevel) {
	string arrQesLevelChoice[4] = { "Easy", "Medium", "Hard", "Mix"};

	return arrQesLevelChoice[QesLevel - 1];
} 

char OpTypeChoiceName(enOpType& OpType) {
	char OpTypeChoice[5] = { '+', '-', '/', '*', 'M'};
	
	return OpTypeChoice[OpType - 1];
} 

int GenerateRandomQuestion(enQuestionLevel& QuestLevel) {
	if (QuestLevel == 1) {
		return RandomNumber(1, 10);
	}
	else if (QuestLevel == 2) {
		return RandomNumber(10, 50);
	}
	else if (QuestLevel == 3) {
		return RandomNumber(50, 100);
	}
	else {
		return RandomNumber(1, 100);
	}
}

char GenerateOpType(enOpType& OpType) {
	if (OpType == 1) {
		return '+';
	}
	else if (OpType == 2) {
		return '-';
	}
	else if (OpType == 3) {
		return '/';
	}
	else if (OpType == 4) {
		return '*';
	}
	else {
		char RandomNum = RandomNumber(1, 4);
		switch (RandomNum)
		{
		case 1:
			return '+';
			break;
		case 2:
			return '-';
			break;
		case 3:
			return '/';
			break;
		case 4:
			return '*';
			break;
		default:
			return '+';
			break;
		}
	}

}

bool IsrResultEqualUserResult(int Reuslt, int UserReuslt) {

	return  (Reuslt == UserReuslt);

}

int CalculateResult(int& RandomQuest1, int &RandomQuest2, char &OpType) {
	if (OpType == '+') {
		return RandomQuest1 + RandomQuest2;
	}
	else if (OpType == '-') {
		return RandomQuest1 - RandomQuest2;
	}
	else if (OpType == '/') {
		return RandomQuest1 / RandomQuest2;
	}
	else {
		return RandomQuest1 * RandomQuest2;
	}
}

stQuizInfo FillFinalResults(int NumberOfQuest, string QuestLevel, char OpType, int NumOfRightAnswer, int NumOfWrongAnswer) {
	stQuizInfo QuizzInfo;

	QuizzInfo.NumberOfQuest = NumberOfQuest;
	QuizzInfo.strQuestLevel = QuestLevel;
	QuizzInfo.chOpType = OpType;
	QuizzInfo.NumOfRightAnswer = NumOfRightAnswer;
	QuizzInfo.NumOfWrongAnswer = NumOfWrongAnswer;

	return QuizzInfo;
}

stQuizInfo PlayGame(short NumberOfQuest, enQuestionLevel QuestLevel, enOpType OpType) {
	int RandomQuest1 = 0;
	int RandomQuest2 = 0;
	char OpTypeChoice = ' ';

	int UserResult = 0;
	int Result = 0; 

	stQuizInfo QuizzInfo;
	int NumOfRightAnswers = 0, NumOfWrongAnswers = 0;



	for (short Quest = 1; Quest <= NumberOfQuest; Quest++)
	{
		RandomQuest1 = GenerateRandomQuestion(QuestLevel);
		RandomQuest2 = GenerateRandomQuestion(QuestLevel);
		OpTypeChoice = GenerateOpType(OpType);

		cout << "Question [" << Quest << "/" << NumberOfQuest << "]" << endl;
		cout << RandomQuest1 << " " << OpTypeChoice << " "
			 << RandomQuest2 << endl;

		Result = CalculateResult(RandomQuest1, RandomQuest2, OpTypeChoice);

		cout << "____________________\n";
		cin >> UserResult;

		if (IsrResultEqualUserResult(Result, UserResult)) {
			cout << "\nRight Answer :-)\n\n";
			system("color 2F"); //Screen Is Gonna Be Green.
			Beep(1397, 200);
			NumOfRightAnswers++;
		}
		else {
			cout << "\nWrong Answer :-(" << endl;
			cout << "The Right Answer Is : " << Result << endl << endl;
			system("color 4F"); //Screen Is Gonna Be Red.
			Beep(440, 665);
			NumOfWrongAnswers++; 
		}


		QuizzInfo.NumberOfQuest = NumberOfQuest;
		QuizzInfo.QuestLevel = QuestLevel;
		QuizzInfo.strQuestLevel = QuestionChoiceNmae(QuestLevel);
		QuizzInfo.OpType = OpType;
		QuizzInfo.chOpType = OpTypeChoiceName(OpType);
		QuizzInfo.NumOfRightAnswer = NumOfRightAnswers;
		QuizzInfo.NumOfWrongAnswer = NumOfWrongAnswers;

	}


	return FillFinalResults(NumberOfQuest, QuestionChoiceNmae(QuestLevel), OpTypeChoiceName(OpType), NumOfRightAnswers, NumOfWrongAnswers);
}

void PrintFinalResults(stQuizInfo QuizzInfo) {

	if (QuizzInfo.NumOfRightAnswer >= QuizzInfo.NumOfWrongAnswer) {
		cout << "\n__________________________________\n" << endl;
		cout << "     Final Results Is Pass :-)\n";
		cout << "__________________________________ \n";
	}
	else {
		cout << "\n__________________________________\n" << endl;
		cout << "     Final Results Is Fail :-)\n";
		cout << "__________________________________ \n";
	}

	cout << "Number Of Question Is : " << QuizzInfo.NumberOfQuest << endl;
	cout << "Question Level Is     : " << QuizzInfo.strQuestLevel << endl;
	cout << "Operation Type Is     : " << QuizzInfo.chOpType << endl;
	cout << "Number Of Right Answer: " << QuizzInfo.NumOfRightAnswer << endl;
	cout << "Number Of Wrong Answer: " << QuizzInfo.NumOfWrongAnswer << endl;

	cout << "__________________________________ \n";
}

void RestScreen() {
	system("cls"); //Remove Anything in the Screen 

	system("color 0F");  //Reset Screen Black

}

void StartGame() {
	char PlayAgain = ' ';
	stQuizInfo QuizInfo;

	do {
		RestScreen();

		QuizInfo = PlayGame(ReadHowManyQuestions(), ReadQuestionLevel(), ReadOpType());

		PrintFinalResults(QuizInfo);

		cout << endl << "Do You Want Play Again ? Y/N ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

	system("color 0F");
	cout << "\nThank you for playing our game! " << endl;
	cout << "\nBest regards," << endl;
	cout << "Abdel-Rahman Owais" << endl;
}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();

}
