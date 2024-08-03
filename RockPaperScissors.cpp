#include <iostream>


enum enPlayOption { Stone = 1, Paper = 2, Scissors = 3};
enum enResult { Player, Computer, Draw };
enum enColor {Red, Yellow, Green};
struct stGameStats {
	int playerWins;
	int computerWins;
	int draws;
};
void initStats(stGameStats& stats) {
	stats.playerWins = 0;
	stats.computerWins = 0;
	stats.draws = 0;
}
short readIntBetween(short from, short to, std::string message) {
	short temp;
	do {
		std::cout << message << "\n";
		std::cin >> temp;
	} while (temp < from or temp > to);
	return temp;
}
void printResultsScreen(int totalRounds, stGameStats stats) {
	std::cout << "\n\n--------------------------------------\n";
	std::cout << "--------------------------------------\n";
	std::cout << "\tEnd of the game\n";
	std::cout << "\tPlayer wins: [" << stats.playerWins << "]\n";
	std::cout << "\tComputer wins: [" << stats.computerWins<< "]\n";
	std::cout << "\tDraw: [" << stats.draws << "]\n";
	if (stats.playerWins > stats.computerWins)
		std::cout << "\tWinner: [" << "Player" << "]\n";
	else if (stats.playerWins < stats.computerWins)
		std::cout << "\tWinner: [" << "Computer" << "]\n";
	else
		std::cout << "\tWinner: [" << "NO WINNER" << "]\n";
	std::cout << "--------------------------------------\n";

}
int randBetween(int from, int to) {
	return rand() % (to - from + 1) + from;
}
bool isPaper(enPlayOption move) {
	return move == enPlayOption::Paper;
}
bool isStone(enPlayOption move) {
	return move == enPlayOption::Stone;
}
bool isScissors(enPlayOption move) {
	return move == enPlayOption::Scissors;
}
void setSecreenColor(enColor color) {
	switch (color)
	{
	case enColor::Red:
		system("color 4F");
		break;
	case enColor::Yellow:
		system("color 6F");
		break;
	case enColor::Green:
		system("color 2F");
		break;
	}
}
enResult checkWinner(enPlayOption playerMove, enPlayOption computerMove) {
	if (playerMove == computerMove) {
		setSecreenColor(enColor::Yellow);
		return enResult::Draw;
	}
	else if (isPaper(playerMove) && isStone(computerMove) ||
			 isStone(playerMove) && isScissors(computerMove) || 
				isScissors(playerMove) && isPaper(computerMove)) {
		setSecreenColor(enColor::Green);
		return enResult::Player;
	}
	else {
		setSecreenColor(enColor::Red);
		std::cout << "\a";
		return enResult::Computer;
	}
}
std::string moveToString(enPlayOption move) {
	switch (move)
	{
	case enPlayOption::Stone:
		return "Stone";
		break;
	case enPlayOption::Paper:
		return "Paper";
		break;
	case enPlayOption::Scissors:
		return "Scissors";
		break;
	default:
		break;
	}
}
std::string resultToString(enResult result)
{
	switch (result) {
	case Player:
		return "Player";
		break;
	case Computer:
		return "Computer";
		break;
	case Draw:
		return "Draw";
		break;
	default:
		break;
	}
}
void printRoundResult(int roundNumber, enResult result, enPlayOption playerMove, enPlayOption computerMove) {
	std::cout << "____________ ROUND [" << roundNumber << "] ____________\n";
	std::cout << "\tPlayer Move:\t" << moveToString(playerMove) << "\n";
	std::cout << "\tComputer Move:\t" << moveToString(computerMove) << "\n";
	std::cout << "\tRound Winner:\t" << resultToString(result) << "\n";


	std::cout << "___________________________________\n";
}
void playRound(int roundNumber, stGameStats& stats) {
	std::cout << "Round [" << roundNumber << "] begins\n";
	std::string message = "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors";
	enPlayOption playerMove = (enPlayOption) readIntBetween(1, 3, message);
	enPlayOption computerMove = (enPlayOption)randBetween(1, 3);
	
	enResult result = checkWinner(playerMove, computerMove);
	printRoundResult(roundNumber, result, playerMove, computerMove);

	switch (result) {
	case enResult::Player:
		stats.playerWins++;
		break;
	case enResult::Computer:
		stats.computerWins++;
		break;
	case enResult::Draw:
		stats.draws++;
		break;
	}
}
void clearScreen() {
	system("cls");
}
void startGame() {
	bool again;
	stGameStats stats;
	do {
		initStats(stats);
		short totalRounds = readIntBetween(1, 10, "Enter the number of rounds:");
		for (short i = 0; i < totalRounds; i++) {
			playRound(i + 1, stats);
		}
		printResultsScreen(totalRounds, stats);
		again = readIntBetween(0, 1, "Play Again? [0]NO [1]YES:");
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