#include "automato.h"


//---------------------function prototypes-------------------
void parser(automato* load_automata, char* file_info);
void nullEventSearcher(automato* load_automata, char* file_info);
void deleteCharacter(char* str, char c);
bool splitString(char* string_to_split, char** substring, int* index, char delimitator);
int findItemStringVector(char* string, string_vector vect);
int findItemIntVector(int_vector myvect, int item);
void intVectPushBack(int_vector* vector, int item);
void stringPushBack(string_vector* char_vector, char* item);
void writeIntVectorInConsole(int_vector* vector, string_vector* string_vect);
void writeStringVectorInConsole(string_vector* string_vect);
void accesibleState(automato* load_automata, int state_index, int *accessible_states);
void rewriteAutomata(automato* load_automata, int* valid_states);
void freeData(automato* load_automata);
void coaccesibleState(automato* load_automata, int state_index, int *coaccessible_states);
void sortArrayAscending(int_vector* array_to_sort);
void eclosureFilling(automato* load_automata, int original_index, int index_next);
void checkDfaTransitions(automato* load_automata, int_vector dfa_states, dfa* load_dfa, int index, int events);
int findItemarray(int* array_to_search, int item, int array_size);
void writeDfaAutomata(automato* load_automata, dfa* load_dfa);
void resetAutomataStruct(automato* load_automata);
void resetDfaStructure(dfa* load_dfa);
void freeDfaStructure(dfa* load_dfa, automato* load_automata);
dfa* newDfa();
void freeDfa(dfa* load_dfa, automato* load_automata);
//-----------------------Public functions--------------------

//function responsible for creating a new automata
automato* new_automata()
{
	automato* new_aut;
	new_aut = (automato*)malloc(sizeof(automato));
	resetAutomataStruct(new_aut);
	return new_aut;
}

//function that loads to an automata a new file
void load_file(automato* load_automata, char* file_path)
{
	FILE* fp;
	int size = 0;
	char* file_info;
	fp = fopen(file_path, "rb");
	//check if there's something in the file
	if (fp == NULL)
	{
		printf("Error opening file");
		getchar();
		exit(0);
	}
	//get amount of characters in file
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//load file to a file_info string
	file_info = (char *)malloc(size + 1);
	fread(file_info, sizeof(char), size, fp);
	//last character is atributted with an end string
	file_info[size] = '\0';
	fclose(fp);
	//calls private function 
	parser(load_automata, file_info);
	free(file_info);
}

//function responsible to write on the console the automata
void printAutomata(automato* load_automata)
{

	printf("G=(X,E,f,Xinit,Xmarked)\n\n");
	int i = 0, j = 0, x = 0, comma_counter = 0;

	printf("States\n");
	printf("X=");
	writeStringVectorInConsole(&(load_automata->states));

	printf("Events\n");
	printf("E=");
	writeStringVectorInConsole(&(load_automata->events));

	printf("Transitions");

	for (i = 0; i < load_automata->states.size; i++)
	{
		for (j = 0; j < load_automata->events.size; j++)
		{
			if (load_automata->transitions[i][j]->size != 0)
			{
				printf("\nf(%s", load_automata->states.string[i]);
				printf(",%s)=", load_automata->events.string[j]);

				for (x = 0; x < load_automata->transitions[i][j]->size; x++)
				{
					if (load_automata->transitions[i][j]->size != 0 && load_automata->transitions[i][j]->size == 1)
					{
						printf("(%s)", load_automata->states.string[load_automata->transitions[i][j]->values[x]]);
						continue;
					}

					if (load_automata->transitions[i][j]->size != 0 && load_automata->transitions[i][j]->size > 1 && (x < ((load_automata->transitions[i][j]->size) - 1)))
					{
						if (x == 0)
						{
							printf("(%s,", load_automata->states.string[load_automata->transitions[i][j]->values[x]]);
						}
						else
							printf("%s,", load_automata->states.string[load_automata->transitions[i][j]->values[x]]);
					}
					if (load_automata->transitions[i][j]->size != 0 && (x == ((load_automata->transitions[i][j]->size) - 1)))
						printf("%s)", load_automata->states.string[load_automata->transitions[i][j]->values[x]]);
				}
			}
		}
	}
	printf("\n\n");

	printf("Initial\n");
	printf("Xinit=%s\n\n", load_automata->states.string[load_automata->initial]);

	printf("Marked\n");
	printf("Xmarked=");
	writeIntVectorInConsole(&(load_automata->marked), &(load_automata->states));

	for (i = 0; i < load_automata->states.size; i++)
	{
		printf("EClosure(%s)=", load_automata->states.string[i]);
		for (j = 0; j < load_automata->e_closure[i].size; j++)
		{
			if (load_automata->e_closure[i].size == 1)
			{
				printf("{%s}", (load_automata)->states.string[(load_automata)->e_closure[i].values[j]]);
			}
			if (load_automata->e_closure[i].size > 1)
			{
				if (j == 0)
				{
					printf("{%s,", (load_automata)->states.string[load_automata->e_closure[i].values[j]]);
				}
				if (j > 0 && j != (load_automata->e_closure[i].size - 1))
				{
					printf("%s,", (load_automata)->states.string[(load_automata)->e_closure[i].values[j]]);
				}
				if (j == load_automata->e_closure[i].size - 1)
				{
					printf("%s}", (load_automata)->states.string[load_automata->e_closure[i].values[j]]);
				}
			}
		}
		printf("\n\n");
	}
}

//check accessibility of a state and delete those that aren't accessible
void checkAccessibilty(automato* load_automata)
{
	int i = 0, j = 0, x = 0, initial_confirmation = 0;
	int *accessible_states;
	int *accessible_states_check;
	int continue_loop = 1, delete_counter = 0;

	accessible_states = malloc(sizeof(int)*(load_automata->states.size));
	accessible_states_check = malloc(sizeof(int)*(load_automata->states.size));

	for (i = 0; i < load_automata->events.size; i++)
	{
		if ((load_automata->transitions[load_automata->initial][i]->size) != 0)
		{
			initial_confirmation = 0;
			break;
		}
		else initial_confirmation = 1;
	}
	if (initial_confirmation == 1)
	{
		printf("No state is acessible through the initial state!\n\n");
		getchar();
		exit(0);
	}
	else
	{
		//initially say that no state is accessilbe
		for (i = 0; i < load_automata->states.size; i++)
		{
			accessible_states[i] = 0;
		}
		//the initial state must be accessible 
		accessible_states[load_automata->initial] = 1;
		x = load_automata->initial;
		//after that check the transitions of the initial state any state that comes from initial will be accessible 
		accesibleState(load_automata, x, accessible_states);

		//while it's still one, it will continue.
		while (continue_loop)
		{
			//every state will be checked and if it is accessible we'll see if its transitions are too
			for (i = 0; i < load_automata->states.size; i++)
			{
				if (accessible_states[i] == 1)
				{
					accesibleState(load_automata, i, accessible_states);
				}
			}

			continue_loop = 0;

			for (i = 0; i < load_automata->states.size; i++)
			{
				//if there are differences in the accessible states array and it's "copy", there are still paths to take
				if (accessible_states[i] != accessible_states_check[i])
				{
					for (j = 0; j < load_automata->states.size; j++)
					{
						accessible_states_check[j] = accessible_states[j];
					}
					continue_loop = 1;
					break;
				}
			}
		}
	}
	for (i = 0; i < load_automata->states.size; i++)
	{
		if (accessible_states[i] == 0)
			delete_counter++;
	}

	if (delete_counter > 0)
	{
		printf("-----------The automata had non-accessible states. They are going to be removed-----------\n\n\n");
		printf("Removed states:\n");
		for (i = 0; i < load_automata->states.size; i++)
		{
			if (accessible_states[i] == 0)
				printf("%s \n", load_automata->states.string[i]);
		}
		rewriteAutomata(load_automata, accessible_states);
		printf("\n\n\n-----------Reprinting the trimmed automata-----------\n\n\n");
		printAutomata(load_automata);
	}
	else
		printf("\n\n\n-----------All states in the automata are accessible!-----------\n\n\n");
	free(accessible_states);
	free(accessible_states_check);
}

void checkCoaccessibilty(automato* load_automata)
{
	int i = 0, j = 0, x = 0, initial_confirmation = 0;
	int *coaccessible_states;
	int *coaccessible_states_check;
	int continue_loop = 1, delete_counter = 0;

	coaccessible_states = malloc(sizeof(int)*(load_automata->states.size));
	coaccessible_states_check = malloc(sizeof(int)*(load_automata->states.size));


	for (j = 0; j < load_automata->marked.size; j++)
	{
		for (i = 0; i < load_automata->events.size; i++)
		{

			if ((load_automata->inverse_transitions[load_automata->marked.values[j]][i]->size) != 0)
			{
				initial_confirmation = 0;
				break;
			}
			else initial_confirmation = 1;
		}
	}

	if (initial_confirmation == 1)
	{
		printf("No state is coacessible through any marked state(s)!\n\n");
		for (i = 0; i < load_automata->states.size; i++)
		{
			coaccessible_states[i] = 0;
		}
		for (j = 0; j < load_automata->marked.size; j++)
		{
			for (i = 0; i < load_automata->states.size; i++)
			{
				if (load_automata->marked.values[j] == i)
				{
					coaccessible_states[i] = 1;
				}
			}
		}
	}
	else
	{
		//initially say that no state is coaccessilbe
		for (i = 0; i < load_automata->states.size; i++)
		{
			coaccessible_states[i] = 0;
		}
		//the marked state(s) must be coaccessible 
		for (j = 0; j < load_automata->marked.size; j++)
		{
			for (i = 0; i < load_automata->states.size; i++)
			{
				if (load_automata->marked.values[j] == i)
				{
					coaccessible_states[i] = 1;
				}
			}
		}


		for (x = 0; x < load_automata->marked.size; x++)
		{
			//after that check the transitions of the marked state any state that comes from marked will be coacessible
			coaccesibleState(load_automata, load_automata->marked.values[x], coaccessible_states);

			//while it's still one, it will continue.
			while (continue_loop)
			{
				//every state will be checked and if it is coaccessible we'll see if its transitions are too
				for (i = 0; i < load_automata->states.size; i++)
				{
					if (coaccessible_states[i] == 1)
					{
						coaccesibleState(load_automata, i, coaccessible_states);
					}
				}

				continue_loop = 0;

				for (i = 0; i < load_automata->states.size; i++)
				{
					//if there are differences in the accessible states array and it's "copy", there are still paths to take
					if (coaccessible_states[i] != coaccessible_states_check[i])
					{
						for (j = 0; j < load_automata->states.size; j++)
						{
							coaccessible_states_check[j] = coaccessible_states[j];
						}
						continue_loop = 1;
						break;
					}
				}
			}
			continue_loop = 0;
		}
	}

	for (i = 0; i < load_automata->states.size; i++)
	{
		if (coaccessible_states[i] == 0)
			delete_counter++;
	}

	if (delete_counter > 0)
	{
		printf("\n\n\n-----------The automata had non-coaccessible states. They are going to be removed-----------\n\n\n");
		printf("Removed states:\n");
		for (i = 0; i < load_automata->states.size; i++)
		{
			if (coaccessible_states[i] == 0)
				printf("%s \n", load_automata->states.string[i]);
		}
		rewriteAutomata(load_automata, coaccessible_states);
		printf("\n\n\n-----------Reprinting the trimmed automata-----------\n\n\n");

		printAutomata(load_automata);
	}
	else
		printf("\n\n\n-----------All states in the automata are coaccessible!-----------\n\n\n");

	free(coaccessible_states);
	free(coaccessible_states_check);
}

void dfaOrNfa(automato* load_automata)
{
	int i = 0, j = 0, x = 0, t = 0, y = 0, confirmation = 0;
	if (load_automata->null_event == 1)
	{
		if (load_automata->states.size == 1)
		{
			printf("The automata only has one state. Please rewrite the automata! \n");
			getchar();
			exit(0);
		}
		printf("The automata is not deterministic\n\n");
		load_automata->deterministic = 0;
		return;
	}
	else
	{
		if (load_automata->states.size == 1)
		{
			printf("The automata only has one state. Please rewrite the automata! \n");
			getchar();
			exit(0);
		}
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_automata->transitions[i][j]->size != 0)
				{
					for (x = 0; x < load_automata->transitions[i][j]->size; x++)
					{
						if (load_automata->transitions[i][j]->size != 0 && load_automata->transitions[i][j]->size == 1)
						{
							continue;
						}

						if (load_automata->transitions[i][j]->size > 0)
						{
							for (int t = 0; t < load_automata->transitions[i][j]->size - 1; t++)
							{
								for (int y = t + 1; y < load_automata->transitions[i][j]->size; y++)
								{
									if (load_automata->transitions[i][j]->values[t] != load_automata->transitions[i][j]->values[y])
									{
										load_automata->null_event = 1;
									}
								}
							}
						}
					}
				}
			}
		}
		if (load_automata->null_event == 1)
		{
			printf("The automata is not deterministic\n\n");
			load_automata->deterministic = 0;
			load_automata->null_event = 0;
		}
		else
		{
			printf("The automata is deterministic!\n\n");
			load_automata->deterministic = 1;
			load_automata->null_event = 0;
		}
	}
}

void nfaToDfa(automato* load_automata, int nda_or_da)
{
	if (nda_or_da == 0)
	{
		printf("\n\n\n-----------Converting the not deterministic finite automata to a deterministic finite automata-----------\n\n\n");
		int i = 0, j = 0, x = 0, y = 0, z = 0, t = 0, confirmation = 0, old_size = 1;
		dfa* load_dfa;
		load_dfa = newDfa();
		load_dfa->dfa_states = (int_vector*)malloc(sizeof(int_vector));
		load_dfa->dfa_states[0].size = 0;
		load_dfa->dfa_states_size = 0;
		load_dfa->dfa_states_size++;

		for (i = 0; i < load_automata->e_closure[load_automata->initial].size; i++)
		{
			intVectPushBack(&(load_dfa->dfa_states[0]), load_automata->e_closure[load_automata->initial].values[i]);
		}


		if (load_dfa->transitions_table == NULL)
		{
			if (load_dfa->dfa_states_size == 1)
			{
				load_dfa->transitions_table = (int_vector**)malloc(sizeof(int_vector*)*load_dfa->dfa_states_size);

				for (i = 0; i < load_dfa->dfa_states_size; i++)
				{
					load_dfa->transitions_table[i] = (int_vector*)malloc(sizeof(int_vector)*(load_automata->events.size));
				}
			}
		}
		for (i = 0; i < load_dfa->dfa_states_size; i++)
		{

			if (i != 0)
			{


				if (load_dfa->dfa_states_size > old_size)
				{
					load_dfa->dfa_states = (int_vector*)realloc(load_dfa->dfa_states, sizeof(int_vector)*load_dfa->dfa_states_size);

					load_dfa->transitions_table = (int_vector**)realloc(load_dfa->transitions_table, sizeof(int_vector*)*load_dfa->dfa_states_size);
				}
				if (load_automata->null_event == 1)
				{
					load_dfa->transitions_table[i] = (int_vector*)malloc(sizeof(int_vector)*((load_automata->events.size)));
				}
				else
				{
					load_dfa->transitions_table[i] = (int_vector*)malloc(sizeof(int_vector)*(load_automata->events.size));
				}

				old_size = load_dfa->dfa_states_size;

				if (load_automata->null_event == 1)
				{
					for (y = 1; y < load_automata->events.size; y++)
					{
						load_dfa->transitions_table[i][y].size = 0;
					}
				}
				else
				{
					for (y = 0; y < load_automata->events.size; y++)
					{
						load_dfa->transitions_table[i][y].size = 0;
					}
				}
			}
			else
			{
				if (load_automata->null_event == 1)
				{
					for (y = 1; y < load_automata->events.size; y++)
					{
						load_dfa->transitions_table[i][y].size = 0;
					}
				}
				else
				{
					for (y = 0; y < load_automata->events.size; y++)
					{
						load_dfa->transitions_table[i][y].size = 0;
					}
				}

			}



			if (load_automata->null_event == 1)
			{
				for (x = 1; x < load_automata->events.size; x++)
				{
					checkDfaTransitions(load_automata, load_dfa->dfa_states[i], load_dfa, i, x);
				}
			}

			else
			{
				for (x = 0; x < load_automata->events.size; x++)
				{
					checkDfaTransitions(load_automata, load_dfa->dfa_states[i], load_dfa, i, x);
				}
			}

		}
		writeDfaAutomata(load_automata, load_dfa);
		printf("\n\n\n-----------Automata converted... Rewriting the converted automata-----------\n\n\n");
		printAutomata(load_automata);

	}
}



void checkDfaTransitions(automato* load_automata, int_vector dfa_states, dfa* load_dfa, int index, int events)
{
	int* dfa_provisory_state = (int*)malloc(sizeof(int));
	int dfa_provisory_state_size = 0;
	int i = 0, y = 0, j = 0, z = 0, test = 0, counter = 0, different_state = 0;

	for (j = 0; j < dfa_states.size; j++)
	{
		if (load_automata->transitions[dfa_states.values[j]][events]->size != 0)
		{
			for (y = 0; y < load_automata->transitions[dfa_states.values[j]][events]->size; y++)
			{
				for (z = 0; z < load_automata->e_closure[load_automata->transitions[dfa_states.values[j]][events]->values[y]].size; z++)
				{
					if (dfa_provisory_state_size == 0)
					{
						dfa_provisory_state_size++;
						dfa_provisory_state[dfa_provisory_state_size - 1] = load_automata->e_closure[load_automata->transitions[load_dfa->dfa_states[index].values[j]][events]->values[y]].values[z];

					}
					else
					{
						if (findItemarray(dfa_provisory_state, load_automata->e_closure[load_automata->transitions[load_dfa->dfa_states[index].values[j]][events]->values[y]].values[z], dfa_provisory_state_size) == dfa_provisory_state_size)
						{
							dfa_provisory_state_size++;
							dfa_provisory_state = (int*)realloc(dfa_provisory_state, sizeof(int)*dfa_provisory_state_size);
							dfa_provisory_state[dfa_provisory_state_size - 1] = load_automata->e_closure[load_automata->transitions[load_dfa->dfa_states[index].values[j]][events]->values[y]].values[z];
						}
					}
				}
			}
		}
	}
	if (dfa_provisory_state_size == 0)
	{
		free(dfa_provisory_state);
		return;
	}
	for (j = 0; j < load_dfa->dfa_states_size; j++)
	{
		if (load_dfa->dfa_states[j].size == dfa_provisory_state_size)
		{
			test++;
		}
	}
	if (test == 0)
	{
		for (j = 0; j < dfa_provisory_state_size; j++)
		{
			if (j == 0)
			{
				load_dfa->dfa_states = (int_vector*)realloc(load_dfa->dfa_states, sizeof(int_vector)*(load_dfa->dfa_states_size + 1));
				load_dfa->dfa_states[load_dfa->dfa_states_size].size = 0;
				intVectPushBack(&(load_dfa->dfa_states[load_dfa->dfa_states_size]), dfa_provisory_state[j]);
			}
			else
				intVectPushBack(&(load_dfa->dfa_states[load_dfa->dfa_states_size]), dfa_provisory_state[j]);
		}
		sortArrayAscending(&(load_dfa->dfa_states[load_dfa->dfa_states_size]));

		load_dfa->transitions_table[index][events].values = (int_vector*)malloc(sizeof(int*));
		load_dfa->transitions_table[index][events].values[0] = load_dfa->dfa_states_size;
		load_dfa->transitions_table[index][events].size++;
		load_dfa->dfa_states_size++;

	}
	else
	{
		test = 0;
		for (j = 0; j < load_dfa->dfa_states_size; j++)
		{
			if (load_dfa->dfa_states[j].size == dfa_provisory_state_size)
			{
				test++;
			}
			if (test != 0)
			{
				test = 0;
				counter = 0;
				for (z = 0; z < dfa_provisory_state_size; z++)
				{
					if (findItemIntVector(load_dfa->dfa_states[j], dfa_provisory_state[z]) != load_dfa->dfa_states[j].size)
					{
						counter++;
						continue;
					}
				}
				if (counter != load_dfa->dfa_states[j].size)
				{
					different_state++;
					counter = 0;
				}

			}
			else
			{
				if (dfa_provisory_state_size == 0)
				{
					return;
				}
				different_state++;
			}
		}
		if (different_state == load_dfa->dfa_states_size)
		{
			test = 0;
			different_state = 0;

			for (j = 0; j < dfa_provisory_state_size; j++)
			{
				if (j == 0)
				{
					load_dfa->dfa_states = (int_vector*)realloc(load_dfa->dfa_states, sizeof(int_vector)*(load_dfa->dfa_states_size + 1));
					load_dfa->dfa_states[load_dfa->dfa_states_size].size = 0;
					intVectPushBack(&(load_dfa->dfa_states[load_dfa->dfa_states_size]), dfa_provisory_state[j]);
				}
				else
					intVectPushBack(&(load_dfa->dfa_states[load_dfa->dfa_states_size]), dfa_provisory_state[j]);
			}
			sortArrayAscending(&(load_dfa->dfa_states[load_dfa->dfa_states_size]));

			load_dfa->transitions_table[index][events].values = (int_vector*)malloc(sizeof(int*));
			load_dfa->transitions_table[index][events].values[0] = load_dfa->dfa_states_size;
			load_dfa->transitions_table[index][events].size++;
			load_dfa->dfa_states_size++;
		}
		else
		{
			test = 0;
			different_state = 0;

			for (i = 0; i < load_dfa->dfa_states_size; i++)
			{
				if (dfa_provisory_state_size == load_dfa->dfa_states[i].size)
				{
					for (j = 0; j < dfa_provisory_state_size; j++)
					{
						if (findItemIntVector(load_dfa->dfa_states[i], dfa_provisory_state[j]) != load_dfa->dfa_states[i].size)
						{
							test++;
						}
						if (test == load_dfa->dfa_states[i].size)
						{
							load_dfa->transitions_table[index][events].values = (int_vector*)malloc(sizeof(int*));
							load_dfa->transitions_table[index][events].values[0] = i;
							load_dfa->transitions_table[index][events].size++;
						}
					}
				}
				test = 0;
			}
			test = 0;
		}
	}
	free(dfa_provisory_state);
}

void freeAutomata(automato* load_automata)
{
	freeData(load_automata);
	free(load_automata);
}

void dfaCanonical(automato* load_automata)
{

}
//----------------------Private functions---------------------------
void freeData(automato* load_automata)
{
	int i = 0, j = 0, x = 0, z = 0;
	if (load_automata->states.size > 0)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_automata->transitions[i][j]->size != 0)
				{
					free(load_automata->transitions[i][j]->values);
				}
				free(load_automata->transitions[i][j]);
			}
			free(load_automata->transitions[i]);
		}
		free(load_automata->transitions);
	}

	if (load_automata->states.size > 0)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_automata->inverse_transitions[i][j]->size != 0)
				{
					free(load_automata->inverse_transitions[i][j]->values);
				}
				free(load_automata->inverse_transitions[i][j]);
			}
			free(load_automata->inverse_transitions[i]);
		}
		free(load_automata->inverse_transitions);
	}


	if (load_automata->states.size > 0)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			if (load_automata->e_closure[i].size > 0)
			{
				free(load_automata->e_closure[i].values);
			}
		}
		free(load_automata->e_closure);
	}

	if (load_automata->marked.size > 0)
	{
		free(load_automata->marked.values);
	}

	if (load_automata->states.size > 0)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			free(load_automata->states.string[i]);
		}
		free(load_automata->states.string);
	}

	if (load_automata->events.size)
	{
		for (i = 0; i < load_automata->events.size; i++)
		{
			free(load_automata->events.string[i]);
		}
		free(load_automata->events.string);
	}

	resetAutomataStruct(load_automata);
}

void resetAutomataStruct(automato* load_automata)
{
	load_automata->states.size = 0;
	load_automata->events.size = 0;
	load_automata->marked.size = 0;
	load_automata->initial = 0;
	load_automata->transitions = NULL;
	load_automata->inverse_transitions = NULL;
	load_automata->e_closure = NULL;
	load_automata->null_event = 0;
	load_automata->deterministic = 0;
}

void freeDfa(dfa* load_dfa, automato* load_automata)
{
	freeDfaStructure(load_dfa, load_automata);
	free(load_dfa);
}

void freeDfaStructure(dfa* load_dfa, automato* load_automata)
{
	int i = 0, j = 0;
	if (load_dfa->dfa_states_size > 0)
	{
		if (load_automata->null_event == 1)
		{
			for (i = 0; i < load_dfa->dfa_states_size; i++)
			{

				for (j = 1; j < load_automata->events.size; j++)
				{
					if (load_dfa->transitions_table[i][j].size != 0)
					{
						free(load_dfa->transitions_table[i][j].values);
					}

				}
				free(load_dfa->transitions_table[i]);
			}

		}

		else
		{
			for (i = 0; i < load_dfa->dfa_states_size; i++)
			{
				for (j = 0; j < load_automata->events.size; j++)
				{
					if (load_dfa->transitions_table[i][j].size != 0)
					{
						free(load_dfa->transitions_table[i][j].values);
					}

				}
				free(load_dfa->transitions_table[i]);
			}

		}
		free(load_dfa->transitions_table);
	}



	if (load_dfa->dfa_states_size > 0)
	{
		for (i = 0; i < load_dfa->dfa_states_size; i++)
		{
			if (load_dfa->dfa_states[i].size > 0)
			{
				free(load_dfa->dfa_states[i].values);
			}
		}
		free(load_dfa->dfa_states);
	}

	resetDfaStructure(load_dfa);
}

dfa* newDfa()
{
	dfa* new_dfa;
	new_dfa = (dfa*)malloc(sizeof(dfa));
	resetDfaStructure(new_dfa);
	return new_dfa;
}


void resetDfaStructure(dfa* load_dfa)
{
	load_dfa->transitions_table = NULL;
	load_dfa->dfa_states = NULL;
	load_dfa->dfa_states_size = 0;
}


//rewrites the automata case it's needed 
void rewriteAutomata(automato* load_automata, int* valid_states)
{
	int i = 0, j = 0, x = 0, z = 0;

	x = x + strlen("STATES\r\n");
	char* new_automata_info;
	int* valid_events;

	valid_events = (int*)malloc(sizeof(int)*load_automata->events.size);
	for (i = 0; i < load_automata->events.size; i++)
	{
		valid_events[i] = 0;
	}

	new_automata_info = malloc(x);

	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcpy(new_automata_info, "STATES\r\n\0");
	//strcat(new_automata_info, "\0");
	for (i = 0; i < load_automata->states.size; i++)
	{
		if (valid_states[i] == 1)
		{
			x = x + strlen(load_automata->states.string[i]) + strlen("\r\n") + 2;
			new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
			strcat(new_automata_info, load_automata->states.string[i]);
			strcat(new_automata_info, "\0");
			strcat(new_automata_info, "\r\n\0");
		}
	}

	x = x + strlen("EVENTS\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "EVENTS\r\n\0");


	for (i = 0; i < load_automata->events.size; i++)
	{
		for (j = 0; j < load_automata->states.size; j++)
		{
			if (valid_states[j] == 1)
			{
				if (load_automata->transitions[j][i]->size != 0)
				{
					valid_events[i] = 1;
					break;
				}
			}
		}
	}





	if (load_automata->null_event == 1)
	{
		for (i = 1; i < load_automata->events.size; i++)
		{
			if (valid_events[i] == 1)
			{
				x = x + strlen(load_automata->events.string[i]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->events.string[i]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
		}
	}
	else
	{
		for (i = 0; i < load_automata->events.size; i++)
		{
			if (valid_events[i] == 1)
			{
				x = x + strlen(load_automata->events.string[i]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->events.string[i]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
		}
	}


	x = x + strlen("TRANSITIONS\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "TRANSITIONS\r\n\0");


	for (i = 0; i < load_automata->states.size; i++)
	{
		if (valid_states[i] == 1)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_automata->transitions[i][j]->size != 0)
				{
					for (z = 0; z < load_automata->transitions[i][j]->size; z++)
					{

						if (valid_states[load_automata->transitions[i][j]->values[z]] == 1)
						{
							x = x + strlen(load_automata->states.string[i]) + strlen(";") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[i]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, ";\0");

							x = x + strlen(load_automata->events.string[j]) + strlen(";") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->events.string[j]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, ";\0");

							x = x + strlen(load_automata->states.string[load_automata->transitions[i][j]->values[z]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_automata->transitions[i][j]->values[z]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, "\r\n\0");
						}
					}
				}
			}
		}
	}

	x = x + strlen("INITIAL\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "INITIAL\r\n\0");

	x = x + strlen(load_automata->states.string[load_automata->initial]) + strlen("\r\n") + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, load_automata->states.string[load_automata->initial]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "\r\n\0");


	x = x + strlen("MARKED\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "MARKED\r\n\0");


	for (i = 0; i < load_automata->marked.size; i++)
	{
		for (j = 0; j < load_automata->states.size; j++)
		{
			if ((load_automata->states.string[j] == load_automata->states.string[load_automata->marked.values[i]]) && valid_states[j] == 1)
			{
				x = x + strlen(load_automata->states.string[load_automata->marked.values[i]]) + strlen("\r\n") + 2;
				strcat(new_automata_info, load_automata->states.string[load_automata->marked.values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
		}
	}
	FILE* fp;
	fp = fopen("new_aut.aut", "w");
	fprintf(fp, new_automata_info);
	freeData(load_automata);
	parser(load_automata, new_automata_info);
	fclose(fp);
	free(new_automata_info);
	free(valid_events);
}



void writeDfaAutomata(automato* load_automata, dfa* load_dfa)
{
	int i = 0, j = 0, x = 0, z = 0, y = 0, k = 0;

	x = x + strlen("STATES\r\n");
	char* new_automata_info;
	new_automata_info = malloc(x);

	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcpy(new_automata_info, "STATES\r\n\0");

	for (i = 0; i < load_dfa->dfa_states_size; i++)
	{
		for (j = 0; j < load_dfa->dfa_states[i].size; j++)
		{
			if (load_dfa->dfa_states[i].size == 1)
			{
				x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
			else
			{
				if (j == load_dfa->dfa_states[i].size - 1)
				{
					x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("_") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "\r\n\0");
				}
				else
				{
					x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("_") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "_\0");

				}
			}
		}
	}

	x = x + strlen("EVENTS\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "EVENTS\r\n\0");
	if (load_automata->null_event == 1)
	{
		for (i = 1; i < load_automata->events.size; i++)
		{
			x = x + strlen(load_automata->events.string[i]) + strlen("\r\n") + 2;
			new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
			strcat(new_automata_info, load_automata->events.string[i]);
			strcat(new_automata_info, "\0");
			strcat(new_automata_info, "\r\n\0");
		}
	}
	else
	{
		for (i = 0; i < load_automata->events.size; i++)
		{
			x = x + strlen(load_automata->events.string[i]) + strlen("\r\n") + 2;
			new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
			strcat(new_automata_info, load_automata->events.string[i]);
			strcat(new_automata_info, "\0");
			strcat(new_automata_info, "\r\n\0");
		}
	}


	x = x + strlen("TRANSITIONS\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "TRANSITIONS\r\n\0");

	for (i = 0; i < load_dfa->dfa_states_size; i++)
	{
		if (load_automata->null_event == 1)
		{
			for (j = 1; j < (load_automata)->events.size; j++)
			{
				if (load_dfa->transitions_table[i][j].size != 0)
				{
					for (z = 0; z < load_dfa->dfa_states[i].size; z++)
					{
						if (load_dfa->dfa_states[i].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, ";\0");
						}
						else
						{
							if (z == load_dfa->dfa_states[i].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(";") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ";\0");
							}
							else
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen("_") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "_\0");

							}
						}
					}

					x = x + strlen(load_automata->events.string[j]) + strlen(";") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->events.string[j]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, ";\0");

					z = 0;
					z = load_dfa->transitions_table[i][j].values[0];
					for (y = 0; y < load_dfa->dfa_states[z].size; y++)
					{
						if (load_dfa->dfa_states[z].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, "\r\n\0");
						}
						else
						{
							if (y == load_dfa->dfa_states[z].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "\r\n\0");
							}
							else
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("_") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "_\0");
							}
						}
					}

				}
			}
		}
		else
		{
			for (j = 0; j < (load_automata)->events.size; j++)
			{
				if (load_dfa->transitions_table[i][j].size != 0)
				{
					for (z = 0; z < load_dfa->dfa_states[i].size; z++)
					{
						if (load_dfa->dfa_states[i].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, ";\0");
						}
						else
						{
							if (z == load_dfa->dfa_states[i].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(";") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ";\0");
							}
							else
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen("_") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "_\0");

							}
						}
					}

					x = x + strlen(load_automata->events.string[j]) + strlen(";") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->events.string[j]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, ";\0");

					z = 0;
					z = load_dfa->transitions_table[i][j].values[0];
					for (y = 0; y < load_dfa->dfa_states[z].size; y++)
					{
						if (load_dfa->dfa_states[z].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, "\r\n\0");
						}
						else
						{
							if (y == load_dfa->dfa_states[z].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "\r\n\0");
							}
							else
							{
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("_") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "_\0");
							}
						}
					}

				}
			}
		}
	}

	x = x + strlen("INITIAL\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "INITIAL\r\n\0");
	for (i = 0; i < (load_dfa->dfa_states[0].size); i++)
	{
		if (load_dfa->dfa_states[0].size == 1)
		{
			x = x + strlen(load_automata->states.string[load_dfa->dfa_states[0].values[i]]) + strlen("\r\n") + 2;
			new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
			strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[0].values[i]]);
			strcat(new_automata_info, "\0");
			strcat(new_automata_info, "\r\n\0");
		}
		else
		{
			if (i == load_dfa->dfa_states[0].size - 1)
			{
				x = x + strlen(load_automata->states.string[load_dfa->dfa_states[0].values[i]]) + strlen("_") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[0].values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");

			}
			else
			{
				x = x + strlen(load_automata->states.string[load_dfa->dfa_states[0].values[i]]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[0].values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "_\0");
			}
		}
	}

	x = x + strlen("MARKED\r\n");
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char) + 1);
	strcat(new_automata_info, "MARKED\r\n\0");
	int marked = 0;
	for (i = 0; i < load_dfa->dfa_states_size; i++)
	{
		for (j = 0; j < load_automata->marked.size; j++)
		{
			if (findItemIntVector(load_dfa->dfa_states[i], load_automata->marked.values[j]) != load_dfa->dfa_states[i].size)
			{
				marked++;
				continue;
			}
		}
		if (marked != 0)
		{
			marked = 0;
			for (j = 0; j < load_dfa->dfa_states[i].size; j++)
			{
				if (load_dfa->dfa_states[i].size == 1)
				{
					x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("\r\n") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "\r\n\0");
				}
				else
				{
					if (j == load_dfa->dfa_states[i].size - 1)
					{
						x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("_") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
					else
					{
						x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("_") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "_\0");

					}
				}
			}
		}
	}
	FILE* fp;
	fp = fopen("new_aut.aut", "w");
	fprintf(fp, new_automata_info);
	freeDfa(load_dfa, load_automata);
	freeData(load_automata);
	parser(load_automata, new_automata_info);
	fclose(fp);
	free(new_automata_info);
}



//check if a state is accessible or not. if it is, the reached state will be accessible
void accesibleState(automato* load_automata, int state_index, int *accessible_states)
{
	int i = 0, j = 0, x = 0;

	for (i = 0; i < load_automata->events.size; i++)
	{
		if (load_automata->transitions[state_index][i]->size != 0)
		{
			for (x = 0; x < load_automata->transitions[state_index][i]->size; x++)
			{
				accessible_states[load_automata->transitions[state_index][i]->values[x]] = 1;
			}
		}
	}
}

void coaccesibleState(automato* load_automata, int state_index, int *coaccessible_states)
{
	int i = 0, j = 0, x = 0;

	for (i = 0; i < load_automata->events.size; i++)
	{
		if (load_automata->inverse_transitions[state_index][i]->size != 0)
		{
			for (x = 0; x < load_automata->inverse_transitions[state_index][i]->size; x++)
			{
				coaccessible_states[load_automata->inverse_transitions[state_index][i]->values[x]] = 1;
			}
		}
	}
}


//parser for the automatata
void parser(automato* load_automata, char* file_info)
{
	//private initializations 
	char* line;
	line = (char*)malloc(1);
	int  parser_state = 0, i = 0, index = 0, j = 0, x = 0, y = 0, z = 0, initial_test = 0;
	char* trs_line;
	trs_line = (char*)malloc(1);
	int trs_index = 0;
	int second_trs_state_index = 0, trs_event_index = 0, trs_state_index = 0;
	int inv_trs_index = 0, trs_test = 0;

	nullEventSearcher(load_automata, file_info);

	//split the automata's read file with each paragraph and search for each states, events, etc
	while (splitString(file_info, &line, &index, '\n'))
	{
		//each line is compared to predefined strings
		//continue is used to force the next iteration
		if (strcmp(line, "STATES") == 0)
		{
			parser_state = 1;
			continue;
		}

		if (strcmp(line, "EVENTS") == 0)
		{
			parser_state = 2;
			continue;
		}

		if (strcmp(line, "TRANSITIONS") == 0)
		{
			parser_state = 3;
			continue;
		}

		if (strcmp(line, "INITIAL") == 0)
		{
			parser_state = 4;
			continue;
		}

		if (strcmp(line, "MARKED") == 0)
		{
			parser_state = 5;
			continue;
		}

		//depending on the value of the parser in each iteration, there will be a case
		switch (parser_state)
		{

			//state case
		case 1:
			stringPushBack(&(load_automata->states), line);
			break;

			//event case
		case 2:
			stringPushBack(&(load_automata->events), line);
			break;

			//transition case
		case 3:
			trs_index = 0;
			int i = 0, j = 0;

			//memory allocation for the transitions (triple pointer)
			if (load_automata->transitions == NULL)
			{
				//memory allocation for the double pointer, poiting to a pointer
				load_automata->transitions = (int_vector***)malloc(sizeof(int_vector**)*(load_automata->states.size));
				for (i = 0; i < load_automata->states.size; i++)
				{
					load_automata->transitions[i] = (int_vector**)malloc(sizeof(int_vector*)*(load_automata->events.size));
					for (j = 0; j < load_automata->events.size; j++)
					{
						load_automata->transitions[i][j] = (int_vector*)malloc(sizeof(int_vector));
						load_automata->transitions[i][j]->size = 0;
					}
				}
			}

			if (load_automata->inverse_transitions == NULL)
			{
				//memory allocation for the double pointer, poiting to a pointer
				load_automata->inverse_transitions = (int_vector***)malloc(sizeof(int_vector**)*(load_automata->states.size));
				for (i = 0; i < load_automata->states.size; i++)
				{
					load_automata->inverse_transitions[i] = (int_vector**)malloc(sizeof(int_vector*)*(load_automata->events.size));
					for (j = 0; j < load_automata->events.size; j++)
					{
						load_automata->inverse_transitions[i][j] = (int_vector*)malloc(sizeof(int_vector));
						load_automata->inverse_transitions[i][j]->size = 0;
					}
				}
			}

			//transitions will only happen with 2 states and one event
			for (i = 0; i != 3; i++)
			{
				//transitions made correctly
				if (splitString(line, &trs_line, &trs_index, ';') == false)
				{
					printf("Invalid transition in file. Correct this transition:\n\nPress enter to continue");
					puts(line);

					getchar();
					exit(0);
				}

				//when it's not an event
				if (i == 0)
				{

					//confirm if there are states in the transitions vector
					trs_state_index = findItemStringVector(trs_line, load_automata->states);
					if (trs_state_index == load_automata->states.size)
					{
						printf("Invalid state being used on the transition. Correct this transition:\n\nPress enter to continue");
						puts(line);
						getchar();
						exit(0);
					}
				}
				if (i == 2)
				{

					//confirm if there are states in the transitions vector
					second_trs_state_index = findItemStringVector(trs_line, load_automata->states);
					if (second_trs_state_index == load_automata->states.size)
					{
						printf("Invalid state being used on the transition. Correct this transition:\n\nPress enter to continue");
						puts(line);
						getchar();
						exit(0);
					}
				}
				if (i == 1)
				{

					trs_event_index = findItemStringVector(trs_line, load_automata->events);
					if (trs_event_index == load_automata->events.size)
					{
						printf("Invalid event being used on the transition. Correct this transition:\n\nPress enter to continue");
						puts(line);
						getchar();
						exit(0);
					}
				}

			}
			if (load_automata->transitions[trs_state_index][trs_event_index]->size !=0)
			{
				for (i = 0; i < load_automata->transitions[trs_state_index][trs_event_index]->size; i++)
				{
					if (load_automata->transitions[trs_state_index][trs_event_index]->values[i] == second_trs_state_index)
						trs_test++;
				}
				if (trs_test != load_automata->transitions[trs_state_index][trs_event_index]->size)
				{
					intVectPushBack(load_automata->transitions[trs_state_index][trs_event_index], second_trs_state_index);
					intVectPushBack(load_automata->inverse_transitions[second_trs_state_index][trs_event_index], trs_state_index);
				}
				trs_test = 0;
			}
			
			else
			{
				intVectPushBack(load_automata->transitions[trs_state_index][trs_event_index], second_trs_state_index);
				intVectPushBack(load_automata->inverse_transitions[second_trs_state_index][trs_event_index], trs_state_index);
			}
			
			break;

		case 4:


			for (j = 0; j < load_automata->states.size; j++)
			{
				if (strcmp(line, load_automata->states.string[j]) == 0)
				{
					load_automata->initial = j;
					initial_test++;
				}
			}

			if (initial_test >1)
			{
				printf("More than one initial state. Press enter to continue!");
				getchar();
				exit(0);
			}



			break;

		case 5:

			for (x = 0; x < load_automata->states.size; x++)
			{
				if (strcmp(line, load_automata->states.string[x]) == 0)
				{
					intVectPushBack(&(load_automata->marked), x);
				}
			}
			break;

		default:
			printf("\nParser error!Automata's file not correct!\n\nPress enter to continue");
			getchar();
			exit(0);
		}
	}

	free(line);
	free(trs_line);

	if (load_automata->states.size == 0)
	{
		printf("There are no states in the automata!\n\nPress enter to continue");
		getchar();
		exit(0);
	}

	if (load_automata->events.size == 0)
	{
		printf("There are no events in the automata!\n\nPress enter to continue");
		getchar();
		exit(0);
	}

	if (load_automata->marked.size == 0)
	{
		printf("There are no marked states in the automata\n\nPress enter to continue");
		getchar();
		exit(0);
	}


	if (initial_test == 0)
	{
		printf("There is no initial state in this automata!\n\nPress enter to continue");
		getchar();
		exit(0);
	}



	load_automata->e_closure = (int_vector*)malloc(sizeof(int_vector)*((load_automata)->states.size));
	for (i = 0; i < load_automata->states.size; i++)
	{
		load_automata->e_closure[i].size = 0;
		intVectPushBack(&(load_automata->e_closure[i]), i);
	}

	if (load_automata->null_event == 1)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			eclosureFilling(load_automata, i, i);
		}
	}


	for (i = 0; i < (load_automata)->states.size; i++)
	{
		if (load_automata->e_closure[i].size > 1)
		{
			sortArrayAscending(&(load_automata)->e_closure[i]);
		}
	}
}

//delete a character (ignores the selected characters)
void deleteCharacter(char* str, char c)
{
	char *pr = str, *pw = str;
	while (*pr) {
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

//search for the null event
void nullEventSearcher(automato* load_automata, char* file_info)
{
	deleteCharacter(file_info, ' ');
	if (strstr(file_info, ";;") != NULL)
	{
		stringPushBack(&(load_automata->events), "");
		load_automata->null_event = 1;
	}
	else
		load_automata->null_event = 0;
}

//print in console in a tidy way for string_type
void writeStringVectorInConsole(string_vector* string_vect)
{
	int i = 0;
	for (i = 0; i <string_vect->size; i++)
	{
		if (string_vect->size > 1)
		{
			if (i == 0)
			{
				printf("(%s,", string_vect->string[i]);
			}
			if (i > 0 && i < (string_vect->size - 1))
			{
				printf("%s,", string_vect->string[i]);
			}
			if (i == (string_vect->size - 1))
			{
				printf("%s)\n\n", string_vect->string[i]);
			}
		}
		else
			printf("(%s)\n\n", string_vect->string[i]);
	}
}

//print in console in a tidy way for int_vector type
void writeIntVectorInConsole(int_vector* vector, string_vector* string_vect)
{
	int i = 0;
	for (i = 0; i < vector->size; i++)
	{
		if (vector->size > 1)
		{
			if (i == 0)
			{
				printf("(%s,", string_vect->string[vector->values[i]]);
			}

			if (i > 0 && i < ((vector->size) - 1))
			{
				printf("%s,", string_vect->string[vector->values[i]]);
			}

			if (i == ((vector->size) - 1))
			{
				printf("%s)\n\n", string_vect->string[vector->values[i]]);
			}
		}
		else printf("(%s)\n\n", string_vect->string[vector->values[i]]);
	}
}

//push back to allocate memory in vector type
void intVectPushBack(int_vector* vector, int item)
{
	if (vector->size == 0)
	{
		vector->values = (int_vector*)malloc(sizeof(int*));
	}
	vector->size++;
	vector->values = realloc(vector->values, sizeof(int*)*(vector->size));
	vector->values[vector->size - 1] = item;
}

//push back to allocate memory in string type
void stringPushBack(string_vector* char_vector, char* item)
{
	if (char_vector->size <= 0)
	{
		char_vector->string = (char**)malloc(sizeof(char*));
	}
	char_vector->size++;
	char_vector->string = realloc(char_vector->string, sizeof(char*)*(char_vector->size));
	char_vector->string[char_vector->size - 1] = (char*)malloc(sizeof(char)*strlen(item) + 1);
	strcpy(char_vector->string[char_vector->size - 1], item);
}



//function to split strings 
bool splitString(char* string_to_split, char** substring, int* index, char delimitator)
{
	int initial_index;

	initial_index = *index;

	if (string_to_split[*index] == '\0') {

		return false;
	}

	while (true)
	{
		if (string_to_split[*index] == delimitator)
		{
			*index += 1;
			break;
		}

		*index += 1;

		if (string_to_split[*index] == '\0') {
			break;
		}
	}

	if (string_to_split[*index] == '\0') {
		*substring = (char*)realloc(*substring, sizeof(char) * (*index - initial_index + 1));
		strncpy(*substring, (string_to_split + initial_index), (*index - initial_index + 1));
	}
	else
	{
		*substring = (char*)realloc(*substring, sizeof(char) * (*index - initial_index));
		strncpy(*substring, (string_to_split + initial_index), (*index - initial_index - 1));
		(*substring)[*index - initial_index - 1] = '\0';
	}

	deleteCharacter(*substring, '\r');
	deleteCharacter(*substring, '\n');

	return true;
}

//returns string size in case of failure. Else returns item index
int findItemStringVector(char* string, string_vector vect)
{
	int i = 0;

	for (i = 0; i != vect.size; i++)
	{
		if (strcmp(string, vect.string[i]) == 0)
			return i;
	}
	return i;
}

//returns intvector size in case of failure. Else returns item index
int findItemIntVector(int_vector myvect, int item)
{

	int i = 0;
	for (i = 0; i < myvect.size; i++)
	{
		if (item == myvect.values[i])
		{
			return i;
		}
	}
	return i;
}

void eclosureFilling(automato* load_automata, int original_index, int index_next)
{
	int i = 0, j = 0, value = 0, x = 0;

	if (original_index != index_next)
	{
		intVectPushBack(&(load_automata->e_closure[original_index]), index_next);
	}

	if (load_automata->transitions[index_next][0]->size != 0)
	{
		for (i = 0; i < load_automata->transitions[index_next][0]->size; i++)
		{
			if (findItemIntVector(load_automata->e_closure[original_index], load_automata->transitions[index_next][0]->values[i]) == load_automata->e_closure[original_index].size)
			{
				eclosureFilling(load_automata, original_index, load_automata->transitions[index_next][0]->values[i]);
			}
		}
	}
}

void sortArrayAscending(int_vector* array_to_sort)
{
	int i = 0, j = 0, min = 0, swap = 0, first = 0, second = 0;
	for (i = 0; i < (array_to_sort->size - 1); i++)
	{
		min = i;
		for (j = (i + 1); j < array_to_sort->size; j++)
		{
			first = array_to_sort->values[j];
			second = array_to_sort->values[min];
			if (second> first)
			{
				min = j;
			}
		}
		if (i != min) {
			swap = array_to_sort->values[i];
			array_to_sort->values[i] = array_to_sort->values[min];
			array_to_sort->values[min] = swap;
		}
	}
}

int findItemarray(int* array_to_search, int item, int array_size)
{
	int i = 0;
	for (i = 0; i < array_size; i++)
	{
		if (item == array_to_search[i])
		{
			return i;
		}
	}
	return i;
}