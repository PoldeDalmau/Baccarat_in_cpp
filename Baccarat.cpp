#include<iostream>
#include<vector>
#include<ctime>
#include<string>

// class Player;
// class Banker;

class Card{

    private:

        int face;
        std::string symbol;

    public:

    void setCard(const int f, const std::string s){
        face = f;
        symbol = s;
    }
    int getFacevalue()const{
        return face;
    }

    // First card must be burned. Its value is returned.
    int firstBurn()const{
        if(face>10){return 10;}
        else{return face;}
    }

    void printCard(){
        std::string faces[]{"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
        std::cout<<faces[face-1]<<" of "<<symbol;
    }
};

class Participant{

    private:

    std::vector<Card> playerDeck;
    int num_cards = 0;

    public:

    void addCard(const Card c){
        playerDeck.push_back(c);
        num_cards ++;
    }
    void printDeck(){
        for(int i = 0; i < playerDeck.size(); i++){
            playerDeck[i].printCard();
            std::cout<<"\n";
        }
    }

    std::string getDeckstring()const{
        std::string faces[]{"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
        std::string s;
        for(int i = 0; i < playerDeck.size(); i++){
            if(i != 0){s += ",";}
            s += faces[playerDeck[i].getFacevalue() - 1]; // the -1 is important. Example: Ace has value 1, but is at position 0 of the vector.
        }
        return s;
    }

    int getDeckvalue()const{ 
        int dval = 0;
        for(auto card : playerDeck){
            int face_val = card.getFacevalue();
            if(face_val < 10){
                dval += face_val;
            }
        }
        return dval % 10;
    }

    int getNumcards()const{
        return num_cards;
    }

    bool isNextturnplayer(const int b_dval) const{
        int p_dval = getDeckvalue();
        if (p_dval < 6 && b_dval < 8){ // excludes the "natural" and only returns true if 
            return true;
        }
        else{return false;}
    }
};

class Player : public Participant{};

class Banker : public Participant
{
    public:

    bool isNextturnbanker(const Player player_) const{
        if(player_.getNumcards() < 3){
            return isNextturnplayer(player_.getDeckvalue());
        }
        else{return 0;}
    }
};

const int num_decks = 8;
const int num_cards = num_decks * 52;
Card deck[num_cards];

void shuffle(){
    // switches cards at positions n and m by storing card n in a temporary card temp.    
    Card temp;
    int n, m;
    for(n=0;n<num_cards;n++){
        m = rand() % num_cards;
        temp = deck[n];
        deck[n] = deck[m];
        deck[m] = temp;
    }
}

void printFinalscore(Player p_, Banker b_){
    std::cout<<"PHand - BHand - Outcome"<<std::endl;
    std::string outcome;
    std::string all_cards;
    int p_dval = p_.getDeckvalue();
    int b_dval = b_.getDeckvalue();
    all_cards = p_.getDeckstring() + " - " + b_.getDeckstring() + " - ";
    if(p_dval > b_dval){
        outcome = "PLAYER";
    }
    if(p_dval == b_dval){
        outcome = "TIE";
    }
    if (p_dval < b_dval){
        outcome = "BANKER";
    }
    std::cout<< all_cards + outcome<<std::endl;
}

int main(){
    // RNG for shuffeling cards.
    srand(time(0)); 
    int face_number[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::string symbol[]{"Hearts", "Diamonds", "Spades", "Clubs"};

    // Shuffled deck initialization:
    int i, j, k, l;
    l=0;
    for(i=0;i<4;i++){
        for(j=0;j<13;j++){
            for(k=0;k<num_decks;k++){
                deck[l].setCard(face_number[j], symbol[i]); // This line and the one below into one line with the getmethod!!!
                l++;
            }
        }
    }
    // std::cout<<"before"<<endl;
    // printDeck();
    shuffle();
    // std::cout<<"after"<<endl;
    // printDeck();

    Player p;
    Banker b;
    
    // Shuffled cards are given to player and banker following the right order.
    // From wikipedia: The dealer burns the first card face up and then based on its respective
    // numerical value, with aces worth 1 and face cards worth 10, the dealer burns that many cards face down.
    
    int num_burns = deck[0].firstBurn();
    // // std::cout<<"Burned card:"<<std::endl;
    // deck[0].printCard();
    p.addCard(deck[num_burns]);
    b.addCard(deck[num_burns++]);
    p.addCard(deck[num_burns++]);
    b.addCard(deck[num_burns++]);
    // std::cout<<"\n\nPlayer cards:"<<std::endl;
    // p.printDeck();
    // std::cout<<"\nBanker cards:"<<std::endl;
    // b.printDeck();
    // std::cout<<std::endl;
    std::cout<<"\nInitial player deck value: "<<p.getDeckvalue()<<std::endl;
    std::cout<<"Initial banker deck value: "<<b.getDeckvalue()<<std::endl;

    std::cout<<p.isNextturnplayer(b.getDeckvalue())<<std::endl;

    if(p.isNextturnplayer(b.getDeckvalue())){p.addCard(deck[num_burns++]);}
    if(b.isNextturnbanker(p)){b.addCard(deck[num_burns++]);}

    std::cout<<"\nFinal player deck value: "<<p.getDeckvalue()<<std::endl;
    std::cout<<"Final banker deck value: "<<b.getDeckvalue()<<std::endl;
    printFinalscore(p, b);
    return 0;
}