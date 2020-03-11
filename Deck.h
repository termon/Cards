/**
 *  Name: Deck.h
 *  Author: amc
 *  Date: 10-03-2020 14:00
 *  
 */

#include <vector>
#include <stdlib.h> /* srand */
#include <time.h>   /* time */

enum Suit { Spades, Clubs, Hearts, Diamonds };
enum Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card {
public:
    explicit Card(Suit s, Rank r) : suit(s), rank(r) {};

    Suit getSuit() const { return suit; };
    Rank getRank() const { return rank; };

    // public method to print card to specified stream (defaults to cout)
    // converts enum values to string representations
    void print(std::ostream & os = std::cout) const {
        os << getRankAsString() << "-" << getSuitAsString(); 
    };

    // overloaded comparison operators
    // this is the key ingredient to allow any sort algorithm to be used
    // only < is needed for sort and > is provided for completeness
    bool operator<(const Card & right) const { 
       if (getSuit() < right.getSuit())
            return true;
        else if (getSuit() == right.getSuit() && getRank() < right.getRank())
            return true;
        else
            return false; 
    }
    bool operator>(const Card & right) const { 
       if (getSuit() > right.getSuit())
            return true;
        else if (getSuit() == right.getSuit() && getRank() > right.getRank())
            return true;
        else
            return false; 
    }

private:
    Suit suit;
    Rank rank;

    // private function to convert Card Suit to string
    std::string getSuitAsString() const {
        switch (getSuit()) {
            case Spades   : return "Spades";
            case Clubs    : return "Clubs";
            case Hearts   : return "Hearts";
            case Diamonds : return "Diamonds";
            default       : return "Unknown";
        }
    }
    // private function to convert Card Rank to string
    std::string getRankAsString() const {
        switch (getRank()) {
            case Ace    : return "Ace";           
            case Two    : return "Two";
            case Three  : return "Three";
            case Four   : return "Four";
            case Five   : return "Five";
            case Six    : return "Six";
            case Seven  : return "Seven";
            case Eight  : return "Eight";
            case Nine   : return "Nine";
            case Ten    : return "Ten";
            case Jack   : return "Jack";
            case Queen  : return "Queen";
            case King   : return "King";
            default     : return "Unknown";
        }
    }
};

class Deck {
public:
    // constructor creates a sorted deck of cards based on Face/Value enum ordering
    explicit Deck() : cards() {
        // create lists of Faces and Values from enums to make it easy to iterate over them and create a deck
        std::initializer_list<Suit> suits = { Spades, Clubs, Hearts, Diamonds }; 
        std::initializer_list<Rank> ranks = { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
        for (Suit s : suits) {
            for (Rank r : ranks) {
                cards.push_back(Card(s, r)); // add new card to deck
            }
        } 
    }

    std::vector<Card> getCards() const { return cards; }

    // shuffle the deck of cards
    void shuffle() {
        srand (time(NULL)); // seed random number generator
        /* generate number between 0 and 51 */
        for (int i = 0; i < 52; i++) {
            int p = rand() % 52;
            Card t = cards[i];
            cards[i] = cards[p];
            cards[p] = t;
        }
    }

    // sort cards (selection sort - exchange sort)
    void sort()
    {
        int min;
        // loop over each card
        for (int marker = 0; marker < cards.size() - 1; marker++) {
            min = marker;
            // find smallest card from current position to end of deck
            for (int i = marker + 1; i < cards.size(); i++) {
                if (cards[i] < cards[min]) {
                    min = i; // new smallest card found
                }
            }
            // swap smallest card and card at marker
            Card t = cards[marker];
            cards[marker] = cards[min];
            cards[min] = t;
        }
    }

    // utility function to verify if cards are ordered
    bool areOrdered() const {
        for (int i = 1; i < cards.size(); i++) {
            if (cards[i-1] > cards[i]) {                   
                return false;
            }
        }
        return true;
    }

    // print Deck on specified stream - calls card print method   
    void print(std::ostream & os = std::cout) const {      
       os << "[ ";   
       for(int i=0; i<cards.size(); i++) {
           cards[i].print(os);
           os << " ";
       }
       os << "]";
    }

private:
    std::vector<Card> cards;    
};

// overloaded stream operators use public Card/Deck print methods
// thus do not need access to private Card/Deck implementation
std::ostream& operator <<(std::ostream& output, const Card& c) {
    c.print(output);
    return output;  // for multiple << operators.
}
std::ostream& operator <<(std::ostream& output, const Deck& d) {
    d.print(output);
    return output;  // for multiple << operators.
}
