/**
 *  Name: Deck2.h
 *  Author: amc
 *  Date: 10-03-2020 15:30
 *  Description: Improved version with Suit/Rank enum and conversions embedded within Card
 *               Provides card dealing functionality (mutates the deck)
 */

#include <vector>
#include <stdlib.h> /* srand */
#include <time.h>   /* time */
#include <string>   /* to_string */

class Card {
public:
    // Card Suit and Rank enumerations encapsulated within the Card class
    enum Suit { Spades, Clubs, Hearts, Diamonds };
    enum Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

    // constructor to create a card
    explicit Card(Suit s, Rank r) : suit(s), rank(r) {};

    Suit getSuit() const { return suit; };
    Rank getRank() const { return rank; };

    // return card as a string
    std::string toString() const { return rankToString(rank) + "-" + suitToString(suit); }

    // overloaded card comparison operators 
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

    // static Card methods to return a list of possible suits and ranks
    static std::vector<Suit> getSuits() { 
        return std::vector<Suit>{ Spades, Clubs, Hearts, Diamonds }; 
    } 
    static std::vector<Rank> getRanks() { 
        return std::vector<Rank>{ Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
    }

    // static Card methods to return string value of a rank or suit 
    static std::string suitToString(Suit s) {
        switch (s) {
            case Spades   : return "Spades";
            case Clubs    : return "Clubs";
            case Hearts   : return "Hearts";
            case Diamonds : return "Diamonds";
            default       : return "Unknown";
        }
    }
    static std::string rankToString(Rank r) {
        switch (r) {
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

private:
    Suit suit;
    Rank rank;
};

class Deck {
public:
    // constructor creates a sorted deck of cards based on Face/Value enum ordering
    explicit Deck() : cards() {
        // Initialise the deck of cards
        initialise(); 
    }

    // clear any existing cards in deck and initialise with a full set of cards in Suit/Rank order
    void initialise() {
        cards.clear();
        for (auto s : Card::getSuits()) {
            for (auto r : Card::getRanks()) {
                cards.push_back(Card(s, r)); // add new card to deck
            }
        } 
    }
    // return a copy of the cards in the deck
    std::vector<Card> getCards() const { return cards; }

    // check how many cards are left in the deck
    int availableCards() { return getCards().size(); }
    
    // deal a hand of cards out of the deck (remove cards from deck)
    std::vector<Card> dealHand(int count) 
    { 
        shuffle(); // first shuffle the deck

        std::vector<Card> hand; // vector to hold hand being default
        // create hand of required size up to available cards
        for(int i=0; i<count && cards.size() > 0; i++) {
            hand.push_back(cards[0]);   // copy top card from deck into hand
            cards.erase(cards.begin()); // remove top card from deck
        }
        return hand; 
    }

    // shuffle the deck of cards
    void shuffle() {
        srand (time(NULL)); // seed random number generator
        /* generate number between 0 and 51 */
        for (int i = 0; i < cards.size(); i++) {
            int p = rand() % cards.size();
            Card t = cards[i];
            cards[i] = cards[p];
            cards[p] = t;
        }
    }

    // sort cards (selection sort - exchange sort)
    void sort() {
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

    // return deck as a string
    std::string toString() const {
        std::string s = std::to_string(cards.size()) + " Cards { ";
        for(int i=0; i<cards.size(); i++) {
            s += cards[i].toString();
            s += i < cards.size()-1 ? ", " : "";
       }
       return s = s + " }";
    }

private:
    std::vector<Card> cards;    
};

// overloaded stream operators use public Card/Deck print methods
// thus do not need access to private Card/Deck implementation
std::ostream& operator <<(std::ostream& output, const Card& c) {
    output << c.toString();
    return output;  // for multiple << operators.
}
std::ostream& operator <<(std::ostream& output, const Deck& d) {
    output << d.toString();
    return output;  // for multiple << operators.
}
