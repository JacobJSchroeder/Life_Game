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
//counter of all living cells;
int living_cells_num = 0;
//array for users choice of starting live cells
vector<vector<int> > start_cells;

//string for colored cells
string live_cell = "\033[1;31mX\033[0m";
string no_cell = "\033[1;34mO\033[0m";

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
						cout << "Which collumn (1-20)?" << endl;
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
						cout << "Which row (1-20)?" << endl;
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
			cout << cells[i][j] << " "; 
		}
		cout << " " << endl;
	}
}

//printing the gameboard
int print_board(){
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			cout << cells[i][j] << " ";
		}
		cout << " " << endl;
	}	
}

//finding which cells are living
int find_life(){
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			if (cells[i][j] == live_cell){
				living_cells_num += 1;
				living_cells.resize(living_cells_num);
				for (int k = living_cells_num-1; k < living_cells_num; k++){
					living_cells[k].resize(1);
					living_cells[k][0] = i;
					living_cells[k][1] = j;
					//debug
					cout << living_cells[k][0] << " " << living_cells[k][1] << endl;
				}
			}
		}
	}	
}

//finding which cells live or die
int day(){
	// finding surrounding cells
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			//accounting for the non existant coordinantes
			if (!cells[i-1][j-1]){
				cout << "anal";
			}
		}
	}	
}

int main() 
{ 
	//welcoming user
	cout << "\033[1;32mWelcome to the Game of Life!\033[0m" << endl;
	creation();
	find_life();
	day();
    return 0; 
} 