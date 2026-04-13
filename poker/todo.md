1. methods called by routes return HTTP codes
2. validate input
3. all in logic -> round_end but should progress round / deal streets then go to distribute_winnings

current:

	everyone match -> progress street (deal cards, do showdown)
	someone off -> dont update state
	penultimate player folds -> give winnings to last player, reset
	
wanted:
	n-1 players all in -> deal last streets, give winnings, reset
