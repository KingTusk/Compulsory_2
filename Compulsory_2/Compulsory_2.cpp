#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>

struct Player { //struct is used to store, change and evaluate variables for each player
    int money = 100;
    std::string name;
    std::string hand;
    int score = 0;
}Dealer, Player;

std::string drawACard(bool pTurn, std::string cards[], int cardsSize); //function is used to determine which card is drawn
int getRandomNumber(int min, int max); //function is used to get a randomised number
bool checkForError();
int getIntOfCard(bool pturn, std::string card);
void printHands(bool pturn);


int main()
{
    //setting random generation in order below
    std::srand(std::time(nullptr));
    getRandomNumber(1, 100);

    Dealer.name = "Dealer";
    std::string cards[13]{ "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
    bool pTurn = true;
    bool endGame = false;
    int bet = 0;

    std::cout << "Please enter your name: ";

    std::getline(std::cin, Player.name);
    std::cin.clear();
    std::cin.sync();

    do { //beggining of game

        if (pTurn) { //Players turn
            bool turnEnd = false;
            bool okValue = false;
            bool error = false;

            do { // loops until we get valid input
                bet = 0;
                okValue = false;
                error = false;
                std::cout << "You have " << Player.money << ". The house has " << Dealer.money <<". How much are you betting this round?";
                std::cin >> bet;
                error = checkForError();
                if (bet <= Player.money && bet <= Dealer.money) {
                    okValue = true;
                }
                else {
                    std::cout << "You can't bet more money than you, or the house, has. Try again";
                }
                if (error) {
                    std::cout << "invalid input, only use numbers.";
                }
            } while (!error && okValue);

            do {
                system("cls");
                int choice = 'n';
                std::string carddrawn = "n";
                int carddrawnValue = 0;

                printHands(pTurn);

                choice = _getch();
                std::cout << choice;
                if (char(choice) == 'd' || char(choice) == 'D') {
                    carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
                    carddrawnValue = getIntOfCard(pTurn, carddrawn);
                    Player.score += carddrawnValue;
                    Player.hand += " " + carddrawn;
                    std::cout << "You drew a " << carddrawn << "It has the value " << carddrawnValue;
                }
                else if (char(choice) == 's' || char(choice) == 'S') {
                    std::cout << "You choose to stand with a total value of " << Player.score << " On your hand";
                    turnEnd = true;
                }
                else if (char(choice) == 'e' || char(choice) == 'E') {
                    return 0;
                }
                else {
                    std::cout << "Invalid input, you can only use d, s or e";
                }
            } while (!turnEnd);
        }
        else { //Dealers turn
            bool turnEnd = false;
            do {
                system("cls");
                std::string carddrawn = "n";
                int carddrawnValue = 0;
                if (Dealer.score < Player.score) {
                    carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
                    carddrawnValue = getIntOfCard(pTurn, carddrawn);
                    Dealer.score += carddrawnValue;
                    Dealer.hand += " " + carddrawn;
                    std::cout << "The dealer drew a " << carddrawn;
                }
                else {
                    std::cout << "The dealer stands with a score of " << Dealer.score;
                    turnEnd = true;
                }
                Sleep(1000);
            } while (!turnEnd);
        }
    } while (!endGame);
}

void printHands(bool pturn) {
    if (pturn) {
        std::cout << Player.name << "Hand: " << Player.hand << " " << "Points: " << Player.score << std::endl;
    }
    else {
        std::cout << "Dealer:\n" << "Hand: " << Dealer.hand << " " << "Points: " << Dealer.score << std::endl;
    }
}

int getIntOfCard(bool pturn, std::string card) {
    if (card == "A") {
        if(pturn){
            bool done = false;
            do {
                char choice = '0';
                std::cout << "You have drawn an ace!, choose whether to give it the value 1 (1) or 11 (2): ";
                choice = _getch();
                switch (choice) {
                case '1':
                    done = true;
                    return 1;
                case '2':
                    done = true;
                    return 11;
                default:
                    std::cout << "Invalid input, you can only choose 1 for the value 1, or 2 for the value 11";
                    break;
                }
            } while (!done);
        }
        else { //Delear draws ace
            if ((Dealer.score + 11) == 21 || ((Dealer.score + 11) >= Player.score && (Dealer.score + 11) < 22)) {
                return 11;
            }
            else if ((Dealer.score + 1) == 21 || ((Dealer.score + 1) >= Player.score && (Dealer.score +1)< 22)) {
                return 1;
            }
            else if ((Dealer.score + 11) <= 14) {
                return 11;
            }
            else {
                return 1;
            }
        }
    }
    else if (card == "2") {
        return 2;
    }
    else if (card == "3") {
        return 3;
    }
    else if (card == "4") {
        return 4;
    }
    else if (card == "5") {
        return 5;
    }
    else if (card == "6") {
        return 6;
    }
    else if (card == "7") {
        return 7;
    }
    else if (card == "8") {
        return 8;
    }
    else if (card == "9") {
        return 9;
    }
    else if (card == "10" || card == "K" || card == "J" || card == "Q") {
        return 10;
    }
    else {
        std::cout << "\n There was an unexpected error, terminating program";
        exit(0);
    }
}

std::string drawACard(bool pTurn, std::string cards[], int cardsSize){
    int cardDrawn = getRandomNumber(0, cardsSize-1);
    return cards[cardDrawn];
}

int getRandomNumber(int min, int max) //code is from learncpp.com, it produces a random number between min and max
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

bool checkForError() {//Checks whether if the input was an invalid value and fixes potential issues caused by this
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return true;
    }
    else {
        return false;
    }
}