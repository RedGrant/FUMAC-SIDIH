#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//code structures


//vectores structures that hold the size and values of something
typedef struct int_vector
{
	int size;
	int* values;

}int_vector;


//vectores structures that hold the size and a string of something
typedef struct string_vector
{
	int size;
	char** string;

} string_vector;


//the automata's structure
typedef struct automato
{
	string_vector states;
	
	string_vector events;
	
	int initial;
	
	int_vector marked;

	int_vector*** transitions;

	int_vector*** inverse_transitions;

	int_vector* e_closure;
	
	int null_event;

	int deterministic;

	int error;

} automato;


typedef struct dfa
{
	int dfa_states_size;

	int_vector* dfa_states;

	int_vector** transitions_table;

	int error;

}dfa;

typedef struct canonical
{
	int pair_size;

	int marked_counter;

	int_vector* pair;

	int_vector* table_marked;

	int_vector* states_to_combine;

	int_vector** combined_states_trs;

	int combined_states;

	int trs_size;

	int error;

}canonical;

typedef struct product

{
	int product_states_size;
	int product_trs_size;
	int_vector* product_states;
	int_vector** product_states_trs;
	int error;

}product;

//the prototype of the used functions
void menu();
void load_file(automato* load_automata, char* file_path);
void printAutomata(automato* load_automata);
void checkAccessibilty(automato* load_automata, int dfa_canonical);
void checkCoaccessibilty(automato* load_automata);
void dfaOrNfa(automato* load_automata);
void nfaToDfa(automato* load_automata, int nda_or_da);
void freeAutomata(automato* load_automata);
void dfaCanonical(automato* load_automata);
void automataProduct(automato* automata1, automato* automata2);
void writeAutomataToFile(automato* load_automata);
automato* new_automata();
