#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mentry.h"
MEntry *me_get(FILE *fd){
	if(fd == NULL){
		return NULL;}
	MEntry *entries;
	entries = (MEntry *)malloc(sizeof(MEntry));
	entries->surname = (char *)malloc(1024 * sizeof(char));
	entries->zipcode = (char *)malloc(6 * sizeof(char));
	entries->full_address = (char *)malloc(1024 * sizeof(char));
	memset(entries->full_address, 0, 1024);
	entries->house_number = 0;
	char buffer[1024];
	memset(buffer, 0, 1024);
	int i = 0;
	for(; i < 3; i++){
		if(feof(fd)){
			me_destroy(entries);
			return NULL;
		}
		else{
		fgets(buffer, sizeof(buffer), fd);
		//Howard Lin assisted with regex syntax
		if (i == 0){
			sscanf(buffer,"%[^,]", entries->surname);}
		else if (i == 1){
			sscanf(buffer, "%d%*s", &entries->house_number);}
		else if (i == 2){
			sscanf(buffer, "%*[^0-9]%s", entries->zipcode);}
	}
	strcat(entries->full_address, buffer);}
	return entries;
}


unsigned long me_hash(MEntry *me, unsigned long size){
	if(me == NULL){
		fprintf(stderr, "Entry is NULL; returning 0");
		return 0;}
	unsigned long hashval = 0;
	char address_buff[1024];
	memset(address_buff, 0, 1024);
	strcat(address_buff, me->surname);
	strcat(address_buff, me->zipcode);
	char house_buff[6];
	sprintf(house_buff, "%d", me->house_number);
	strcat(address_buff, house_buff);
	int i;
	for(i = 0; address_buff[i] != '\0'; i++){
		hashval = address_buff[i] + 31 * hashval;
    }
	return hashval%size;
}

void me_print(MEntry *me, FILE *fd){
	fprintf(fd, "%s", me->full_address);
}

int me_compare(MEntry *me1, MEntry *me2){
	if(me1 == NULL){
		fprintf(stderr, "entry 1 is null");
    }
	else if(me2 == NULL){
		fprintf(stderr, "entry 2 is null");
    }
	int sur_check = strcasecmp(me1->surname, me2->surname);
	int zip_check = strcmp(me1->zipcode, me2->zipcode);
	int house_check = me1->house_number - me2->house_number;
	if(sur_check == 0 && zip_check == 0 && house_check == 0){
		return 0;
    }
	else if (sur_check < 0 || zip_check < 0 || house_check<0){
		return -1;
    }
	else{
		return 1;
    }
}

void me_destroy(MEntry *me){
	if(me == NULL){
		fprintf(stderr, "Can't delete a NULL entry");}
	free(me->full_address);
	free(me->surname);
	free(me->zipcode);
	free(me);
}
