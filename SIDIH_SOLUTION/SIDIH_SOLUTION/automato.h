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


//the dfa's structure

typedef struct dfa
{
	int dfa_states_size;

	int_vector* dfa_states;

	int_vector** transitions_table;

	int error;

}dfa;


//the canonical's structure

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


//the product's structure

typedef struct product

{
	int product_states_size;
	int product_trs_size;
	int_vector* product_states;
	int_vector** product_states_trs;
	int error;

}product;

//the parallel's structure

typedef struct parallel

{
	string_vector parallel_events;
	int parallel_states_size;
	int parallel_trs_size;
	int_vector* parallel_states;
	int_vector** parallel_states_trs;
	int error;

}parallel;


//the automata_array's structure

typedef struct automata_array
{
	automato** automata;
	string_vector automata_name;
	int automata_number;

} automata_array;


//the prototype of the publi
void menu();

