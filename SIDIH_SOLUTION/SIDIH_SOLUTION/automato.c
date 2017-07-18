#include "automato.h"

//----------------------------------------------------------private functions prototypes----------------------------------------------------------//


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
void rewriteAutomata(automato* load_automata, int* valid_states, int dfa_canonical);
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
void pairCreation(automato* load_automata, int_vector* pair);
int nCr(automato* load_automata);
int factorial(int number);
canonical* newCanonical();
void resetCanonicalStructure(canonical* load_canonical);
void freeCanonical(canonical* load_canonical, automato* load_automata);
void resetDfaStructure(dfa* load_dfa);
void freeCanonicalStructure(canonical* load_canonical, automato* load_automata);
void checkIfIsMarkedOnTable(automato* load_automata, canonical* load_canonical, int  pair_index, int y, int table_index, int pair_one, int pair_two);
void createCanonicalStates(automato* load_automata, canonical* load_canonical, int result_pair, int pair_1st_index, int pair_index);
void writeCanonicalAutomata(automato* load_automata, canonical* load_canonical);
int clean_stdin();
product* newProduct();
void resetProductStructure(product* load_product);
void productStatescreation(product* load_product, automato* load_automata1, automato* load_automata2, int product_state_index);
void freeProductStructure(product* load_product, automato* load_automata);
void freeProduct(product* load_product, automato* load_automata);
void writeProductAutomata(automata_array* automata_vector, automato* automata1, automato* automata2, product* load_product);
parallel* newParallel();
void resetParallelStructure(parallel* load_parallel);
void parallelStatescreation(parallel* load_parallel, automato* load_automata1, automato* load_automata2, int parallel_state_index);
void freeParallelStructure(parallel* load_parallel);
void freeParallel(parallel* load_parallel);
void writeParallelAutomata(automata_array* automata_vector, automato* automata1, automato* automata2, parallel* load_parallel);
automata_array* newAutomatonArray();
resetAutomataArrayStructure(automata_array* load_array);
void load_file(automato* load_automata, char* file_path);
void printAutomata(automato* load_automata);
void checkAccessibilty(automato* load_automata, int dfa_canonical);
void checkCoaccessibilty(automato* load_automata, int dfa_canonical);
void dfaOrNfa(automato* load_automata);
void nfaToDfa(automato* load_automata, int nda_or_da);
void freeAutomata(automato* load_automata);
void dfaCanonical(automato* load_automata);
void automataProduct(automata_array* automata_vector, automato* automata1, automato* automata2);
void automataParallel(automata_array* automata_vector, automato* automata1, automato* automata2);
void writeAutomataToFile(automato* load_automata);
void deleteAutomata(automata_array* automata_vector, string_vector* automata_name, int automata_to_delete);
automato* new_automata();


//----------------------------------------------------------private functions prototypes----------------------------------------------------------//




//----------------------------------------------------------------Public functions----------------------------------------------------------------//

//solution's menu called in the main function
void menu()
{
	int i = 0, j = 0, k = 0, z = 0, automata_to_load = 0, dummy = 0, automata1 = 0, automata2 = 0, dfa_canonical = 0;
	int count = 0;
	char c;
	char buffer[1000];
	i = 13;
	j = 0;
	automata_array* automata_vector;
	automata_vector = newAutomatonArray();
	

	while (1)
	{
		switch (i)
		{
		
		//invisible choice -> rewrite the menu
		
		case 0:
			printf("---------------------------------------------Finite automata implementation menu--------------------------------------\n\n");
			printf("1 - Load automaton \n");
			printf("2 - Print the automaton to the console\n");
			printf("3 - Check automaton accesibility\n");
			printf("4 - Check automaton coaccesibility\n");
			printf("5 - Check if the automaton is DFA or NFA\n");
			printf("6 - Convert the automaton if it is NFA\n");
			printf("7 - Convert the automaton to its canonical form\n");
			printf("8 - Automata product\n");
			printf("9 - Automata parallel\n");
			printf("10 - Write any automata to a file\n");
			printf("11 - Delete automata\n");
			printf("12 - Exit\n");
			printf("13 - Authors\n");
			printf("Default - the menu will be rewritten\n\n");
			printf("---------------------------------------------Finite automata implementation menu--------------------------------------\n\n");

		//wait for the user to insert a number (only numbers are accepted)
			
			while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin())
			{

				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
				break;
			}

			break;

		
		//first option of the menu -> load an automaton
		
		case 1:
		
		//if the automata array doesn't have any automaton, allocate memory and load the file
			
			if (automata_vector->automata_number == 0)
			{
				automata_vector->automata = (automato**)malloc(sizeof(automato*));
				automata_vector->automata[automata_vector->automata_number] = new_automata();
		
		//ask the user to write the file path

				printf("Write the file path\n\n");
				scanf("%s", buffer);
				getchar();
				load_file(automata_vector->automata[automata_vector->automata_number], buffer);
				stringPushBack(&(automata_vector->automata_name), buffer);
				memset(buffer, 0, 1000);
				automata_vector->automata_number++;
				
		//if the inserted automaton hasn't pass the parser succesfully, it will be deleted
				
				if (automata_vector->automata[automata_vector->automata_number - 1]->error == 1)
				{
					printf("The automata was not correctly loaded! Press any key to return to the menu\n\n");
					getchar();
					automata_vector->automata[automata_vector->automata_number - 1]->error = 0;
					deleteAutomata(automata_vector,  &(automata_vector->automata_name), (automata_vector->automata_number - 1));
					i = 0;
					break;
				}
				k = 1;


			}
		
		//if there are automaton already in memory
			
			else
			{

				printf("Write the file path\n\n");
				scanf("%s", buffer);
				getchar();
		

		//-----------avoid repeatead automaton-----------//

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
						dummy = 1;
				}
				if (dummy == 1)
				{
					dummy = 0;
					printf("\n\nThis automata has already been loaded! Press enter to continue! \n\n");
					while (getchar() != '\n');
					i = 0;
					do
					{
						j++;
						printf("\n");
					} while (j != 10);
					j = 0;
					break;
				}

		//-----------avoid repeatead automaton-----------//
		

		//if it isn't, add it to the automata's array
				else
				{
					automata_vector->automata = (automato**)realloc(automata_vector->automata, sizeof(automato*)*(automata_vector->automata_number + 1));
					automata_vector->automata[automata_vector->automata_number] = new_automata();
					load_file(automata_vector->automata[automata_vector->automata_number], buffer);
					stringPushBack(&(automata_vector->automata_name), buffer);
					memset(buffer, 0, 1000);
					automata_vector->automata_number++;
					
		//if the inserted automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata_vector->automata_number - 1]->error == 1)
					{
						printf("The automata was not correctly loaded! Press any key to return to the menu\n\n");
						getchar();
						automata_vector->automata[automata_vector->automata_number - 1]->error = 0;
						deleteAutomata(automata_vector, &(automata_vector->automata_name), automata_vector->automata_number - 1);
						i = 0;
						break;
					}
					k = 1;

				}
			}

		//otherwise, this message will be printed

			printf("\n\nAutomata loaded! Press enter to continue! \n\n");
			while (getchar() != '\n');
			i = 0;
			do
			{
				j++;
				printf("\n");
			} while (j != 10);
			j = 0;
			break;


		//second option -> write a selected automaton in the console 

		case 2:

		//if there aren'y automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to print in the console 

			else
			{
				printf("\nWhich automata do you wish to print? Available automata:\n\n");
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}

		//if the inserted automaton is valid, it will be printed
				
				memset(buffer, 0, 1000);
				if (dummy == 1)
				{
					dummy = 0;
					printAutomata(automata_vector->automata[automata_to_load]);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');

				}

		//otherwise a warning will be written in the console
				
				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					while (getchar() != '\n');
				}

				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			i = 0;
			break;

		//third option -> check automaton's accessibility

		case 3:

		//if there aren'y automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to check accessibility

			else
			{
				printf("\nWhich automata do you wish to test accessibility? Available automata:\n\n");

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//if the inserted automaton is valid, checkAccesibilty function will be called
		//in order to the user see the changes caused by this function

				if (dummy == 1)
				{
					dummy = 0;
					printf("\n");
					checkAccessibilty(automata_vector->automata[automata_to_load], 0);

		//if the resulting automaton didn't pass the parser, it will be removed from the array
					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}
				else

		//otherwise a warning will be written in the console

				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}


				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			break;

		//fourth option in the menu -> checkcoaccessibilty, the same procedure as the 3rd option

		case 4:

		//if there aren'y automatons in memory write a warning in the console


			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to check coaccessibility

			else
			{

		//if the inserted automaton is valid, checkAccesibilty function will be called with 2nd argument 0
		//in order to the user see the changes caused by this function

				printf("Which automata do you wish to test the coaccessibility? Available automata:\n\n");
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);
				if (dummy == 1)
				{
					dummy = 0;
					checkCoaccessibilty(automata_vector->automata[automata_to_load], 0);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}
				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			break;

		//fith option in the menu -> check if the automaton is DFA or NFA

		case 5:

		//if there aren'y automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}
			else
			{

		//otherwise the user chooses what automaton he wants to check if it is NFA or DFA

				printf("Which automata do you wish to test if it is deterministic or not? Available automata:\n\n");
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//if the inserted automaton is valid, dfaOrNfa function will be called 

				if (dummy == 1)
				{
					dummy = 0;


					dfaOrNfa(automata_vector->automata[automata_to_load]);
					
		//if the resulting automaton didn't pass the parser, it will be removed from the array
					
					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}

					if (automata_vector->automata[automata_to_load]->deterministic == 1)
					{
						printf("\n\nThe automata is deterministic!\n\n");
					}
					else
					{
						printf("\n\nThe automata is not deterministic!\n\n");
					}

					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}


		//otherwise a warning will be written in the console

				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			break;

		//sixth option -> convert NFA to DFA

		case 6:

		//if there aren'y automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to convert from NFA to DFA

			else
			{
				printf("\nWhich automata do you wish to convert? Available automata:\n\n");

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//if the inserted automaton is valid, dfaOrNfa function will be called

				if (dummy == 1)
				{
					dummy = 0;

					dfaOrNfa(automata_vector->automata[automata_to_load]);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}

					if (automata_vector->automata[automata_to_load]->deterministic == 0)
					{
						nfaToDfa(automata_vector->automata[automata_to_load], automata_vector->automata[automata_to_load]->deterministic);
					}
					else
						printf("\n\nThe automata is already deterministic!\n\n");

					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

		//otherwise a warning will be written in the console

				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			break;



		case 7:

		//if there aren't automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
				i = 0;
			}

		//otherwise the user chooses what automaton he wants to convert to the canonical form

			else
			{
				printf("\nWhich automata do you wish to convert to the canonical form? Available automata:\n\n");

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//1st step: if the inserted automaton is valid, first step of the algorithm is to check if it's NFA or DFA

				if (dummy == 1)
				{
					dummy = 0;

					dfaOrNfa(automata_vector->automata[automata_to_load]);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}

		//if it is NFA a warning will be displayed and will leave this menu section


					if (automata_vector->automata[automata_to_load]->deterministic == 0)
					{
						printf("The automata is NFA, try to convert it first to DFA!\n\n Press any key to return to menu\n");
						getchar();
						break;
					}

		// 2nd step : otherwise the automaton's accessibility will be checked, unreachable states removed, without the changes being shown
		//at the console (because of the 2nd argument having the value 1)

					checkAccessibilty(automata_vector->automata[automata_to_load], 1);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata_to_load]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata_to_load]->error = 0;
						deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
						i = 0;
						break;
					}

		//finally the dfaCanonical is called 

					dfaCanonical(automata_vector->automata[automata_to_load]);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}


		//otherwise a warning will be written in the console

				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}


				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}
			break;



		//seventh option -> product between two automatons

		case 8:
			dummy = 0;

		//if there aren't automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
				i = 0;
			}

		//otherwise the user will choose the first automaton for the product

			else
			{
				printf("\nWhich automatas do you wish to do a product? Available automata:\n\n");

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				printf("First automata:\n\n");
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata1 = z;
					}
				}
				memset(buffer, 0, 1000);

		//otherwise a warning will be written in the console

				if (dummy == 0)
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
					i = 0;
					do
					{
						j++;
						printf("\n");
					} while (j != 10);
					j = 0;
					break;
				}

		//and then, the 2nd automaton

				dummy = 0;
				printf("\nSecond automata:\n\n");
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata2 = z;
					}
				}
				memset(buffer, 0, 1000);

		//otherwise a warning will be written in the console

				if (dummy == 0)
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
					i = 0;
					do
					{
						j++;
						printf("\n");
					} while (j != 10);
					j = 0;
					break;
				}


		//if both automata are valid, checkAccesibilty function will be called with 2nd argument 1
		//in order to the user to not see the changes caused by this function, in both automatons

				if (dummy == 1)
				{

					checkAccessibilty(automata_vector->automata[automata1], 1);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata1]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata1]->error = 0;
						deleteAutomata(automata_vector, &(automata_vector->automata_name), automata1);
						i = 0;
						break;
					}

					checkAccessibilty(automata_vector->automata[automata2], 1);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata2]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata2]->error = 0;
						deleteAutomata(automata_vector, &(automata_vector->automata_name), automata2);
						i = 0;
						break;
					}


		//finally, the function automataProduct is called, to make the composition of the inserted automata

					automataProduct(automata_vector ,automata_vector->automata[automata1], automata_vector->automata[automata2]);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}
			}
			i = 0;
			do
			{
				j++;
				printf("\n");
			} while (j != 10);
			j = 0;

			break;



		//eigth option -> parallel of automata

		case 9:

			dummy = 0;

		//if there aren't automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
				i = 0;
			}
			else
			{
				printf("\nWith which automaton do you wish to do a parallel? Available automata:\n\n");

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}

		//otherwise the user will choose the first automaton for the product

				printf("First automata:\n\n");
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata1 = z;
					}
				}

		//if it's not valid a warning will be written in the console
				memset(buffer, 0, 1000);
				if (dummy == 0)
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
					i = 0;
					do
					{
						j++;
						printf("\n");
					} while (j != 10);
					j = 0;
					break;
				}

		//and then, the 2nd automaton

				dummy = 0;
				printf("\nSecond automata:\n\n");
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata2 = z;
					}
				}
				memset(buffer, 0, 1000);

		//if it's not valid a warning will be written in the console

				if (dummy == 0)
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
					i = 0;
					do
					{
						j++;
						printf("\n");
					} while (j != 10);
					j = 0;
					break;
				}


		//if both automata are valid, checkAccesibilty function will be called with 2nd argument 1
		//in order to the user to not see the changes caused by this function, in both automatons

				if (dummy == 1)
				{

					checkAccessibilty(automata_vector->automata[automata1], 1);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata1]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata1]->error = 0;
						deleteAutomata(automata_vector, &(automata_vector->automata_name), automata1);
						i = 0;
						break;
					}


					checkAccessibilty(automata_vector->automata[automata2], 1);

		//if the resulting automaton didn't pass the parser, it will be removed from the array

					if (automata_vector->automata[automata2]->error == 1)
					{
						printf("Press any key to return to the main menu\n\n");
						getchar();
						automata_vector->automata[automata2]->error = 0;
						deleteAutomata(automata_vector, &(automata_vector->automata_name), automata2);
						i = 0;
						break;
					}

		//finally, the function automataParallel is called, to make the composition of the inserted automata

					automataParallel(automata_vector ,automata_vector->automata[automata1], automata_vector->automata[automata2]);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}
			}
			i = 0;
			do
			{
				j++;
				printf("\n");
			} while (j != 10);
			j = 0;

			break;

		//ninth option -> save a given automaton in a file

		case 10:

		//if there aren't automatons in memory write a warning in the console

			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to save in a file

			else
			{
				printf("\nWhich automata do you wish to print to a file? Available automata:\n\n");
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}

				scanf("%s", buffer);
				getchar();

				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//if the inserted automaton is valid, writeAutomataToFile function will be called 

				if (dummy == 1)
				{
					dummy = 0;
					writeAutomataToFile(automata_vector->automata[automata_to_load]);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

		//otherwise a warning will be written in the console

				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					while (getchar() != '\n');
				}
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}
			i = 0;
			break;


		//tenth option -> delete a given automaton

		case 11:

		//if there aren't automatons in memory write a warning in the console


			if (automata_vector->automata_number == 0)
			{
				printf("\n\nNo automata has been loaded yet! Press enter to continue! \n\n");
				while (getchar() != '\n');
				i = 0;
				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

		//otherwise the user chooses what automaton he wants to delete

			else
			{
				printf("\nWhich automata do you wish to delete? Available automata:\n\n");
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					printf("%s\n\n", automata_vector->automata_name.string[z]);
				}
				scanf("%s", buffer);
				getchar();
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					if (strcmp(buffer, automata_vector->automata_name.string[z]) == 0)
					{
						dummy = 1;
						automata_to_load = z;
					}
				}
				memset(buffer, 0, 1000);

		//if the inserted automaton is valid, deleteAutomata function will be called 

				if (dummy == 1)
				{
					dummy = 0;
					deleteAutomata(automata_vector,  &(automata_vector->automata_name), automata_to_load);
					printf("\n\nPress enter to procede to the menu!\n");
					while (getchar() != '\n');
				}

		//otherwise a warning will be written in the console

				else
				{
					printf("\n\nInvalid automata was written, try again!\n\n");
					while (getchar() != '\n');
				}

				do
				{
					j++;
					printf("\n");
				} while (j != 10);
				j = 0;
			}

			i = 0;
			break;


		//eleventh option -> exit the program freeing the memory

		case 12:

			if (automata_vector->automata_number > 0)
			{
				for (z = 0; z < automata_vector->automata_number; z++)
				{
					freeAutomata(automata_vector->automata[z]);
				}
				free(automata_vector->automata);

				if (automata_vector->automata_name.size != 0)
				{
					for (z = 0; z < automata_vector->automata_name.size; z++)
					{
						free(automata_vector->automata_name.string[z]);
					}
					free(automata_vector->automata_name.string);
					automata_vector->automata_name.size = 0;
				}
				
			}
			free(automata_vector);
			return;
			break;


		//twelfth option -> writing the authors' names in the console

		case 13:
			do
			{
				j++;
				printf("\n");
			} while (j != 10);
			j = 0;
			printf("                                             --------SIDIH PROJECT--------                                             \n\n                                                        made by                                                       \n\n                                                  1130625 Nuno Viana                                                  \n                                                  1130691 Pedro Guedes                                                  \n                                                       2016/2017                                                  \n\n                                             -----------------------------                                             ");
			do
			{
				i++;
			} while (i != 1000000000);
			i = 0;
			printf("\n");
			do
			{
				for (i = 0; i < 100000000; i++)
				{

				}
				j++;
				printf("                                                    \n");
			} while (j != 30);
			i = 0;
			j = 0;

			break;
		default:
			i = 0;
			do
			{
				j++;
				printf("\n");
			} while (j != 10);
			j = 0;
			break;
		}
	}
}

//----------------------------------------------------------------Public functions----------------------------------------------------------------//





//----------------------------------------------------------------Private functions----------------------------------------------------------------//

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
		load_automata->error = 1;
		return;
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

	if (load_automata->transitions != NULL)
	{
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
	}

	printf("\n\n");

	printf("Initial\n");
	printf("Xinit=%s\n\n", load_automata->states.string[load_automata->initial]);

	printf("Marked\n");
	printf("Xmarked=");
	writeIntVectorInConsole(&(load_automata->marked), &(load_automata->states));

	if (load_automata->e_closure != NULL)
	{
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
}

//check accessibility of a state and delete those that aren't accessible
void checkAccessibilty(automato* load_automata, int dfa_canonical)
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
		load_automata->error = 1;
		return;
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
		if (dfa_canonical == 0)
		{
			printf("-----------The automata had non-accessible states. They are going to be removed-----------\n\n\n");
			printf("Removed states:\n");
			for (i = 0; i < load_automata->states.size; i++)
			{
				if (accessible_states[i] == 0)
					printf("%s \n", load_automata->states.string[i]);
			}
		}

		rewriteAutomata(load_automata, accessible_states, dfa_canonical);

	}
	else
	{
		if (dfa_canonical == 0)
		{
			printf("\n\n\n-----------All states in the automata are accessible!-----------\n\n\n");
		}
	}


	free(accessible_states);
	free(accessible_states_check);
}

void checkCoaccessibilty(automato* load_automata, int dfa_canonical)
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
		getchar();
		load_automata->error = 1;
		return;
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
		rewriteAutomata(load_automata, coaccessible_states, dfa_canonical);
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
			load_automata->error = 1;
			return;
		}
		load_automata->deterministic = 0;
		return;
	}
	else
	{
		if (load_automata->states.size == 1)
		{
			printf("The automata only has one state. Please rewrite the automata! \n");
			getchar();
			load_automata->error = 1;
			return;
		}
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_automata->transitions[i][j]->size != 0)
				{
					if (load_automata->transitions[i][j]->size > 1)
					{
						load_automata->deterministic = 0;
						return;
					}
				}
			}
		}
		load_automata->deterministic = 1;
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
		printf("\n\n\n-----------Automata converted-----------\n\n\n");

	}
}




void freeAutomata(automato* load_automata)
{
	freeData(load_automata);
	free(load_automata);
}

//function that minimizes automata
void dfaCanonical(automato* load_automata)
{
	if (load_automata->states.size > 1)
	{
		printf("\n\n\n-----------Checking if the automata needs to be converted to the canonical form.-----------\n\n\n");
		int  i = 0, j = 0, z = 0, x = 0, y = 0, k = 0, marked_test = 0, leave_iterations = 0;

		//creation of canonical type variable
		canonical* load_canonical = newCanonical();
		resetCanonicalStructure(load_canonical);

		//-----------------memory allocation and variables declaration-----------------// 
		if (load_canonical->pair == NULL)
		{
			load_canonical->pair = (int_vector*)malloc(sizeof(int_vector)* load_automata->states.size);
		}

		if (load_canonical->table_marked == NULL)
		{
			load_canonical->table_marked = (int_vector*)malloc(sizeof(int_vector)* load_automata->states.size);
		}

		for (i = 0; i < load_automata->states.size; i++)
		{
			load_canonical->pair[i].size = 0;
			load_canonical->table_marked[i].size = 0;
		}
		//-----------------memory allocation and variables declaration-----------------// 
		


		//number of possible states' pairs
		load_canonical->pair_size = nCr(load_automata);
		printf("Number of pairs available in the automata: %d\n\n", load_canonical->pair_size);

		//states' pairs creation
		pairCreation(load_automata, load_canonical->pair);

		for (i = 0; i < load_automata->states.size; i++)
		{

			for (j = 0; j < load_automata->marked.size; j++)
			{
				if (i == load_automata->marked.values[j])
				{
					marked_test++;
				}
			}
			
			//third step of the minimization algorithm:
			// if the first element of the pair isn't final, then the 2nd element must be final, for the pair to be marked
			if (marked_test == 0)
			{
				for (z = 0; z < load_canonical->pair[i].size; z++)
				{
					for (j = 0; j < load_automata->marked.size; j++)
					{
						if (load_canonical->pair[i].values[z] == load_automata->marked.values[j])
						{
							marked_test++;
							break;
						}

					}
					if (marked_test > 0)
					{
						intVectPushBack(&(load_canonical->table_marked[i]), 1);
						load_canonical->marked_counter++;
						marked_test = 0;
					}
					else
					{
						intVectPushBack(&(load_canonical->table_marked[i]), 0);
						marked_test = 0;
					}
				}
			}

			//since the first element of the pair is final, then to the pair be marked, the 2nd element mustn't be final
			else
			{
				marked_test = 0;
				for (z = 0; z < load_canonical->pair[i].size; z++)
				{
					for (x = 0; x < load_automata->marked.size; x++)
					{
						if (load_canonical->pair[i].values[z] == load_automata->marked.values[x])
						{
							marked_test++;
							break;
						}

					}
					if (marked_test == 0)
					{
						intVectPushBack(&(load_canonical->table_marked[i]), 1);
						load_canonical->marked_counter++;
						marked_test = 0;
					}

					else
					{
						marked_test = 0;
						intVectPushBack(&(load_canonical->table_marked[i]), 0);
					}

				}
			}
		}

		int marked_counter = 0;

		int pair_one = 0, pair_two = 0, dummy = 0, trs1_not = 0, trs2_not = 0;

		//4th step of the minimization algorithm
		//step done while there are new marked pairs
		do
		{
			//variable atribution needed to check if there are new marked pairs
			marked_counter = load_canonical->marked_counter;
			
			
			for (i = 0; i < load_automata->states.size; i++)
			{
				for (y = 0; y < load_canonical->table_marked[i].size; y++)
				{
					if (load_canonical->table_marked[i].values[y] == 0)
					{
						for (j = 0; j < load_automata->events.size; j++)
						{
							//if there is a transition save the value of the first pair
							if (load_automata->transitions[i][j]->size != 0)
							{
								pair_one = load_automata->transitions[i][j]->values[0];
							}
							else
								//this is flagged otherwised
								trs1_not = 1;
							
							//same is done to the second element
							if (load_automata->transitions[load_canonical->pair[i].values[y]][j]->size != 0)
							{
								pair_two = load_automata->transitions[load_canonical->pair[i].values[y]][j]->values[0];
							}
							else
								trs2_not = 1;
							
							//ordenate the pairs
							if (pair_one > pair_two)
							{
								dummy = pair_one;
								pair_one = pair_two;
								pair_two = dummy;
							}
							
							//----------------mark if one of the states hasn't a transition----------------//
							if (trs1_not == 1 && trs2_not == 0)
							{
								trs1_not = 0;
								load_canonical->table_marked[i].values[y] = 1;
								load_canonical->marked_counter++;
							}
							else
							{
								if (trs1_not == 0 && trs2_not == 1)
								{
									trs2_not = 0;
									load_canonical->table_marked[i].values[y] = 1;
									load_canonical->marked_counter++;
								}
							//----------------mark if one of the states hasn't a transition----------------//
								
							//if both states have transitions need to call the function checkIfIsMarkedOnTable
								else
								{
									if (trs1_not == 0 && trs2_not == 0)
									{

										if (pair_one != pair_two)
										{
											checkIfIsMarkedOnTable(load_automata, load_canonical, i, y, load_canonical->pair[i].values[y], pair_one, pair_two);
										}
									}

								}
							}
							trs1_not = 0;
							trs2_not = 0;
						}
					}
				}
			}

		} while (marked_counter != load_canonical->marked_counter);

		//create the combined states that belong to the unmarked pairs
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_canonical->table_marked[i].size; j++)
			{
				if (load_canonical->table_marked[i].values[j] == 0)
				{
					createCanonicalStates(load_automata, load_canonical, load_canonical->pair[i].values[j], i, j);
				}
			}
		}

		dummy = 0;
		for (i = 0; i < load_automata->states.size; i++)
		{
			for (j = 0; j < load_canonical->table_marked[i].size; j++)
			{
				if (load_canonical->table_marked[i].values[j] == 1)
				{
					dummy++;
				}
			}
		}

		//if the number of combined states is equal to the initial pair size, it means it was already in the canonical form
		if (dummy == load_canonical->pair_size)
		{
			printf("The automata is already at the canonical form! All states are marked! Leaving function...\n\n");
			freeCanonical(load_canonical, load_automata);
			return;
		}

		//otherwise there is a new minimized automaton. Next steps are here to take care of the transitions of each combined state
		else
		{
			dummy = 0;
			if (load_canonical->combined_states != 0)
			{
				printf("\n\n-----------The automata needs to be converted to the canonical form... Converting-----------\n\n");
				for (i = 0; i < load_automata->states.size; i++)
				{
					for (j = 0; j < load_canonical->combined_states; j++)
					{
						if (findItemarray(load_canonical->states_to_combine[j].values, i, load_canonical->states_to_combine[j].size) != load_canonical->states_to_combine[j].size)
							dummy++;
					}
					if (dummy == 0)
					{
						load_canonical->states_to_combine = (int_vector*)realloc(load_canonical->states_to_combine, sizeof(int_vector)*(load_canonical->combined_states + 1));
						load_canonical->states_to_combine[load_canonical->combined_states].size = 0;
						intVectPushBack(&(load_canonical->states_to_combine[load_canonical->combined_states]), i);
						load_canonical->combined_states++;
					}
					else
						dummy = 0;
				}
			}
			else
			{
				load_canonical->states_to_combine = (int_vector*)malloc(sizeof(int_vector)*load_automata->states.size);
				for (i = 0; i < load_automata->states.size; i++)
				{
					intVectPushBack(&(load_canonical->states_to_combine[i]), i);
				}
			}


			if (load_canonical->combined_states_trs == NULL)
			{
				load_canonical->combined_states_trs = (int_vector**)malloc(sizeof(int_vector*)*load_canonical->combined_states);

				for (i = 0; i < load_canonical->combined_states; i++)
				{
					load_canonical->combined_states_trs[i] = (int_vector*)malloc(sizeof(int_vector)*(load_automata->events.size));
				}
			}

			for (i = 0; i < load_canonical->combined_states; i++)
			{
				for (j = 0; j < load_automata->events.size; j++)
				{
					load_canonical->combined_states_trs[i][j].size = 0;
				}
			}


			dummy = 0;
			for (i = 0; i < load_canonical->combined_states; i++)
			{
				for (x = 0; x < load_canonical->states_to_combine[i].size; x++)
				{
					for (j = 0; j < load_automata->events.size; j++)
					{
						if (load_automata->transitions[load_canonical->states_to_combine[i].values[x]][j]->size != 0)
						{
							if (load_canonical->trs_size == 0)
							{

								for (k = 0; k < load_canonical->combined_states; k++)
								{
									if (findItemarray(load_canonical->states_to_combine[k].values, load_automata->transitions[load_canonical->states_to_combine[i].values[x]][j]->values[0], load_canonical->states_to_combine[k].size) != load_canonical->states_to_combine[k].size)
									{
										load_canonical->combined_states_trs[i][j].values = (int_vector*)malloc(sizeof(int*));
										load_canonical->combined_states_trs[i][j].values[0] = k;
										load_canonical->combined_states_trs[i][j].size = 1;
										load_canonical->trs_size++;
										break;
									}
								}

							}
							else
							{
								if (load_canonical->combined_states_trs[i][j].size != 0)
								{
									dummy++;
								}

								if (dummy == 0)
								{
									for (k = 0; k < load_canonical->combined_states; k++)
									{
										if (findItemarray(load_canonical->states_to_combine[k].values, load_automata->transitions[load_canonical->states_to_combine[i].values[x]][j]->values[0], load_canonical->states_to_combine[k].size) != load_canonical->states_to_combine[k].size)
										{
											load_canonical->combined_states_trs[i][j].values = (int_vector*)malloc(sizeof(int*));
											load_canonical->combined_states_trs[i][j].values[0] = k;
											load_canonical->combined_states_trs[i][j].size = 1;
											load_canonical->trs_size++;
											break;
										}
									}
								}
								else
								{
									dummy = 0;
								}
							}
						}
					}
				}
			}

			writeCanonicalAutomata(load_automata, load_canonical);
		}
	}
	else
	{
		printf("Not enough states to make pairs! The automata is already at canonical form! \n\n ");
	}

}

//function responsible of making the product between two automatons 
void automataProduct(automata_array* automata_vector, automato* automata1, automato* automata2)
{
	int i = 0, j = 0, x = 0, k = 0, y = 0, z = 0, dummy = 0;
	
	//the product is made as long as there are states in the automatons and if both are deterministic
	if (automata1->states.size > 0 && automata2->states.size > 0)
	{
		dfaOrNfa(automata1);
		dfaOrNfa(automata2);
		if (automata1->deterministic == 1 && automata2->deterministic == 1)
		{
			printf("\n\n\n-----------Making the product between the inserted automata-----------\n\n\n");

			//---------------------------------memory allocation and variables initialization---------------------------------//
			product* load_product = newProduct();
			resetProductStructure(load_product);

			if (load_product->product_states == NULL)
			{
				load_product->product_states = (int_vector*)malloc(sizeof(int_vector));
			}

			load_product->product_states[0].size = 0;

			//the first state is the combination of the initial state of both automata
			intVectPushBack(&(load_product->product_states[0]), automata1->initial);
			intVectPushBack(&(load_product->product_states[0]), automata2->initial);

			load_product->product_states_size++;
			//---------------------------------memory allocation and variables initialization---------------------------------//
			
			
			
			//recursive function that creates the product states
			productStatescreation(load_product, automata1, automata2, 0);

			
			
			//---------------------------------memory allocation and variables initialization---------------------------------//
			if (load_product->product_states_trs == NULL)
			{
				load_product->product_states_trs = (int_vector**)malloc(sizeof(int_vector*)*load_product->product_states_size);

				for (i = 0; i < load_product->product_states_size; i++)
				{
					load_product->product_states_trs[i] = (int_vector*)malloc(sizeof(int_vector)*(automata1->events.size));
				}
			}

			for (i = 0; i < load_product->product_states_size; i++)
			{
				for (j = 0; j < automata1->events.size; j++)
				{
					load_product->product_states_trs[i][j].size = 0;
				}
			}
			//---------------------------------memory allocation and variables initialization---------------------------------//


			//-------------------------------------------product states transitions-------------------------------------------//
			dummy = 0;
			for (i = 0; i < load_product->product_states_size; i++)
			{
				for (j = 0; j < automata1->events.size; j++)
				{
					for (z = 0; z < automata2->events.size; z++)
					{
						if (strcmp(automata1->events.string[j], automata2->events.string[z]) == 0)
						{
							if (automata1->transitions[load_product->product_states[i].values[0]][j]->size != 0 && automata2->transitions[load_product->product_states[i].values[1]][z]->size != 0)
							{
								if (load_product->product_trs_size == 0)
								{
									for (k = 0; k < load_product->product_states_size; k++)
									{
										if (findItemarray(load_product->product_states[k].values, automata1->transitions[load_product->product_states[i].values[0]][j]->values[0], load_product->product_states[k].size) != load_product->product_states[k].size &&
											findItemarray(load_product->product_states[k].values, automata2->transitions[load_product->product_states[i].values[1]][z]->values[0], load_product->product_states[k].size) != load_product->product_states[k].size)
										{
											load_product->product_states_trs[i][j].values = (int_vector*)malloc(sizeof(int*));
											load_product->product_states_trs[i][j].values[0] = k;
											load_product->product_states_trs[i][j].size = 1;
											load_product->product_trs_size++;
											break;
										}
									}

								}
								else
								{
									if (load_product->product_states_trs[i][j].size != 0)
									{
										dummy++;
									}

									if (dummy == 0)
									{
										for (k = 0; k < load_product->product_states_size; k++)
										{
											if (findItemarray(load_product->product_states[k].values, automata1->transitions[load_product->product_states[i].values[0]][j]->values[0], load_product->product_states[k].size) != load_product->product_states[k].size &&
												findItemarray(load_product->product_states[k].values, automata2->transitions[load_product->product_states[i].values[1]][z]->values[0], load_product->product_states[k].size) != load_product->product_states[k].size)
											{
												load_product->product_states_trs[i][j].values = (int_vector*)malloc(sizeof(int*));
												load_product->product_states_trs[i][j].values[0] = k;
												load_product->product_states_trs[i][j].size = 1;
												load_product->product_trs_size++;
												break;
											}
										}
									}
									else
									{
										dummy = 0;
									}
								}
							}
						}
					}
				}
			}
			//-------------------------------------------product states transitions-------------------------------------------//
			
			
			
			
			writeProductAutomata(automata_vector,automata1, automata2, load_product);
		}
		else
		{
			printf("One of the automata is NFA, please use the other functions in the menu to change that!\n\n");
			return;
		}

	}



}

//function responsible of making the parallel between two automatons 
void automataParallel(automata_array* automata_vector, automato* automata1, automato* automata2)
{
	int i = 0, j = 0, x = 0, k = 0, y = 0, z = 0, dummy = 0, automata1_event = 0, automata2_event = 0;
	
	//the parallel is made as long as there are states in the automatons and if both are deterministic
	if (automata1->states.size > 0 && automata2->states.size > 0)
	{
		dfaOrNfa(automata1);
		dfaOrNfa(automata2);
		if (automata1->deterministic == 1 && automata2->deterministic == 1)
		{
			printf("\n\n\n-----------Making the parallel between the inserted automaton-----------\n\n\n");


			//---------------------------------memory allocation and variables initialization---------------------------------//
			parallel* load_parallel = newParallel();
			resetParallelStructure(load_parallel);

			if (load_parallel->parallel_states == NULL)
			{
				load_parallel->parallel_states = (int_vector*)malloc(sizeof(int_vector));
			}

			//----------------------------save the events of both automata withouth repeating them----------------------------//
			for (i = 0; i < automata1->events.size; i++)
			{
				stringPushBack(&(load_parallel->parallel_events), automata1->events.string[i]);
			}

			for (i = 0; i < automata2->events.size; i++)
			{
				if (findItemStringVector(automata2->events.string[i], load_parallel->parallel_events) == load_parallel->parallel_events.size)
				{
					stringPushBack(&(load_parallel->parallel_events), automata2->events.string[i]);
				}
			}
			//----------------------------save the events of both automata withouth repeating them----------------------------//



			//---------------------------------memory allocation and variables initialization---------------------------------//
			
			
			load_parallel->parallel_states[0].size = 0;
			
			//the first state is the combination of the initial state of both automata
			intVectPushBack(&(load_parallel->parallel_states[0]), automata1->initial);
			intVectPushBack(&(load_parallel->parallel_states[0]), automata2->initial);

			load_parallel->parallel_states_size++;

			//recursive function that creates the parallel states
			parallelStatescreation(load_parallel, automata1, automata2, 0);


			//-------------------------------------------product states transitions-------------------------------------------//
			if (load_parallel->parallel_states_trs == NULL)
			{
				load_parallel->parallel_states_trs = (int_vector**)malloc(sizeof(int_vector*)*load_parallel->parallel_states_size);

				for (i = 0; i < load_parallel->parallel_states_size; i++)
				{
					load_parallel->parallel_states_trs[i] = (int_vector*)malloc(sizeof(int_vector)*(load_parallel->parallel_events.size));
				}
			}


			for (i = 0; i < load_parallel->parallel_states_size; i++)
			{
				for (j = 0; j < load_parallel->parallel_events.size; j++)
				{
					load_parallel->parallel_states_trs[i][j].size = 0;
				}
			}


			dummy = 0;

			//the procedure of saving the transitions is almost the same as the one found in parallelStatescreation
			for (i = 0; i < load_parallel->parallel_states_size; i++)
			{
				for (y = 0; y < load_parallel->parallel_events.size; y++)
				{
					for (j = 0; j < automata1->events.size; j++)
					{
						for (z = 0; z < automata2->events.size; z++)
						{
							if (strcmp(automata1->events.string[j], automata2->events.string[z]) == 0 && (strcmp(load_parallel->parallel_events.string[y], automata1->events.string[j]) == 0))
							{
								if (automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->size != 0 && automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->size != 0)
								{
									if (load_parallel->parallel_trs_size == 0)
									{
										for (k = 0; k < load_parallel->parallel_states_size; k++)
										{
											if ((load_parallel->parallel_states[k].values[0] == automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->values[0]) && (load_parallel->parallel_states[k].values[1] == automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->values[0]))
											{
												load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
												load_parallel->parallel_states_trs[i][y].values[0] = k;
												load_parallel->parallel_states_trs[i][y].size = 1;
												load_parallel->parallel_trs_size++;
												break;
											}
										}
									}
									else
									{
										if (load_parallel->parallel_states_trs[i][y].size != 0)
										{
											dummy++;
										}

										if (dummy == 0)
										{
											for (k = 0; k < load_parallel->parallel_states_size; k++)
											{
												if ((load_parallel->parallel_states[k].values[0] == automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->values[0]) && (load_parallel->parallel_states[k].values[1] == automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->values[0]))
												{
													load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
													load_parallel->parallel_states_trs[i][y].values[0] = k;
													load_parallel->parallel_states_trs[i][y].size = 1;
													load_parallel->parallel_trs_size++;
													break;

												}
											}
										}
										else
										{
											dummy = 0;
										}
									}
								}
							}

							else
							{

								dummy = 0;

								if (strcmp(load_parallel->parallel_events.string[y], automata1->events.string[j]) == 0)
								{
									automata1_event = j;
									dummy++;
								}

								if (dummy == 0)
								{
									automata1_event = -1;
								}
								else
									dummy = 0;

								if (automata1_event != -1)
								{
									for (x = 0; x < automata2->events.size; x++)
									{

										if (strcmp(load_parallel->parallel_events.string[automata1_event], automata2->events.string[x]) == 0)
										{
											automata2_event = x;
											dummy++;
											break;
										}

									}
									if (dummy == 0)
									{
										automata2_event = -1;
									}
									else
										dummy = 0;
								}
								else
									automata2_event = -1;


								if (automata1_event != -1)
								{
									if (automata2_event == -1)
									{
										if (load_parallel->parallel_trs_size == 0)
										{
											if (automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->size != 0)
											{
												for (k = 0; k < load_parallel->parallel_states_size; k++)
												{
													if ((load_parallel->parallel_states[k].values[0] == automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->values[0]) && (load_parallel->parallel_states[k].values[1] == load_parallel->parallel_states[i].values[1]))
													{
														load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
														load_parallel->parallel_states_trs[i][y].values[0] = k;
														load_parallel->parallel_states_trs[i][y].size = 1;
														load_parallel->parallel_trs_size++;
														break;
													}
												}

											}
										}
										else
										{
											if (load_parallel->parallel_states_trs[i][y].size != 0)
											{
												dummy++;
											}

											if (dummy == 0)
											{
												if (automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->size != 0)
												{
													for (k = 0; k < load_parallel->parallel_states_size; k++)
													{
														if ((load_parallel->parallel_states[k].values[0] == automata1->transitions[load_parallel->parallel_states[i].values[0]][j]->values[0]) && (load_parallel->parallel_states[k].values[1] == load_parallel->parallel_states[i].values[1]))
														{
															load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
															load_parallel->parallel_states_trs[i][y].values[0] = k;
															load_parallel->parallel_states_trs[i][y].size = 1;
															load_parallel->parallel_trs_size++;
															break;
														}
													}
												}
											}
											else
												dummy = 0;
										}
									}
								}


								dummy = 0;

								if (strcmp(load_parallel->parallel_events.string[y], automata2->events.string[z]) == 0)
								{
									automata2_event = z;
									dummy++;
								}

								if (dummy == 0)
								{
									automata2_event = -1;
								}
								else
									dummy = 0;

								if (automata2_event != -1)
								{
									for (x = 0; x < automata1->events.size; x++)
									{
										if (strcmp(load_parallel->parallel_events.string[automata2_event], automata1->events.string[x]) == 0)
										{
											automata1_event = x;
											dummy++;
											break;
										}

									}
									if (dummy == 0)
									{
										automata1_event = -1;
									}
									else
										dummy = 0;
								}
								else
								{
									automata1_event = -1;
								}



								if (automata2_event != -1)
								{


									if (automata1_event == -1)
									{
										if (load_parallel->parallel_trs_size == 0)
										{
											if (automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->size != 0)
											{
												for (k = 0; k < load_parallel->parallel_states_size; k++)
												{
													if ((load_parallel->parallel_states[k].values[1] == automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->values[0]) && (load_parallel->parallel_states[k].values[0] == load_parallel->parallel_states[i].values[0]))
													{
														load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
														load_parallel->parallel_states_trs[i][y].values[0] = k;
														load_parallel->parallel_states_trs[i][y].size = 1;
														load_parallel->parallel_trs_size++;
														break;
													}
												}

											}
										}
										else
										{
											if (load_parallel->parallel_states_trs[i][y].size != 0)
											{
												dummy++;
											}

											if (dummy == 0)
											{
												if (automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->size != 0)
												{
													for (k = 0; k < load_parallel->parallel_states_size; k++)
													{
														if ((load_parallel->parallel_states[k].values[1] == automata2->transitions[load_parallel->parallel_states[i].values[1]][z]->values[0]) && (load_parallel->parallel_states[k].values[0] == load_parallel->parallel_states[i].values[0]))
														{
															load_parallel->parallel_states_trs[i][y].values = (int_vector*)malloc(sizeof(int*));
															load_parallel->parallel_states_trs[i][y].values[0] = k;
															load_parallel->parallel_states_trs[i][y].size = 1;
															load_parallel->parallel_trs_size++;
															break;
														}
													}
												}
											}
											else
												dummy = 0;
										}
									}
								}
							}
						}
					}
				}
			}
			//-------------------------------------------product states transitions-------------------------------------------//
			
			
			
			writeParallelAutomata(automata_vector, automata1, automata2, load_parallel);
		}
		else
		{
			printf("One of the automaton is NFA, please use the other functions in the menu to change that!\n\n");
			return;
		}
	}
}


//----------------------Private functions---------------------------

int clean_stdin()
{
	while (getchar() != '\n');
	return 1;
}


//creates pairs with the automaton's states
void pairCreation(automato* load_automata, int_vector* pair)
{
	int i = 0, j = 0, pair_size = 0, temp = 0;

	for (i = 0; i < load_automata->states.size; i++)
	{
		for (j = i + 1; j <= (load_automata->states.size - 1); j++)
		{
			intVectPushBack(&(pair[i]), j);
		}
	}
}

//the 4th step of the minimization algorithm. Checks if the pair of states resultant from the pair transition is one of the marked pairs or not
void checkIfIsMarkedOnTable(automato* load_automata, canonical* load_canonical, int  pair_index, int y, int table_index, int pair_one, int pair_two)
{
	int i = 0;


	for (i = 0; i < load_canonical->pair[pair_one].size; i++)
	{
		if (load_canonical->pair[pair_one].values[i] == pair_two)
			pair_two = i;
	}

	if (load_canonical->table_marked[pair_one].values[pair_two] == 1)
	{
		load_canonical->table_marked[pair_index].values[y] = 1;
		load_canonical->marked_counter++;
		table_index = 1;
	}
}


//function responsible of creating the combined states out of the states that belong to the unmarked pairs
void createCanonicalStates(automato* load_automata, canonical* load_canonical, int result_pair, int pair_1st_index, int pair_index)
{
	int i = 0, j = 0, x = 0, test = 0;
	int* provisory_states;
	int provisory_states_size = 0;
	for (i = pair_1st_index; i < load_automata->states.size; i++)
	{
		if (i == pair_1st_index)
		{
			for (j = pair_index + 1; j < load_canonical->pair[i].size; j++)
			{
				if (load_canonical->table_marked[i].values[j] == 0)
				{
					if (i == pair_1st_index || load_canonical->pair[i].values[j] == result_pair || i == result_pair || load_canonical->pair[i].values[j] == pair_1st_index)
					{
						if (provisory_states_size == 0)
						{
							provisory_states_size++;
							provisory_states = (int*)malloc(sizeof(int));
							provisory_states[provisory_states_size - 1] = pair_1st_index;

							if (findItemarray(provisory_states, result_pair, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = result_pair;
							}

							if (findItemarray(provisory_states, i, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = i;
							}

							if (findItemarray(provisory_states, load_canonical->pair[i].values[j], provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = load_canonical->pair[i].values[j];
							}

						}
						else
						{
							if (findItemarray(provisory_states, pair_1st_index, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = pair_1st_index;
							}

							if (findItemarray(provisory_states, result_pair, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = result_pair;
							}

							if (findItemarray(provisory_states, i, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = i;
							}

							if (findItemarray(provisory_states, load_canonical->pair[i].values[j], provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = load_canonical->pair[i].values[j];
							}
						}
					}
				}
			}
		}
		else
		{
			for (j = 0; j < load_canonical->pair[i].size; j++)
			{
				if (load_canonical->table_marked[i].values[j] == 0)
				{
					if (i == pair_1st_index || load_canonical->pair[i].values[j] == result_pair || i == result_pair || load_canonical->pair[i].values[j] == pair_1st_index)
					{
						if (provisory_states_size == 0)
						{
							provisory_states_size++;
							provisory_states = (int*)malloc(sizeof(int));
							provisory_states[provisory_states_size - 1] = pair_1st_index;

							if (findItemarray(provisory_states, result_pair, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = result_pair;
							}

							if (findItemarray(provisory_states, i, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = i;
							}

							if (findItemarray(provisory_states, load_canonical->pair[i].values[j], provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = load_canonical->pair[i].values[j];
							}
						}
						else
						{
							if (findItemarray(provisory_states, pair_1st_index, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = pair_1st_index;
							}

							if (findItemarray(provisory_states, result_pair, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = result_pair;
							}

							if (findItemarray(provisory_states, i, provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = i;
							}

							if (findItemarray(provisory_states, load_canonical->pair[i].values[j], provisory_states_size) == provisory_states_size)
							{
								provisory_states_size++;
								provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
								provisory_states[provisory_states_size - 1] = load_canonical->pair[i].values[j];
							}
						}
					}
				}
			}
		}
	}

	if (provisory_states_size > 0)
	{
		if (load_canonical->combined_states == 0)
		{
			load_canonical->states_to_combine = (int_vector*)malloc(sizeof(int_vector));
			load_canonical->states_to_combine[load_canonical->combined_states].size = 0;
			for (i = 0; i < provisory_states_size; i++)
			{
				intVectPushBack(&(load_canonical->states_to_combine[load_canonical->combined_states]), provisory_states[i]);
			}
			sortArrayAscending(&(load_canonical->states_to_combine[load_canonical->combined_states]));
			load_canonical->combined_states++;
		}
		else
		{
			for (i = 0; i < load_canonical->combined_states; i++)
			{
				for (j = 0; j < load_canonical->states_to_combine[i].size; j++)
				{
					for (x = 0; x < provisory_states_size; x++)
					{
						if (findItemarray(load_canonical->states_to_combine[i].values, provisory_states[x], load_canonical->states_to_combine[i].size) != load_canonical->states_to_combine[i].size)
							test++;
					}
				}
			}
			if (test == 0)
			{
				load_canonical->states_to_combine = (int_vector*)realloc(load_canonical->states_to_combine, sizeof(int_vector)*(load_canonical->combined_states + 1));
				load_canonical->states_to_combine[load_canonical->combined_states].size = 0;
				for (i = 0; i < provisory_states_size; i++)
				{
					intVectPushBack(&(load_canonical->states_to_combine[load_canonical->combined_states]), provisory_states[i]);
				}
				sortArrayAscending(&(load_canonical->states_to_combine[load_canonical->combined_states]));
				load_canonical->combined_states++;
			}

		}
	}
	else
	{
		provisory_states_size++;
		provisory_states = (int*)malloc(sizeof(int));
		provisory_states[provisory_states_size - 1] = pair_1st_index;

		if (findItemarray(provisory_states, result_pair, provisory_states_size) == provisory_states_size)
		{
			provisory_states_size++;
			provisory_states = (int*)realloc(provisory_states, sizeof(int)*provisory_states_size);
			provisory_states[provisory_states_size - 1] = result_pair;
		}
	}

	if (load_canonical->combined_states == 0)
	{
		load_canonical->states_to_combine = (int_vector*)malloc(sizeof(int_vector));
		load_canonical->states_to_combine[load_canonical->combined_states].size = 0;
		for (i = 0; i < provisory_states_size; i++)
		{
			intVectPushBack(&(load_canonical->states_to_combine[load_canonical->combined_states]), provisory_states[i]);
		}
		sortArrayAscending(&(load_canonical->states_to_combine[load_canonical->combined_states]));
		load_canonical->combined_states++;
	}
	else
	{
		for (i = 0; i < load_canonical->combined_states; i++)
		{
			for (j = 0; j < load_canonical->states_to_combine[i].size; j++)
			{
				for (x = 0; x < provisory_states_size; x++)
				{
					if (findItemarray(load_canonical->states_to_combine[i].values, provisory_states[x], load_canonical->states_to_combine[i].size) != load_canonical->states_to_combine[i].size)
						test++;
				}
			}
		}
		if (test == 0)
		{
			load_canonical->states_to_combine = (int_vector*)realloc(load_canonical->states_to_combine, sizeof(int_vector)*(load_canonical->combined_states + 1));
			load_canonical->states_to_combine[load_canonical->combined_states].size = 0;
			for (i = 0; i < provisory_states_size; i++)
			{
				intVectPushBack(&(load_canonical->states_to_combine[load_canonical->combined_states]), provisory_states[i]);
			}
			sortArrayAscending(&(load_canonical->states_to_combine[load_canonical->combined_states]));
			load_canonical->combined_states++;
		}

	}

	if (provisory_states_size > 0)
	{
		free(provisory_states);
	}
}


int nCr(automato* load_automata)
{
	int result = 0;
	int n = load_automata->states.size;
	int k = 2;
	int n_fact = factorial(n);
	int k_fact = factorial(k);
	int n_k = n - k;
	int n_k_factorial = factorial(n_k);
	result = n_fact / (k_fact * n_k_factorial);

	return(result);
}

int factorial(int number)
{
	int i, fact = 1;

	for (i = 1; i <= number; i++)
	{
		fact = fact * i;
	}
	return(fact);
}


void freeData(automato* load_automata)
{
	int i = 0, j = 0, x = 0, z = 0;
	if (load_automata->states.size > 0 && load_automata->transitions != NULL)
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

	if (load_automata->states.size > 0 && load_automata->transitions != NULL)
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


	if (load_automata->states.size > 0 && load_automata->e_closure != NULL)
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
	load_automata->error = 0;
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
	load_dfa->error = 0;
}


canonical* newCanonical()
{
	canonical* new_canonical;
	new_canonical = (canonical*)malloc(sizeof(canonical));
	resetCanonicalStructure(new_canonical);
	return new_canonical;
}

void resetCanonicalStructure(canonical* load_canonical)
{
	load_canonical->error = 0;
	load_canonical->trs_size = 0;
	load_canonical->pair_size = 0;
	load_canonical->marked_counter = 0;
	load_canonical->combined_states = 0;
	load_canonical->states_to_combine = NULL;
	load_canonical->table_marked = NULL;
	load_canonical->pair = NULL;
	load_canonical->combined_states_trs = NULL;
}


void freeCanonical(canonical* load_canonical, automato* load_automata)
{
	freeCanonicalStructure(load_canonical, load_automata);
	free(load_canonical);
}

void freeCanonicalStructure(canonical* load_canonical, automato* load_automata)
{
	int i = 0, j = 0;

	if (load_canonical->combined_states != 0)
	{
		for (i = 0; i < load_canonical->combined_states; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_canonical->combined_states_trs[i][j].size != 0)
				{
					free(load_canonical->combined_states_trs[i][j].values);
				}
			}
			free(load_canonical->combined_states_trs[i]);
		}
		free(load_canonical->combined_states_trs);
	}

	if (load_automata->states.size > 0)
	{
		for (i = 0; i < load_automata->states.size; i++)
		{
			if (load_canonical->pair[i].size > 0)
			{
				free(load_canonical->pair[i].values);
			}
		}
		free(load_canonical->pair);

		for (i = 0; i < load_automata->states.size; i++)
		{
			if (load_canonical->table_marked[i].size > 0)
			{
				free(load_canonical->table_marked[i].values);
			}
		}
		free(load_canonical->table_marked);
	}

	if (load_canonical->combined_states != 0)
	{
		for (i = 0; i < load_canonical->combined_states; i++)
		{
			if (load_canonical->states_to_combine[i].size > 0)
			{
				free(load_canonical->states_to_combine[i].values);
			}
		}
		free(load_canonical->states_to_combine);
	}




	resetCanonicalStructure(load_canonical);
}




product* newProduct()
{
	product* new_product;
	new_product = (product*)malloc(sizeof(product));
	resetProductStructure(new_product);
	return new_product;
}

void resetProductStructure(product* load_product)
{
	load_product->error = 0;
	load_product->product_trs_size = 0;
	load_product->product_states_size = 0;
	load_product->product_states = NULL;
	load_product->product_states_trs = NULL;
}



void freeProduct(product* load_product, automato* load_automata)
{
	freeProductStructure(load_product, load_automata);
	free(load_product);
}


void freeProductStructure(product* load_product, automato* load_automata)
{
	int i = 0, j = 0;

	if (load_product->product_states_size != 0)
	{
		for (i = 0; i < load_product->product_states_size; i++)
		{
			for (j = 0; j < load_automata->events.size; j++)
			{
				if (load_product->product_states_trs[i][j].size != 0)
				{
					free(load_product->product_states_trs[i][j].values);
				}
			}
			free(load_product->product_states_trs[i]);
		}
		free(load_product->product_states_trs);
	}

	if (load_product->product_states_size != 0)
	{
		for (i = 0; i < load_product->product_states_size; i++)
		{
			if (load_product->product_states[i].size > 0)
			{
				free(load_product->product_states[i].values);
			}
		}
		free(load_product->product_states);
	}

	resetProductStructure(load_product);
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

//rewrites the automata case it's needed 
void rewriteAutomata(automato* load_automata, int* valid_states, int dfa_canonical)
{


	int i = 0, j = 0, x = 0, z = 0, k = 0;
	int* buffer[1000];
	char c;
	x = x + strlen("STATES\r\n") + 1;
	char* new_automata_info;
	int* valid_events;

	valid_events = (int*)malloc(sizeof(int)*load_automata->events.size);
	for (i = 0; i < load_automata->events.size; i++)
	{
		valid_events[i] = 0;
	}

	new_automata_info = malloc(x);

	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcpy(new_automata_info, "STATES\r\n\0");
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

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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


	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "INITIAL\r\n\0");

	x = x + strlen(load_automata->states.string[load_automata->initial]) + strlen("\r\n") + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, load_automata->states.string[load_automata->initial]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "\r\n\0");


	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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


	if (dfa_canonical == 0)
	{
		printf("\n\nDo you wish to change the current automata? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &k, &c) != 2 || c != '\n') && clean_stdin());
		if (k == 1)
		{
			freeData(load_automata);
			parser(load_automata, new_automata_info);
		}
		else
		{
			printf("\n\nDo you wish to print the changed automata? Press 1 if yes, any other number if not \n\n");
			while ((scanf("%d%c", &k, &c) != 2 || c != '\n') && clean_stdin());
			if (k == 1)
			{
				automato* provisory;
				provisory = new_automata();
				parser(provisory, new_automata_info);
				printAutomata(provisory);
				freeAutomata(provisory);
			}
			printf("\n\nDo you wish to print the changed automata to a file? Press 1 if yes, any other number if not \n\n");
			while ((scanf("%d%c", &k, &c) != 2 || c != '\n') && clean_stdin());
			if (k == 1)
			{
				automato* provisory;
				provisory = new_automata();
				parser(provisory, new_automata_info);
				writeAutomataToFile(provisory);
				freeAutomata(provisory);
			}
		}
	}
	else
	{
		freeData(load_automata);
		parser(load_automata, new_automata_info);
	}
	free(new_automata_info);
	free(valid_events);
}


//function that writes the DFA automata in the .aut format. Also it gives the user the choice of saving the automata in memory...
//...or print it in the console or writing it to a file.
void writeDfaAutomata(automato* load_automata, dfa* load_dfa)
{
	int i = 0, j = 0, x = 0, z = 0, y = 0, k = 0;
	int* buffer[1000];
	char c;
	x = x + strlen("STATES\r\n") + 1;
	char* new_automata_info;
	new_automata_info = malloc(x);

	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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
					x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("\r\n") + 4;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "}");
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "\r\n\0");
				}
				else
				{
					if (j == 0)
					{
						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");
					}
					x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen(",") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, ",\0");

				}
			}
		}
	}

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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


	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(";") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ";\0");
							}
							else
							{
								if (z == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");

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
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "\r\n\0");
							}
							else
							{
								if (y == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");
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
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(";") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ";\0");
							}
							else
							{
								if (z == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[z]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");

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
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen("\r\n") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "\r\n\0");
							}
							else
							{
								if (y == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_dfa->dfa_states[z].values[y]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");
							}
						}
					}

				}
			}
		}
	}

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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
				x = x + strlen(load_automata->states.string[load_dfa->dfa_states[0].values[i]]) + strlen("\r\n") + 4;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[0].values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "}");
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");

			}
			else
			{
				if (i == 0)
				{
					x = x + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, "{");
					strcat(new_automata_info, "\0");
				}
				x = x + strlen(load_automata->states.string[load_dfa->dfa_states[0].values[i]]) + strlen(",") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[0].values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ",\0");
			}
		}
	}

	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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
						x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen("\r\n") + 4;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
					else
					{
						if (j == 0)
						{
							x = x + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, "{");
							strcat(new_automata_info, "\0");
						}
						x = x + strlen(load_automata->states.string[load_dfa->dfa_states[i].values[j]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_dfa->dfa_states[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

					}
				}
			}
		}
	}

	freeDfa(load_dfa, load_automata);

	//user choices
	printf("\n\nDo you wish to change the current automata? Press 1 if yes, any other number if not \n\n");
	while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
	if (i == 1)
	{
		freeData(load_automata);
		parser(load_automata, new_automata_info);
		printf("\n\n\n-----------Automata in canonical form-----------\n\n\n");
	}
	else
	{
		printf("\n\nDo you wish to print the changed automata? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			printAutomata(provisory);
			freeAutomata(provisory);
		}

		printf("\n\nDo you wish to print the changed automata to a file? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			writeAutomataToFile(provisory);
			freeAutomata(provisory);
		}
	}
	free(new_automata_info);
}

//function that writes the minimized automata in the .aut format. Also it gives the user the choice of saving the automata in memory...
//...or print it in the console or writing it to a file.
void writeCanonicalAutomata(automato* load_automata, canonical* load_canonical)
{
	int i = 0, j = 0, x = 0, z = 0, y = 0, k = 0;

	x = x + strlen("STATES\r\n");
	char* new_automata_info;
	new_automata_info = malloc(x);
	x = x + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcpy(new_automata_info, "STATES\r\n\0");
	int* buffer[1000];
	char c;

	for (i = 0; i < load_canonical->combined_states; i++)
	{
		for (j = 0; j < load_canonical->states_to_combine[i].size; j++)
		{
			if (load_canonical->states_to_combine[i].size == 1)
			{
				x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
			else
			{
				if (j == load_canonical->states_to_combine[i].size - 1)
				{
					x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen("\r\n") + 3 + strlen("}");
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "}");
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "\r\n\0");
				}
				else
				{
					if (j == 0)
					{
						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");
					}
					x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen(",") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, ",\0");

				}
			}
		}
	}

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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


	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "TRANSITIONS\r\n\0");

	for (i = 0; i < load_canonical->combined_states; i++)
	{
		{
			for (j = 0; j < (load_automata)->events.size; j++)
			{
				if (load_canonical->combined_states_trs[i][j].size != 0)
				{
					for (z = 0; z < load_canonical->states_to_combine[i].size; z++)
					{
						if (load_canonical->states_to_combine[i].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[z]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[z]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, ";\0");
						}
						else
						{
							if (z == load_canonical->states_to_combine[i].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[z]]) + strlen(";") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ";\0");
							}
							else
							{
								if (z == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[z]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[z]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");

							}
						}
					}

					x = x + strlen(load_automata->events.string[j]) + strlen(";") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->events.string[j]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, ";\0");

					z = 0;
					z = load_canonical->combined_states_trs[i][j].values[0];
					for (y = 0; y < load_canonical->states_to_combine[z].size; y++)
					{
						if (load_canonical->states_to_combine[z].size == 1)
						{
							x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[z].values[y]]) + strlen("\r\n") + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[z].values[y]]);
							strcat(new_automata_info, "\0");
							strcat(new_automata_info, "\r\n\0");
						}
						else
						{
							if (y == load_canonical->states_to_combine[z].size - 1)
							{
								x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[z].values[y]]) + strlen("\r\n") + 4;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "}");
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, "\r\n\0");
							}
							else
							{
								if (y == 0)
								{
									x = x + 2;
									new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
									strcat(new_automata_info, "{");
									strcat(new_automata_info, "\0");
								}
								x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[z].values[y]]) + strlen(",") + 2;
								new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
								strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[z].values[y]]);
								strcat(new_automata_info, "\0");
								strcat(new_automata_info, ",\0");
							}
						}
					}

				}
			}
		}
	}

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "INITIAL\r\n\0");

	int dummy = 0;

	for (i = 0; i < load_canonical->combined_states; i++)
	{
		for (j = 0; j < load_canonical->states_to_combine[i].size; j++)
		{
			if (load_canonical->states_to_combine[i].values[j] == load_automata->initial)
			{
				dummy = i;
			}
		}
	}
	for (z = 0; z < load_canonical->states_to_combine[dummy].size; z++)
	{
		if (load_canonical->states_to_combine[dummy].size == 1)
		{
			x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]) + strlen("\r\n") + 2;
			new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
			strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]);
			strcat(new_automata_info, "\0");
			strcat(new_automata_info, "\r\n\0");
		}
		else
		{
			if (z == load_canonical->states_to_combine[dummy].size - 1)
			{
				x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]) + strlen("\r\n") + 4;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "}");
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");

			}
			else
			{
				if (z == 0)
				{
					x = x + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, "{");
					strcat(new_automata_info, "\0");
				}
				x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]) + strlen(",") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[dummy].values[z]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ",\0");
			}
		}
	}

	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "MARKED\r\n\0");
	int marked = 0;


	for (i = 0; i < load_canonical->combined_states; i++)
	{
		for (j = 0; j < load_automata->marked.size; j++)
		{
			if (findItemarray(load_canonical->states_to_combine[i].values, load_automata->marked.values[j], load_canonical->states_to_combine[i].size) != load_canonical->states_to_combine[i].size)
			{
				marked++;
				continue;
			}
		}
		if (marked != 0)
		{


			marked = 0;
			for (j = 0; j < load_canonical->states_to_combine[i].size; j++)
			{
				if (load_canonical->states_to_combine[i].size == 1)
				{
					x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen("\r\n") + 2;
					new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
					strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
					strcat(new_automata_info, "\0");
					strcat(new_automata_info, "\r\n\0");
				}
				else
				{
					if (j == load_canonical->states_to_combine[i].size - 1)
					{
						x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen("\r\n") + 4;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
					else
					{
						if (j == 0)
						{
							x = x + 2;
							new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
							strcat(new_automata_info, "{");
							strcat(new_automata_info, "\0");
						}
						x = x + strlen(load_automata->states.string[load_canonical->states_to_combine[i].values[j]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, load_automata->states.string[load_canonical->states_to_combine[i].values[j]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

					}
				}
			}
		}
	}

	freeCanonical(load_canonical, load_automata);

	//the user choices
	printf("\n\nDo you wish to change the current automata? Press 1 if yes, any other number if not \n\n");
	while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
	if (i == 1)
	{
		freeData(load_automata);
		parser(load_automata, new_automata_info);
		printf("\n\n\n-----------Automata in canonical form-----------\n\n\n");
	}
	else
	{
		printf("\n\nDo you wish to print the changed automata? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			printAutomata(provisory);
			freeAutomata(provisory);
		}

		printf("\n\nDo you wish to print the changed automata to a file? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			writeAutomataToFile(provisory);
			freeAutomata(provisory);
		}
	}

	free(new_automata_info);
}

//function that writes the product result in the .aut format. Also it gives the user the choice of saving the automata in memory...
//...or print it in the console or writing it to a file.
void writeProductAutomata(automata_array* automata_vector ,automato* automata1, automato* automata2, product* load_product)
{
	int i = 0, j = 0, x = 0, z = 0, y = 0, k = 0;
	x = x + strlen("STATES\r\n");
	char* new_automata_info;
	int* buffer[1000];
	char* buffer_name[1000];
	char c;
	new_automata_info = malloc(x);
	x = x + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcpy(new_automata_info, "STATES\r\n\0");

	for (i = 0; i < load_product->product_states_size; i++)
	{
		x = x + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, "{");
		strcat(new_automata_info, "\0");

		x = x + strlen(automata1->states.string[load_product->product_states[i].values[0]]) + strlen(",") + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, automata1->states.string[load_product->product_states[i].values[0]]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, ",\0");

		x = x + strlen(automata2->states.string[load_product->product_states[i].values[1]]) + strlen("\r\n") + 3 + strlen("}");
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, automata2->states.string[load_product->product_states[i].values[1]]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "}");
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "\r\n\0");
	}

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "EVENTS\r\n\0");

	

	if (automata1->events.size < automata2->events.size)
	{
		for (i = 0; i < automata1->events.size; i++)
		{
			
				x = x + strlen(automata1->events.string[i]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata1->events.string[i]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
		}
	}
	else
	{
		for (i = 0; i < automata2->events.size; i++)
		{
			
				x = x + strlen(automata1->events.string[i]) + strlen("\r\n") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata2->events.string[i]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			
		}
	}


	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "TRANSITIONS\r\n\0");

	for (i = 0; i < load_product->product_states_size; i++)
	{
		if (automata1->events.size < automata2->events.size)
		{
			for (j = 0; j < automata1->events.size; j++)
			{
				
					if (load_product->product_states_trs[i][j].size != 0)
					{

						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_product->product_states[i].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_product->product_states[i].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_product->product_states[i].values[1]]) + strlen(";") + 3 + strlen("}");
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_product->product_states[i].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ";");


						x = x + strlen(automata1->events.string[j]) + strlen(";") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->events.string[j]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ";\0");

						z = 0;
						z = load_product->product_states_trs[i][j].values[0];

						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_product->product_states[z].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_product->product_states[z].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_product->product_states[z].values[1]]) + strlen(";") + strlen("\r\n") + 4;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_product->product_states[z].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
		
			}
		}
		else
		{
			for (j = 0; j < automata2->events.size; j++)
			{
				
					if (load_product->product_states_trs[i][j].size != 0)
					{

						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_product->product_states[i].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_product->product_states[i].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_product->product_states[i].values[1]]) + strlen(";") + 3 + strlen("}");
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_product->product_states[i].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ";");


						x = x + strlen(automata2->events.string[j]) + strlen(";") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->events.string[j]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ";\0");

						z = 0;
						z = load_product->product_states_trs[i][j].values[0];

						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_product->product_states[z].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_product->product_states[z].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_product->product_states[z].values[1]]) + strlen(";") + strlen("\r\n") + 4;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_product->product_states[z].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
				
			}
		}
	}

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "INITIAL\r\n\0");

	int dummy = 0;

	x = x + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, "{");
	strcat(new_automata_info, "\0");

	x = x + strlen(automata1->states.string[load_product->product_states[0].values[0]]) + strlen(",") + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, automata1->states.string[load_product->product_states[0].values[0]]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, ",\0");

	x = x + strlen(automata2->states.string[load_product->product_states[0].values[1]]) + strlen("\r\n") + 3 + strlen("}");
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, automata2->states.string[load_product->product_states[0].values[1]]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "}");
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "\r\n\0");

	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "MARKED\r\n\0");
	int marked = 0;


	for (i = 0; i < load_product->product_states_size; i++)
	{
		for (j = 0; j < automata1->marked.size; j++)
		{
			if (load_product->product_states[i].values[0] == automata1->marked.values[j])
			{
				for (k = 0; k < automata2->marked.size; k++)
				{
					if (load_product->product_states[i].values[1] == automata2->marked.values[k])
					{
						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_product->product_states[i].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_product->product_states[i].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_product->product_states[i].values[1]]) + strlen("\r\n") + 3 + strlen("}");
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_product->product_states[i].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
				}
			}
		}
	}

	if (automata1->events.size < automata2->events.size)
	{
		freeProduct(load_product, automata1);
	}
	else
		freeProduct(load_product, automata2);


	//user choices
	printf("\n\nDo you wish to save the product result? Press 1 if yes, any other number if not \n\n");
	while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
	if (i == 1)
	{
		dummy = 0;

		while (dummy == 0)
		{
			printf("Write the new automata name\n\n");
			scanf("%s", buffer_name);
			getchar();

			for (z = 0; z < automata_vector->automata_number; z++)
			{
				if (strcmp(buffer_name, automata_vector->automata_name.string[z]) == 0)
				{
					dummy = 0;
					printf("\n\nThis automata has already been loaded! Press enter to continue! \n\n");
					break;
				}
				dummy = 1;
			}
		}


		automata_vector->automata = (automato**)realloc(automata_vector->automata, sizeof(automato*)*(automata_vector->automata_number + 1));
		automata_vector->automata[automata_vector->automata_number] = new_automata();
		stringPushBack(&(automata_vector->automata_name), buffer_name);
		memset(buffer, 0, 1000);

		parser(automata_vector->automata[automata_vector->automata_number], new_automata_info);
		automata_vector->automata_number++;
	}
	else
	{
		printf("\n\nDo you wish to print the changed automata? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			printAutomata(provisory);
			freeAutomata(provisory);
		}

		printf("\n\nDo you wish to print the changed automata to a file? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			writeAutomataToFile(provisory);
			freeAutomata(provisory);
		}
	}
	free(new_automata_info);
	printf("\n\n\n-----------Product ended-----------\n\n\n");
}

void writeAutomataToFile(automato* load_automata)
{
	printf("\n\n\n-----------Writing automata to file-----------\n\n\n");
	int i = 0, j = 0, x = 0, z = 0;
	char buffer[1000];
	x = x + strlen("STATES\r\n") + 1;
	char* new_automata_info;

	new_automata_info = (char*)malloc(sizeof(char)*x);
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcpy(new_automata_info, "STATES\r\n\0");

	for (i = 0; i < load_automata->states.size; i++)
	{
		x = x + strlen(load_automata->states.string[i]) + strlen("\r\n") + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, load_automata->states.string[i]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "\r\n\0");
	}

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
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


	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "TRANSITIONS\r\n\0");


	for (i = 0; i < load_automata->states.size; i++)
	{
		for (j = 0; j < load_automata->events.size; j++)
		{
			if (load_automata->transitions[i][j]->size != 0)
			{
				for (z = 0; z < load_automata->transitions[i][j]->size; z++)
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

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "INITIAL\r\n\0");

	x = x + strlen(load_automata->states.string[load_automata->initial]) + strlen("\r\n") + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, load_automata->states.string[load_automata->initial]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "\r\n\0");


	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "MARKED\r\n\0");


	for (i = 0; i < load_automata->marked.size; i++)
	{
		for (j = 0; j < load_automata->states.size; j++)
		{
			if ((load_automata->states.string[j] == load_automata->states.string[load_automata->marked.values[i]]))
			{
				x = x + strlen(load_automata->states.string[load_automata->marked.values[i]]) + strlen("\r\n") + 2;
				strcat(new_automata_info, load_automata->states.string[load_automata->marked.values[i]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
		}
	}
	printf("\n\n\nInsert path file\n\n\n");
	scanf("%s", &buffer);
	getchar();
	FILE* fp;
	fp = fopen(buffer, "w");
	memset(buffer, 0, 1000);
	fprintf(fp, new_automata_info);
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
	int  parser_state = 0, i = 0, index = 0, j = 0, x = 0, y = 0, z = 0, states_test = 0, events_test = 0, initial_test = 0, marked_test = 0;
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
			if (strcmp(line, "") != 0)
			{
				if (load_automata->states.size != 0)
				{
					for (i = 0; i < load_automata->states.size; i++)
					{
						if (strcmp(line, load_automata->states.string[i]) == 0)
							states_test++;
					}
					if (states_test == 0)
						stringPushBack(&(load_automata->states), line);
					else
						states_test = 0;
				}
				else
					stringPushBack(&(load_automata->states), line);
			}
			break;

			//event case
		case 2:
			if (strcmp(line, "") != 0)
			{
				if (load_automata->events.size != 0)
				{
					for (i = 0; i < load_automata->events.size; i++)
					{
						if (strcmp(line, load_automata->events.string[i]) == 0)
							events_test++;
					}
					if (events_test == 0)
						stringPushBack(&(load_automata->events), line);
					else
						events_test = 0;
				}
				else
					stringPushBack(&(load_automata->events), line);
			}
			break;

			//transition case
		case 3:
			if (strcmp(line, "") != 0)
			{
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
						printf("Invalid transition in file. Correct this transition:\n\nPress enter to continue\n");
						puts(line);
						load_automata->error = 1;
						return;
					}

					//when it's not an event
					if (i == 0)
					{

						//confirm if there are states in the transitions vector
						trs_state_index = findItemStringVector(trs_line, load_automata->states);
						if (trs_state_index == load_automata->states.size)
						{
							printf("Invalid state being used on the transition. Correct this transition:\n\nPress enter to continue\n");
							puts(line);
							load_automata->error = 1;
							return;
						}
					}
					if (i == 2)
					{

						//confirm if there are states in the transitions vector
						second_trs_state_index = findItemStringVector(trs_line, load_automata->states);
						if (second_trs_state_index == load_automata->states.size)
						{
							printf("Invalid state being used on the transition. Correct this transition:\n\nPress enter to continue\n");
							puts(line);
							load_automata->error = 1;
							return;
						}
					}
					if (i == 1)
					{

						trs_event_index = findItemStringVector(trs_line, load_automata->events);
						if (trs_event_index == load_automata->events.size)
						{
							printf("Invalid event being used on the transition. Correct this transition:\n\nPress enter to continue\n");
							puts(line);
							load_automata->error = 1;
							return;
						}
					}

				}
				if (load_automata->transitions[trs_state_index][trs_event_index]->size != 0)
				{
					for (i = 0; i < load_automata->transitions[trs_state_index][trs_event_index]->size; i++)
					{
						if (load_automata->transitions[trs_state_index][trs_event_index]->values[i] == second_trs_state_index)
							trs_test++;
					}
					if (trs_test == 0)
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
			}
			break;

		case 4:

			if (strcmp(line, "") != 0)
			{
				for (j = 0; j < load_automata->states.size; j++)
				{
					if (strcmp(line, load_automata->states.string[j]) == 0)
					{
						load_automata->initial = j;
						initial_test++;
					}
				}

				if (initial_test > 1)
				{
					printf("More than one initial state. Press enter to continue!\n");
					load_automata->error = 1;
					return;
				}
			}


			break;

		case 5:
			if (strcmp(line, "") != 0)
			{
				for (x = 0; x < load_automata->states.size; x++)
				{
					if (strcmp(line, load_automata->states.string[x]) == 0)
					{
						if (load_automata->marked.size != 0)
						{
							for (i = 0; i < load_automata->marked.size; i++)
							{
								if (load_automata->marked.values[i] == x)
									marked_test++;

							}
							if (marked_test == 0)
								intVectPushBack(&(load_automata->marked), x);
							else
								marked_test = 0;
						}
						else
							intVectPushBack(&(load_automata->marked), x);
					}
				}
			}
			break;

		default:
			printf("\nParser error!Automata's file not correct!\n\nPress enter to continue\n");
			load_automata->error = 1;
			return;
		}
	}

	free(line);
	free(trs_line);

	if (load_automata->states.size == 0)
	{
		printf("There are no states in the automata!\n\nPress enter to continue\n");
		load_automata->error = 1;
		return;
	}

	if (load_automata->events.size == 0)
	{
		printf("There are no events in the automata!\n\nPress enter to continue\n");
		load_automata->error = 1;
		return;
	}

	if (load_automata->marked.size == 0)
	{
		printf("There are no marked states in the automata\n\nPress enter to continue\n");
		load_automata->error = 1;
		return;
	}


	if (initial_test == 0)
	{
		printf("There is no initial state in this automata!\n\nPress enter to continue\n");
		load_automata->error = 1;
		return;
	}


	if (load_automata->transitions == NULL)
	{
		printf("There are no transitions in this automata!\n\nPress enter to continue\n");
		getchar();
		getchar();
		load_automata->error = 1;
		return;
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

//recursive function that creates the states that result in the product two automatons
void productStatescreation(product* load_product, automato* load_automata1, automato* load_automata2, int product_state_index)
{
	int  i = 0, j = 0, z = 0, x = 0, y = 0, k = 0, dummy = 0, trs1_provisory_value = 0, trs2_provisory_value = 0;

	for (i = 0; i < load_automata1->events.size; i++)
	{
		for (j = 0; j < load_automata2->events.size; j++)
		{
			//they must share the same event
			if (strcmp(load_automata1->events.string[i], load_automata2->events.string[j]) == 0)
			{
				//both of them must have transitions with the same event
				if ((load_automata1->transitions[load_product->product_states[product_state_index].values[0]][i]->size != 0) && (load_automata2->transitions[load_product->product_states[product_state_index].values[1]][j]->size != 0))
				{
					//check if the state already exists in memory
					for (z = 0; z < load_product->product_states_size; z++)
					{
						if ((load_product->product_states[z].values[0] == load_automata1->transitions[load_product->product_states[product_state_index].values[0]][i]->values[0]) && (load_product->product_states[z].values[1] == load_automata2->transitions[load_product->product_states[product_state_index].values[1]][j]->values[0]))
						{
							dummy++;
						}
					}

					//if it doesn't add the new state
					if (dummy == 0)
					{

						trs1_provisory_value = load_automata1->transitions[load_product->product_states[product_state_index].values[0]][i]->values[0];
						trs2_provisory_value = load_automata2->transitions[load_product->product_states[product_state_index].values[1]][j]->values[0];
						load_product->product_states = (int_vector*)realloc(load_product->product_states, sizeof(int_vector)*(load_product->product_states_size + 1));
						load_product->product_states[load_product->product_states_size].size = 0;

						intVectPushBack(&(load_product->product_states[load_product->product_states_size]), trs1_provisory_value);
						intVectPushBack(&(load_product->product_states[load_product->product_states_size]), trs2_provisory_value);
						load_product->product_states_size++;

						//and the function is called recursively with each new state
						productStatescreation(load_product, load_automata1, load_automata2, load_product->product_states_size - 1);
					}

					else
					{
						dummy = 0;
					}

				}

			}
		}
	}
}



parallel* newParallel()
{
	parallel* new_parallel;
	new_parallel = (parallel*)malloc(sizeof(parallel));
	resetParallelStructure(new_parallel);
	return new_parallel;
}


void resetParallelStructure(parallel* load_parallel)
{
	load_parallel->error = 0;
	load_parallel->parallel_trs_size = 0;
	load_parallel->parallel_events.size = 0;
	load_parallel->parallel_states_size = 0;
	load_parallel->parallel_states = NULL;
	load_parallel->parallel_states_trs = NULL;
}

void freeParallelStructure(parallel* load_parallel)
{
	int i = 0, j = 0;

	if (load_parallel->parallel_states_size != 0)
	{
		for (i = 0; i < load_parallel->parallel_states_size; i++)
		{
			for (j = 0; j < load_parallel->parallel_events.size; j++)
			{
				if (load_parallel->parallel_states_trs[i][j].size != 0)
				{
					free(load_parallel->parallel_states_trs[i][j].values);
				}
			}
			free(load_parallel->parallel_states_trs[i]);
		}
		free(load_parallel->parallel_states_trs);
	}

	if (load_parallel->parallel_states_size != 0)
	{
		for (i = 0; i < load_parallel->parallel_states_size; i++)
		{
			if (load_parallel->parallel_states[i].size > 0)
			{
				free(load_parallel->parallel_states[i].values);
			}
		}
		free(load_parallel->parallel_states);
	}

	if (load_parallel->parallel_events.size != 0)
	{
		for (i = 0; i < load_parallel->parallel_events.size; i++)
		{
			free(load_parallel->parallel_events.string[i]);
		}
		free(load_parallel->parallel_events.string);
	}

	resetParallelStructure(load_parallel);
}

void freeParallel(parallel* load_parallel)
{
	freeParallelStructure(load_parallel);
	free(load_parallel);
}


automata_array* newAutomatonArray()
{
	automata_array* new_array;
	new_array = (automata_array*)malloc(sizeof(automata_array));
	resetAutomataArrayStructure(new_array);
	return new_array;
}


resetAutomataArrayStructure(automata_array* load_array)
{
	load_array->automata = NULL;
	load_array->automata_name.size = 0;
	load_array->automata_number = 0;
}


//recursive function that creates the states that result of the parallel between two automatons
void parallelStatescreation(parallel* load_parallel, automato* load_automata1, automato* load_automata2, int parallel_state_index)
{
	int  i = 0, j = 0, z = 0, x = 0, y = 0, k = 0, dummy = 0, trs1_provisory_value = 0, trs2_provisory_value = 0, automata1_event = 0, automata2_event = 0;

	//check the global events that exist in the parallel automata (Reunion of the events)
	for (y = 0; y < load_parallel->parallel_events.size; y++)
	{
		for (i = 0; i < load_automata1->events.size; i++)
		{
			for (j = 0; j < load_automata2->events.size; j++)
			{
				//this situtation is equal to the product . When both of automatons have the same event 
				if (strcmp(load_automata1->events.string[i], load_automata2->events.string[j]) == 0 && (strcmp(load_parallel->parallel_events.string[y], load_automata1->events.string[i]) == 0))
				{
					//if both of them have transitions with the same event 
					if ((load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->size != 0) && (load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->size != 0))
					{
						//and if the resultant pair is different of any parallel state ( avoid states repetition)
						for (z = 0; z < load_parallel->parallel_states_size; z++)
						{
							if ((load_parallel->parallel_states[z].values[0] == load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->values[0]) && (load_parallel->parallel_states[z].values[1] == load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->values[0]))
							{
								dummy++;
							}
						}
						//if it isn't repeated save the new state
						if (dummy == 0)
						{

							trs1_provisory_value = load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->values[0];
							trs2_provisory_value = load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->values[0];
							load_parallel->parallel_states = (int_vector*)realloc(load_parallel->parallel_states, sizeof(int_vector)*(load_parallel->parallel_states_size + 1));
							load_parallel->parallel_states[load_parallel->parallel_states_size].size = 0;

							intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs1_provisory_value);
							intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs2_provisory_value);
							load_parallel->parallel_states_size++;

							//call the function again with the new state
							parallelStatescreation(load_parallel, load_automata1, load_automata2, load_parallel->parallel_states_size - 1);
						}

						else
						{
							dummy = 0;
						}
					}
				}
				else
				{
					dummy = 0;

					//the situation that the first automaton has an event that the 2nd hasn't
					if (strcmp(load_parallel->parallel_events.string[y], load_automata1->events.string[i]) == 0)
					{
						automata1_event = i;
						dummy++;
					}

					//if the 1st automaton doesn't have the event
					if (dummy == 0)
					{
						automata1_event = -1;
					}
					else
						dummy = 0;

					//if the first automaton has that event check if the 2nd doesn't have it
					if (automata1_event != -1)
					{
						for (x = 0; x < load_automata2->events.size; x++)
						{

							if (strcmp(load_parallel->parallel_events.string[automata1_event], load_automata2->events.string[x]) == 0)
							{
								automata2_event = x;
								dummy++;
								break;
							}

						}
						if (dummy == 0)
						{
							automata2_event = -1;
						}
						else
							dummy = 0;
					}
					else
						automata2_event = -1;

					//if only the 1st has the event
					if (automata1_event != -1)
					{
						if (automata2_event == -1)
						{
							//if there are transitions with that event
							if (load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->size != 0)
							{
								//confirm that the state isn't repeated
								for (z = 0; z < load_parallel->parallel_states_size; z++)
								{
									if ((load_parallel->parallel_states[z].values[0] == load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->values[0]) && (load_parallel->parallel_states[z].values[1] == load_parallel->parallel_states[parallel_state_index].values[1]))
									{
										dummy++;
									}
								}

								//if it isn't repeated save the new state
								if (dummy == 0)
								{

									trs1_provisory_value = load_automata1->transitions[load_parallel->parallel_states[parallel_state_index].values[0]][i]->values[0];
									trs2_provisory_value = load_parallel->parallel_states[parallel_state_index].values[1];
									load_parallel->parallel_states = (int_vector*)realloc(load_parallel->parallel_states, sizeof(int_vector)*(load_parallel->parallel_states_size + 1));
									load_parallel->parallel_states[load_parallel->parallel_states_size].size = 0;

									intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs1_provisory_value);
									intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs2_provisory_value);
									load_parallel->parallel_states_size++;

									//call the function with the new state
									parallelStatescreation(load_parallel, load_automata1, load_automata2, load_parallel->parallel_states_size - 1);
								}
								else
								{
									dummy = 0;
								}
							}
						}
					}


					dummy = 0;

					//the same is made when there is an event of the 2nd automaton and not on the first
					if (strcmp(load_parallel->parallel_events.string[y], load_automata2->events.string[j]) == 0)
					{
						automata2_event = j;
						dummy++;
					}

					if (dummy == 0)
					{
						automata2_event = -1;
					}
					else
						dummy = 0;

					if (automata2_event != -1)
					{
						for (x = 0; x < load_automata1->events.size; x++)
						{
							if (strcmp(load_parallel->parallel_events.string[automata2_event], load_automata1->events.string[x]) == 0)
							{
								automata1_event = x;
								dummy++;
								break;
							}

						}
						if (dummy == 0)
						{
							automata1_event = -1;
						}
						else
							dummy = 0;
					}
					else
					{
						automata1_event = -1;
					}



					if (automata2_event != -1)
					{


						if (automata1_event == -1)
						{

							if (load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->size != 0)
							{


								for (z = 0; z < load_parallel->parallel_states_size; z++)
								{
									if ((load_parallel->parallel_states[z].values[0] == load_parallel->parallel_states[parallel_state_index].values[0]) && (load_parallel->parallel_states[z].values[1] == load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->values[0]))
									{
										dummy++;
									}
								}

								if (dummy == 0)
								{

									trs1_provisory_value = load_parallel->parallel_states[parallel_state_index].values[0];
									trs2_provisory_value = load_automata2->transitions[load_parallel->parallel_states[parallel_state_index].values[1]][j]->values[0];

									load_parallel->parallel_states = (int_vector*)realloc(load_parallel->parallel_states, sizeof(int_vector)*(load_parallel->parallel_states_size + 1));
									load_parallel->parallel_states[load_parallel->parallel_states_size].size = 0;

									intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs1_provisory_value);
									intVectPushBack(&(load_parallel->parallel_states[load_parallel->parallel_states_size]), trs2_provisory_value);
									load_parallel->parallel_states_size++;

									parallelStatescreation(load_parallel, load_automata1, load_automata2, load_parallel->parallel_states_size - 1);
								}
								else
								{
									dummy = 0;
								}
							}
						}
					}
				}
			}
		}
	}
}

//function that writes the parallel result in the .aut format. Also it gives the user the choice of saving the automata in memory...
//...or print it in the console or writing it to a file.
void writeParallelAutomata(automata_array* automata_vector ,automato* automata1, automato* automata2, parallel* load_parallel)
{
	int i = 0, j = 0, x = 0, z = 0, y = 0, k = 0;
	int* valid_events;
	x = x + strlen("STATES\r\n");
	char* new_automata_info;
	int* buffer[1000];
	char* buffer_name[1000];
	char c;
	new_automata_info = malloc(x);
	x = x + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcpy(new_automata_info, "STATES\r\n\0");

	for (i = 0; i < load_parallel->parallel_states_size; i++)
	{
		x = x + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, "{");
		strcat(new_automata_info, "\0");

		x = x + strlen(automata1->states.string[load_parallel->parallel_states[i].values[0]]) + strlen(",") + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, automata1->states.string[load_parallel->parallel_states[i].values[0]]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, ",\0");

		x = x + strlen(automata2->states.string[load_parallel->parallel_states[i].values[1]]) + strlen("\r\n") + 3 + strlen("}");
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, automata2->states.string[load_parallel->parallel_states[i].values[1]]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "}");
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "\r\n\0");
	}

	x = x + strlen("EVENTS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "EVENTS\r\n\0");



	for (i = 0; i < load_parallel->parallel_events.size; i++)
	{
		x = x + strlen(load_parallel->parallel_events.string[i]) + strlen("\r\n") + 2;
		new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
		strcat(new_automata_info, load_parallel->parallel_events.string[i]);
		strcat(new_automata_info, "\0");
		strcat(new_automata_info, "\r\n\0");
	}



	x = x + strlen("TRANSITIONS\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "TRANSITIONS\r\n\0");

	for (i = 0; i < load_parallel->parallel_states_size; i++)
	{

		for (j = 0; j < load_parallel->parallel_events.size; j++)
		{
			if (load_parallel->parallel_states_trs[i][j].size != 0)
			{

				x = x + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, "{");
				strcat(new_automata_info, "\0");

				x = x + strlen(automata1->states.string[load_parallel->parallel_states[i].values[0]]) + strlen(",") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata1->states.string[load_parallel->parallel_states[i].values[0]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ",\0");

				x = x + strlen(automata2->states.string[load_parallel->parallel_states[i].values[1]]) + strlen(";") + 3 + strlen("}");
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata2->states.string[load_parallel->parallel_states[i].values[1]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "}");
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ";");


				x = x + strlen(load_parallel->parallel_events.string[j]) + strlen(";") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, load_parallel->parallel_events.string[j]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ";\0");

				z = 0;
				z = load_parallel->parallel_states_trs[i][j].values[0];

				x = x + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, "{");
				strcat(new_automata_info, "\0");

				x = x + strlen(automata1->states.string[load_parallel->parallel_states[z].values[0]]) + strlen(",") + 2;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata1->states.string[load_parallel->parallel_states[z].values[0]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, ",\0");

				x = x + strlen(automata2->states.string[load_parallel->parallel_states[z].values[1]]) + strlen(";") + strlen("\r\n") + 4;
				new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
				strcat(new_automata_info, automata2->states.string[load_parallel->parallel_states[z].values[1]]);
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "}");
				strcat(new_automata_info, "\0");
				strcat(new_automata_info, "\r\n\0");
			}
		}
	}

	x = x + strlen("INITIAL\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "INITIAL\r\n\0");

	int dummy = 0;

	x = x + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, "{");
	strcat(new_automata_info, "\0");

	x = x + strlen(automata1->states.string[load_parallel->parallel_states[0].values[0]]) + strlen(",") + 2;
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, automata1->states.string[load_parallel->parallel_states[0].values[0]]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, ",\0");

	x = x + strlen(automata2->states.string[load_parallel->parallel_states[0].values[1]]) + strlen("\r\n") + 3 + strlen("}");
	new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
	strcat(new_automata_info, automata2->states.string[load_parallel->parallel_states[0].values[1]]);
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "}");
	strcat(new_automata_info, "\0");
	strcat(new_automata_info, "\r\n\0");

	x = x + strlen("MARKED\r\n") + 1;
	new_automata_info = (char*)realloc(new_automata_info, x * sizeof(char));
	strcat(new_automata_info, "MARKED\r\n\0");
	int marked = 0;


	for (i = 0; i < load_parallel->parallel_states_size; i++)
	{
		for (j = 0; j < automata1->marked.size; j++)
		{
			if (load_parallel->parallel_states[i].values[0] == automata1->marked.values[j])
			{
				for (k = 0; k < automata2->marked.size; k++)
				{
					if (load_parallel->parallel_states[i].values[1] == automata2->marked.values[k])
					{
						x = x + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, "{");
						strcat(new_automata_info, "\0");

						x = x + strlen(automata1->states.string[load_parallel->parallel_states[i].values[0]]) + strlen(",") + 2;
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata1->states.string[load_parallel->parallel_states[i].values[0]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, ",\0");

						x = x + strlen(automata2->states.string[load_parallel->parallel_states[i].values[1]]) + strlen("\r\n") + 3 + strlen("}");
						new_automata_info = (char*)realloc(new_automata_info, (x * sizeof(char)));
						strcat(new_automata_info, automata2->states.string[load_parallel->parallel_states[i].values[1]]);
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "}");
						strcat(new_automata_info, "\0");
						strcat(new_automata_info, "\r\n\0");
					}
				}
			}
		}
	}


	freeParallel(load_parallel);

	//user choices
	printf("\n\nDo you wish to save the parallel result? Press 1 if yes, any other number if not \n\n");
	while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
	if (i == 1)
	{
		dummy = 0;

		while (dummy == 0)
		{
			printf("Write the new automata name\n\n");
			scanf("%s", buffer_name);
			getchar();

			for (z = 0; z < automata_vector->automata_number; z++)
			{
				if (strcmp(buffer_name, automata_vector->automata_name.string[z]) == 0)
				{
					dummy = 0;
					printf("\n\nThis automata has already been loaded! Press enter to continue! \n\n");
					break;
				}
				dummy = 1;
			}
		}


		automata_vector->automata = (automato**)realloc(automata_vector->automata, sizeof(automato*)*(automata_vector->automata_number + 1));
		automata_vector->automata[automata_vector->automata_number] = new_automata();
		stringPushBack(&(automata_vector->automata_name), buffer_name);
		memset(buffer, 0, 1000);

		parser(automata_vector->automata[automata_vector->automata_number], new_automata_info);
		automata_vector->automata_number++;
	}
	else
	{
		printf("\n\nDo you wish to print the changed automata? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			printAutomata(provisory);
			freeAutomata(provisory);
		}

		printf("\n\nDo you wish to print the changed automata to a file? Press 1 if yes, any other number if not \n\n");
		while ((scanf("%d%c", &i, &c) != 2 || c != '\n') && clean_stdin());
		if (i == 1)
		{
			automato* provisory;
			provisory = new_automata();
			parser(provisory, new_automata_info);
			writeAutomataToFile(provisory);
			freeAutomata(provisory);
		}
	}
	free(new_automata_info);
	printf("\n\n\n-----------Parallel ended-----------\n\n\n");
}


//function that deletes an automaton chosen by the user
void deleteAutomata(automata_array* automata_vector, string_vector* automata_name, int automata_to_delete)
{
	int i = 0;
	//frees the memory of the mentioned automata
	freeAutomata(automata_vector->automata[automata_to_delete]);
	
	//changes the array positions if necessary
	if (automata_to_delete + 1 < automata_vector->automata_number)
	{
		for (i = automata_to_delete; i <  automata_vector->automata_number - 1; i++)
		{
			automata_vector->automata[i] = automata_vector->automata[i + 1];
		}
	}

	//frees the memory of the name of the said automaton
	free(automata_name->string[automata_to_delete]);

	//changes the array positions if necessary.
	if (automata_to_delete + 1 <  automata_vector->automata_number)
	{
		for (i = automata_to_delete; i <  automata_vector->automata_number - 1; i++)
		{
			automata_name->string[i] = automata_name->string[i + 1];

		}
	}

	//if there are more than one automaton there is the need to reallocate everything
	if (automata_vector->automata_number > 1)
	{
		automata_vector->automata_number--;
		automata_vector->automata = (automato**)realloc(automata_vector->automata, sizeof(automato*)* automata_vector->automata_number);
		automata_name->string = (char**)realloc(automata_name->string, sizeof(char*)*automata_vector->automata_number);
		automata_name->size--;
	}
	
	//otherwise just free the memory and redefine the size of each variable
	else
	{
		
		automata_name->size = 0;
		free(automata_name->string);
		automata_vector->automata_number=0;
		free(automata_vector->automata);
	}

}


//----------------------------------------------------------------Private functions----------------------------------------------------------------//