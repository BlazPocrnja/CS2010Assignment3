#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;
using std::string;

typedef string STRING;
typedef bool BOOL;
typedef string WORD; 

/*
    structure describing a word entry in the dictionary
*/
typedef struct entry {
      int count;                  /* frequency count for a particular word */
      WORD w;                     /* the word itself */
      struct entry *nextWord;     /* pointer to next entry */
} ENTRY;

/*
    structure describing the dictionary
*/
typedef struct dict {
     int maxEntries;	  	   /* maximum number of entries allowed; this is an artificial limit */
                                   /* link lists can be as big as you want. This limit ensures that   */
                                   /* this code tries to behave like the previous ones */    
                    
     int numWords;                 /* number of words in the dictionary */
     ENTRY *Words;                 /* pointer to the entries in the dictionary */

} DICT;  

ENTRY *LocateWord(DICT& , WORD);
BOOL FullDictionary(DICT&);
BOOL InsertWord(DICT&,WORD);
WORD GetNextWord(void);
void DumpDictionary(DICT&);

BOOL InsertWord(DICT &dict, WORD word)
{
/* 
  adds word to dictionary in alphabetic order , if word can't be added returns false else returns true
*/	bool inserted = false;
	if (!FullDictionary(dict)){
		if(dict.numWords == 0){
			dict.Words = new ENTRY;
			dict.Words->w = word;
			dict.Words->count = 1;
			dict.Words->nextWord = NULL;
			dict.numWords = 1;
			inserted = true;
		}
		else{
			ENTRY* tempnode = new ENTRY;
			tempnode->w = word;
			tempnode->count = 1;
			ENTRY* pointer = dict.Words;
			if((tempnode->w) < (dict.Words->w)){
				tempnode->nextWord = dict.Words;
				dict.Words = tempnode;
				dict.numWords++;
				inserted = true;
			}
			else{
				while(pointer->nextWord != NULL){
					if((tempnode->w) < (pointer->nextWord->w)){
						tempnode->nextWord = pointer->nextWord;
						pointer->nextWord = tempnode;
						dict.numWords++;
						inserted = true;
						break;
					}
					pointer = pointer->nextWord;
				}
				if (inserted == false){
					pointer->nextWord = tempnode;
					tempnode->nextWord = NULL;
					dict.numWords++;
					inserted = true;
				}
			}
				
		}
		return true;
	}
	return false;
}

void DumpDictionary(DICT &dict) {
/* 
  displays the contents, if word is too big displays number of character not printed. Deletes list.
*/
	WORD maxprnt;
	int omittedchars;
	cout << "Word				Frequency" << endl; 
	cout << "-------------------------------------" << endl;
	ENTRY *pointer = dict.Words;
	while(pointer != NULL){
		if(pointer->w.length() > 20){
			maxprnt = pointer->w.substr(0, 20);
			omittedchars = pointer->w.length() - maxprnt.length();
			cout << maxprnt << "(" << omittedchars << ") " << "		" << pointer->count << endl;
		}
		else {
			cout << pointer->w << "					" << pointer->count << endl;
		}
		ENTRY* used = pointer;
		pointer = pointer->nextWord;
		delete used;
	}
}

WORD GetNextWord(void){
/* 
   will retrieve next word in input stream. Word is defined just as in assignment #1 
   returns WORD or ""(null string) if no more words in input stream
*/
	char ch;
	WORD s;

	while(cin.good()){
		ch = cin.get();
		if (isalpha(ch)){
			s.push_back(tolower(ch));
			
		}
		else if (ch == ' ' || ch == '\n' ){
			if(s.size() != 0){
				return s;
			}
			
		}
	}

	return s; 
}

BOOL FullDictionary(DICT &dict) {
/* 
   if dictionary is full, return true else return false
 */
	if (dict.numWords == dict.maxEntries){
		return true;
	}
	return false;
}

ENTRY *LocateWord(DICT &dict, WORD word) {
/*
   will determine if dictionary contains word. if found, returns pointer to entry else returns 0
*/
	ENTRY *pointer = dict.Words;
	while(pointer != NULL){
		if (pointer->w == word){
			return pointer;
		}
		pointer = pointer->nextWord;
	}
	return 0;	
}
