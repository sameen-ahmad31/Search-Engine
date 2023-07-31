#ifndef HASHMAP_H
#define HASHMAP_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct llnode {
        char* word;
        int numOfDoc; 
        //char* document_id;
        // int num_occurrences
        struct llnode* next;
        struct lldoc * document;
};

struct lldoc
{
        char * doc_id;
        int numOfOccurrenceOfWords;
        struct lldoc * next;
};

struct hashmap {
        struct llnode** map;
        int num_buckets;
        int num_elements;
};


struct hashmap* hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_rem(struct hashmap* hm, char* word);
void hash_table_insert(struct hashmap* hm, char* word, char* document_id);
int hm_get2(struct hashmap * hm, char * word);
//void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void hm_remove(struct hashmap* hm, char* word, char* document_id);
void hm_destroy(struct hashmap* hm);
int hash_code(struct hashmap* hm, char* word);
void readwords(struct hashmap *hm, FILE *f, char * filename);
void writeScoresToFile(float score[]);
void training(struct hashmap *hm);
void rank(struct hashmap *hm, char *array[], int length);
float termFreq(struct hashmap *hm, char *word, char *doc);
float idf(struct hashmap *hm, char *word);
void read_query(struct hashmap *hm, char query[]);
void stop_word(struct hashmap *hm);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void printHashMap(struct hashmap *hm);
int docFreq(struct hashmap *hm, char *word);

#endif

