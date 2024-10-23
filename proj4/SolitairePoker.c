#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//do not remove
//#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


void instructions(){
    printf("\n\n\n\n"
           "\t********************************************************************************\n"
           "\t*                         Welcome to Solitaire Poker                           *\n"
           "\t********************************************************************************\n"
           "\t\n"
           "\tSolitaire Poker is based on Five Card Draw -- a classic poker game\n"
           "\tthat's relatively simple. Here are the basic rules for playing:\n"
           "\t\n"
           "\tObjective: The goal of the game is to make standard five-card poker hands.\n"
           "\t\n"
           "\tSetup: A standard 52-card deck is used. The player is dealt five random cards.\n"
           "\tGameplay: Players can choose to replace up to three cards.\n"
           "\tScoring: Players score points for each hand made.\n"
           "\t\n"
           "\t* 50 Royal Flush: A, K, Q, J, 10, all of the same suit.\n"
           "\t* 45 Straight Flush: Five consecutive cards of the same suit (e.g., 9, 8, 7, 6, 5 of hearts).\n"
           "\t* 40 Four of a Kind: Four cards of the same rank (e.g., four 7s).\n"
           "\t* 32 Full House: Three cards of one rank and two cards of another rank (e.g., three 9s and two 4s).\n"
           "\t* 26 Flush: Five cards of the same suit, not in sequence.\n"
           "\t* 17 Straight: Five consecutive cards of different suits.\n"
           "\t* 11 Three of a Kind: Three cards of the same rank.\n"
           "\t*  7 Two Pair: Two sets of pairs (e.g., two 10s and two 7s).\n"
           "\t*  3 One Pair: Two cards of the same rank.\n"
           "\t*  1 High Card: If none of the above combinations are made.\n"
           "\t\n"
           "\tEnding: The game ends after 10 hands are played.\n"
           "\t********************************************************************************\n\n\n");
}

int private_nextcard(int private_shuffle){
    //static is permanant/persistant across calls
    static int deck[52] = {0};//first time init
    static int top = 0;
    static int counter = 0;
    if (private_shuffle){
        top = 52;//new shuffle
        return 0;
    }
    if (52==top){//first time through
        for (int card = 0; card < 52; card++){
            deck[card]=card;//build the deck
        }
        //now shuffle
        for (int card = 0; card < 52; card++){
            int random = rand()%52;
            int shuffled = deck[card];
            deck[card] = deck[random];
            deck[random]=shuffled;
        }
    }
    if (top) {
        return deck[--top];
    }
    else
    {
        printf("cards exhausted, building new deck\n");
        private_nextcard(1);
        return private_nextcard(0);
    }
}

void seed(int argc, char ** argv){
    srand(time(NULL)); // Initialize random seed
    if (argc>1){
        int i;
        if (1 == sscanf(argv[1],"%d",&i)){
            srand(i);
        }
    }
}




// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);

void printhand(int hand[]) {

    printf("[%d %s-%s %d %s-%s %d %s-%s %d %s-%s %d %s-%s]\n", hand[0], suitNames[getsuit(hand[0])], rankNames[getrank(hand[0])], hand[1], suitNames[getsuit(hand[1])], rankNames[getrank(hand[1])], hand[2], suitNames[getsuit(hand[2])], rankNames[getrank(hand[2])], hand[3], suitNames[getsuit(hand[3])], rankNames[getrank(hand[3])], hand[4], suitNames[getsuit(hand[4])], rankNames[getrank(hand[4])]);

}


int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions

    int score[10] = {0};

    int card[5];

    int hand1[5];
    int hand2[5];
    int hand3[5];
    int hand4[5];
    int hand5[5];
    int hand6[5];
    int hand7[5];
    int hand8[5];
    int hand9[5];
    int hand10[5];

    for (int i = 0; i < 10; i++) {
        shuffle();

        char str[50];

        

        for (int i = 0; i < 5; i++) {
            card[i] = nextcard();
        }

        for (int i = 0; i < 5; i++) {
            printf("%s-%s ", suitNames[getsuit(card[i])], rankNames[getrank(card[i])]);
        }
    
        printf("\n");

        printf("Select up to three cards to replace[1-5] and press enter\n");



        if (fgets(str, sizeof(str), stdin) != NULL) {
            int positionsToReplace[3];
            int numReplacements = 0;
        
            char* token = strtok(str, " ");
            while (token != NULL && numReplacements < 3) {
                positionsToReplace[numReplacements] = atoi(token);
                token = strtok(NULL, " ");
                numReplacements++;
            }
        
            for (int i = 0; i < numReplacements; i++) {
                int position = positionsToReplace[i];
                if (position >= 1 && position <= 5) {
                    card[position - 1] = nextcard();
                } 
            }
        }


        for (int i = 0; i < 5; i++) {
            printf("%s-%s ", suitNames[getsuit(card[i])], rankNames[getrank(card[i])]);
        }

        if (i == 0) {
            for (int i = 0; i < 5; i++) {
                hand1[i] = card[i];
            }
        } else if (i == 1) {
            for (int i = 0; i < 5; i++) {
                hand2[i] = card[i];
            }
        } else if (i == 2) {
            for (int i = 0; i < 5; i++) {
                hand3[i] = card[i];
            }
        } else if (i == 3) {
            for (int i = 0; i < 5; i++) {
                hand4[i] = card[i];
            }
        } else if (i == 4) {
            for (int i = 0; i < 5; i++) {
                hand5[i] = card[i];
            }
        } else if (i == 5) {
            for (int i = 0; i < 5; i++) {
                hand6[i] = card[i];
            }
        } else if (i == 6) {
            for (int i = 0; i < 5; i++) {
                hand7[i] = card[i];
            }
        } else if (i == 7) {
            for (int i = 0; i < 5; i++) {
                hand8[i] = card[i];
            }
        } else if (i == 8) {
            for (int i = 0; i < 5; i++) {
                hand9[i] = card[i];
            }
        } else if (i == 9) {
            for (int i = 0; i < 5; i++) {
                hand10[i] = card[i];
            }
        }

        printf("\n");

        int max = 1;

        if (pair(card) > max) {
            max = pair(card);
        } if (twopair(card) > max) {
            max = twopair(card);
        } if (threekind(card) > max) {
            max = threekind(card);
        } if (straight(card) > max) {
            max = straight(card);
        } if (flush(card) > max) {
            max = flush(card);
        } if (fullhouse(card) > max) {
            max = fullhouse(card);
        } if (fourofkind(card) > max) {
            max = fourofkind(card);
        } if (straightflush(card) > max) {
            max = straightflush(card);
        } if (royalflush(card) > max) {
            max = royalflush(card);
        }

        score[i] = score[i] + max;

        printf("Score: %d\n\n", score[i]);

    }

    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");
    printf("Hand  1: Score:\t%d %s ", score[0], handNames[eval(hand1)]);
    printhand(hand1);
    printf("Hand  2: Score:\t%d %s ", score[1], handNames[eval(hand2)]);
    printhand(hand2);
    printf("Hand  3: Score:\t%d %s ", score[2], handNames[eval(hand3)]);
    printhand(hand3);
    printf("Hand  4: Score:\t%d %s ", score[3], handNames[eval(hand4)]);
    printhand(hand4);
    printf("Hand  5: Score:\t%d %s ", score[4], handNames[eval(hand5)]);
    printhand(hand5);
    printf("Hand  6: Score:\t%d %s ", score[5], handNames[eval(hand6)]);
    printhand(hand6);
    printf("Hand  7: Score:\t%d %s ", score[6], handNames[eval(hand7)]);
    printhand(hand7);
    printf("Hand  8: Score:\t%d %s ", score[7], handNames[eval(hand8)]);
    printhand(hand8);
    printf("Hand  9: Score:\t%d %s ", score[8], handNames[eval(hand9)]);
    printhand(hand9);
    printf("Hand 10: Score:\t%d %s ", score[9], handNames[eval(hand10)]);
    printhand(hand10);

    int total = 0;

    for (int i = 0; i < 10; i++) {
        total = total + score[i];
    }

    printf("==============================================================================\n");
    printf("Total points:\t%d\n", total);
    printf("==============================================================================\n");

    //TODO:
        //WRITE CODE TO PLAY 10 HANDS OF POKER *
            //DEAL 5 CARDS *
            //SHOW DEALT HAND *
            //DRAW UP TO 3 CARDS *
            //SHOW FINAL HAND *
            //EVAL REPPORT AND SAVE INFO FOR LATER *
        //GENERATE SCORESHEET USING INFO
    
   

    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY // DONE

// Function to get the suit of a card
enum suits getsuit(int card){ // DONE
    if (card >= 0 && card <= 12) {
        return CLUB;
    } else if (card > 12 && card <= 25) {
        return DIAMOND;
    } else if (card > 25 && card <= 38) {
        return HEART;
    } else return SPADE;

    return 0;
}

// Function to get the rank of a card
enum ranks getrank(int card){ // DONE
    if (card == 0 || card == 13 || card == 26 || card == 39) {
        return ACE;
    } else if (card == 1 || card == 14 || card == 27 || card == 40) {
        return TWO;
    } else if (card == 2 || card == 15 || card == 28 || card == 41) {
        return THREE;
    } else if (card == 3 || card == 16 || card == 29 || card == 42) {
        return FOUR;
    } else if (card == 4 || card == 17 || card == 30 || card == 43) {
        return FIVE; 
    } else if (card == 5 || card == 18 || card == 31 || card == 44) {
        return SIX;
    } else if (card == 6 || card == 19 || card == 32 || card == 45) {
        return SEVEN;
    } else if (card == 7 || card == 20 || card == 33 || card == 46) {
        return EIGHT;
    } else if (card == 8 || card == 21 || card == 34 || card == 47) {
        return NINE;
    } else if (card == 9 || card == 22 || card == 35 || card == 48) {
        return TEN;
    } else if (card == 10 || card == 23 || card == 36 || card == 49) {
        return JACK;
    } else if (card == 11 || card == 24 || card == 37 || card == 50) {
        return QUEEN;
    } else return KING;

    return 0;
}
// Function to evaluate the poker hand
enum hands eval(int hand[]){ // DONE
    if (royalflush(hand) > 0) {
        return ROYALFLUSH;
    } else if (straightflush(hand) > 0) {
        return STRAIGHTFLUSH;
    } else if (flush(hand) > 0) {
        return FLUSH;
    } else if (fourofkind(hand) > 0) {
        return QUADS;
    } else if (fullhouse(hand) > 0) {
        return FULLHOUSE;
    } else if (straight(hand) > 0) {
        return STRAIGHT;
    } else if (threekind(hand) > 0) {
        return TRIPS;
    } else if (twopair(hand) > 0) {
        return TWOPAIR;
    } else if (pair(hand) > 0) {
        return PAIR;
    } else {
        return HIGHCARD;
    }
}

// Function to check for a royal flush
int royalflush(int hand[]) { // DONE

    int ccount = 0;
    int dcount = 0;
    int scount = 0;
    int hcount = 0;

    int flush = 0;

    for (int i = 0; i < 5; i++) {
        if (hand[i] >= 0 && hand[i] <=12) {
            ccount++;
        } else if (hand[i] > 12 && hand[i] <= 25) {
            dcount++;
        } else if (hand[i] > 25 && hand[i] <= 38) {
            hcount++;
        } else {
            scount++;
        }
    }

    if (ccount == 5 || dcount == 5 || scount == 5 || hcount == 5) {
        flush = 1;
    }

    int rstraight = 0;

    int ranks[5];
    for (int i = 0; i < 5; i++) {
        ranks[i] = getrank(hand[i]);
    }

    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 4 - i; x++) {
            if (ranks[x] > ranks[x + 1]) {
                int temp = ranks[x];
                ranks[x] = ranks[x + 1];
                ranks[x + 1] = temp;
            }
        }
    }
    
    if (ranks[0] == ACE && ranks[1] == TEN && ranks[2] == JACK && ranks[3] == QUEEN && ranks[4] == KING) {
        rstraight = 1;
    }

    if (flush && rstraight) {
        return 50;
    }
    
    return 0;

}

int straightflush(int hand[]) { // DONE

    int ccount = 0;
    int dcount = 0;
    int scount = 0;
    int hcount = 0;

    int flush = 0;

    for (int i = 0; i < 5; i++) {
        if (hand[i] >= 0 && hand[i] <=12) {
            ccount++;
        } else if (hand[i] > 12 && hand[i] <= 25) {
            dcount++;
        } else if (hand[i] > 25 && hand[i] <= 38) {
            hcount++;
        } else {
            scount++;
        }
    }

    if (ccount == 5 || dcount == 5 || scount == 5 || hcount == 5) {
        flush = 1;
    }

    int straight = 0;

    int ranks[5];
    for (int i = 0; i < 5; i++) {
        ranks[i] = getrank(hand[i]);
    }

    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 4 - i; x++) {
            if (ranks[x] > ranks[x + 1]) {
                int temp = ranks[x];
                ranks[x] = ranks[x + 1];
                ranks[x + 1] = temp;
            }
        }
    }
    
    if (ranks[0] == ACE && ranks[1] == TWO && ranks[2] == THREE && ranks[3] == FOUR && ranks[4] == FIVE) {
        straight = 1; 
    }

    int stcount = 0;

    for (int i = 0; i < 4; i++) {
        if (ranks[i] + 1 == ranks[i + 1]) {
            stcount++;

        }
    }

    if ((stcount == 4 && flush) || (straight && flush)) {
        return 45;
    } else return 0;

}


// Function to check for a flush
int flush(int hand[]) { // DONE

    int ccount = 0;
    int dcount = 0;
    int scount = 0;
    int hcount = 0;

    for (int i = 0; i < 5; i++) {
        if (hand[i] >= 0 && hand[i] <=12) {
            ccount++;
        } else if (hand[i] > 12 && hand[i] <= 25) {
            dcount++;
        } else if (hand[i] > 25 && hand[i] <= 38) {
            hcount++;
        } else {
            scount++;
        }
    }

    if (ccount == 5 || dcount == 5 || scount == 5 || hcount == 5) {
        return 26;
    }

    return 0; 
}


// Function to check for a straight
int straight(int hand[]) { //DONE
    int ranks[5];
    for (int i = 0; i < 5; i++) {
        ranks[i] = getrank(hand[i]);
    }

    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 4 - i; x++) {
            if (ranks[x] > ranks[x + 1]) {
                int temp = ranks[x];
                ranks[x] = ranks[x + 1];
                ranks[x + 1] = temp;
            }
        }
    }
    
    if (ranks[0] == ACE && ranks[1] == TWO && ranks[2] == THREE && ranks[3] == FOUR && ranks[4] == FIVE) {
        return 17; 
    }
    if (ranks[0] == ACE && ranks[1] == TEN && ranks[2] == JACK && ranks[3] == QUEEN && ranks[4] == KING) {
        return 17;
    }

    for (int i = 0; i < 4; i++) {
        if (ranks[i] + 1 != ranks[i + 1]) {
            return 0;
        }
    }
    
    return 17;
}


// Function to check for four of a kind
int fourofkind(int hand[]){ // DONE
 
    int rankCounts[13] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }

    for (int i = 0; i < 13; i++) {
        if (rankCounts[i] == 4) {
            return 40;
        }
    }
    return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){ // DONE

    int rankCounts[13] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }

    int threekind = 0;
    int pair = 0;

    for (int r = 0; r < 13; r++) {
        if (rankCounts[r] == 3) {
            threekind = 1;
        } else if (rankCounts[r] == 2) {
            pair = 1;
        }
    }

    if (threekind && pair) {
        return 32;
    }

    return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){ // DONE
    int rankCounts[13] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }

    for (int i = 0; i < 13; i++) {
        if (rankCounts[i] == 3) {
            return 11;
        }
    }

    return 0;
}

// Function to check for two pairs
int twopair(int hand[]){ // DONE
    int rankCounts[13] = {0};
    int pairs = 0;

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }

    for (int i = 0; i < 13; i++) {
        if (rankCounts[i] == 2) {
            pairs++;
        }
    }

    if (pairs == 2) {
        return 7;
    }
    
    return 0;
}

// Function to check for a pair
int pair(int hand[]){ //DONE
    int rankCounts[13] = {0};

    for (int i = 0; i < 5; i++) {
        int rank = getrank(hand[i]);
        rankCounts[rank]++;
    }

    for (int i = 0; i < 13; i++) {
        if (rankCounts[i] == 2) {
            return 3;
        }
    }

    return 0;
}