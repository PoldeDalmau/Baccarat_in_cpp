# Baccarat_in_cpp
 A small script that runs one Baccarat game.

## Game description

 Two players are involved: the player and the banker. They each receive two cards from the top of eight decks shuffled together.
 Depending on the outcome, the player can take another card (see the table for the specific rules). Following this, the banker takes
 a third card under some different conditions. The player and the banker add up their respective cards, where the ace and face cards
 are worth one and zero respectively. Sums larger than 10 are subtracted 10. The winner is the player with a sum closest to 9. If
 both players have the same sum, it is a tie.  

 ![image](https://user-images.githubusercontent.com/73791685/178543025-06d55762-c2f1-4795-aa8f-0b893da5b62f.png)
 
 A detailed description of the rules can be found under:  
 https://en.wikipedia.org/wiki/Baccarat  

 Expected win distribution(Google):  
 Banker: 45.8%  
 Player: 44.6%  
 Tie: 9.6%

 Measured win distribution:
 Banker: 43.7692  
 Player: 45.3538  
 Tie: 10.877  
## How to use this code:
 Running this C++ code gives the outcome of a Baccarat game using a standard
 random number generation library from C++. The outcome is printed in the
 following format:

PHand - BHand - Outcome  
7,8,J - 3,3 - BANKER
