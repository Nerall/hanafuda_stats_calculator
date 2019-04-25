# Hanafuda Stats Calculator


## Introduction

This project was made last year by myself for entertainment in order have
some statistics about the hanafuda game, koi-koi rules.

For more information about the rules, look here:
https://www.hanafuda.fr/en/#presentation

The project was done only for my own purpose and I don't need it anymore since
I have got all the values I was searching for. Still, it is available to anyone
that could be interested in statistics for hanafuda. Adapting it to other rules
wouldn't be that hard if you need results for other hanafuda rules.


## Dependencies

`Python3` with `pandas` and `matplotlib`


## How it works...

The goal is the following: giving a card, I want to know its theorical value
comparing to other cards and numbers that have some meaning.

To do so, the program will, for each possible number of cards gained,
take all possible hand of that many cards, compute its value, and increase
the score of all the cards and all the yaku (combinaisons) included in.

The results are stored in four files, one containing the average score that
one card will give depending on the number of cards gained, one
containing the average score that one yaku will give depending on the number
of cards gained, and the two same files without the sake yaku (this yaku
being optional, disabling it balances the game).


## ...Then

Having all tables available, it is possible to concatenate data of all files
into data bases.

With those data bases, it is possible to build any kind of chart to represent
the results.


## Building and running

To build the project, run `make` at the root of the project.
To clean what you made, run `make clean` at the root of the project.
To run the program, do the following:
* `./hanafuda_stats_calculator` [ARG]
[ARG] being an optional value for the number of cards for which you want to
have results.
If no ARG is provided, it will compute results for every
number of cards (between 0 and 48).

/!\ Some values can be really slow to compute, especially those between 20 and
30. It is normal due to the number of calculus the program has to do.

Having all values ready, you can run `python3 generate_csv.py` at the root of
the project to generate .csv files associated with the values.

After doing this, if you want to have pretty charts, you can run
`python3 generate_charts.py` at the root of the project.

If you want to clean everything, just run 'rm -rf results' at the
root of the project.


## Authors

* Neral