#include "hashmap.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// to create a hashmap
struct hashmap *hm_create(int num_buckets) {
  if (num_buckets <=
      0) // not valid because num_buckets can not be less than or equal to zero
  {
    return 0; // simply return
  }
  // this only happens if the input is valid
  struct hashmap *hm = calloc(sizeof(struct hashmap), 1); // create the hashmap
  hm->map = calloc(sizeof(struct llnode), num_buckets);   // create the buckets
  hm->num_elements = 0;          // right now the num_elements are zero
  hm->num_buckets = num_buckets; // num_buckets equals the parameter passed in
  return hm;                     // return the hashmap
}

// gets the number of occurrences
// returns term freq
int hm_get(struct hashmap *hm, char *word, char *document_id) {
  if ((hm == NULL) || (word == NULL) ||
      (document_id == NULL)) // if the any of the parameters are not valid which
                             // means they are passed in as NULL
  {
    return 0; // then simply return from it
  }
  // goes on if all of them are valid parameters
  unsigned int l = hash_code(hm, word); // hash the hm and the word
  struct llnode *cur = hm->map[l]; // create a node that is the hashed value
  while (cur != NULL)              // while the node is not null
  {
    // if the word and the document id exists
    if (strcmp(cur->word, word) == 0) {
      struct lldoc *dcur = cur->document;
      while (dcur != NULL) {
        if (strcmp(dcur->doc_id, document_id) == 0) {
          return (dcur->numOfOccurrenceOfWords);
        }
        dcur = dcur->next;
      }
    }
    cur = cur->next; // go the next node
  }
  return 0; // if the word and document id do not exist then you return 0
}

int hm_get2(struct hashmap *hm, char *word) {
  if ((hm == NULL) || (word == NULL)) {
    return 0;
  }
  unsigned int p = hash_code(hm, word); // hash the hm and the word
  struct llnode *cur = hm->map[p]; // create a node that is the hashed value
  while (cur != NULL)              // while the node is not null
  {
    // if the word is the same
    if (strcmp(cur->word, word) == 0) 
    {
      return (cur->numOfDoc);
    }
     cur = cur->next; // go the next node
  }
  return 0;
}

// inserts a string w and the associated document number i in the hash table
// (into bucket hash_code of string w)
void hash_table_insert(struct hashmap *hm, char *word, char *document_id) {
  // if the any of the parameters are not valid which means they are passed in
  // as NULL or the num of the occurrences is less than or equal to zero
  if ((hm == NULL) || (word == NULL) || (document_id == NULL)) {
    return; // then simply return from it
  }
  unsigned int k = hash_code(hm, word); // hash the hm and the word
  struct llnode *cur = hm->map[k]; // create the node that is the hashed value
  if (cur == NULL) {
    // create a new node and allocate space for it, so calloc the word
    struct llnode *newnode = calloc(sizeof(struct llnode), 1);
    char *s = strdup(word); // use strdup for the word so it points correctly
    char *t = strdup(document_id); // use strdup for the document_id so it also
                                   // points correctly
    newnode->word = s;             // new node's word is the strdup of the word
    newnode->numOfDoc++;
    newnode->document = calloc(sizeof(struct lldoc), 1);
    newnode->document->doc_id = t; // new node's document_id is the strdup of the document_id
    newnode->document->numOfOccurrenceOfWords++;
    newnode->document->next = NULL;
    hm->num_elements++; // increase the number of elements since a new node is
                        // created
    hm->map[k] = newnode;
    newnode->next = NULL; // the new node's next is equal to NULL
    return;               // return to exit faster
  } else {
    while (cur != NULL) // while the node is not empty
    {
      // if the word is correct and the document i_d exist
      if (strcmp(cur->word, word) == 0) {
        struct lldoc *dcur = cur->document;
        while (dcur != NULL) 
        {
          if (strcmp(dcur->doc_id, document_id) == 0) 
          {
            dcur->numOfOccurrenceOfWords++;
            return; // return to exit faster
          } 
          else if (dcur->next == NULL) 
          {
            char *w = strdup(document_id);
            cur->numOfDoc++;
            struct lldoc *newdoc = calloc(sizeof(struct lldoc), 1);
            newdoc->doc_id = w;
            newdoc->numOfOccurrenceOfWords++;
            dcur->next = newdoc;
            newdoc->next = NULL;
            return;
          }
          dcur = dcur->next;
        }

      }
      // if the word and the document does not exist
      else if (cur->next == NULL) {
        // create a new node and allocate space for it, so calloc the word
        struct llnode *newnode = calloc(sizeof(struct llnode), 1);
        char *s = strdup(word);        // use strdup for the word so it points
                                       // correctly
        char *t = strdup(document_id); // use strdup for the document_id so it
                                       // also points correctly
        newnode->word = s; // new node's word is the strdup of the word
        newnode->numOfDoc++;
        newnode->document = calloc(sizeof(struct lldoc), 1);
        newnode->document->doc_id =
            t; // new node's document_id is the strdup of the document_id
        newnode->document->numOfOccurrenceOfWords++;
        newnode->document->next = NULL;
        hm->num_elements++; // increase the number of elements since a new node
                            // is created
        cur->next = newnode;
        newnode->next = NULL; // the new node's next is equal to NULL
        return;               // return to exit faster
      }
      cur = cur->next; // go the next node
    }
  }
}

void hm_put(struct hashmap *hm, char *word, char *document_id,
            int num_occurrences) {
  // if the any of the parameters are not valid which means they are passed in
  // as NULL or the num of the occurrences is less than or equal to zero
  if ((hm == NULL) || (word == NULL) || (document_id == NULL) ||
      (num_occurrences <= 0)) {
    return; // then simply return from it
  }
  unsigned int k = hash_code(hm, word); // hash the hm and the word
  struct llnode *cur = hm->map[k]; // create the node that is the hashed value
  if (cur == NULL) {
    // create a new node and allocate space for it, so calloc the word

    struct llnode *newnode = calloc(sizeof(struct llnode), 1);
    char *s = strdup(word); // use strdup for the word so it points correctly
    char *t = strdup(document_id); // use strdup for the document_id so it also
                                   // points correctly
    newnode->word = s;             // new node's word is the strdup of the word
    newnode->document->doc_id =
        t; // new node's document_id is the strdup of the document_id
    newnode->document->numOfOccurrenceOfWords =
        num_occurrences; // number of occurrence
    hm->num_elements++;  // increase the number of elements since a new node is
                         // created
    hm->map[k] = newnode;
    newnode->next = NULL; // the new node's next is equal to NULL
    return;               // return to exit faster

  } else {
    while (cur != NULL) // while the node is not empty
    {
      // if the word is correct and the document i_d exist
      if (strcmp(cur->word, word) == 0 &&
          strcmp(cur->document->doc_id, document_id) == 0) {
        cur->document->numOfOccurrenceOfWords++; // increase its num_occurrences
        return;                                  // return to exit faster
      }
      // if the word and the document does not exist
      else if (cur->next == NULL) {
        // create a new node and allocate space for it, so calloc the word
        struct llnode *newnode = calloc(sizeof(struct llnode), 1);
        char *s = strdup(word);        // use strdup for the word so it points
                                       // correctly
        char *t = strdup(document_id); // use strdup for the document_id so it
                                       // also points correctly
        newnode->word = s; // new node's word is the strdup of the word
        newnode->document->doc_id =
            t; // new node's document_id is the strdup of the document_id
        newnode->document->numOfOccurrenceOfWords =
            num_occurrences; // number of occurrence
        hm->num_elements++;  // increase the number of elements since a new node
                             // is created
        cur->next = newnode;
        newnode->next = NULL; // the new node's next is equal to NULL
        return;               // return to exit faster
      }
      cur = cur->next; // go the next node
    }
  }
}

// removes the node that has the given word and document id
void hm_remove(struct hashmap *hm, char *word, char *document_id) {
  // if it is an invalid input so if hashmap, word, or document_id is invalid
  if ((hm == NULL) || (word == NULL) || (document_id == NULL)) {
    return; // simply return
  }
  // this only reaches here if all the parameters are valid
  unsigned int i = hash_code(hm, word); // hash the word and the hm
  struct llnode *cur =
      hm->map[i]; // create a cur node (current node) that is the hashed value

  while (cur != NULL) {
    // if word and document id are the same as the current's word and document
    // id
    if (strcmp(cur->word, word) == 0) {
      struct lldoc *dcur = cur->document;
      struct lldoc *dprev = cur->document;
      while (dcur != NULL) {
        if (strcmp(dcur->doc_id, document_id) == 0) {
          // document is at the beginning
          if (dcur->next == NULL) {
            cur->numOfDoc--;
             free(dcur->doc_id);
            free(dcur);
            hm->num_elements--;
            return; // return to exit faster
          }
          // if document is in the middle or the end
          else {
            cur->numOfDoc--;
            dprev->next = dcur->next;
            free(dcur->doc_id);
            free(dcur);
            hm->num_elements--;
            return; // return to exit faster
          }
        }
        dprev = dcur;
        dcur = dcur->next;
      }
    }
    cur = cur->next;
  }
}

void hm_rem(struct hashmap *hm, char *word) {
  // removes the node that has the given word
  // if it is an invalid input so if hashmap, word, or document_id is invalid
  if ((hm == NULL) || (word == NULL)) {
    return; // simply return
  }
  // this only reaches here if all the parameters are valid
  unsigned int i = hash_code(hm, word); // hash the word and the hm
  struct llnode *cur =
      hm->map[i]; // create a cur node (current node) that is the hashed value
  struct llnode *prev = hm->map[i];
  while (cur != NULL) 
  {
    // if word is the same
    if (strcmp(cur->word, word) == 0) 
    {
      struct lldoc *dcur = cur->document;
      struct lldoc *dprev = cur->document;
      while (dcur != NULL) 
      {
        if (dcur->next == NULL) 
        {
          cur->numOfDoc--;
          free(dcur->doc_id);
          free(dcur);
          hm->num_elements--;
        } else 
        {
          cur->numOfDoc--;
          dprev->next = dcur->next;
           free(dcur->doc_id);
          free(dcur);
          hm->num_elements--;
        }
        dprev = dcur;
        dcur = dcur->next;
      }

      if (cur->next == NULL) {
        free(cur->word);
        // free(cur->document);
        //free(cur);
        hm->num_elements--;
        return;
      } 
      else 
      {
        prev->next = cur->next; // make previous node's next point to current node's next
        free(cur->word); // free the current's word
        // free(cur->document);
       // free(cur);
        hm->num_elements--;
        return;
      }
    }
    prev = cur;
    cur = cur->next;
  }
}

// deletes the entire hashmap
void hm_destroy(struct hashmap *hm) {
  // if it is an invalid input so hm equals NULL
  if (hm == NULL) {
    return; // simply return
  }
  for (int i = 0; i < hm->num_buckets; i++) // go through the num_buckets
  {
   struct llnode *cur = hm->map[i]; 
  //struct llnode *track = hm->map[i]; 
   while(cur != NULL)
   {
      hm_rem(hm, cur->word);
      cur = cur->next;
   }

  }
  free(hm->map); // free the hm->map
  free(hm);      // free the entire hashmap itself
}

void printHashMap(struct hashmap *hashm)
{
  if(hashm == NULL)
  {
    printf("The hashmap is NULL");
    return;
  }
  for(int i = 0; i < hashm->num_buckets; i++)
    {
      printf("At Bucket: %d", i);
      struct llnode * cur = hashm->map[i];
      while(cur != NULL)
      {
        printf(", Word: %s ", cur->word);
        printf(", Number of Doc: %d" ,cur->numOfDoc);
        cur = cur->next;
      }
       printf("\n");
    }
  
}

// hash the word in the hashmap, given the word in the hashmap, it maps to the
// bucket in the hashmap
int hash_code(struct hashmap *hm, char *word) {
  // if the hashmap or the word is NULL so that is an invalid input
  if ((hm == NULL) || (word == NULL)) {
    return 0; // simply return
  }
  double sum = 0;                    // double sum is 0
  double len = (double)strlen(word); // find the length of the word
  int i = 1;                         // int i is equal to 1

  // go through the characters
  for (char *c = word; *c; c++, i++) {
    // power function for pow(31,len-i)
    int ans = 1;
    for (int i = 1; i <= (len - i); i++) {
      ans *= 31;
    }
    sum += (*c) * ans; // sum all the ASCII values in the word
  }
  // compute modulo with the num_buckets to get the bucket number in the hashmap
  return (unsigned int)(((unsigned long)sum) % hm->num_buckets);
}

