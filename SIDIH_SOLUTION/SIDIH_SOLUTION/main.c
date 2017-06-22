//FUMAC 2016/2017 
//1130625 - Nuno Viana
//1130691 - Pedro Guedes

#include "automato.h"

//main function of the automata's project
void main(void)
{
	int i = 0, j = 0;
	//automata type's being a pointer in order to be altered throughout the functions
	automato* automata;
	while (1)
	{
		automata = new_automata();

		load_file(automata, "Example.aut");
		printAutomata(automata);
		checkAccessibilty(automata);
		//checkCoaccessibilty(automata);
		dfaOrNfa(automata);
		nfaToDfa(automata, automata->deterministic);
		dfaCanonical(automata);
		printAutomata(automata);
		freeAutomata(automata);
		getchar();
	}
	
	
}