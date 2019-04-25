#include "math.h"

static uint64_t fact(uint8_t number) {
    if (number < 2)
        return 1;
    uint64_t result = 2;
    for (uint64_t i = 3; i <= number; ++i) {
        result *= i;
    }
    return result;
}

static uint64_t cnk(uint8_t n, uint8_t k) {
    return fact(n) / fact(n - k) / fact(k);
}

double count_hands(int nb_cards) {
    if (nb_cards > 48 || nb_cards % 2 != 0)
        return 0;
    if (nb_cards > 24)
        return count_hands(48 - nb_cards);
    if (nb_cards == 0)
        return 1;
    uint8_t nb_united_pairs = 0;
    uint8_t nb_isolated_pairs = nb_cards / 2;
    uint64_t result = 0;
    while (1) {
        uint64_t sixtothex = 1;
        for (int i = 0; i < nb_isolated_pairs; ++i) {
            sixtothex *= 6;
        }
        result += cnk(12, nb_united_pairs) * cnk(12 - nb_united_pairs, nb_isolated_pairs) * sixtothex;
        nb_united_pairs += 1;
        if (nb_isolated_pairs < 2)
            break;
        nb_isolated_pairs -= 2;
    }
    return result;
}
