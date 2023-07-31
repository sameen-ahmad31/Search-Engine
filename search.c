#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int main(void)
{
	//glob_t result;
	//retval = glob(search_string, flags, error_func, result);
	FILE *file = fopen("search_scores.txt", "w");
	int num_bucks = 0;
  int numread = 0;
  fclose(file);
  
  	while (1) 
	{
    	printf("How many buckets?\n");
    	numread = scanf("%d", &num_bucks);
    	if(numread != 1)
    	{
      	printf("Invalid Input\n");
      	scanf("%*[^\n]");
    	}
    	else
    	{
      		if (num_bucks > 0) 
      		{
       			break;
      		} 
      		else 
      		{
       			printf("Invalid Input\n");
      		}
      	}
  }
  
	struct hashmap * hashm = hm_create(num_bucks);

	training(hashm);
  
  char dv [1];
  scanf("%c", dv);

  while(1)
   {
      char searchquery[1024];
     // searchquery[strlen(searchquery)] = '\0';
      printf("Enter search string or X to exit: \n");
     // scanf(" %s", searchquery);
      fgets(searchquery, 1024, stdin);
      //printf("%s", searchquery);
      searchquery[strlen(searchquery)] = '\0';
     // char x [] = "X";
      //int y = strcmp(searchquery, x);
      if (searchquery[0] == 'X')
      {
	hm_destroy(hashm);
        break;
      }
      searchquery[strcspn(searchquery, "\n")] = '\0';
      read_query(hashm, searchquery);
       
   }
  
  return 0;




}
