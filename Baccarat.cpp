#include<iostream>
#include<vector>
#include<ctime>
#include<string>

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

    int getLastcardvalue()const{
        return playerDeck[playerDeck.size()].getFacevalue();
    }

    int getNumcards()const{
        return num_cards;
    }

};

class Player : public Participant{
    public:
    
    bool isNextturnplayer(const int b_dval) const{
        /* If neither the player nor the banker is dealt 
        a total of 8 or 9 in the first two cards (known as
        a "natural"), the tableau is consulted, first for 
        the player's rules, then the banker's.
        If the player has an initial total of 5 or less, 
        they draw a third card. If the player has an initial
        total of 6 or 7, they stand. Of course this doesn't 
        happen if the bankhas a "natural". In that case, the 
        player stands. */
        int p_dval = getDeckvalue();
        if (p_dval < 6 && b_dval < 8){  
            return true;
        }
        else{return false;}
    }
};

class Banker : public Participant
{
    public:

    bool isNextturnbanker(const Player player_) const{
        int this_dval = getDeckvalue();
        if(player_.getNumcards() < 3){
            if(this_dval < 6 && player_.getDeckvalue() < 8){
                return 1;
            }
            else{return 0;}
        }
        // Conditions from different source:
        // b1: If Player drew a 2 or 3, Banker draws with 0-4 and stands with 5-7.
        // b2: If Player drew a 4 or 5, Banker draws with 0-5 and stands with 6-7.
        // b3: If Player drew a 6 or 7, Banker draws with 0-6 and stands with 7.
        // b4: If Player drew an 8, Banker draws with 0-2 and stands with 3-7.
        // b5: If Player drew an ace, 9, 10, or face-card, the Banker draws with 0-3 and stands with 4-7.
        // else{
        //     bool b1, b2, b3, b4, b5;
        //     int player_3rdcard = player_.getLastcardvalue();
        //     b1 = (player_3rdcard == 2 || player_3rdcard == 3) && this_dval < 5;
        //     b2 = (player_3rdcard == 4 || player_3rdcard == 5) && this_dval < 6;
        //     b3 = (player_3rdcard == 6 || player_3rdcard == 7) && this_dval < 7;
        //     b4 = player_3rdcard == 8 && this_dval < 3;
        //     b5 = (player_3rdcard == 1 || player_3rdcard > 8) && this_dval < 4;
           
        //     if(b1 || b2 || b3 || b4 || b5){
        //         return 1;
        //     }

        // Conditions how I understood them from wikipedia:
        // If the banker total is 2 or less, they draw a third card, regardless of what the player's third card is.
        // If the banker total is 3, they draw a third card unless the player's third card is an 8.
        // If the banker total is 5, they draw a third card if the player's third card is 4, 5, 6, or 7.
        // If the banker total is 4, they draw a third card if the player's third card is 2, 3, 4, 5, 6, 7.
        // If the banker total is 6, they draw a third card if the player's third card is a 6 or 7.
        else{
            bool b1, b2, b3, b4, b5;
            int player_3rdcard = player_.getLastcardvalue();
            b1 = this_dval<3;
            b2 = this_dval==3 && player_3rdcard != 8;
            b3 = this_dval == 4 && 1 < player_3rdcard && player_3rdcard < 8;
            b4 = this_dval == 5 && 3 < player_3rdcard && player_3rdcard < 8;
            b5 = this_dval == 6 && 5 < player_3rdcard && player_3rdcard < 8;
            if(b1 || b2 || b3 || b4 || b5){
                return 1;
            }
            // If the banker total is 7, they stand.
            else{
                return 0;
            }
        }
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

int getFinalscore(Player p__, Banker b__){
    int p__dval = p__.getDeckvalue();
    int b_dval = b__.getDeckvalue();
    if(p__dval > b_dval){
        return 0; // player win
    }
    if(p__dval == b_dval){
        return 2; // banker win
    }
    if (p__dval < b_dval){
        return 1; // tie
    }
    else{return -1;} // This line avoids the compiler to think it might be a void.
}

int main(){
    double player_win, banker_win, tie = 0; // counters
    int num_games = 1;
    // RNG for shuffeling cards.
    // srand(time(0)); 
    int time_now = time(0);
    for(int i_game = 0; i_game < num_games; i_game++){
        srand(i_game + time_now);
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
        shuffle();

        Player p;
        Banker b;
        
        // Shuffled cards are given to player and banker following the right order.
        // From wikipedia: The dealer burns the first card face up and then based on its respective
        // numerical value, with aces worth 1 and face cards worth 10, the dealer burns that many cards face down.
        
        int num_burns = deck[0].firstBurn() + 1;
        // // std::cout<<"Burned card:"<<std::endl;
        // deck[0].printCard();
        p.addCard(deck[num_burns++]);
        b.addCard(deck[num_burns++]);
        p.addCard(deck[num_burns++]);
        b.addCard(deck[num_burns++]);
        // std::cout<<"\n\nPlayer cards:"<<std::endl;
        // p.printDeck();
        // std::cout<<"\nBanker cards:"<<std::endl;
        // b.printDeck();
        // std::cout<<std::endl;
        // std::cout<<"\nInitial player deck value: "<<p.getDeckvalue()<<std::endl;
        // std::cout<<"Initial banker deck value: "<<b.getDeckvalue()<<std::endl;

        // std::cout<<p.isNextturnplayer(b.getDeckvalue())<<std::endl;

        // Conditions for participants to pick a third card:
        if(p.isNextturnplayer(b.getDeckvalue())){
            p.addCard(deck[num_burns++]);
        }
        if(b.isNextturnbanker(p)){
            b.addCard(deck[num_burns++]);
        }

        // std::cout<<"Final player deck value: "<<p.getDeckvalue()<<std::endl;
        // std::cout<<"Final banker deck value: "<<b.getDeckvalue()<<std::endl;
        printFinalscore(p, b);
        // if(getFinlalscore(p, b) == 0){player_win += 1;}
        // if(getFinalscore(p, b) == 1){banker_win += 1;}
        // if(getFinascore(p, b) == 2){tie += 1;}
        // std::cout << getFinalscore(p, b)<<std::endl;
    }
    std::cout<<"Banker: "<<banker_win/(player_win + banker_win + tie) * 100.0<<std::endl;
    std::cout<<"Player: "<<player_win/(player_win + banker_win + tie) * 100.0<<std::endl;
    std::cout<<"Tie:    "<<tie/(player_win + banker_win + tie) * 100.0<<std::endl;
    return 0;
}