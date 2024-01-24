#include "invertedIndex.h"
void update_DB(file_node_t **f_head, wlist_t **head)
{ 
    int status,result;                                              //declaring variables        
    char file[NAMELENGTH];
    printf("Enter the filename that you want to add in database : ");
    scanf("%s",file);
    status=IsFileValid(file);                                       //function call to validate the file to update
    if(status==NOT_PRESENT)                                     //checking if status is eqaul to NOT_PRESENT
    {
        printf("The file %s is not present\n", file);
        printf("Hence we are not adding this file into database");
        return;
    }
    else if(status==FILE_EMPTY)                                 //checks if status is file empty
    {
        printf("The file %s is empty\nHence we are not adding %s into database",file,file);
        return;
    }
    else
    {
        result = store_filenames_to_list(file,f_head);   //function call to check the file existance in database and returns success if file does not already exist       
        if(result == SUCCESS)                           //checking if result is equal to SUCCESS
        {
        	printf("Successfully updated the file into database");
        }
        else if(result == REPEATED)                     //checking if result is equal to REPEATED
        {
	        printf("File is repeated\nSo we cannot update file into database");
	        return;
        }
        else                                            //if result is other than SUCCESS or REPEATED, file doesnt even exist    
        {
	        printf("Failed to update the file into database");
	        return;
        }
        file_node_t *temp = *f_head;                                            //updating file into database
        while(temp)                                                             //traversing to find the file    
        {
        	if(strcmp(temp ->f_name,file)==0)                                   //if filename matches
	        {
	            create_DB(temp,head);                                       //function call to update
	            return;
	        }
	        temp = temp -> link;
        }   
        printf("Database updated successfully\n");
    }
}

