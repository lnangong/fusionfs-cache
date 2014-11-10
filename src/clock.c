/**
 *	clock.c--Clock Caching Algorithm
 *
 *	Copyright (c) 2014, Long(Ryan) Nangong.
 *	All right reserved.
 *
 *	Email: lnangong@hawk.iit.edu
 *	Created on: 12/6/2013             
 */


#include "params.h"
#include "util.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include "log.h"


/*search element in the Q (it's double cyclic Q)*/
inode_t* findelem_clock(const char *fname)
{
        log_msg("\nfindelem_clock\n");

        if (FUSION_DATA->clock_head == NULL)
                return NULL;

        inode_t *curr = FUSION_DATA->clock_head;
        do
        {
                if (strcmp(curr->fname, fname) == 0) //found match in the Q
                {
                        return curr;
                }

                curr = curr->next;
        }
        while (curr != FUSION_DATA->clock_head);  //check each element until pointer points back to the head of Q

        return NULL; // If there's no match in the Q
}

//insert element to the Q 
void ins_Q(inode_t *elem)
{
	if(FUSION_DATA->victim != NULL)
	{
		if(FUSION_DATA->victim == FUSION_DATA->clock_head)
			FUSION_DATA->clock_head = elem;    //new head
		//add new elem before the victim pointer
		inode_t *prev = FUSION_DATA->victim->prev; 
		prev->next = elem; 
		elem->next = FUSION_DATA->victim;	
		FUSION_DATA->victim->prev = elem;
		elem->prev = prev;
	}
	else{
		//insert new element to tail
		elem->prev = FUSION_DATA->clock_tail; 
		elem->next = FUSION_DATA->clock_tail->next; //it's cyclic Q
		FUSION_DATA->clock_tail->next = elem;
		FUSION_DATA->clock_tail = elem; //new inserted element becomes tail
		FUSION_DATA->clock_head->prev = FUSION_DATA->clock_tail;//points prev of head to new tail
	}
}

//remove an element from the Q
void rem_Q(inode_t *elem)
{
	//only one element in the Q
	if(elem == elem->next) 
	{
		FUSION_DATA->victim = NULL;
	        FUSION_DATA->clock_head = NULL;
       		FUSION_DATA->clock_tail = NULL;
		free(elem);
		return;
	}
	//more than one element in the Q
	else if(elem == FUSION_DATA->clock_head) //if it's head
		FUSION_DATA->clock_head = elem->next;
	
	else if(elem == FUSION_DATA->clock_tail) //if it's tail
		FUSION_DATA->clock_tail = elem->prev;
		
	//remove procedure
	inode_t *prev = elem->prev;
	inode_t *next = elem->next;
	//if this element found by victim pointer, advance pointer and remove this elem
	if(FUSION_DATA->victim == elem)
		FUSION_DATA->victim = elem->next;

	prev->next = next;
	next->prev = prev;

	free(elem);

}

/**
 *update reference bit, if file found in the Q
 *if file not found in the Q, insert it into the Q
 *fname is full path ssd
 */
void insque_clock(const char *fname)
{
        log_msg("\ninsque_clock\n");

        // Find the element in the Q
        inode_t *found = findelem_clock(fname);

        // If it is already in the FIFO Q, update the reference bit
        if (found != NULL)     
                found->ref_bit = 1;
	
	//File not found, insert it to the Q
	else
	{
		inode_t *elem = (inode_t *)malloc(sizeof(inode_t));
		strcpy(elem->fname, fname);
		elem->ref_bit = 1;

		// If FIFO Q is empty 
		if (FUSION_DATA->clock_head == NULL)
		{
		 	elem->next = elem;
		        elem->prev = elem;
		        FUSION_DATA->clock_head = elem;
		        FUSION_DATA->clock_tail = elem;
		}
		// FIFO Q is nonempty 
		else
			ins_Q(elem);
		
	}

	log_msg("\ninsque_clock debug: insque files\n");
	inode_t *pt = FUSION_DATA->clock_head; 
	do
	{
		log_msg("%s-->",pt->fname);
		pt = pt->next;
	}while(pt != FUSION_DATA->clock_head);
}

/**
 *find victim file, and remove it from the Q
 *copy back victim's file name to remove it to hdd
 */
void remque_clock(char *fname)
{
        log_msg("\nremque_clock\n");

        if (FUSION_DATA->clock_head == NULL)
                fusion_error("remque_clock FIFO Q is alreay empty");
        
	if(FUSION_DATA->victim == NULL) //first time to use victim pointer, or all cached files have been removed from the Q
		FUSION_DATA->victim = FUSION_DATA->clock_head;

        //only one elememt in the Q
        if (FUSION_DATA->victim == FUSION_DATA->victim->next)
        {
		strcpy(fname,FUSION_DATA->victim->fname); //copy back victim's path to fname to remove file to hdd
                rem_Q(FUSION_DATA->victim); //remove victim from the Q
		
                return;
        }

	//have more than one element in the Q
	while(1) 
	{       //find victim element
		if(FUSION_DATA->victim->ref_bit == 0)
		{
			strcpy(fname,FUSION_DATA->victim->fname);//copy back victim's path to fname to remove file to hdd
			rem_Q(FUSION_DATA->victim); //remove victim from the Q
			log_msg("\nremque_clock--victim dirname = %s \n", fname);
			break;
		}
		else
		{
			//if pointed element's refrence bit is not 0, clear it, move to next elment
			FUSION_DATA->victim->ref_bit = 0;		
			FUSION_DATA->victim = FUSION_DATA->victim->next;
		}
	}
	
	log_msg("\nremque_clock debug: insque files\n");
        inode_t *pt = FUSION_DATA->clock_head;
        do
        {
                log_msg("-->%s",pt->fname);
                pt = pt->next;
        }while(pt != FUSION_DATA->clock_head);
}

//remove specific file from the Q
void rmelem_clock(const char *fname)
{
	log_msg("\nrmelem_clock\n");

	if(FUSION_DATA->clock_head == NULL)
		return;
	
	inode_t *found = findelem_clock(fname); //search file from the Q
	if(found != NULL)
		rem_Q(found); //remove file
	
}
