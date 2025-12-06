
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner{ Player = 1, Computer = 2, Draw = 3 };


struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner GameWinner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

short HowManyRounds()
{
    short Rounds;
    do
    {
        cout << "How Many Rounds 1 to 10 : " << endl;
        cin >> Rounds;

    } while (Rounds < 1 || Rounds > 10);

    return Rounds;
}

enGameChoice ReadPlayerChoice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? : ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{

    return (enGameChoice)RandomNumber(1, 3);

}

void SetWinnerScreenColor(enWinner Winner)
{

    switch (Winner)
    {
    case enWinner::Player:
        system("color 2f"); // Green Color
        break;

    case enWinner::Computer:
        system("color 4f");  // Red Color
        cout << "\a";
        break;

    case enWinner::Draw:
        system("color 6f"); // Yellow Color
        break;
    }

}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n_________________[" << RoundInfo.RoundNumber << "]_________________\n";
    cout << "Player Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : " << RoundInfo.WinnerName << endl;
    cout << "______________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.GameWinner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice ::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player;

}

stGameResults FillGameResult(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResult;

    GameResult.GameRounds = GameRounds;
    GameResult.PlayerWinTimes = PlayerWinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame( PlayerWinTimes,ComputerWinTimes);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins : " << endl;

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.GameWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.GameWinner);



        if (RoundInfo.GameWinner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.GameWinner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;


        PrintRoundResult(RoundInfo);

    }

    return FillGameResult(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }

    return t;
}

void ShowGameOverScreen()
{

    cout << Tabs(2) << "______________________________________________\n\n";
    cout << Tabs(2) << "          +++ G a m e   O v e r +++ \n";
    cout << Tabs(2) << "______________________________________________\n\n";

} 

void ShowFinelGameResult(stGameResults GameResults)
{
    cout << Tabs(2) << "______________________ [ Game Resulats ]______________________\n\n";
    cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Player Win Times : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "DrawTimes : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "_____________________________________________________________" << endl;
         
    SetWinnerScreenColor(GameResults.GameWinner);

}

void ResetScreen()
{

    system("cls");
    system("color 0f"); // Black Color

}

void StartGame()
{
    char PlayAgain = 'y';


    do
    {

        ResetScreen();
        stGameResults GameResult = PlayGame(HowManyRounds());
        ShowGameOverScreen();
        ShowFinelGameResult(GameResult);


        cout << endl << Tabs(3) << "Do You Want Play Again ? y/n ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

 
int main()
{
    srand((unsigned)time(NULL));


    StartGame();

}
