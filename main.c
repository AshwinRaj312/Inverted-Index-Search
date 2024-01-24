/*
NAME        : ASHWIN RAJ K 
DESCRIPTION : DATA STRUCTURES PROJECT - INVERTED SEARCH 
DATE        : 18/08/2023
*/
#include "invertedIndex.h"

int main(int argc, char *argv[])
{
    //Check CLA's Passed or not
    if (argc == 1)
    {
        printf("Error : Invalid no.of arguments\nUsage ./inverted_index <file.txt> <file1.txt> ...\n");
        return FAILURE;
    }
 
    file_node_t *fhead = NULL;                                      //declaring pointer
    validate_n_store_filenames(&fhead, argv + 1);                   //function call to validate and store filenames

    if (fhead == NULL)                                              //checking whether pointer is null        
    {
        printf("There is no valid files\nPlease pass the valid file\n");
        return FAILURE;
    }

    //Display the menu
    wlist_t *HT_head[27] = {NULL};                           //declaration of variables   
    int choice;
    char option,word[15];
    do
    {
	printf("Select your choice from options:\n1.Create Database\n2.Display Database\n3.Update Database\n4.Search\n5.Save Database\nEnter your choice:");
	scanf("%d", &choice);
    switch(choice)                                          //function call with respect to choice
	{ 
	    case 1:
		    create_DB(fhead,HT_head);
		    break;
		
	    case 2:
	    	display_DB(HT_head);
		    break;
 
	    case 3:
	    	update_DB(&fhead,HT_head);
		    break;
	    
        case 4:
	    	printf("Enter the word that you want to search:");
		    scanf("%s",word);
	    	search_DB(HT_head[tolower(word[0])%97],word);
		    break;
	    
        case 5:
		    save_DB(HT_head);
		    break;

	    default:
		    break;

	}
    printf("Do you want to continue (y/n): ");
	getchar();
	scanf("%c",&option);

    }while(option == 'Y' || option == 'y');                             //condition to continue the loop
}

void validate_n_store_filenames(file_node_t **fhead, char *filenames[]) 
{
    int i = 0, status;                                                  //variables declaration
    while (filenames[i] != NULL)                                        //checking if filename is not null    
    {
        status = IsFileValid(filenames[i]);                             //function call to indicate the file status    
        if (status == NOT_PRESENT)                                      //checks if file not present
        {
            printf("The file %s does not exist\n", filenames[i]);
        }
        else if (status == FILE_EMPTY)                                  //checks if file is empty
        {
            printf("The file %s is an empty file\n", filenames[i]);
        }
        else
        {
            if (store_filenames_to_list(filenames[i], fhead) == REPEATED)   //checks if file is repeated
                printf("The file %s is repeated\n", filenames[i]);
            else
                printf("Successfull: Adding the file %s into the list\n", filenames[i]);
        }
        i++;
    }
}

int IsFileValid(char *f_name)
{
    //1. Check whether the file exist or not.
        //If the file not exist, then return NOT_PRESENT
    //2. If the file is exist, then check it is empty or not
        //If file empty, FILE_EMPTY

    //3. If file not empty, then return SUCCESS
    FILE *fptr = fopen(f_name,"r");         //opening file f_name in read only mode    
    if(fptr==NULL)                          //checks whether file exist or not    
    {
	    return NOT_PRESENT;
    }
    fseek(fptr,0L,SEEK_END);                //file pointer moved to end of the file
    if(ftell(fptr)==0)                      //checks if file is empty            
    {
	    return FILE_EMPTY;
    }
    return SUCCESS;                         //returns SUCCESS if file is not empty    
}

file_node_t *create_node(char *fname)
{
    file_node_t *new = malloc(sizeof(file_node_t));
    
    strcpy(new -> f_name,fname);            //storing file name
    new -> link = NULL;
    return new;
} 

int store_filenames_to_list(char *f_name, file_node_t **head)
{
    file_node_t *new;
    //Insert at last operation
    if (*head == NULL)
    {
        new = create_node(f_name);
        *head = new;
        return SUCCESS;
    }

    file_node_t *temp = *head,*prev=NULL;

    while (temp != NULL)                                        //traversing through the list            
    {
        // TODO: previous pointer, which points to previous node
        if (strcmp(temp -> f_name, f_name) != 0)                //checks if the file name is different from the file name already present
        {
            prev = temp;    
            temp = temp -> link;
        }
        else                                                   //returns repeated if same 
            return REPEATED;
    }
    prev -> link  = create_node(f_name);                        //updating the link of prev with the new file name
    return SUCCESS;
} 
