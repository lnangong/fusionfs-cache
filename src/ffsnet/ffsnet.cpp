/**
 * File name: ffsnet.cpp
 *
 * Function: utilities for FusionFS network transfer
 *
 * Author: dzhao8@hawk.iit.edu
 *
 * Update history:
 * 		- 07/18/2012: add ffs_mkdir()
 * 		- 07/17/2012: add ffs_rmfile()
 *		- 06/18/2012: initial development
 *
 * To compile this single file:
 * 		g++ ffsnet.cpp -c -o ffsnet.o -I../src -L../src -ludt -lstdc++ -lpthread
 *		NOTE: -I../src (similarly to -L../src) means to include the directory of the udt library, i.e. libudt.so 
 *
 * To compile it to a shared library:
 * 		g++ ffsnet.cpp -fPIC --shared -o libffsnet.so -I../src -L../src -ludt -lstdc++ -lpthread
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <udt.h>
#include <unistd.h>

#include "ffsnet.h"

using namespace std;

/*
 * request a remote node to make a new directory; if the requested directory already exists, do nothing
 */
int
ffs_mkdir(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename)
{
	/*connect to ffsnetd*/
	UDT::startup();

	struct addrinfo hints, *peer;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	UDTSOCKET fhandle = UDT::socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

	if (0 != getaddrinfo(remote_ip, server_port, &hints, &peer)) {
		cout << "incorrect server/peer address. " << remote_ip << ":" << server_port << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::connect(fhandle, peer->ai_addr, peer->ai_addrlen)) {
		cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	freeaddrinfo(peer);

	/*send request type, i.e. 2 for rmfile*/
	int three = 3;
	if (UDT::ERROR == UDT::send(fhandle, (char*)&three, sizeof(int), 0))	{
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*send the length of the filename to be removed*/
	int len = strlen(remote_filename);
	if (UDT::ERROR == UDT::send(fhandle, (char*)&len, sizeof(int), 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*send the directory to be created*/
	if (UDT::ERROR == UDT::send(fhandle, remote_filename, len, 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*wait for the return status of ffsnetd daemon*/
	int stat;
	if (UDT::ERROR == UDT::recv(fhandle, (char*)&stat, sizeof(int), 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	} else
		return stat;
}

/*
 * request a remote node to remove a filename, blocked until success
 */
int
ffs_rmfile(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename)
{
	/*connect to ffsnetd*/
	UDT::startup();

	struct addrinfo hints, *peer;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	UDTSOCKET fhandle = UDT::socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

	if (0 != getaddrinfo(remote_ip, server_port, &hints, &peer)) {
		cout << "incorrect server/peer address. " << remote_ip << ":" << server_port << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::connect(fhandle, peer->ai_addr, peer->ai_addrlen)) {
		cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	freeaddrinfo(peer);

	/*send request type, i.e. 2 for rmfile*/
	int two = 2;
	if (UDT::ERROR == UDT::send(fhandle, (char*)&two, sizeof(int), 0))	{
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*send the length of the filename to be removed*/
	int len = strlen(remote_filename);
	if (UDT::ERROR == UDT::send(fhandle, (char*)&len, sizeof(int), 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*send the filename to be removed*/
	if (UDT::ERROR == UDT::send(fhandle, remote_filename, len, 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/*wait for the return status of ffsnetd daemon*/
	int stat;
	if (UDT::ERROR == UDT::recv(fhandle, (char*)&stat, sizeof(int), 0)) {
		cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	} else
		return stat;
}

/*
 * download remote_filename from remoteip:server_port and save as local_filename
 */
static int 
_recvfile_udt(const char *remote_ip, const char *server_port, const char *remote_filename, const char *local_filename)
{
	/* use this function to initialize the UDT library */
	UDT::startup();

	struct addrinfo hints, *peer;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	UDTSOCKET fhandle = UDT::socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

	if (0 != getaddrinfo(remote_ip, server_port, &hints, &peer)) {
		cout << "incorrect server/peer address. " << remote_ip << ":" << server_port << endl;
		return -1;
	}

	/* connect to the server, implict bind */
	if (UDT::ERROR == UDT::connect(fhandle, peer->ai_addr, peer->ai_addrlen)) {
		cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	freeaddrinfo(peer);


	/* send name information of the requested file */
	int len = strlen(remote_filename);

	/* send 0 to indicate this is to receive */
	int zero = 0;
	if (UDT::ERROR == UDT::send(fhandle, (char*)&zero, sizeof(int), 0))	{
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::send(fhandle, (char*)&len, sizeof(int), 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::send(fhandle, remote_filename, len, 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/* get size information */
	int64_t size;
	if (UDT::ERROR == UDT::recv(fhandle, (char*)&size, sizeof(int64_t), 0))	{
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	if (size < 0) {
		cout << "no such file " << remote_filename << " on the server\n";
		return -1;
	}

	/*create the parent paths if necessary*/
	char pathname[PATH_MAX] = {0};
	const char *pch = strrchr(local_filename, '/');
	strncpy(pathname, local_filename, pch - local_filename);
	if (access(pathname, F_OK)) {
		char cmd[PATH_MAX] = {0};
		strcpy(cmd, "mkdir -p ");
		strcat(cmd, pathname);
		system(cmd);
	}

	/* receive the file */
	fstream ofs(local_filename, ios::out | ios::binary | ios::trunc);
	int64_t recvsize; 
	int64_t offset = 0;

	if (UDT::ERROR == (recvsize = UDT::recvfile(fhandle, ofs, offset, size))) {
		cout << "recvfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	UDT::close(fhandle);

	ofs.close();

	/* use this function to release the UDT library */
	UDT::cleanup();	
}

/*
 * upload local_filename to remoteip:server_port and rename it to remote_filename
 */
static int 
_sendfile_udt(const char *remote_ip, const char *server_port, const char *local_filename, const char *remote_filename)
{
	/* use this function to initialize the UDT library */
	UDT::startup();

	/* create socket */
	struct addrinfo hints, *peer;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	UDTSOCKET fhandle = UDT::socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

	if (0 != getaddrinfo(remote_ip, server_port, &hints, &peer)) {
		cout << "incorrect server/peer address. " << remote_ip << ":" << server_port << endl;
		return -1;
	}

	/* connect to the server, implict bind */
	if (UDT::ERROR == UDT::connect(fhandle, peer->ai_addr, peer->ai_addrlen)) {
		cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	freeaddrinfo(peer);

	/* send name information of the requested file on the server */
	int len = strlen(remote_filename);

	/* send 1 to indicate this is to upload */
	int one = 1;
	if (UDT::ERROR == UDT::send(fhandle, (char*)&one, sizeof(int), 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::send(fhandle, (char*)&len, sizeof(int), 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	if (UDT::ERROR == UDT::send(fhandle, remote_filename, len, 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return -1;
	}

	/* open the file to read */
	fstream ifs(local_filename, ios::in | ios::binary);

	ifs.seekg(0, ios::end);
	int64_t size = ifs.tellg();
	ifs.seekg(0, ios::beg);

	/* send file size information */
	if (UDT::ERROR == UDT::send(fhandle, (char*)&size, sizeof(int64_t), 0)) {
		cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	UDT::TRACEINFO trace;
	UDT::perfmon(fhandle, &trace);

	// send the file
	int64_t offset = 0;
	if (UDT::ERROR == UDT::sendfile(fhandle, ifs, offset, size)) {
		cout << "sendfile: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	UDT::perfmon(fhandle, &trace);
	/* cout << "speed = " << trace.mbpsSendRate << "Mbits/sec" << endl; */

	UDT::close(fhandle);

	ifs.close();   

	/* use this function to release the UDT library */
	UDT::cleanup();	
}

/*
 * wrapper for download
 */
int
ffs_recvfile(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename, const char *local_filename)
{
	/* only support UDT for now */
	if (strcmp("udt", proto)) {
		cerr << "Only UDT supported for now. " << endl;
		return -1;
	}

	if (-1 == _recvfile_udt(remote_ip, server_port, remote_filename, local_filename)) {
		cerr << "Error in _recvfile_udt(). " << endl;
		return -1;
	}

	return 0;
}

/*
 * wrapper for upload
 */
int
ffs_sendfile(const char *proto, const char *remote_ip, const char *server_port, const char *local_filename, const char *remote_filename)
{
	/* only support UDT for now */
	if (strcmp("udt", proto)) {
		cerr << "Only UDT supported for now. " << endl;
		return -1;
	}

	if (-1 == _sendfile_udt(remote_ip, server_port, local_filename, remote_filename)) {
		cerr << "Error in _sendfile_udt(). " << endl;
		return -1;
	}

	return 0;
}
