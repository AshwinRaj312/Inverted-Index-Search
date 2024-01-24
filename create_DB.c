#include "invertedIndex.h"
 
int create_DB(file_node_t *file_head, wlist_t **head)
{
    while (file_head)
    {
        read_datafile(head, file_head -> f_name);
        file_head  = file_head -> link;
    }
}

void read_datafile(wlist_t **head, char *f_name)
{
    FILE *fptr = fopen(f_name, "r");                            //opening file

    char word[15];
    int index, flag = 1;

    if(fptr == NULL)                                            //checks if pointer is null
       	printf("Error in opening %s file\n",*f_name);

    while (fscanf(fptr, "%s", word) != EOF)                    
    {
        flag = 1;
        index =  tolower(word[0]) % 97;                 // Only for lower case, TODO: Uppercase and non-alphabet
    	if(!(index >= 0 && index <= 25))                //Characters other than alphabets
            index=26;

        if (head[index] != NULL)
        {
            wlist_t *temp = head[index];                //Creating local reference
            while (temp)                                //traversing
            {                                                        
                if (strcmp(temp -> word, word))         //Checking if the word matches
                {
                    temp = temp -> link;
                }
                else
                {
                    update_word_count(&temp, f_name);
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 1)                                  //checking if flag is 1    
            insert_at_last_main(&head[index], word, f_name);
    }
    printf("Successfull : Creation of database for file %s\n", f_name);
}
int update_word_count(wlist_t **head, char *f_name)
{
    /*TODO: Create local reference for table link node
      table_link_t *t = temp -> t_link
      Run the loop and check whether filename matching or not
      1) If filename matches, increment the wordcount in respective table link node, return SUCCESS.
      2) If filaname not  matches, you reached end of the list,
      2.1) Create table link node, and insert the node as last in the table link list.
      update_link_table(temp, f_name);
      return SUCCESS
     */
    table_link_t *tab = (*head) -> t_link, *prev= NULL;               //local reference created
    while(tab)
    {
	    if(strcmp(tab ->f_name,f_name)==0)                            //if file name matches, increment wordcount
	    {
	        //update word count
	        tab->w_count++;
	        return SUCCESS;
	    }
        prev=tab;
	    tab=tab-> link;
    }
    (*head) -> f_count++;                                           //increments and update file count    
    table_link_t *new = malloc(sizeof(table_link_t));
    if(new == NULL)
    {
	return FAILURE;
    }
    
    //updating the table link value
    strcpy(new -> f_name,f_name);
    new ->w_count = 1;
    new -> link = NULL;

    prev -> link = new;
    return SUCCESS;
}
int insert_at_last_main(wlist_t **head, char *word, char *f_name)
{
    //Create a node
    wlist_t *new = malloc(sizeof(wlist_t));

    //Validate new
    if(new == NULL)
    {
	return FAILURE;
    }
    //Update fields
    new -> f_count = 1;
    strcpy(new -> word,word);
    new -> link = NULL;

    update_link_table(&new, f_name);

    //Check the list empty
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    //Traverse and find the last node, insert new as last node
    //TODO: Write insert last logic
    else
    {
	wlist_t *temp = *head;
	while(temp->link!=NULL)                     //traversing till last node to insert at last
	{
	    temp = temp ->link;
	}
	temp->link = new;
	return SUCCESS;
    }
}


int update_link_table(wlist_t **word_node, char *f_name)
{
    //Create the linktable node
    table_link_t *new = malloc(sizeof(table_link_t));

    //Validate new
    if(new==NULL)
    {
	    return FAILURE;
    }
    //Update the node fields (wordcount, filename, link)
    new -> w_count = 1;
    new -> link = NULL;
    strcpy(new -> f_name,f_name);

    (*word_node) -> t_link = new;
    return SUCCESS;
}
