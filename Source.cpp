#include <iostream>
#include <vector>
#include <string>
using namespace std;
char matrix[3][3] = { 'a','b','c','d','e','f','g','h','i' };
char player = 'x';
vector<string> pName = {""};
vector<int> pScore = { 0 };
vector<int> pWins = { 0 };
vector<int> pLoss = { 0 };


int min(int a, int b)
{
	if (a < b) return a;
	else return b;
}
int max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}

struct Move 
{ 
    int row, col; 
}; 
  
// True if no moves are left on board.
bool isMovesLeft(char b[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (b[i][j]=='a' || b[i][j]=='b' || b[i][j]=='c' || b[i][j]=='d' || b[i][j]=='e' || b[i][j]=='f' || b[i][j]=='g' || b[i][j]=='h' || b[i][j]=='i' ) 
                return true; 
    return false; 
} 
  
int checkWin(char b[3][3]) 
{ 
    // Wins on Rows
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]=='o') 
                return +10; 
            else if (b[row][0]=='x') 
                return -10; 
        } 
    } 
  
    // Wins on Columns
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]=='o') 
                return +10; 
  
            else if (b[0][col]=='x') 
                return -10; 
        } 
    } 
  
    // Wins on Diagonals
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]=='o') 
            return +10; 
        else if (b[0][0]=='x') 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]=='o') 
            return +10; 
        else if (b[0][2]=='x') 
            return -10; 
    } 
 
    return 0; 
} 
  
// Minimax function.
int minimax(char b[3][3], int depth, bool isMax) 
{ 
    int score = checkWin(b); 
  
    // If maximizer has won
    if (score == 10) 
        return score; 
  
    // If minimizer has won
    if (score == -10) 
        return score; 
  
    // If game is draw
    if (isMovesLeft(b)==false) 
        return 0; 
  
    // If maximizer move 
    if (isMax) 
    { 
        int best = -500; 
   
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                if (b[i][j]=='a' || b[i][j]=='b' || b[i][j]=='c' || b[i][j]=='d' || b[i][j]=='e' || b[i][j]=='f' || b[i][j]=='g' || b[i][j]=='h' || b[i][j]=='i' ) 
                { 
					char temp = b[i][j];
                    b[i][j] = 'o'; //Because computer plays as 'o'

                    best = max( best, 
                        minimax(b, depth+1, !isMax) ); 

                    b[i][j] = temp; 
                } 
            } 
        } 
        return best; 
    } 
	
    // If minimizer move 
    else
    { 
        int best = 500; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (b[i][j]=='a' || b[i][j]=='b' || b[i][j]=='c' || b[i][j]=='d' || b[i][j]=='e' || b[i][j]=='f' || b[i][j]=='g' || b[i][j]=='h' || b[i][j]=='i' ) 
                { 
					char temp = b[i][j];
                    // Make the move 
                    b[i][j] = 'x'; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, 
                           minimax(b, depth+1, !isMax)); 
  
                    // Undo the move 
                    b[i][j] = temp; 
                } 
            } 
        } 
        return best; 
		
    } 
} 
  
// To find the best possible move
Move bestMove(char b[3][3]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    //  return the cell with optimal value 
    for (int i = 0; i<3; i++) 
    { 
        for (int j = 0; j<3; j++) 
        { 
            // If cell is empty
            if (b[i][j]=='a' || b[i][j]=='b' || b[i][j]=='c' || b[i][j]=='d' || b[i][j]=='e' || b[i][j]=='f' || b[i][j]=='g' || b[i][j]=='h' || b[i][j]=='i' ) 
            { 
				char temp = b[i][j];
 
                b[i][j] = 'o'; 
  
                int tryMove = minimax(b, 0, false); 
  
                // Undo the move 
                b[i][j] = temp; 
  
                // If current score is higher then update that as best move
                if (tryMove > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = tryMove; 
                } 
            } 
        } 
    }  
    return bestMove; 
} 



void Draw()
{

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << matrix[i][j] << " " ;
		}
		cout << endl;
	}
}

void Input()
{
	char inp;
	cout << "Input letter of field :";
	cin >> inp;
	if (inp != 'a' && inp != 'b' && inp != 'c' && inp != 'd' && inp != 'e' && inp != 'f' && inp != 'g' && inp != 'h' && inp != 'i') {
		cout << "Please enter a valid input." << endl;
		Input();
	}
	if (inp == 'a') {
		if (matrix[0][0] == 'a') matrix[0][0]=player; 
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'b') {
		if (matrix[0][1] == 'b') matrix[0][1] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'c') {
		if (matrix[0][2] == 'c') matrix[0][2] = player; 
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'd') {
		if (matrix[1][0] == 'd') matrix[1][0] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'e') {
		if (matrix[1][1] == 'e') matrix[1][1] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'f') {
		if (matrix[1][2] == 'f') matrix[1][2] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'g') {
		if (matrix[2][0] == 'g') matrix[2][0] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'h') {
		if (matrix[2][1] == 'h') matrix[2][1] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}
	if (inp == 'i') {
		if (matrix[2][2] == 'i') matrix[2][2] = player;
		else {
			cout << "Field in use, try again." << endl; Input();
		}
	}

}

void TogglePlayer()
{
	if (player == 'x') {
		player = 'o';
	}
	else {
		player = 'x';
	}
}

char win()
{
	if (matrix[0][0] == player && matrix[0][1] == player && matrix[0][2] == player) return player;
	if (matrix[1][0] == player && matrix[1][1] == player && matrix[1][2] == player) return player;
	if (matrix[2][0] == player && matrix[2][1] == player && matrix[2][2] == player) return player;
	if (matrix[0][0] == player && matrix[1][0] == player && matrix[2][0] == player) return player;
	if (matrix[0][1] == player && matrix[1][1] == player && matrix[2][1] == player) return player;
	if (matrix[0][2] == player && matrix[1][2] == player && matrix[2][2] == player) return player;
	if (matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player) return player;
	if (matrix[2][0] == player && matrix[1][1] == player && matrix[0][2] == player) return player;

	
	return '/';
}

void twoPlayer() {
	Draw();
	while (1)
	{
		Input();
		if (win() == 'x') {
			cout << "X wins!"<<endl;


		}
		else if (win() == 'o')
		{
			cout << "O wins!" <<endl;

		}
		else if (!isMovesLeft(matrix))
		{
			cout << "Game is  draw!"<<endl;
			break;
		}
		Draw();
		TogglePlayer();
	}
}

void vsComp() {
	Draw();
	while (1)
	{
		if (player == 'x')
		{
			Input();

			if (win() == 'x') {
				cout << "X wins!";
				break;
			}
			else if (win() == 'o')
			{
				cout << "O wins!";
				break;
			}
			Draw();
			TogglePlayer();
		}
		if (player == 'o')
		{
			Move newMove = bestMove(matrix);
			cout << endl << "best move is [" << newMove.row << "][" << newMove.col << "]" << endl;
			matrix[newMove.row][newMove.col] = 'o';
			if (win() == 'x') {
				cout << "X wins!";
				break;
			}
			else if (win() == 'o')
			{
				cout << "O wins!";
				break;
			}
			Draw();
			TogglePlayer();

		}
	}
}

int main()
{
	
	while (1)
	{	
		int index = 0;
		int score = 0;

		string name;
		cout << "Please enter your name :";
		cin >> name;
		for (int i = 0; i < pName.size(); i++)
		{
			if (pName[i] == name) index = i;
			else
			{
				pName.push_back(name);
				pScore.push_back(0);
				pWins.push_back(0);
				pLoss.push_back(0);
			}
		}

		int mode;
		cout << "1. Player vs Player" << endl << "2. Player vs Computer" << endl << "3. Close game." << endl << "Select Game mode : " ;
		cin >> mode; cout << endl;
		if (mode == 1) {

			twoPlayer();
		}
		else if (mode == 2)
		{
			vsComp();
		}
		else if (mode == 3) break;
		return 0;
	}
}