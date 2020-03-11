#include <iostream>
#include "Deck2.h"

int main() {
    // create a new  deck -its ordered by Card Suit and Rank by default
    Deck d;
    std::cout << "New Deck has " <<  d << "\n\n";

    // randomise the deck
    d.shuffle();
    std::cout << "Shuffled Deck has " <<  d << "\n\n";

    // sort the deck (uses selection sort but you can use any suitable exchange sort)
    d.sort();
    std::cout << "Sorted Deck has " <<  d << "\n\n";

    // deal 5 cards from the deck (leaving a deck of 47 cards)
    std::vector<Card> hand = d.dealHand(5);
    std::cout << "Delt Deck has " <<  d << "\n\n";

    // initialise deck again
    d.initialise();
    std::cout << "Initialised Deck has " <<  d << "\n\n";

}