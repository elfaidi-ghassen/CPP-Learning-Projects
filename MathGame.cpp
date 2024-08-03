#include <iostream>

enum enColor { Red, Green };
enum enDifficuly { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperation { Add = 1, Sub = 2, Mult = 3, Div = 4, OpMix = 5 };

struct stSettings {
	int numberOfQuestions;
	enDifficuly difficultyOption;
	enOperation operationOption;

};
struct stQuestion {
	int firstOperand;
	int secondOperand;
	enOperation operationType;
	int correctAnswerValue;
};

void setSecreenColor(enColor color) {
	switch (color)
	{
	case enColor::Red:
		system("color 4F");
		break;
	case enColor::Green:
		system("color 2F");
		break;
	}
}
int readIntBetween(short from, short to, std::string message) {
	short temp;
	do {
		std::cout << message << "\n";
		std::cin >> temp;
	} while (temp < from or temp > to);
	return temp;
}
int randBetween(int from, int to) {
	return rand() % (to - from + 1) + from;
}
int readInt() {
	int temp;
	std::cin >> temp;
	return temp;
}

int getStartRange(enDifficuly difficulty) {
	switch (difficulty) {
	case enDifficuly::Easy:
		return 1;
	case enDifficuly::Med:
		return 10;
	case enDifficuly::Hard:
		return 50;
	case enDifficuly::Mix:
		return 1;
	}
}
int getEndRange(enDifficuly difficulty) {
	switch (difficulty) {
	case enDifficuly::Easy:
		return 10;
	case enDifficuly::Med:
		return 50;
	case enDifficuly::Hard:
		return 300;
	case enDifficuly::Mix:
		return 300;
	}
}

int calculateCorrectAnswer(stQuestion question) {
	int a = question.firstOperand;
	int b = question.secondOperand;
	switch (question.operationType) {
	case enOperation::Add:
		return a + b;
	case enOperation::Sub:
		return a - b;
	case enOperation::Div:
		return a / b;
	case enOperation::Mult:
		return a * b;
	}
}
stQuestion generateQuestion(stSettings settings) {
	stQuestion question;
	int rangeStart = getStartRange(settings.difficultyOption);
	int rangeEnd = getEndRange(settings.difficultyOption);
	question.firstOperand = randBetween(rangeStart, rangeEnd);
	question.secondOperand = randBetween(rangeStart, rangeEnd);
	if (settings.operationOption != enOperation::OpMix)
		question.operationType = settings.operationOption;
	else
		question.operationType = (enOperation)randBetween(1, 4);

	question.correctAnswerValue = calculateCorrectAnswer(question);
	return question;
}

char operationToChar(enOperation operation) {
	switch (operation) {
	case Add:
		return '+';
	case Sub:
		return '-';
	case Mult:
		return '*';
	case Div:
		return '/';
	case OpMix:
		return '?';
	}
}
std::string operationToString(enOperation operation) {
	switch (operation) {
	case Add:
		return "Add";
	case Sub:
		return "Sub";
	case Mult:
		return "Mult";
	case Div:
		return "Div";
	case OpMix:
		return "Mix";
	}
}
std::string diffToString(enDifficuly diff) {
	switch (diff) {
	case enDifficuly::Easy:
		return "Easy";
	case enDifficuly::Med:
		return "Med";
	case enDifficuly::Hard:
		return "Hard";
	case enDifficuly::Mix:
		return "Mix";
	}
}


void printQuestion(stQuestion question, int n, int total) {
	std::cout << "Question [" << n << "/" << total << "]\n";
	std::cout << question.firstOperand << "\n";
	std::cout << question.secondOperand << " ";
	std::cout << operationToChar(question.operationType) << "\n";
	std::cout << "___________________" << "\n";
}
void validateQuestion(int playerAnswer, stQuestion question, int& correctCount) {
	if (playerAnswer == question.correctAnswerValue) {
		correctCount++;
		setSecreenColor(enColor::Green);
		std::cout << "Correct answer :-)\n\n";
	}
	else {
		setSecreenColor(enColor::Red);
		std::cout << "Wrong answer :-(\n";
		std::cout << "Correct answer is: " << question.correctAnswerValue << "\n\n";
	}
}
void printEndGameHeading(int correctCount, int total) {
	std::cout << "______________________________________\n";
	std::cout << "Final Result is ";
	if (correctCount >= total / 2)
		std::cout << "PASS :-)\n";
	else
		std::cout << "FAIL :-(\n";
	std::cout << "______________________________________\n";
}
void printResultSecreen(int correctCount, stSettings settings) {
	std::cout << "\n\n";
	printEndGameHeading(correctCount, settings.numberOfQuestions);
	std::cout << "\n";
	std::cout << "Number of Questions:\t" << settings.numberOfQuestions << "\n";
	std::cout << "Questions Level:\t" << diffToString(settings.difficultyOption) << "\n";
	std::cout << "Operations type:\t" << operationToString(settings.operationOption) << "\n";
	std::cout << "Number of correct answers:\t" << correctCount << "\n";
	std::cout << "Number of wrong answers:\t" << settings.numberOfQuestions - correctCount << "\n";
}
void startGameSession(stSettings settings) {
	stQuestion question;
	int playerAnswer;
	int correctCount = 0;
	for (int i = 1; i <= settings.numberOfQuestions; i++) {
		question = generateQuestion(settings);
		printQuestion(question, i, settings.numberOfQuestions);
		playerAnswer = readInt();
		validateQuestion(playerAnswer, question, correctCount);
	}
	printResultSecreen(correctCount, settings);
}
void clearScreen() {
	system("cls");
}
void startGame() {
	bool again = true;
	stSettings settings;
	do {
		settings.numberOfQuestions = readIntBetween(1, 100, "How many questions?");
		settings.difficultyOption = (enDifficuly)readIntBetween(1, 4, "[1]: Easy, [2]: Med, [3]: Hard, [4]: Mix");
		settings.operationOption = (enOperation)readIntBetween(1, 5, "[1]: Add, [2]: Sub, [3]: Mult, [4]: Div, [5]: Mix");
		startGameSession(settings);

		again = readIntBetween(0, 1, "Play again [0]:NO [1]:YES?");
		if (again) {
			clearScreen();
		}
	} while (again);
}

int main() {
	srand((unsigned)time(NULL));
	startGame();
	return 0;
}