#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;


class Card{
    public:
        string face;
        string symbol;

    void printCard(){
        cout<<face<<" of "<<symbol;
    }
};

// class Participant as parent class, Player and Banker are daughter classes from this one. -> Polymorphism.
class Player{
    public:
        Card playerDeck[2];
    
    void showCards(){
        cout<<"hello";
    }
    void printdeck(){
        int k;
        for(k=0;k<num_cards;k++){
            deck[k].printCard();
            cout<<"\n";
        }
    }
};

const int num_decks = 8;
const int num_cards = num_decks * 52;
Card deck[num_cards]; // 52 will become 416 since we'll be using 8 decks
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
void printdeck(){
    int k;
    for(k=0;k<num_cards;k++){
        deck[k].printCard();
        cout<<"\n";
    }
}

int main(){
    // RNG for shuffeling cards.
    srand(time(0)); 
    string face[]{"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    // cout<<face[2];
    string symbol[]{"Hearts", "Diamonds", "Spades", "Clubs"};


    // Deck initialization:
    int i, j, k, l;
    l=0;
    for(i=0;i<4;i++){
        for(j=0;j<13;j++){
            for(k=0;k<num_decks;k++){
                deck[l].face=face[j];
                deck[l].symbol=symbol[i];
                l++;
            }
        }
    }
    // cout<<"before"<<endl;
    // printdeck();
    // shuffle();
    // cout<<"after"<<endl;
    // printdeck();

    Player p;
    p.showCards();
    return 0;
}