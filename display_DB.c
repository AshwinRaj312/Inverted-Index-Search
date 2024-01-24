#include "invertedIndex.h"
void display_DB(wlist_t **head) 
{  
    printf("[index] [word] filecount file/s : file_name word_count\n");         //prints database
    printf("\n----------------------------------------------------\n");
    for(int i=0;i<27;i++)                                                       //loop for hash table
    {
	    wlist_t *temp = head[i];                                                //local reference
	    while(temp)                                                         	//Traversing till last node
	    {
	        printf("[%d] [%s] %d files :\t", i, temp -> word,temp->f_count);
	        table_link_t *Temp2 = temp -> t_link;
	        while(Temp2)                                                    	//Traverse through link
	        {
		        printf("%s %d   ", Temp2 -> f_name,Temp2 -> w_count);
        		Temp2 = Temp2 -> link;											//updating Temp2
	        }
	        printf("\n");
	        temp = temp -> link;												//updating temp
    	}
    }
    printf("\n----------------------------------------------------\n");
}
