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
bool checkForError();//checks for, and fixes,  input errors concerning std::cin
int getIntOfCard(bool pturn, std::string card); //gets the integer value of any card drawn, to keep track of score
void printHands(std::string lastMove); //prints the current hands of the dealer and the player


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

        Player.score = 0;
        Dealer.score = 0;

        system("cls");
        bool turnEnd = false;
        bool okValue = false;
        bool error = false;
        pTurn = true;
        std::string lastMove = " ";
        int choice = 'n';
        std::string carddrawn = "n";
        int carddrawnValue = 0;

        //below code draws 1 card for the Player and the Dealer
        carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
        carddrawnValue = getIntOfCard(pTurn, carddrawn);
        Player.score += carddrawnValue;
        Player.hand += " " + carddrawn;
        lastMove = "You drew a " + carddrawn + ". ";
        pTurn = false;
        carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
        carddrawnValue = getIntOfCard(pTurn, carddrawn);
        Dealer.score += carddrawnValue;
        Dealer.hand += " " + carddrawn;
        lastMove += "The dealer drew a " + carddrawn + ".";
        pTurn = true;

        printHands(lastMove);

        do { // loops until we get valid input
            bet = 0;
            okValue = false;
            error = false;
            std::cout << "You have " << Player.money << " dollars. The house has " << Dealer.money << " dollars. How much are you betting this round?" << std::endl;
            std::cin >> bet;
            error = checkForError();
            if (bet <= Player.money && bet <= Dealer.money && bet >= 10) {
                okValue = true;
            }
            else if (bet < 0) {
                std::cout << "You cannot bet a negative sum or 0." << std::endl;
            }
            else if (bet < 10) {
                std::cout << "You cannot bet less than 10" << std::endl;
            }
            else if (bet > Player.money || bet > Dealer.money) {
                std::cout << "You cannot bet more money than you, or the house, has. Try again" << std::endl;
            }
            if (error) {
                std::cout << "invalid input, only use numbers." << std::endl;
            }
        } while (error || !okValue);

        do {
            //Players turn begins here, loop repeats if users input is invalid
            system("cls");
            int choice = 'n';
            std::string carddrawn = "n";
            int carddrawnValue = 0;

            printHands(lastMove);
            std::cout << "Choose whether to hit(h), stand(s)." << std::endl; //Makes player choose an action to do
            choice = _getch();
            std::cout << choice;

            if (char(choice) == 'h' || char(choice) == 'H') {
                carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
                carddrawnValue = getIntOfCard(pTurn, carddrawn);
                Player.score += carddrawnValue;
                Player.hand += " " + carddrawn;
                lastMove = "You drew a " + carddrawn + " It has the value " + std::to_string(carddrawnValue);
                if (Player.score > 21) {
                    std::cout << "You overdrew! your total score is " << Player.score << " which is higer than 21." << std::endl;
                    turnEnd = true;
                }
            }
            else if (char(choice) == 's' || char(choice) == 'S') {
                std::cout << "You choose to stand with a total value of " << Player.score << " on your hand" << std::endl;
                turnEnd = true;
            }
            else {
                std::cout << "Invalid input, you can only use h(to draw a card) or s(t keep you cards)" << std::endl;
                turnEnd = false;
            }
        } while (!turnEnd);
        pTurn = false;

        //Dealers turn begins here
        do {
            system("cls");
            printHands(lastMove);
            Sleep(2000);
            turnEnd = false;;
            std::string carddrawn = "n";
            int carddrawnValue = 0;
            if (Dealer.score < Player.score && Player.score < 21) {
                carddrawn = drawACard(pTurn, cards, sizeof(cards) / sizeof(cards[0]));
                carddrawnValue = getIntOfCard(pTurn, carddrawn);
                Dealer.score += carddrawnValue;
                Dealer.hand += " " + carddrawn;
                lastMove = "The dealer drew a " + carddrawn;
            }
            else if (Dealer.score > 21) {
                std::cout << "The Dealer drew too much!" << std::endl;
                turnEnd = true;
            }
            else {
                std::cout << "The dealer stands with a score of " << Dealer.score << std::endl;
                turnEnd = true;
            }
        } while (!turnEnd);
        //below if statements check for win conditions, or a draw
        if (Player.score > 21) {
            std::cout << "Your score is higher than 21, you lose this round and " << bet << " dollars" << std::endl;
            Player.money -= bet;
            Dealer.money += bet;
        }
        else if (Dealer.score > 21) {
            std::cout << "The dealer drew more than 21, you win this round and " << bet << " dollars" << std::endl;
            Player.money += bet;
            Dealer.money -= bet;
        }
        else if (Dealer.score > Player.score) {
            std::cout << "The dealer has higher score than you: " << Dealer.score << " to your " << Player.score << ". You lose " << bet << " dollars" << std::endl;
            Player.money -= bet;
            Dealer.money += bet;
        }
        else if (Player.score > Dealer.score) {
            std::cout << "You have a higher score than the dealer: " << Player.score << "to his " << Dealer.score << ". You win " << bet << " dollars" << std::endl;
            Player.money += bet;
            Dealer.money -= bet;
        }
        else {
            std::cout << "The game is a draw and bobody loses anything" << std::endl;
        }
        if (Dealer.money > 10 && Player.money > 10) {
            char choice = 'y';
            do {//runs until valid input is given
                std::cout << "You have " << Player.money << " wanna keep going?(y) Or stop gambling?(n)" << std::endl; //gives user the option to play again
                choice = _getch();
            } while (checkForError() || (choice != 'n' && choice != 'y' && choice != 'Y' && choice != 'N'));
            switch (choice) {
                //intentional fall-through behaviour
            case 'y':
            case 'Y':
                endGame = false;
                break;
            case 'n':
            case 'N':
                endGame = true;
                break;
            default:
                endGame = false;
            }
        }
        //stops game if either side can't play anymore
        else if (Dealer.money < 10) {
            std::cout << "The dealer does not have enough money to play more." << std::endl;
            endGame = true;
        }
        else if (Player.money < 10) {
            std::cout << "You don't have enough money to play more." << std::endl;
            endGame = true;
        }
        
    } while (!endGame);

    //End result is declared here
    if (Player.money > Dealer.money) {
        std::cout << "Congratualations, you won " << Player.money - Dealer.money << " money" << std::endl;
    }
    else if (Dealer.money > Player.money) {
        std::cout << "Too bad, you lost " << Dealer.money - Player.money << " money" << std::endl;
    }
    else {
        std::cout << "You split even and did not lose or win any moeny" <<std::endl;
    }
}

void printHands(std::string lastMove) { //I use several lines here too make the code look better
    std::cout << lastMove << std::endl << Player.name << "'s hand:" << Player.hand << " " << "Points: " << Player.score << std::endl;
    std::cout << Dealer.name << "'s hand:" << Dealer.hand << " " << "Points: " << Dealer.score << std::endl;
}

int getIntOfCard(bool pturn, std::string card) {
    if (card == "A") {
        if(pturn){
            bool done = false;
            do {
                char choice = '0';
                std::cout << "You have drawn an ace!, choose whether to give it the value 1 (1) or 11 (2): " << std::endl;
                choice = _getch();
                switch (choice) {
                case '1':
                    done = true;
                    return 1;
                case '2':
                    done = true;
                    return 11;
                default:
                    std::cout << "Invalid input, you can only choose 1 for the value 1, or 2 for the value 11" << std::endl;
                    done = false;
                }
            } while (!done);
        }
        else { //When dealer draws an ace, he chooses it's value based on whether or not the total value would exceed 14, or hit 21
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
        std::cout << "\n There was an unexpected error";
        return 0;
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