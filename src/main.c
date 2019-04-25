#include "calc.h"
#include "math.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

// Yaku names
char *yakus[12] = { "Kasu", "Tane", "Tan", "Sankou", "Ame-shikou",
                    "Shikou", "Gokou", "Ino-shika-chou", "Akatan", "Aotan",
                    "Hanami-zake", "Tsukimi-zake" };

// Card names
char *cards[12] = { "Crane, Aka1, Kasu11, Kasu12",
                    "Nightingale, Aka2, Kasu21, Kasu22",
                    "Curtain, Aka3, Kasu31, Kasu32",
                    "Cuckoo, Tan4, Kasu41, Kasu42",
                    "Bridge, Tan5, Kasu51, Kasu52",
                    "Butterflies, Ao6, Kasu61, Kasu62",
                    "Boar, Tan7, Kasu71, Kasu72",
                    "Moon, Geese, Kasu81, Kasu82",
                    "Sake, Ao9, Kasu91, Kasu92",
                    "Deer, AoA, KasuA1, KasuA2",
                    "Rain, Swallow, TanB, Lightning",
                    "Phoenix, KasuC1, KasuC2, KasuC3" };

// ID of useful cards
extern int id_cards[30];

// for cards that are equivalent with other cards, like 2nd plains or
// similar month, the values are just copied
int id_cards_from[18] = { 2, 6, 10, 14, 12, 13, 14, 14, 22,
    26, 30, 34, 20, 21, 22, 22, 45, 45 };
int id_cards_to[18] = { 3, 7, 11, 15, 16, 17, 18, 19, 23,
    27, 31, 35, 36, 37, 38, 39, 46, 47 };

// main function, outside of main to permit loops
void print_stats(int nb_cards) {
    // destinations files
    char str[31];
    sprintf(str, "results/yakus%d.txt", nb_cards);
    FILE *fyakus = fopen(str, "w");
    sprintf(str, "results/yakusno%d.txt", nb_cards);
    FILE *fyakusno = fopen(str, "w");
    sprintf(str, "results/scores%d.txt", nb_cards);
    FILE *fcards = fopen(str, "w");
    sprintf(str, "results/scoresno%d.txt", nb_cards);
    FILE *fcardsno = fopen(str, "w");

    // struct that will contain final datas
    struct gstats gstats;
    init_gstats(&gstats);

    // empty histogram that will fill the gstats struct
    struct histobit histo;
    if (nb_cards <= 24) {
        init_histobit(&histo, 0);
        add_cards(&histo, nb_cards, &gstats, 0);
    }
    else {
        init_histobit(&histo, 1);
        remove_cards(&histo, 48 - nb_cards, &gstats, 0);
    }

    // some values are redundant so they are just copied
    uint64_t cardsS[48];
    uint64_t cardsnoS[48];
    for (int i = 0; i < 30; ++i) {
        cardsS[id_cards[i]] = gstats.cardsS[i];
        cardsnoS[id_cards[i]] = gstats.cardsnoS[i];
    }
    for (int i = 0; i < 18; ++i) {
        cardsS[id_cards_to[i]] = cardsS[id_cards_from[i]];
        cardsnoS[id_cards_to[i]] = cardsnoS[id_cards_from[i]];
    }

    // the number of combinations are counted here rather than in structs
    double nb_hands = count_hands(nb_cards);

    // datas are printed in corresponding files
    for (int i = 0; i < 12; ++i) {
        fprintf(fyakus, "%s:\n%.3f\n\n", yakus[i],
            ((double) gstats.yakusS[i]) / nb_hands);
    }
    for (int i = 0; i < 10; ++i) {
        fprintf(fyakusno, "%s:\n%.3f\n\n", yakus[i],
            ((double) gstats.yakusnoS[i]) / nb_hands);
    }
    for (int i = 0; i < 12; ++i) {
        fprintf(fcards, "%s:\n%.3f, %.3f, %.3f, %.3f\n\n", cards[i],
            ((double) cardsS[4 * i]) / nb_hands,
            ((double) cardsS[4 * i + 1]) / nb_hands,
            ((double) cardsS[4 * i + 2]) / nb_hands,
            ((double) cardsS[4 * i + 3]) / nb_hands);
        fprintf(fcardsno, "%s:\n%.3f, %.3f, %.3f, %.3f\n\n", cards[i],
            ((double) cardsnoS[4 * i]) / nb_hands,
            ((double) cardsnoS[4 * i + 1]) / nb_hands,
            ((double) cardsnoS[4 * i + 2]) / nb_hands,
            ((double) cardsnoS[4 * i + 3]) / nb_hands);
    }
    fclose(fyakus);
    fclose(fyakusno);
    fclose(fcards);
    fclose(fcardsno);
    printf("%.f combination%s for %d card%s\n", nb_hands, (nb_hands > 1) ?
           "s": "", nb_cards, (nb_cards > 1) ? "s" : "");
}

int main(int argc, char *argv[]) {
    mkdir("results", 0777);
    if (argc < 2) {
        for(int i = 0; i <= 48; i += 2) {
            print_stats(i);
        }
    }
    else {
        int nb_cards = atoi(argv[1]);
        if (nb_cards >= 0 && nb_cards < 48 && nb_cards % 2 == 0)
            print_stats(nb_cards);
        else
            printf("%d is not a valid number", nb_cards);
    }
    return 0;
}