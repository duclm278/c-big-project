#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    // rank_value will be used for sorting
    int rank_value;

    // suit_value will be used for sorting
    int suit_value;

    // covert rank_value to string
    char rank[3];

    // [s = spades], [h = hearts], [c = clubs], [d = diamonds]
    char suit;
}
card;

card deal_card(int cards[][4], char suits[]);
void sort_hand(card players[][13]);
void print_hand(card players[][13]);

int main(void)
{
    // All the suits
    char suits[4] = {'s', 'h', 'c', 'd'};

    // 2D array to store each player's cards
    card players[4][13];

    // Set all cards to 0;
    int cards[13][4];
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cards[i][j] = 0;
        }
    }

    // Deal cards
    srand(time(NULL));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            players[i][j] = deal_card(cards, suits);
        }
    }

    // Sort hand
    sort_hand(players);

    // Prind hand
    print_hand(players);

    return 0;
}

card deal_card(int cards[][4], char suits[])
{
    card dealt_card;
    int x = rand() % 52;

    // dealt == 1 <=> successful
    int dealt = 0;

    // If x reaches the end of the array, assign x = 0
    while (dealt == 0)
    {
        while (x <= 52)
        {
            // If the card hasn't been dealt, update the rank_value to 1
            if (cards[x / 4][x % 4] == 0)
            {
                dealt_card.rank_value = x / 4;
                switch(x / 4)
                {
                case 10:
                    strcpy(dealt_card.rank, "J");
                    break;
                case 11:
                    strcpy(dealt_card.rank, "Q");
                    break;
                case 12:
                    strcpy(dealt_card.rank, "K");
                    break;
                case 0:
                    strcpy(dealt_card.rank, "A");
                    break;
                default:
                    sprintf(dealt_card.rank, "%d", x / 4 + 1);
                    break;
                }
                dealt_card.suit_value = x % 4;
                dealt_card.suit = suits[x % 4];
                cards[x / 4][x % 4] = 1;
                dealt = 1;
                break;
            }
            x++;
        }
        x = 0;
    }

    return dealt_card;
}

void sort_hand(card players[][13])
{
    for (int i = 0; i < 4; i++)
    {
        card tmp;
        for (int j = 0; j < 12; j++)
        {
            for (int k = j + 1; k < 13; k++)
            {
                // Sort by rank_value
                if (players[i][j].rank_value > players[i][k].rank_value)
                {
                    tmp = players[i][j];
                    players[i][j] = players[i][k];
                    players[i][k] = tmp;
                }

                // Sort by suit_value
                else if (players[i][j].rank_value == players[i][k].rank_value)
                {
                    if (players[i][j].suit_value > players[i][k].suit_value)
                    {
                        tmp = players[i][j];
                        players[i][j] = players[i][k];
                        players[i][k] = tmp;
                    }
                }
            }
        }
    }
}

void print_hand(card players[][13])
{
    for (int i = 0; i < 4; i++)
    {
        printf("Player %d: ", i + 1);
        for (int j = 0; j < 13; j++)
        {
            printf("%2s[%c] ", players[i][j].rank, players[i][j].suit);
        }

        // Print out four of a kind
        printf("\n- Four of a kind: ");
        int card_count = 0, four_count = 0, previous = -1;
        for (int j = 0; j < 13; j++)
        {
            if (players[i][j].rank_value == previous)
            {
                card_count++;
                if (card_count == 4)
                {
                    printf("%2s  ", players[i][j].rank);
                    card_count = 0;
                    four_count++;
                }
            }
            else
                card_count = 1;
            previous = players[i][j].rank_value;
        }
        if (four_count == 0)
            printf("None!");
        printf("\n\n");
    }
}
