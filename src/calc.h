#ifndef CALC_H
#define CALC_H

#include "structs.h"

extern int id_cards[30];

void count_histo(struct histobit *histo, struct stats *stats);

void add_cards(struct histobit *histo, uint8_t nb_add,
                    struct gstats *gstats, int start);

void remove_cards(struct histobit *histo, uint8_t nb_remove,
                    struct gstats *gstats, int start);

#endif