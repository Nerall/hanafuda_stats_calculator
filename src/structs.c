#include "structs.h"

uint8_t types[48] = {
    3, 2, 0, 0,
    1, 2, 0, 0,
    3, 2, 0, 0,
    1, 2, 0, 0,
    1, 2, 0, 0,
    1, 2, 0, 0,
    1, 2, 0, 0,
    3, 1, 0, 0,
    1, 2, 0, 0,
    1, 2, 0, 0,
    3, 1, 2, 0,
    3, 0, 0, 0
};

void init_stats(struct stats *stats) {
    for (int i = 0; i < 10; ++i) {
        stats->yakusS[i] = 0;
        stats->yakusnoS[i] = 0;
    }
    stats->yakusS[10] = 0;
    stats->yakusS[11] = 0;
    stats->scoreS = 0;
    stats->scorenoS = 0;
}

void init_gstats(struct gstats *gstats) {
    for (int i = 0; i < 10; ++i) {
        gstats->yakusS[i] = 0;
        gstats->yakusnoS[i] = 0;
    }
    gstats->yakusS[10] = 0;
    gstats->yakusS[11] = 0;
    for (int i = 0; i < 30; ++i) {
        gstats->cardsS[i] = 0;
        gstats->cardsnoS[i] = 0;
    }
}

void init_histobit(struct histobit *histo, int full) {
    if (!full) {
        for (int i = 0; i < 6; ++i) {
            histo->cells[i] = 0;
        }
        histo->nb_cards = 0;
        for (int i = 0; i < 4; ++i) {
            histo->types[i] = 0;
        }
    }
    else {
        for (int i = 0; i < 6; ++i) {
            histo->cells[i] = 255;
        }
        histo->nb_cards = 48;
        histo->types[0] = 24;
        histo->types[1] = 9;
        histo->types[2] = 10;
        histo->types[3] = 5;
    }
}

void set_histobit(struct histobit *histo, uint8_t index) {
    histo->cells[index / 8] |= (1 << (index % 8));
    ++histo->nb_cards;
    ++histo->types[types[index]];
}

void clear_histobit(struct histobit *histo, uint8_t index) {
    histo->cells[index / 8] &= ~(1 << (index % 8));
    --histo->nb_cards;
    --histo->types[types[index]];
}
uint8_t get_histobit(const struct histobit *histo, uint8_t index) {
    return (histo->cells[index / 8] & (1 << (index % 8))) != 0;
}