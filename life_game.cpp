// Created by Jacob Schroeder April 2019
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

//array of all cells
vector<vector<string> > cells;
//array of all living cells
vector<vector<int> > living_cells;
//gameboard array
vector<vector<string> > game_board; 
//counter of all living cells;
int living_cells_num = 0;
//array for users choice of starting live cells
vector<vector<int> > start_cells;

//string for colored cells
string live_cell = "\033[1;31mX\033[0m";
string no_cell = "\033[1;34mO\033[0m";

//bool seeing if live cells exist or not
bool life_exists = false;

//function for creating the game board and allowing user to choose where the start cells will be
int creation(){
	//loctaions of the cells
	int choice_x;
	int choice_y;

	//number of starting live cells
	int live_cells_num;

	//allowing user to choose amount of starting cells
	cout << "How many live cells would you like (1-400)" << endl; 
	cout << "*note anything over 10 takes awhile to set" << endl;
	
	//getting live cell values and setting them in the start_cells array
	bool started = true;
	while (started == true){
		cin >> live_cells_num;

		//starting setting values if number is in the correct range
		if (live_cells_num >= 1 and live_cells_num <=400 ){

			start_cells.resize(live_cells_num);
			for (int i = 0; i < live_cells_num; i++){
				start_cells[i].resize(2);

				//setting proper grammar for number positions
				if (i+1 == 1){
					cout << "Where would you like your " << i+1 << "st cell" << endl;
				}
				else if (i+1 ==2){
					cout << "Where would you like your " << i+1 << "nd cell" << endl; 
				}
				else if (i+1 == 3){
					cout << "Where would you like your " << i+1 << "rd cell" << endl;
				} 
				else{
					cout << "Where would you like your " << i+1 << "th cell" << endl;
				}

				//setting values for live cells and ensuring they arent repeated
				bool is_choice_new = false;
				while (is_choice_new == false){

					//setting x value for live cell
					bool choice_x_range = true;
					while (choice_x_range == true){
						cout << "Which row (1-20)?" << endl;
						cin >> choice_x;

						if(choice_x >= 1 and choice_x <= 20){
							start_cells[i][0] = choice_x-1;
							choice_x_range = false;
						}
						else{
							cout << "Please enter a number in the range (1-20)" << endl;
						}
					}
					//setting y value for live cell
					bool choice_y_range = true;
					while (choice_y_range == true){
						cout << "Which collumn (1-20)?" << endl;
						cin >> choice_y;

						if(choice_y >= 1 and choice_y <= 20){
							start_cells[i][1] = choice_y-1;
							choice_y_range = false;
						}
						else{
							cout << "Please enter a number in the range (1-20)" << endl;
						}
					}
					//checking if the cell choice is new
					int safety = 0;
					for (int j = 0; j < i; j++){
						if (start_cells[i][0] != start_cells[j][0] or start_cells[i][1] != start_cells[j][1]){
							//do nothing
						}
						else{
							safety += 1;							
						}
					}
				    
					//checking for repeat values (safety != 0) if new value is a repeat
					if (safety == 0){
						is_choice_new = true;
					}
					else{
						safety = 0;
						cout << "Please enter a different value that you havent already used" << endl;
						is_choice_new = false;
					}
				}
			}

			started = false;
		}
		
		//ensuring value is in the appropriate range
		else{
			cout << "Please enter a number between 1 and 400" << endl;
			started = true;
		}
	}

	//setting live and dead cells
	cout << "This will be your cell board to begin" << endl;
	cells.resize(20);
	for (int i = 0; i < 20; i++){
		cells[i].resize(20);
		for (int j = 0; j < 20 ; j++){
			cells[i][j] = no_cell;
			for (int k = 0; k < live_cells_num; k++){
				if(i == start_cells[k][0] and j == start_cells[k][1]){
					cells[i][j] = live_cell;
				}
			}
		}
	}
}

//printing the gameboard
int form_game_board(){
	game_board.resize(22);
	for (int i = 0; i < 22; i++){
		game_board[i].resize(22);
		for (int j = 0; j < 22; j++){
			if (i == 0 or i == 21){
				game_board[i][j] = "─";
			}
			else if (j == 0 or j == 21){
				game_board[i][j] = "|";
			}
			else if (i >= 1 and i <= 20 and j >= 1 and j <= 20) {
				game_board[i][j] = cells[i-1][j-1];
			} 
		}
	}	
}

int print_game_board(){
	for (int i = 0; i < 22; i++){
		for (int j = 0; j< 22; j++){
			cout << game_board[i][j] << " ";
		}
		cout << endl;
	}
}

int day(){
	for (int i = 0; i < 22; i++){
		for (int j = 0; j < 22; j++){
			int surrounding_cells = 0;
			//checking surrounds for each cell on the board
			if (i >= 1 and i <= 20 and j >= 1 and j <= 20){
				//top left corner
				if (game_board[i-1][j-1] == live_cell){
					surrounding_cells += 1;
				}
				//top
				if (game_board[i-1][j] == live_cell){
					surrounding_cells += 1;
				}
				//top right corner
				if (game_board[i-1][j+1] == live_cell){
					surrounding_cells += 1;
				}
				//left side
				if (game_board[i][j-1] == live_cell){
					surrounding_cells += 1;
				}
				//right side
				if (game_board[i][j+1] == live_cell){
					surrounding_cells += 1;
				}
				//bottom left
				if (game_board[i+1][j-1] == live_cell){
					surrounding_cells += 1;
				}
				//bottom
				if (game_board[i+1][j] == live_cell){
					surrounding_cells += 1;
				}
				//bottom right
				if (game_board[i+1][j+1] == live_cell){
					surrounding_cells += 1;
				}

				//using surrounding cells to dictate what happens based on the rules:

				//if cell is alive and its neibours are less than 2 or greater than 1 it dies
				if ((game_board[i][j] == live_cell and surrounding_cells < 2) or (game_board[i][j] == live_cell and surrounding_cells >= 3)){
					cells[i-1][j-1] = no_cell;
					//add in vector array addition of coordinantes of new dead cells
				}

				//if a cell is null and its neibours equal 3 it is born
				else if (game_board[i][j] == no_cell and surrounding_cells == 3){
					cells[i-1][j-1] = live_cell;
					//add in vector array addition or coordinates of new live cells
				}
			}
		}
	}
}

//checking to see if cells still exist on the board
int find_life(){
	life_exists = false;
	for (int i = 0; i < 20; i++){
		for (int j = 0; j< 20; j++){
			if (cells[i][j] == live_cell){
				life_exists = true;
			}
		}
	}
}

int main() 
{ 
	cout << "\033[1;32mWelcome to the Game of Life!\033[0m" << endl;
	bool game_playing = true;
	bool cont_game = true;
	int days_played = 0;
	string Y_or_N;
	while (game_playing == true){
		
		//welcoming user
		cout << "Begin by setting which cells you would like alive on the first day" << endl;
		
		//creating the base gameboard
		creation();
		form_game_board();
		print_game_board();

		while (cont_game == true){
			
			//checking for living cells
			life_exists = false;
			for (int i = 0; i < 22; i++){
				for (int j = 0; j< 22; j++){
					if (game_board[i][j] == live_cell){
						life_exists = true;
					}
				}
			}

			//checking if life still exists on the board
			if (life_exists == false){
				cout << "You have no living cells left " << "[Days survived " << days_played  << "]" << endl;
				cont_game = false;
				break;
			}

			//user inputs to go to the next cell day
			if (days_played == 0){
				cout << "Press Y then enter to begin the game of life or N then enter to exit" << endl;
				cin >> Y_or_N;
			}
			else if (days_played > 0){
				cout << "End of day number " << days_played << endl;
				cout << "Press Y then enter to continue or N then enter to exit" << endl;
				cin >> Y_or_N;
			}

			//getting inputs
			if (Y_or_N == "Y" or Y_or_N == "y"){

				//updating amount of days cell board has survived for
				days_played += 1;
				
				//updating board
				day();
				form_game_board();
				print_game_board();
			}
			else if (Y_or_N == "N" or Y_or_N == "n"){
				cont_game = false;
			}
			else{
				cout << "I do not understand that input please try again";
			}
		}

		//seeing if player wants to try again after they have quit out
		cout << "Would you like to play another game? (Y for yes N for no)" << endl;
		bool play_again = true;
		while (play_again == true){
			cin >> Y_or_N;
			if (Y_or_N == "Y" or Y_or_N == "y"){
				game_playing = true;
				cont_game = true;
				play_again = false;
			}
			else if (Y_or_N == "N" or Y_or_N == "n"){
				game_playing = false;
				play_again = false;
			}
			else{
				cout << "Please input a suitable input" << endl;
			}
		}
	}
	
	// Thanking user and ending the program
	if (game_playing == false){
		cout << "Thank you for playing the game of life" << endl;
		return 0; 
	}	
} 