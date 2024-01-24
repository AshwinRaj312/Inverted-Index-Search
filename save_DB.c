#include "invertedIndex.h"  
void save_DB(wlist_t *head[])
{
    char f_name[NAMELENGTH];                                
    printf("Enter the file name that you want to save : ");  //statement displayed followed by string user input
    scanf("%s", f_name);
    FILE *fptr = fopen(f_name, "w");                        //Opens file name in write mode
    if(fptr == NULL)                                        //checks whether file is not present
    {
	    printf("Error : File is not present\n");             //if true then returns with statement
	    return;
    } 
    wlist_t *temp = NULL;                                   //declaring local reference
    for(int index=0;index<27;index++)                               
    {
		temp = head[index];
    	while(temp)                                         //traversing through the list in the table   
       	{
    	    fprintf(fptr, "#:%d\n%s:%d:",index,temp->word,temp->f_count);
    	    table_link_t *new = temp -> t_link;
    	    while(new)										
    	    {
    		    fprintf(fptr, "%s:%d:#", new -> f_name, new -> w_count);
    		    new = new -> link;
    	    }
    	    fprintf(fptr,"\n");
    	    temp=temp->link; 
    	}
    }
    printf("Database saved successfully in %s\n",f_name);                       //displays statement and closes the file
    fclose(fptr);
}