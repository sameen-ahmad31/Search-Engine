#include "hashmap.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void writeScoresToFile(float score[]) {
FILE *filew = fopen("search_scores.txt", "a");

  // scores should be sorted from highest to lowest
  // need to use bubble sort to sort the files correctly
  // then placed to file search_scores.txt
  float temp = 0;
  char docs[] = {"D1.txt D2.txt D3.txt"};
  char *doclist[3];
  char *docarray = strtok(docs, " ");
  int p = 0;
  doclist[p] = docarray;
  while (docarray != NULL) {
    // printf("%s\n", docarray);
    // printf(" %s\n", query[i]);
    p++;
    // separate by the space and then store into the hashmap
    docarray = strtok(NULL, " ");
    doclist[p] = docarray;
  }
  int n = 3;
  char *tempd;
  for (int c = 0; c < n - 1; c++) {
    for (int d = 0; d < n - c - 1; d++) {
      if (score[d] < score[d + 1]) {
        temp = score[d];
        tempd = doclist[d];
        score[d] = score[d + 1];
        doclist[d] = doclist[d + 1];
        score[d + 1] = temp;
        doclist[d + 1] = tempd;
      }
    }
  }

  int z = 0;
  float fz = (float) z;
  //char * ff;

  for (int i = 0; i < 3; i++) 
  {
	 
    if ((score[i] != 0) && (score[i] != fz) && (score[i] != 0.000000))
    {
	    printf("%s\n",doclist[i]);
    	fprintf(filew, "%s     ", doclist[i]);
      fprintf(filew, "%f\n", score[i]);
    }
  }

  fclose(filew);
}

// identifies stop words and removes the stop words
void stop_word(struct hashmap *hm) {
  FILE *d1;
  FILE *d2;
  FILE *d3;
  // make sure the file name is correct
  d1 = fopen("p5docs/D1.txt", "r");
  d2 = fopen("p5docs/D2.txt", "r");
  d3 = fopen("p5docs/D3.txt", "r");

  int zero = 0;
  float fzero = (float) zero;
  // removes the words that appear that in all the doc
  for (int i = 0; i < hm->num_buckets; i++) // go through the num_buckets
  {
    struct llnode *cur = hm->map[i];
    while (cur != NULL) 
    {
      if ( (idf(hm, cur->word) == fzero) || (idf(hm, cur->word) == 0)) 
      {
       // printf("stop words are: %s\n", cur->word);
        hm_rem(hm, cur->word);
      }
      cur = cur->next; // make current equal the current's next to loop through
    }
  }
 // printHashMap(hm);
  fclose(d1);
  fclose(d2);
  fclose(d3);
}

void readwords(struct hashmap *hm, FILE *f, char * filename) {
  char word[1024];
  
  while (fscanf(f, "%1023s", word) != EOF) {
    // insert each scanned word from the file into the hashmap
    //printf("word being inserted into hashmap: %s|\n", word);
   // printf("file is: %s|\n", filename);
    hash_table_insert(hm, word, filename);
  }

}
// training method
void training(struct hashmap *hm) {
  FILE *D1;
  FILE *D2;
  FILE *D3;
  // make sure the file name is correct
  D1 = fopen("p5docs/D1.txt", "r");
  D2 = fopen("p5docs/D2.txt", "r");
  D3 = fopen("p5docs/D3.txt", "r");

  readwords(hm, D1, "D1.txt");
  readwords(hm, D2, "D2.txt");
  readwords(hm, D3, "D3.txt");
  stop_word(hm);

  fclose(D1);
  fclose(D2);
  fclose(D3);
}

// rank method
void rank(struct hashmap *hm, char *array[], int length) {
 FILE *f1 = fopen("p5docs/D1.txt", "r");
  FILE *f2 = fopen("p5docs/D2.txt", "r");
  FILE *f3 = fopen("p5docs/D3.txt", "r");
  float ranking[3];
  ranking[0] = 0.0;
	ranking[1] = 0.0;
	ranking[2] = 0.0;
  //printf("%s \n", array[0]);
 // printf("%s \n", array[1]);
 // printf("%s \n", array[2]);

  double cal[3][length];
  char * fn;
 // array[length] = '\0';
  
  for(int i = 0; i < length; i++)
  {
     for(int file = 0; file < 3; file++)
       {
         if(file == 0)
         {
           fn = "D1.txt";
         }
         else if(file == 1)
         {
           fn = "D2.txt";
         }
         else
         {
           fn = "D3.txt";
         }
     cal[file][i] = (termFreq(hm, array[i], fn) * idf(hm, array[i]));

        }
    }

  
    for(int file = 0; file < 3; file++)
        {
          for(int i = 0; i < length; i++)
    {
          ranking[file] = ranking[file] + cal[file][i];
        }
    }
    
  
  fclose(f1);
  fclose(f2);
  fclose(f3);
  writeScoresToFile(ranking);
}

// tf: how many times a word appears in doc
float termFreq(struct hashmap *hm, char *word, char *doc) {
  float wcounter = (float) hm_get(hm, word, doc);
  return wcounter;
}

int docFreq(struct hashmap *hm, char *word)
{
  int df = hm_get2(hm, word);
  return df;
}

// idf: inverse doc frequency
float idf(struct hashmap *hm, char *word) {
  int num_docs = 3;
  int dcounter = docFreq(hm, word);
  if(dcounter == 0)
  {
    dcounter++;
  }
  float val = (float) num_docs / dcounter;
  float idfresult = log(val);
  return idfresult;
}

// read the search query
void read_query(struct hashmap *hm, char query[]) 
{
 // printf("goes into read query as: %s", query);
  char *sq[20];
  char *array;
  const char s[2] = " ";
  array = strtok(query, s);
  int i = 0;
  //sq[i] = array;
 // printf("%s\n", sq[i]);
  while (array != NULL)
  {
    sq[i] = array;
   // printf("it is here: %s\n", sq[i]);
    i++;
    array = strtok(NULL, s);
  }
 // sq[i] = '\0';
  rank(hm, sq, i);

}
