#include <iostream>
#include <string>
#include <fstream>
#include <stack>


using namespace std;



const int maxRows = 200;
const int maxCols = 300;

int rows = 0;
int cols = 0;
bool found = false;

struct stateSpace {
	int x;
	int y;
};

stack<stateSpace> arrayStack;

stateSpace startingPosition = { 0, 0 };

char mazeArray[maxRows][maxCols] = { 0 };

//int rows, cols;

//string file;



//const int R = 12, C = 25s;

/*= {



	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','e','W','W','W','W','W','W','W','W','W'},







	{'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},







	{'W','W','W','W',' ','W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W','W','W',' ','W'},







	{'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','W'},







	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W','W','W','W','W','W','W',' ','W'},







	{'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W'},







	{'W','W','W','W','W','W',' ','W','W','W','W','W','W','W','W','W',' ','W','W','W','W',' ','W',' ','W'},







	{'W',' ',' ',' ',' ','W',' ','W',' ','W','W','W','W','W','W','W',' ','W','W','W','W','W','W',' ','W'},







	{'W',' ','W','W',' ','W',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ','W'},







	{'W',' ','W','W',' ','W',' ','W',' ','W','W','W','W','W',' ','W','W','W','W','W','W','W','W',' ','W'},







	{'W',' ','X','W',' ',' ',' ','W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},







	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},



 };



 */







 /*



  WWWWWWWWWWWWWWWWeWWWWWWWW



  W                       W



  WWWWW WWWWWWWWWWW WWWWW W



  W             W         W



  WWWWWWWWWWWWW WWWWWWWWW W



  W             W       W W



  WWWWWW WWWWWWWW WWWWW W W



  W    W W WWWWWW WWWWWWW W



  W WW W W              W W



  W WW W W WWWWW WWWWWWWW W



  W xW   W     W          W



  WWWWWWWWWWWWWWWWWWWWWWWWW



  */



bool buildPath(stateSpace current);
//bool boundaryCheck(stateSpace current);

void fileSize(string file) {
	ifstream read;
	string line;
	read.open(file);
	while (getline(read, line)) {
		rows++;
	}
	cols = (int)line.length();
	read.close();
}

void readFromFile(char mazeArray[maxRows][maxCols], string file) {
	ifstream read;
	char fileChar;
	int i = 0, j = 0;
	read.open(file);

	if (!read) {
		cout << "error" << endl;
		system("pause");
		read.close();
	}
	while (!read.eof()) {
		read.get(fileChar);
		if (fileChar == 'e') {
			startingPosition.x = i;
			startingPosition.y = j;
		}
		mazeArray[i][j] = fileChar;
		j++; 
		if (j > cols) {
			j = 0;
			i++;
		}
	}
	read.close();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << mazeArray[i][j] << ' ';
		}
		cout << endl;
	}
}

stateSpace backtrack(stateSpace current) {
	mazeArray[current.x][current.y] = '.';
	arrayStack.pop();
	stateSpace newCoord = arrayStack.top();
	arrayStack.pop();
	return newCoord;
}


bool treasure(stateSpace current) {

	if (mazeArray[current.x][current.y] == 'X')
		return found = true;
	return found = false;
}


int main() {
	

	string file = "maze.txt";
	fileSize(file);
	readFromFile(mazeArray, file);
	
	
	cout << "Press ENTER repeatedly to travese the maze...\n";
	
	arrayStack.push(startingPosition);
	buildPath(startingPosition);


	return 0;
}


bool buildPath(stateSpace current) {

	arrayStack.push(current);

	cin.ignore();


	for (int i = 0; i < rows; ++i) {

		for (int j = 0; j < cols; ++j) {

			cout << mazeArray[i][j] << ' ';

		}

		cout << endl;
	}

	stateSpace newSpace = { 0,0 };


	while (found != true) {

		if ((mazeArray[current.x][current.y]) == 'X')				// If goal is reached, X representing goal on maze
			return true;

		if (mazeArray[current.x][current.y] != 'e') {
			mazeArray[current.x][current.y] = '*';
		}

		if (mazeArray[current.x - 1][current.y] == ' ') {     // Check north

			newSpace.x = current.x - 1;
			newSpace.y = current.y;
			treasure(newSpace);
			buildPath(newSpace);
			return true;
		}

		if (mazeArray[current.x][current.y - 1] == ' ') {	// Check west
			newSpace.x = current.x;
			newSpace.y = current.y - 1;
			treasure(newSpace);
			buildPath(newSpace);
			return true;
		}


		if (mazeArray[current.x + 1][current.y] == ' ') {	// Check south
			newSpace.x = current.x + 1;
			newSpace.y = current.y;
			treasure(newSpace);
			buildPath(newSpace);
			return true;
		}


		if (mazeArray[current.x][current.y + 1] == ' ') {		// Check east
			newSpace.x = current.x;
			newSpace.y = current.y + 1;
			treasure(newSpace);
			buildPath(newSpace);
			return true;
		}


		if (mazeArray[current.x][current.y] != ' ') {
			newSpace = backtrack(current);
			buildPath(newSpace);
			return true;
		}

	}
	return false;
}