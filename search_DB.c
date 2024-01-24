#include "invertedIndex.h"
void search_DB(wlist_t *head, char *word) 
{ 
    if(head == NULL)                                //checks if there is any word present
    {
	    printf("No word is found\n");               //prints statement
    }
    while(head)                                     //traverses till end
    { 
	    if(strcmp(head -> word, word) == 0)         //if word matches
	    {
	        printf("Word %s is found in %d file\n", head->word,head-> f_count);         //displays the word with its location in file
    	    table_link_t *Temp = head-> t_link;
	        while(Temp)
	        {
		        printf("In file : %s\t%d times \n", Temp -> f_name, Temp -> w_count);
        		Temp = Temp -> link;
	        }
	        return;
    	}
	    head = head-> link;
    }
    printf("Error: The word to be searched is not found in the list\n");
}
