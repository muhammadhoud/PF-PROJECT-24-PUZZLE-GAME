#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<fstream>
using namespace std;
int* add;



// Function prototypes
// These functions are declared here to allow the compiler to recognize them before they are defined.
void menu();                // Menu function prototype
void lock();                // Lock function prototype
void game();                // Game function prototype
void stage();               // Stage function prototype
void init();                // Initialization function prototype
void goal();                // Goal state generation function prototype
void showGrid();            // Display the game board function prototype
void showGoal();            // Display the goal state function prototype
bool Is_Solveable(void goal(), void init());    // Solvability check function prototype
bool is_goal();             // Check if the current state is the goal state function prototype
int* legal_moves();         // Determine legal moves function prototype
void make_move(char move);  // Execute a move function prototype
void print_path();          // Print the path taken during the game function prototype

char k, pr[200];            // Variables for user input and storing path
int p, y, u, arr[25], arg[25], leg[4]; // Variables for game state and legal moves

// Main function
int main()
{
    // Display welcome messages and initiate the menu
    system("Color 16");
    cout << "                                                  IT'S A PLEASURE TO HAVE YOU IN THIS GAME          " << endl;
    cout << "                                    GENTLE MAN YOU ARE GOING TO WITNESS A MASTERPIECE OF PUZZLE GAMES" << endl << endl;
    cout << "                                                     Get yourself ready for the game" << endl << endl;
    cout << "                                                     Input any charcter to continue ";
    char z;
    cin >> z;
    menu(); // Call the menu function
}

// Menu function
void menu()
{
    // Display the main menu and proceed according to user input
    system("Color DE");
    lock(); // Call the lock function to display the menu and get user input
    stage(); // Call the stage function to proceed based on user choice
}

// Stage function
void stage()
{
    // Loop until user chooses to exit
    while (y != 4)
    {
        // Display appropriate message for invalid input
        if (y < 0 || y>4)
        {
            cout << "please eneter valid number ";
        }
        // Proceed based on user choice
        if (y == 1)
        {
            game(); // Start the game
            break;
        }
        if (y == 2)
        {
            // Display game instructions
            cout << endl << "INSTRUCTIONS:" << endl;
            cout << "The 24 is a puzzle invented and popularized by Noyes Palmer Chapman in the 1870s. It is played on a 5-by-5 grid with 15" << endl;
            cout << "square blocks labeled 1 through 15 and a blank square.There are two boards, one is the board you play game at, other" << endl;
            cout << "is the goal state we want to achieve.Your goal is to rearrange the tiles / blocks so that they are in order specified as goal state." << endl;
            cout << "You are permitted to slide blank tile horizontally or vertically in order to make moves." << endl;
        }
        if (y == 3)
        {
            // Display game credits
            cout << endl << "MUHAMMAD HOUD      22F-3376    1E" << endl;
            cout << "ALIA               22F-3339    1E" << endl;
        }
        lock(); // Redisplay the menu for further input
    }
}

// Lock function
void lock()
{
    // Display the main menu options and get user input
    cout << endl << "                  MAIN MENU                     " << endl << endl;
    cout << "    1. PLAY GAME" << endl;
    cout << "    2.INSTRUCTIONS" << endl;
    cout << "    3.CREDITS OF GAME" << endl;
    cout << "    4.EXIT GAME" << endl << endl;
    cout << "    INPUT 1,2,3 OR 4 ACCORDING TO THE NUMBER IN MENU TO GET THE DESIRED RESULT ";
    cin >> y;
}

// Game function
void game()
{
    int j = 0;
    bool ok = true, go = true;
    system("Color 74");
    cout << endl << "DO YOU WANT TO RESUME OLD GAME? PRESS '1' TO RESUME '2' FOR NEW GAME" << endl;
    cin >> u;
    while (ok != false)
    {
        init(); // Initialize the game state
        goal(); // Generate the goal state
        if (u == 1)
        {
            // Load saved game data if requested
            ifstream indata;
            indata.open("gamedata.txt");
            int component, is_goal;
            if (indata.is_open() == true)
            {
                indata >> p;
                cout << endl;
                indata >> go;
                for (int i = 0; i < 24; i++) {
                    indata >> arr[i];
                    cout << endl;
                }

                for (int i = 0; i < 24; i++) {
                    indata >> arg[i];
                    cout << endl;
                }

            }
            indata.close();
        }
        // Check if the game is solvable
        ok = Is_Solveable(goal, init);
    }
    while (go != false)
    {

        showGrid(); // Display the current game state
        showGoal(); // Display the goal state
        is_goal(); // Check if the goal is achieved
        add = legal_moves(); // Determine legal moves
        for (int i = 0; i < 4; i++) {
            leg[i] = *(add + i);
        }
        cout << endl << "ENTER YOUR MOVE" << endl;
        cout << "INPUT U FOR UP, D FOR DOWN, L FOR LEFT OR R FOR RIGHT" << endl;
        cin >> k;
        make_move(k); // Execute user move
        pr[j] = k; // Store move in the path
        j++;
        ofstream gamedata;
        gamedata.open("gamedata.txt");

        gamedata << p << endl;
        gamedata << go << endl;
        for (int i = 0; i < 24; i++) {
            gamedata << arr[i] << " " << endl;
        }
        gamedata << endl << endl;
        for (int i = 0; i < 24; i++) {
            gamedata << arg[i] << " " << endl;
        }
        gamedata.close();
    }

    cout << "~~~~~~~~~~~~~~~~~~~~CONGRATULATIONS~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~YOU WIN~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "YOUR MOVES DURING THE GAME:" << endl << endl;
    print_path(); // Print the path taken during the game
}

// Initialize the game state
void init()
{
    int high = 25, b, temp;
    for (int i = 0; i < 25; i++)
    {
        arr[i] = i + 1;
    }
    srand(time(0));
    //random number from 1-24
    for (int j = 25 - 1; j >= 0; j--)
    {
        b = rand() % high + 1;
        temp = arr[b];
        arr[b] = arr[j];
        arr[j] = temp;
        high--;
    }
    for (int i = 0; i < 25; i++)
    {
        if (arr[i] == 25)
        {
            p = i;
        }
    }
}

// Generate the goal state
void goal()
{
    int limit = 25, c, get1;
    for (int i = 0; i < 25; i++)
    {
        arg[i] = i + 1;
    }
    for (int j = 25 - 1; j >= 0; j--)
    {
        c = rand() % limit + 1;
        get1 = arg[c];
        arg[c] = arg[j];
        arg[j] = get1;
        limit--;
    }
}

// Display the current game state
void showGrid()
{
    system("Color B5");
    cout << endl << "INTIAL STATE:" << endl << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < 25; i++)
    {
        if (i == p)
        {
            cout << "|" << setw(4) << "   ";
        }
        else {
            cout << "|" << setw(4) << arr[i];
        }
        if ((i + 1) % 5 == 0)
        {
            cout << "|" << endl;
            cout << "---------------------------" << endl;
        }
    }
}

// Display the goal state
void showGoal()
{
    system("Color B5");
    cout << endl << "GOAL STATE:" << endl << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < 25; i++)
    {
        if (arg[i] == 25 || arg[i] == 0)
        {
            cout << "|" << setw(4) << "  ";
        }
        else
        {
            cout << "|" << setw(4) << arg[i];
        }
        if ((i + 1) % 5 == 0)
        {
            cout << "|" << endl;
            cout << "---------------------------" << endl;
        }
    }
}

// Check if the game is solvable
bool Is_Solveable(void goal(), void init())
{
    int x = 0, z = 0;
    for (int i = 0; i < 25; i++)
    {
        for (int j = i; j < 25; j++)
        {
            if (arr[j] < arr[i])
            {
                x++;
            }
        }
    }
    for (int i = 0; i < 25; i++)
    {
        for (int j = i; j < 25; j++)
        {
            if (arg[j] < arg[i])
            {
                z++;
            }
        }
    }
    if ((z % 2 == x % 2))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Check if the current state is the goal state
bool is_goal()
{
    for (int i = 0; i < 25; i++)
    {
        if (arr[i] != arg[i]) {
            return false;
            break;
        }
        else {
            return true;
        }
    }
}

// Determine legal moves
int* legal_moves()
{
    /* arl[0]=left, arl[1]=up, arl[2]=down, arl[3]=right */
    int arl[4] = { 0 };
    if (p % 5 == 0)
    {
        if (p >= 0 && p <= 20)
        {
            arl[3] = 1;
            if (p != 20 && p != 0) {
                arl[2] = 1;
                arl[1] = 1;
            }
            if (p == 0) {
                arl[2] = 1;
            }
            if (p == 20) {
                arl[1] = 1;
            }
        }
    }
    if (p == 6 || p == 7 || p == 8 || p == 11 || p == 12 || p == 13 || p == 16 || p == 17 || p == 18)
    {
        for (int i = 0; i < 4; i++)
        {
            arl[i] = 1;
        }
    }
    if (p > 0 && p <= 4)
    {
        arl[0] = 1;
        arl[2] = 1;
        if (p != 4)
        {
            arl[3] = 1;
        }
    }
    if (p > 20)
    {
        arl[0] = 1;
        arl[1] = 1;
        if (p < 24)
        {
            arl[3] = 1;
        }
    }
    if (p == 9 || p == 14 || p == 19)
    {
        for (int i = 0; i < 3; i++) {
            arl[i] = 1;
        }
    }
    return arl;
}

// Execute a move
void make_move(char move)
{
    int temp = arr[p];
    if (move == 'L' || move == 'l')
    {
        if (leg[0] == 1)
        {
            arr[p] = arr[p - 1];
            arr[p - 1] = temp;
            p -= 1;
        }
        else
        {
            cout << endl << "PLEASE ENTER A VALID MOVE" << endl;
        }
    }
    else if (move == 'U' || move == 'u')
    {
        if (leg[1] == 1)
        {
            arr[p] = arr[p - 5];
            arr[p - 5] = temp;
            p -= 5;
        }
        else
        {
            cout << endl << "PLEASE ENTER A VALID MOVE" << endl;
        }
    }
    else if (move == 'D' || move == 'd')
    {
        if (leg[2] == 1)
        {
            arr[p] = arr[p + 5];
            arr[p + 5] = temp;
            p += 5;
        }
        else
        {
            cout << endl << "PLEASE ENTER A VALID MOVE" << endl;
        }
    }
    else if (move == 'R' || move == 'r')
    {
        if (leg[3] == 1)
        {
            arr[p] = arr[p + 1];
            arr[p + 1] = temp;
            p += 1;
        }
        else
        {
            cout << endl << "PLEASE ENTER A VALID MOVE" << endl;
        }
    }
    else
    {
        cout << endl << "PLEASE ENTER A VALID MOVE" << endl;
    }
}

// Print the path taken during the game
void print_path()
{
    system("Color E4");
    cout << "U FOR UP, D FOR DOWN, L FOR LEFT AND R FOR RIGHT" << endl;
    cout << "{";
    for (int i = 0; pr[i] != '\0'; i++)
    {
        cout << " " << pr[i] << ",";
    }
    cout << "}" << endl;
}
