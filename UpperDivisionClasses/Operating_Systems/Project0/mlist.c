#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlist.h"
unsigned long HASHSIZE=20;

typedef struct mlistnode{
	struct mlistnode *next;
	MEntry *entry;
	int buckCount;
}MListNode;

typedef struct mlist{
	struct mlistnode **hashtable;
	unsigned long size;
	int largestBucket;
}MList;

MList* ml_create(void){
	MList *ml;

	if((ml = (MList *)malloc(sizeof(MList)))!= NULL){
		memset(ml, 0, sizeof(MList));
		ml->hashtable = (MListNode **)malloc(HASHSIZE*sizeof(MListNode *));
		ml->size = HASHSIZE;
		memset(ml->hashtable, 0, ml->size*sizeof(MListNode *));}
	return ml;}

int ml_add(MList **ml, MEntry *me){
	MList *p;
	MListNode *q;
	MListNode *_next;
	MListNode *_prev;
	p = *ml;
	if(p == NULL){
		fprintf(stderr, "Mailing list entered in add is NULL, returning 0");
		return 0;}
	if(me == NULL){
		fprintf(stderr, "Entry input for add is NULL, returning 0");
		return 0;}
	unsigned long hashval = me_hash(me, p->size);
	if(ml_lookup(p, me)!=NULL){
		return 1;
    }
	if((q=(MListNode *)malloc(sizeof(MListNode)))==NULL){
		return 0;
    }
	memset(q, 0 , sizeof(MListNode));
	q->buckCount = 1;
	q->entry = me;
	if(p->hashtable[hashval] == NULL){
		p->hashtable[hashval] = q;
		return 1;
    }
	_next = p->hashtable[hashval];
	while(_next != NULL){
		_prev = _next;
		_next = _next->next;}

	_prev->next = q;
	p->largestBucket = 0;
	if(p->hashtable[hashval]->buckCount > p->largestBucket){
		p->largestBucket = p->hashtable[hashval]->buckCount;
    }
	p->hashtable[hashval]->buckCount +=1;
	if(p->largestBucket == 20){
		p->largestBucket = 0;
		int j;
		for(j = 0; j < p->size; j++){
			p->hashtable[j]->buckCount = 0;
        }
		MList *old_table = p;
		MList *new_table;
		if((new_table = (MList *)malloc(sizeof(MList)))!= NULL){
			memset(new_table, 0, sizeof(MList));
			new_table->size = old_table->size * 2;
			new_table->hashtable = (MListNode**)malloc(sizeof(MListNode*) * new_table->size);
			memset(new_table->hashtable, 0, new_table->size * sizeof(MListNode*));
        }
		int i;
		for(i = 0; i < p->size; i++){
			MListNode *temp;
			MListNode *next;
			for(temp = old_table->hashtable[i]; temp != NULL; temp = next){
				next = temp->next;
				unsigned long new_hv = me_hash(temp->entry, new_table->size);
				temp->next = new_table->hashtable[new_hv];
				new_table->hashtable[new_hv] = temp;
            }
		}
		*ml = new_table;
		fprintf(stderr, "RESIZING HASHTABLE | old size: %d | new size: %d\n\n", old_table->size, new_table->size);
		free(old_table->hashtable);
		free(old_table);
    }
	return 1;
}



MEntry* ml_lookup(MList *ml, MEntry *me){
	MList *p;
	MListNode *q;
	if(ml == NULL){
		fprintf(stderr, "Mailing list in lookup is NULL");
		return NULL;}
	p = ml;
	if(me == NULL){
		fprintf(stderr, "Entry in lookup is NULL");
		return NULL;}
	unsigned long hashval = me_hash(me, p->size);
	for (q = p->hashtable[hashval]; q != NULL; q = q->next){
		if(me_compare(me, q->entry) == 0){
			return q->entry;}
	}
	return NULL;
}

void ml_destroy(MList *ml){
	if(ml == NULL){
		fprintf(stderr, "Cannot destroy a null mailing list");}
	MListNode *q;
	int i;
	for(i = 0; i < ml->size; i++){
		q = ml->hashtable[i];
		MListNode *r;
		MListNode *next;
		for(r = q; r!= NULL; r=next){
			next = r->next;
			me_destroy(r->entry);
			free(r);
			q = r;}
	}
	free(ml->hashtable);
	free(ml);
}
