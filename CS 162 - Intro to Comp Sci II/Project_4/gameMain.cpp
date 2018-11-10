/*********************************************************************
** Program Name: Fantasy Tournament
** Author: Jacob Leno
** Date:  11/17/17
** Description: This program is a fantasy tournament in which there are 
** two teams. The player(s) can choose from five different characters to 
** populate each of their teams and assign each of the characters names.
** Each team can consist of up to 10 characters of any type. Once both 
** teams have chosen their characters they will fight to the death. The
** Team that wins the most matches wins!
*********************************************************************/

#include "FantasyTournament.hpp"


int main()
{
	FantasyTournament gameStart;
	
	gameStart.gameplay();
	
	return 0;
}
