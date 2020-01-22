#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE ((int)26)
#define MAX_LENGTH 500000

struct Trie {
    int freq;
    struct  Trie* children[ALPHABET_SIZE];
    bool isLeaf ;
    char letter;
} typedef trie_t;

struct Trie* getNode() {
    struct Trie* Node = (struct Trie*)malloc(sizeof(struct Trie));
    
    int i = 0;
    while( i < ALPHABET_SIZE) {
        Node -> children[i] = NULL;
        i++;
    }
    Node -> isLeaf = false;
    Node -> freq = 0;
    
    return Node;
}

void add(trie_t **root, char *arr) {

    if (arr[0]==' '||arr[0]=='\n'||arr[0]=='\t')  return;    

    int len = strlen(arr);
    trie_t* current = *root;

    for(int i = 0; i < len; i++) {
        char letter = arr[i];

        if(letter>='a' && letter<='z') {
            int index = letter - 'a';

            if(current->children[index] == NULL) {
                current->children[index] = getNode();
                current = current->children[index];
            }
            else current = current->children[index];
            current->letter = letter;
        }
    }
	current->freq++;
    current->isLeaf = true;
}

void upperToLower(char* str) {
    int i = 0;
    int length = strlen(str);
    while(i < length){
        str[i] = tolower(str[i]);
        i++;
    }
}

void makeText(trie_t* root, char *text, int i) {
    char letter;
    int j;
    text[i++] = '\0';
    letter = getchar();
    
    for(j = 0; letter != '\0' && j< MAX_LENGTH ; j++) {

        while(letter != ' ' && letter != '\n' && letter != '\t') {
            text = realloc(text,(i + 1) * sizeof(char));
            text[i-1] = letter;
            text[i++] = '\0';
            letter = getchar();
            j++;
        }

        upperToLower(text); 
        add(&root, text);
        free(text);
        letter = getchar();
        

	    if(letter == EOF)
            break;

        i=1;
        text = (char *)malloc(sizeof(char));
        text[0] = letter;

    }
}

void print(trie_t *current, char *str, int level) {

    if(current == NULL)
        return;

    if(current->isLeaf) {     
            str[level] = '\0';
            printf("%s\t%d\n", str, current->freq);
    }

    int i;
    for(i = 0; i < ALPHABET_SIZE; i++) {    
        
        if(current -> children[i] != NULL) {  
            str[level] = 97 + i;
            // increment level for the recursive calls

            print(current->children[i], str, level + 1);
        }
    }
}           

void memClean(trie_t *current){
    int i = 0;
    while(i < ALPHABET_SIZE) {
        if (current->children[i]){
            memClean(current->children[i]);
        }
            i++;
    }
    free(current);
}

int main() {
    trie_t* root = getNode();
    char *text;
    int i;

    i = 0;
    text = (char *)malloc(sizeof(char));
    makeText(root,text,i);
    char* str =(char *)malloc(sizeof(str));
    print(root, str, 0);
        
    memClean(root);
    free (str);
}