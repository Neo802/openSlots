#include "wheel.h"

using namespace std;

int money; // Your money

void print_screen(int n, vector<Wheel*> slot_machine);
void game_play(int n, vector<Wheel*> slot_machine);
bool win_condition1(int n, vector<Wheel*> slot_machine);
bool win_condition2(int n, vector<Wheel*> slot_machine);
bool win_condition3(int n, vector<Wheel*> slot_machine);
void winning(int& prize, vector<Wheel*> slot_machine, int bet);

int main() {
	srand(time(0));

	int req = 0; // requested amount of spins for slot machine
	money = 0; // your amount of money
	vector<Wheel*> slot_machine;

	cout << "Enter a sum of money: " << endl;
	cin >> money;
	
	cout << "Enter number of spins: " << endl;
	cin >> req;

	for (int i = 0; i < req; i++) {
		slot_machine.push_back(new Wheel);
	}

	int num_spins = slot_machine.size();
	bool game_playing = true;
	int bet = 0;
	int betting_rows = 1;
	while (money > 0) {
		while (game_playing) {
			//cout << endl << endl;
			system("cls");
			cout << "Round Beginning... \nEnter bet amount: \n";
			cin >> bet;
			cout << "Enter number of rows to bet on (maximum of 3)\n";
			cin >> betting_rows;

			money -= bet * betting_rows;

			game_play(num_spins, slot_machine);
			// win conditions

			if (betting_rows <= 1)
				if (win_condition2(num_spins, slot_machine))
					winning(money, slot_machine, bet);

			if (betting_rows <= 2)
				if (win_condition1(num_spins, slot_machine))
					winning(money, slot_machine, bet);

			if (betting_rows <= 3)
				if (win_condition3(num_spins, slot_machine))
					winning(money, slot_machine, bet);

			if (money <= 0) {
				cout << "You lose! Out of money!" << endl;
				game_playing = false;
			}
			
			cout << "You lost!" << endl;
			Sleep(3000); // Unit is milliseconds
		
		}
		Sleep(20000); // Unit is milliseconds
	}

}

void print_screen(int n, vector<Wheel*> slot_machine) {
	system("cls");
	for (int i = 0; i < n; i++)
		cout << slot_machine[i]->get_first() << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << slot_machine[i]->get_second() << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << slot_machine[i]->get_third() << " ";
	cout << endl;
	cout << endl << endl << "Money: " << ::money << endl;
}

void game_play(int n, vector<Wheel*> slot_machine) {
	int time = rand() % 15 + 10;
	while (time > 0) {
		for (int i = 0; i < n; i++)
			slot_machine[i]->update();
		print_screen(n, slot_machine);
		usleep(400000);
		time--;
	}

	int stop_count = 0;
	int j = 0;

	while (stop_count < n) {
		for (j = stop_count; j < n; j++)
			slot_machine[j]->update();
		print_screen(n, slot_machine);
		stop_count++;
		usleep(400000);
	}

}

bool win_condition1(int n, vector<Wheel*> slot_machine) {
	int winner_number = slot_machine[0]->get_first();
	for (int i = 1; i < n; i++) {
		if (winner_number != slot_machine[i]->get_first())
			return false;
	}
	return true;
}

bool win_condition2(int n, vector<Wheel*> slot_machine) {
	int winner_number = slot_machine[0]->get_second();
	for (int i = 1; i < n; i++) {
		if (winner_number != slot_machine[i]->get_second())
			return false;
	}
	return true;
}

bool win_condition3(int n, vector<Wheel*> slot_machine) {
	int winner_number = slot_machine[0]->get_third();
	for (int i = 1; i < n; i++) {
		if (winner_number != slot_machine[i]->get_third())
			return false;
	}
	return true;
}

void winning(int& prize, vector<Wheel*> slot_machine, int bet) {
	prize += slot_machine[1]->get_second() * bet;
	cout << "Winner!" << endl;
	cout << "You won $" << slot_machine[1]->get_second() * bet << endl;
}