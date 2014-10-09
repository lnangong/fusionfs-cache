// There are a couple of symbols that need to be #defined before
// #including all the headers.

#ifndef _PARAMS_H_
#define _PARAMS_H_

// The FUSE API has been changed a number of times.  So, our code
// needs to define the version of the API that we assume.  As of this
// writing, the most current API version is 28
#define FUSE_USE_VERSION 28

/* DFZ FusionFS Constants */
#define ZHT_LOOKUP_FAIL -2

// need this to get pwrite().  I have to use setvbuf() instead of
// setlinebuf() later in consequence.
#define _XOPEN_SOURCE 500

// just some handy numbers
#define ONEG (1<<30)
#define ONEK 1024
#define ONEM (1<<20)

// ===================
// IMPORTANT NOTE:
//              CHANGE THE FOLLOWING BEFORE DEPLOYMENT!!!!!!!!
// ===================
#define ROOTSYMSIZE 4096 //ssd mount point size; not in use now.
#define SSD_TOT (ONEM) //the threshold; <= SSD_Capacity - Max_File_size
#define MODE_Clock 1 //Clock caching
#define MODE_LRU 0 //LRU caching
#define LOG_OFF 1 //turn off the log; faster your system!
#define CHKSSD_POSIX 0 //use command line to check SSD usage, seems to have performance degradatoin. Not in use now.
// ======OK you are all set============

// default source folders
#define DEFAULT_SSD "/ssd"
#define DEFAULT_HDD "/hdd"

// default mount points
#define SSD_MOUNT "ssd"
#define HDD_MOUNT "hdd"

// maintain bbfs state in here
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

// schfs extentions:
#include <search.h>
#include <time.h>
#include <ftw.h>

/**
 * Data structures
 */

// inode info for files
typedef struct _inode_t
{
        //element pointers
        struct _inode_t *next;
        struct _inode_t *prev;

        char fname[NAME_MAX]; //file name, absolute path, unique
        int inSSD; // I'm still thinking if this's necessary
        int freq; //for LFU
        time_t atime; //last access time
		int ref_bit; //R bit used for Clock algorithm

}
inode_t;

//Fusionfs state
struct fusion_state {
	FILE *logfile;
   	char *rootdir;
	char ssd[PATH_MAX];
	char hdd[PATH_MAX];
	int ssd_total;
	int ssd_used;

	inode_t *lru_head;
	inode_t *lru_tail;
	inode_t *lfu_head;
	inode_t *lfu_tail;	
	inode_t *clock_head;
	inode_t *clock_tail;
	inode_t *victim;
};
#define FUSION_DATA ((struct fusion_state *) fuse_get_context()->private_data)
#define FUSION_SSD \
    (((struct fusion_state *) fuse_get_context()->private_data)->ssd)
#define FUSION_HDD \
    (((struct fusion_state *) fuse_get_context()->private_data)->hdd)

/**
 * FusionFS specifically
 */
#include <search.h> /* hash table, linked list */
#define MAX_HT_ENTRY 1024
ENTRY e, *ep; /* Global hash table entry */


#endif
