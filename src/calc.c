#include "calc.h"

int id_cards[30] = { 0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14, 20, 21, 22, 24, 25,
                     26, 28, 29, 30, 32, 33, 34, 40, 41, 42, 43, 44, 45 };

void count_histo(struct histobit *histo, struct stats *stats) {
    uint8_t sake = get_histobit(histo, 32);
    histo->types[0] += sake;
    if (histo->types[0] > 9) {
        stats->scorenoS += histo->types[0] - 9;
        stats->yakusnoS[0] += histo->types[0] - 9;
    }
    if (histo->types[1] > 4) {
        stats->scorenoS += histo->types[1] - 4;
        stats->yakusnoS[1] += histo->types[1] - 4;
    }
    if (histo->types[2] > 4) {
        stats->scorenoS += histo->types[2] - 4;
        stats->yakusnoS[2] += histo->types[2] - 4;
    }
    uint8_t brights = histo->types[3];
    if (brights >= 3) {
        uint8_t rain = get_histobit(histo, 40);
        if (!rain) {
            if (brights == 3) {
                stats->scorenoS += 5;
                stats->yakusnoS[3] += 5;
            }
            else {
                stats->scorenoS += 8;
                stats->yakusnoS[5] += 8;
            }
        }
        else {
            if (brights == 4) {
                stats->scorenoS += 7;
                stats->yakusnoS[4] += 7;
            }
            else if (brights == 5) {
                stats->scorenoS += 10;
                stats->yakusnoS[6] += 10;
            }
        }
    }
    if (get_histobit(histo, 20) && get_histobit(histo, 24) &&
        get_histobit(histo, 36)) {
        stats->scorenoS += 5;
        stats->yakusnoS[7] += 5;
    }
    if (get_histobit(histo, 1) && get_histobit(histo, 5) &&
        get_histobit(histo, 9)) {
        stats->scorenoS += 5;
        stats->yakusnoS[8] += 5;
    }
    if (get_histobit(histo, 21) && get_histobit(histo, 33) &&
        get_histobit(histo, 37)) {
        stats->scorenoS += 5;
        stats->yakusnoS[9] += 5;
    }
    stats->scoreS = stats->scorenoS;
    if (sake) {
        if (get_histobit(histo, 8)) {
            stats->scoreS += 5;
            stats->yakusS[10] += 5;
        }
        if (get_histobit(histo, 28)) {
            stats->scoreS += 5;
            stats->yakusS[11] += 5;
        }
    }
    if (stats->scorenoS >= 7) {
        stats->scorenoS *= 2;
        stats->scoreS *= 2;
        for (int i = 0; i < 10; ++i) {
            stats->yakusnoS[i] *= 2;
            stats->yakusS[i] = stats->yakusnoS[i];
        }
        stats->yakusS[10] *= 2;
        stats->yakusS[11] *= 2;
    }
    else if (stats->scoreS >= 7) {
        stats->scoreS *= 2;
        for (int i = 0; i < 10; ++i) {
            stats->yakusS[i] = 2 * stats->yakusnoS[i];
        }
        stats->yakusS[10] *= 2;
        stats->yakusS[11] *= 2;
    }
    else {
        for (int i = 0; i < 10; ++i) {
            stats->yakusS[i] = stats->yakusnoS[i];
        }
    }
    histo->types[0] -= sake;
}

void add_cards(struct histobit *histo, uint8_t nb_add,
                struct gstats *gstats, int start) {
    if (nb_add >= 2) {
        int month;
        int month1;
        int month2;
        int month3;
        for (int id_month = start; id_month < 48; id_month += 4) {
            if ((48 - id_month) >= nb_add) {
                month = get_histobit(histo, id_month);
                month1 = get_histobit(histo, id_month + 1);
                month2 = get_histobit(histo, id_month + 2);
                month3 = get_histobit(histo, id_month + 3);
                if (!month) {
                    if (!month1) {
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 1);
                        add_cards(histo, nb_add - 2, gstats, id_month);
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 1);
                    }
                    if (!month2) {
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 2);
                        add_cards(histo, nb_add - 2,
                            gstats, id_month + 4);
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 2);
                    }
                    if (!month3) {
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 3);
                        add_cards(histo, nb_add - 2,
                            gstats, id_month + 4);
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 3);
                    }
                }
                if (!month2) {
                    if (!month3) {
                        set_histobit(histo, id_month + 2);
                        set_histobit(histo, id_month + 3);
                        add_cards(histo, nb_add - 2,
                            gstats, id_month + 4);
                        clear_histobit(histo, id_month + 2);
                        clear_histobit(histo, id_month + 3);
                    }
                    if (!month1) {
                        set_histobit(histo, id_month + 1);
                        set_histobit(histo, id_month + 2);
                        add_cards(histo, nb_add - 2,
                            gstats, id_month + 4);
                        clear_histobit(histo, id_month + 1);
                        clear_histobit(histo, id_month + 2);
                    }
                }
                if (!month1 && !month3) {
                    set_histobit(histo, id_month + 1);
                    set_histobit(histo, id_month + 3);
                    add_cards(histo, nb_add - 2, gstats, id_month + 4);
                    clear_histobit(histo, id_month + 1);
                    clear_histobit(histo, id_month + 3);
                }
            }
        }
    }
    else {
        struct stats stats;
        init_stats(&stats);
        count_histo(histo, &stats);
        if (stats.scoreS) {
            for (int i = 0; i < 10; ++i) {
                gstats->yakusS[i] += ((uint64_t) stats.yakusS[i]);
                gstats->yakusnoS[i] += ((uint64_t) stats.yakusnoS[i]);
            }
            gstats->yakusS[10] += ((uint64_t) stats.yakusS[10]);
            gstats->yakusS[11] += ((uint64_t) stats.yakusS[11]);
            for (int i = 0; i < 30; ++i) {
                if (get_histobit(histo, id_cards[i])) {
                    gstats->cardsS[i] += ((uint64_t) stats.scoreS);
                    gstats->cardsnoS[i] += ((uint64_t) stats.scorenoS);
                }
            }
        }
        else if (stats.scorenoS) {
            for (int i = 0; i < 10; ++i) {
                gstats->yakusnoS[i] += ((uint64_t) stats.yakusnoS[i]);
            }
            for (int i = 0; i < 30; ++i) {
                if (get_histobit(histo, id_cards[i])) {
                    gstats->cardsnoS[i] += ((uint64_t) stats.scorenoS);
                }
            }
        }
    }
}

void remove_cards(struct histobit *histo, uint8_t nb_remove,
                struct gstats *gstats, int start) {
    if (nb_remove >= 2) {
        int month;
        int month1;
        int month2;
        int month3;
        for (int id_month = start; id_month < 48; id_month += 4) {
            if ((48 - id_month) >= nb_remove) {
                month = get_histobit(histo, id_month);
                month1 = get_histobit(histo, id_month + 1);
                month2 = get_histobit(histo, id_month + 2);
                month3 = get_histobit(histo, id_month + 3);
                if (month) {
                    if (month1) {
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 1);
                        remove_cards(histo, nb_remove - 2, gstats, id_month);
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 1);
                    }
                    if (month2) {
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 2);
                        remove_cards(histo, nb_remove - 2,
                            gstats, id_month + 4);
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 2);
                    }
                    if (month3) {
                        clear_histobit(histo, id_month);
                        clear_histobit(histo, id_month + 3);
                        remove_cards(histo, nb_remove - 2,
                            gstats, id_month + 4);
                        set_histobit(histo, id_month);
                        set_histobit(histo, id_month + 3);
                    }
                }
                if (month2) {
                    if (month3) {
                        clear_histobit(histo, id_month + 2);
                        clear_histobit(histo, id_month + 3);
                        remove_cards(histo, nb_remove - 2,
                            gstats, id_month + 4);
                        set_histobit(histo, id_month + 2);
                        set_histobit(histo, id_month + 3);
                    }
                    if (month1) {
                        clear_histobit(histo, id_month + 1);
                        clear_histobit(histo, id_month + 2);
                        remove_cards(histo, nb_remove - 2,
                            gstats, id_month + 4);
                        set_histobit(histo, id_month + 1);
                        set_histobit(histo, id_month + 2);
                    }
                }
                if (month1 && month3) {
                    clear_histobit(histo, id_month + 1);
                    clear_histobit(histo, id_month + 3);
                    remove_cards(histo, nb_remove - 2, gstats, id_month + 4);
                    set_histobit(histo, id_month + 1);
                    set_histobit(histo, id_month + 3);
                }
            }
        }
    }
    else {
        struct stats stats;
        init_stats(&stats);
        count_histo(histo, &stats);
        for (int i = 0; i < 10; ++i) {
            gstats->yakusS[i] += ((uint64_t) stats.yakusS[i]);
            gstats->yakusnoS[i] += ((uint64_t) stats.yakusnoS[i]);
        }
        gstats->yakusS[10] += ((uint64_t) stats.yakusS[10]);
        gstats->yakusS[11] += ((uint64_t) stats.yakusS[11]);
        for (int i = 0; i < 30; ++i) {
            if (get_histobit(histo, id_cards[i])) {
                gstats->cardsS[i] += ((uint64_t) stats.scoreS);
                gstats->cardsnoS[i] += ((uint64_t) stats.scorenoS);
            }
        }
    }
}
