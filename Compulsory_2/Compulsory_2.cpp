#include <iostream>
#include <string>
#include <vector>
#include <ctime>

struct Player { //struct is used to store, change and evaluate variables for each player
    int money = 100;
    std::string name;
    std::string hand;
    std::vector<char> vhand;
    int vCount = 0;
    int score = 0;
}Dealer, Player;

std::string drawACard(bool pTurn, std::string cards[], int cardsSize); //function is used to determine which card is drawn
int getRandomNumber(int min, int max); //function is used to get a randomised number


int main()
{
    //setting random generation in order below
    std::srand(std::time(nullptr));
    getRandomNumber(1, 100);

    Dealer.name = "Deler";
    std::string cards[13]{ "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
    bool pTurn = true;
    bool endGame = false;

    do {
        if (pTurn) {
            bool turnEnd = false;
            do {
                std::cout << "It is your turn " << Player.name << "Current cards: " << Player.hand << "Current score: " << Player.score <<"\nType d to draw, s to stand or e to end the application";

            } while (!turnEnd);
        }
        else {
            return 0;
        }
    } while (!endGame);
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