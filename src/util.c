/**
 *
 * DFZ, 07/14/2012: change zht_lookup() interface
 *
 * DFZ, 07/05/2012: added five ZHT based functions:
 * 		zht_init(), zht_insert(), zht_lookup(), zht_remove() and zht_free()
 *
 * DFZ, 06/27/2012: The hashtable is implemented with <search.h> for now.
 * This will be updated with more fancy ones
 */

/*for net facilities*/
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

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

/*for ZHT interface */
#include <stdbool.h>
#include <errno.h>
#include "./zht/inc/c_zhtclient.h"

#include "log.h"



/*
 * get the ip address of the local machine
 */
int net_getmyip(char *addr) {
//	char hostname[PATH_MAX] = {0};
//	struct hostent *host = (struct hostent *) malloc(sizeof(struct hostent));
//
//	gethostname(hostname, PATH_MAX) ;
//	host = (struct hostent *) gethostbyname(hostname) ;
//
//	strcpy(addr, inet_ntoa(*((struct in_addr *)host->h_addr)));
////	printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *)host->h_addr)));

	struct ifaddrs * ifAddrStruct = NULL;
	struct ifaddrs * ifa = NULL;
	void * tmpAddrPtr = NULL;

	getifaddrs(&ifAddrStruct);

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		/*skip the loopback*/
		if (!strcmp("lo", ifa->ifa_name))
			continue;

		if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
			// is a valid IP4 Address
			tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN] = {0};
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
//            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
			strcpy(addr, addressBuffer);
		}
//        else if (ifa->ifa_addr->sa_family==AF_INET6) { // check it is IP6
//            // is a valid IP6 Address
//            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
//            char addressBuffer[INET6_ADDRSTRLEN];
//            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
//            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
//        }
	}
	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);

	return 0;
}

/**
 *******************************************************************
 ** The following five operations are imported from ZHT utilities **
 *******************************************************************
 */

int zht_init()
{
	/* use TCP by default */
	c_zht_init("./src/zht/neighbor", "./src/zht/zht.cfg", true);

//	/* DFZ: debug info */
//	printf("\n =====DFZ debug: %s \n", "zht_init() succeeded. ");

	return 0;
}

int zht_free()
{
	c_zht_teardown();

//	/* DFZ: debug info */
//	printf("\n =====DFZ debug: %s \n", "zht_free() succeeded. ");

	return 0;
}

int zht_insert(const char *key, const char *value)
{
	return c_zht_insert2(key, value);
}

/* DFZ: This is not in use for now, need to wait for Xiaobing to change the
 * interface
 * */
int zht_lookup(const char *key, char *val)
{
	/* TODO: val should not have the &, waiting for Xiaobing to update*/
//	return c_zht_lookup2(key, val);
	size_t len;
	return c_zht_lookup2(key, val, &len);
	return 0;
}

int zht_remove(const char *key)
{
	return c_zht_remove2(key);
}

/**
 *****************************************************************************
 ** The following 3 functions are hashtable implementations from <search.h> **
 *****************************************************************************
 */

/**
 * Insert <key, val> into the global hash table
 *
 * return int:
 * 		0 - success
 * 		1 - failed to insert
 */
int ht_insert(const char *key, const char *val)
{
	e.key = (char *)key;
	e.data = (void *)val;

	ep = hsearch(e, ENTER);
	if (NULL == ep) {
		fprintf(stderr, "entry failed in hash table \n");
		exit(EXIT_FAILURE);
	}

	/* DFZ: debug info */
	log_msg("\n =====DFZ debug: ep->key = %s, ep->data = %s \n", ep->key, ep->data);

	/*
	 * DFZ: test ht_search
	 */
	ep = ht_search("/tmpfile");
	if ((ENTRY*)0 != ep)
		log_msg("\n =====DFZ debug: ep->key = %s, ep->data = %s (after 'ht_search')\n", ep->key, ep->data);
	else
		log_msg("\n =====DFZ debug: not found '/tmpfile' \n ");

	return 0;
}

/**
 * Remove <key, val> from the global hash table
 *
 * return int:
 * 		0 - success
 * 		1 - <key> not found in the hash table
 */
int ht_remove(const char *key)
{
	e.key = (char *)key;
	e.data = (void *)0;

	ep = hsearch(e, ENTER);
	if (NULL == ep) {
		fprintf(stderr, "entry failed in hash table \n");
		exit(EXIT_FAILURE);
	}

	return 0;
}

/**
 * Search <key> from the global hash table
 *
 * return *ENTRY:
 * 		0 - not found
 * 		Otherwise - the pointer of the first found entry
 */
ENTRY* ht_search(const char *key)
{
	e.key = (char*) key;
	ep = hsearch(e, FIND);

	if (NULL != ep) {
		log_msg("\n ========DFZ debug: in ht_search(): ep->key = %s, ep->data = %s", ep->key, ep->data);
		return ep;
	}

	log_msg("\n ========DFZ debug: in ht_search(): %s not found ", key);

	return (ENTRY*)0;
}

/**
 * check if the ssd should swap some files to hdd
 */
int ssd_is_full()
{
        //temporarily release the SSD limit:
        //return 0;

        if (CHKSSD_POSIX)
                return ssd_is_full_2();

        get_used_ssd();

        // if the current space is under a threshold in SSD, return 1
        if (FUSION_DATA->ssd_used > (FUSION_DATA->ssd_total*0.8))
        {
                return 1;
        }

        return 0;
}
/**
 * get the hdd counterpart of a given ssd path
 */
void get_hdd_path(char hdd_fpath[PATH_MAX], const char *ssd_fpath)
{
        strcpy(hdd_fpath, ssd_fpath);
        char *mountname_pos = strstr(hdd_fpath, DEFAULT_SSD);
        strncpy(mountname_pos, DEFAULT_HDD, strlen(DEFAULT_HDD));
}

/**
 * get the ssd counterpart of a given hdd path, useful?
 */
void get_ssd_path(char ssd_fpath[PATH_MAX], const char *hdd_fpath)
{
        strcpy(ssd_fpath, hdd_fpath);
        char *mountname_pos = strstr(ssd_fpath, DEFAULT_HDD);
        strncpy(mountname_pos, DEFAULT_SSD, strlen(DEFAULT_SSD));
}
/**
 *      Copy a particular directory from ssd to hdd
 */
void copy_dir_ssd(const char *ssd_fpath, mode_t mode)
{
        log_msg("\ncopy_dir_ssd(ssd_fpath=\"%s\", mode=0%03o)\n",
                        ssd_fpath, mode);

        //get the right path in hdd
        char hdd_fpath[PATH_MAX] = {0};
        get_hdd_path(hdd_fpath, ssd_fpath);

        //copy the directory in hdd
        int retstat = mkdir(hdd_fpath, mode);
        if (retstat < 0){
                retstat = fusion_error("copy_dir_ssd mkdir");
	}
}
/**
 * Move a particular file from ssd to hdd
 */
int move_file_ssd(const char *ssd_fpath)
{
        log_msg("\nmove_file_ssd(ssd_fpath=\"%s\")\n",
                        ssd_fpath);

        // Get the right path in hdd
        char hdd_fpath[PATH_MAX] = {0};
        get_hdd_path(hdd_fpath, ssd_fpath);

        // Move the file in hdd
        char cmd[PATH_MAX] = {0};
        strcpy(cmd, "mv ");
        strcat(cmd, ssd_fpath);
        strcat(cmd, " ");
        strcat(cmd, hdd_fpath);
        system(cmd);

        //make symbolic link to the hdd file
        symlink(hdd_fpath, ssd_fpath);

        return 0;
}
/**
 * Move a particular file from hdd to ssd
 */
int move_file_hdd(const char *ssd_fpath)
{
        log_msg("\nmove_file_hdd(ssd_fpath=\"%s\")\n",
                        ssd_fpath);

        //remove the symbolic link
        int retstat = unlink(ssd_fpath);
        if (retstat < 0){
                retstat = fusion_error("move_file_hdd unlink ssd_fpath"); 
	}

        //get the hdd path
        char hdd_fpath[PATH_MAX] = {0};
        get_hdd_path(hdd_fpath, ssd_fpath);

        //move the file to ssd path     
        char cmd[PATH_MAX] = {0};
        strcpy(cmd, "mv ");
        strcat(cmd, hdd_fpath);
        strcat(cmd, " ");
        strcat(cmd, ssd_fpath);
        system(cmd);

        return 0;
}
/**
 * Insert LRU tail
 *
 * Note: Need to check if the same elem is ready in the Q; 
 *              if that is the case, remove it and reinsert it to the end
 */
void insque_lru(inode_t *elem)
{
        log_msg("\ninsque_lru\n");

        // If elem already exists we should remove it first, 
        // e.g. when modifying a SSD file
        if (NULL != findelem_lru(elem->fname))
        {
                rmelem_lru(elem->fname);
        }

        // Add the elem to the LRU Q tail
        if (FUSION_DATA->lru_head == NULL)  // If LRU Q is empty 
        {
                elem->next = elem;
                elem->prev = elem;
                insque(elem, elem);
                FUSION_DATA->lru_head = elem;
                FUSION_DATA->lru_tail = elem;
        }
        else  // Othersise only update the tail
        {
                insque(elem, FUSION_DATA->lru_tail);
                FUSION_DATA->lru_tail = elem;
        }
}
/**
 * Insert a new element to LFU 
 *
 * Note: we need to put the new element at the end of its isovalued
 *              ones. The idea is, if multiple elements have the same frequency
 *              we want to apply LRU
 */
void insque_lfu(inode_t *elem)
{
        log_msg("\ninsque_lfu\n");

        // Find the elem
        inode_t *found = findelem_lfu(elem->fname);

        // If it is already in the LFU Q, we need to remove it first
        if (NULL != found)
        {
                // Update the frequency
                elem->freq = found->freq + 1;

                // Remove Move the element
                rmelem_lfu(found->fname);
        }

        // If LFU Q is empty 
        if (NULL == FUSION_DATA->lfu_head)
        {
                elem->next = elem;
                elem->prev = elem;
                insque(elem, elem);
                FUSION_DATA->lfu_head = elem;
                FUSION_DATA->lfu_tail = elem;
        }
        else
        {
                // Find where to insert the new element 
		// Before calling get_pos_lfu, make sure to check if the 
                //              LFU Q is nonempty
                inode_t *prev = get_pos_lfu(elem);

                // If the element should be the new head
                if (NULL == prev)
                {
                        // Note that this is a double cyclic list.
                        // So inserting before the head is equivalent to
                        //              inserting after the tail.
                        insque(elem, FUSION_DATA->lfu_tail);

                        // The key point is to update the Q head
                        FUSION_DATA->lfu_head = elem;
                }

                // If the element should be the new tail
                else if (FUSION_DATA->lfu_tail == prev)
                {
                        insque(elem, prev);

                        // Update the Q tail
                        FUSION_DATA->lfu_tail = elem;
                }

                // And lastly, elem should land in the middle somewhere
                else
                {
                        insque(elem, prev);
                }
        }
}
/**
 * Find the right position to insert given an element in LFU
 *
 * Return the inode that should be adjacent before the given *elem
 *
 * If the elem should be insert into the Q head, return NULL
 *
 * NOTE: IMPORTANT!!!! This function assumes the LFU Q is non-empty
 */
inode_t* get_pos_lfu(inode_t *elem)
{
        log_msg("\nget_pos_lfu\n");

        // Error check for non-empty LFU Q
        if (NULL == FUSION_DATA->lfu_head)
        {
                log_msg("ERROR: LFU Q is empty in get_pos_lfu() \n");
        }

        // Search for the position
        inode_t *curr = FUSION_DATA->lfu_head;
        int found = 0;//indicate whether the search is successful
        do
        {
                if (elem->freq < curr->freq)
                {
                        found = 1;
                        break;
                }

                curr = curr->next;
        }
        while (curr != FUSION_DATA->lfu_head);//it's a double cyclic linkedlist

        // Corner cases: stop at the head or tail
        if (FUSION_DATA->lfu_head == curr)
	{
                // Insert to the Q head
                if (found)
                {
                        return NULL;
                }
                // Insert to the Q tail
                else
                {
                        return FUSION_DATA->lfu_tail;
                }
        }
        // Stop at some middle elements
        else
        {
                // We need to shift it back one more for prev of elem
                return curr->prev;
        }
}
/**
 * Remove LRU head
 */
void remque_lru()
{
        log_msg("\nremque_lru\n");

        if (FUSION_DATA->lru_head == NULL){
                fusion_error("remque_lru LRU Q is alreay empty");
	}

        inode_t *head = FUSION_DATA->lru_head;

        //only one elem
        if (head == head->next)
        {
                remque(head);
                free(head);
                FUSION_DATA->lru_head = NULL;
                FUSION_DATA->lru_tail = NULL;
                return;
        }

        //reset the LRQ head
        FUSION_DATA->lru_head = head->next;
        remque(head);
        free(head);
}
/**
 * Remove LFU head
 */
void remque_lfu()
{
        log_msg("\nremque_lfu\n");

        if (FUSION_DATA->lfu_head == NULL){
               fusion_error("remque_lfu LFU Q is alreay empty");
	}

        inode_t *head = FUSION_DATA->lfu_head;

        //only one elem
        if (head == head->next)
        {
                remque(head);
                free(head);
                FUSION_DATA->lfu_head = NULL;
                FUSION_DATA->lfu_tail = NULL;
                return;
        }

        //reset the LFU head
        FUSION_DATA->lfu_head = head->next;
        remque(head);
        free(head);
}
/**
 * Remove a particular element of LRU Q given a file name
 */
void rmelem_lru(const char *fname)
{
        log_msg("\nrmelem_lru\n");

        if (NULL == FUSION_DATA->lru_head)
                return;

        inode_t *found = findelem_lru(fname);
        if (NULL != found)
        {
                if (found == FUSION_DATA->lru_head)  //if it's the head
                {
                        remque_lru();
                }
                else if (found == FUSION_DATA->lru_tail)  //if it's tail
                {
                        FUSION_DATA->lru_tail = found->prev;
                        remque(found);
                        free(found);
                }
                else
                {
                        remque(found);
                        free(found);
                }
        }
}
/**
 * Remove a particular element of LFU Q given a file name
 *
 * This is pretty much the same of rmemem_lru()
 */
void rmelem_lfu(const char *fname)
{
        log_msg("\nrmelem_lfu\n");

        if (NULL == FUSION_DATA->lfu_head)
                return;

        inode_t *found = findelem_lfu(fname);
        if (NULL != found)
        {
                if (found == FUSION_DATA->lfu_head)  //if it's the head
                {
                        remque_lfu();
                }
                else if (found == FUSION_DATA->lfu_tail)  //if it's tail
                {
                        FUSION_DATA->lfu_tail = found->prev;
                        remque(found);
                        free(found);
                }
                else
                {
                        remque(found);
                        free(found);
                }
        }
}
/**
 * Find a particular elem of LRU Q, only return the first match
 */
inode_t* findelem_lru(const char *fname)
{
        log_msg("\nfindelem_lru\n");

        if (NULL == FUSION_DATA->lru_head)
                return NULL;

        inode_t *curr = FUSION_DATA->lru_head;
        do
        {
                if (strcmp(curr->fname, fname) == 0)  //found match in LRU Q
                {
                        return curr;
                }

                curr = curr->next;
        } while(curr != FUSION_DATA->lru_head);  //this is a double cyclic list

        return NULL;
}
/**
 * Find a particular element of LFU Q
 *
 * This is pretty much the same as findelem_lru
 */
inode_t* findelem_lfu(const char *fname)
{
        log_msg("\nfindelem_lfu\n");

        if (NULL == FUSION_DATA->lfu_head)
                return NULL;

        inode_t *curr = FUSION_DATA->lfu_head;
        do
        {
                if (0 == strcmp(curr->fname, fname))
                {
                        return curr;
                }

                curr = curr->next;
        }
        while (curr != FUSION_DATA->lfu_head);

        return NULL; // If there's no match in the Q
}
/**
 * Debug print, wrapper of some debug info
 */
void print_debug()
{
        if (MODE_LRU)
        {
                print_lru();
        }
        else
        {
                print_lfu();
        }
        get_used_ssd();
        print_used_ssd();
}

/**
 * Debug print, SSD info
 */
void print_used_ssd()
{
        log_msg("\nSSD Info: \n");
        log_msg("\t mount point = %s \n", FUSION_SSD);
        log_msg("\t space used = %d \n", FUSION_DATA->ssd_used);
}

/**
 * Debug print, LRU info
 */
void print_lru()
{
        log_msg("\nLRU Q Info: \n");

        if (NULL == FUSION_DATA->lru_head)
                return;

        inode_t *head = FUSION_DATA->lru_head;
        do
        {
                log_msg("\t fname = %s \n", head->fname);
                head = head->next;
        }
        while (head != FUSION_DATA->lru_head);
}
/**
 * Debug print, LFU info
 */
void print_lfu()
{
        log_msg("\nLFU Q Info: \n");

        if (NULL == FUSION_DATA->lfu_head)
                return;

        inode_t *head = FUSION_DATA->lfu_head;
        do
        {
                log_msg("\t fname = %s, freq = %d \n", head->fname, head->freq);
                head = head->next;
        }
        while (head != FUSION_DATA->lfu_head);
}

/**
 * Get the space used in SSD
 */
int get_used_ssd()
{
        FUSION_DATA->ssd_used = 0;

        ftw(FUSION_SSD, &sum_size_ssd, 1); //check the SSD size in total

        return 0;
}
/**
 * Callee of ftw in get_used_ssd(), operation on each subfile/subdirectory
 */
int sum_size_ssd(const char *name, const struct stat *sb, int type)
{
        // Don't count the size of the SSD mount point
    if (0 == strcmp(name, FUSION_DATA->ssd))
        {
                return 0;
        }

        //we need to fix the file size if the name is a symbolic link
    //because by default ftw(3) calls stat, not lstat.
        struct stat sbln;
        if (lstat(name, &sbln) == -1) {
                log_msg("    stat error line#%d", __LINE__);
        }

#ifdef DEBUG
        log_msg("\nChecking size of file: %s = % d\n", name, sbln.st_size);
#endif

        int filesize = 0;
        if (S_ISLNK(sbln.st_mode))
        {
                filesize = sbln.st_size;
        }
    else
    {
        filesize = sb->st_size;
    }

        //make the allowance to be 1GB:
	//filesize >>= 1;

        FUSION_DATA->ssd_used += filesize;

    return 0;
}

/**
 * Check if the given SSD path is a symbolic link to a HDD file
 */
int is_symlink_ssd(const char *fpath_ssd)
{
        //get hdd path
        char fpath_hdd[PATH_MAX] = {0};
        get_hdd_path(fpath_hdd, fpath_ssd);

        //check if the SSD path is a symbolic link
        struct stat sb;
        if (-1 == lstat(fpath_ssd, &sb))
        {
                log_msg("    lstat error line#%d", __LINE__);
                log_msg("    Failed to lstat file %s", fpath_ssd);
        }

        if (S_ISLNK(sb.st_mode))
        {
                if (access(fpath_hdd, F_OK) != -1)
                {
                        return 1;
                }

                return 0;
        }

        return 0;
}

