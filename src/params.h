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

// maintain bbfs state in here
#include <limits.h>
#include <stdio.h>
struct fusion_state {
    FILE *logfile;
    char *rootdir;
};
#define FUSION_DATA ((struct fusion_state *) fuse_get_context()->private_data)

/**
 * FusionFS specifically
 */
#include <search.h> /* hash table, linked list */
#define MAX_HT_ENTRY 1024
ENTRY e, *ep; /* Global hash table entry */

#endif
