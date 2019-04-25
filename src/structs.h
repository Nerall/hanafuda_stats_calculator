#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern uint8_t types[48];

struct stats {
    uint8_t yakusS[12];
    uint8_t yakusnoS[10];
    uint8_t scoreS;
    uint8_t scorenoS;
};

struct gstats {
    uint64_t yakusS[12];
    uint64_t yakusnoS[10];
    uint64_t cardsS[30];
    uint64_t cardsnoS[30];
};

struct histobit {
    uint8_t cells[6];
    uint8_t nb_cards;
    uint8_t types[4];
};

void init_stats(struct stats *stats);

void init_gstats(struct gstats *gstats);

void init_histobit(struct histobit *histo, int full);

void set_histobit(struct histobit *histo, uint8_t index);

void clear_histobit(struct histobit *histo, uint8_t index);

uint8_t get_histobit(const struct histobit *histo, uint8_t index);

#endif