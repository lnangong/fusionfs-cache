/**
 * File name: ffsnetd.cpp
 *
 * Function: daemon process for FusionFS network transfer
 *
 * Author: dzhao8@hawk.iit.edu
 *
 * Update history:
 *		- 07/18/2012: add mkdir(), this is not being used for now. It's not been tested either.
 * 		- 07/17/2012: add rmfile()
 * 		- 07/07/2012: better error handling - close file handle and iofs if failure occurs
 *		- 06/18/2012: initial development
 *
 * To compile this single file:
 * 		g++ ffsnetd.cpp -o ffsnetd -I../src -L../src -ludt -lstdc++ -lpthread
 *		NOTE: -I../src (similarly to -L../src) means to include the directory of the udt library, i.e. libudt.so 
 *
 *		You may also need to update the environment variable as:
 *			export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../src
 */

#include <cstdlib>
#include <netdb.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <udt.h>

#include <linux/limits.h>
#include <sys/stat.h>
#include <cerrno>
#include <unistd.h>

using namespace std;

void* transfile(void*);

int main(int argc, char* argv[])
{
	/* usage: ffsd [server_port] */
	if ((2 < argc) || ((2 == argc) && (0 == atoi(argv[1])))) {
		cout << "usage: ffsd [server_port]" << endl;
		return 0;
	}

	/* use this function to initialize the UDT library */
	UDT::startup();

	addrinfo hints;
	addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	string service("9000"); /* default server port */
	if (2 == argc)
		service = argv[1];

	if (0 != getaddrinfo(NULL, service.c_str(), &hints, &res)) {
		cout << "illegal port number or port is busy.\n" << endl;
		return 0;
	}

	UDTSOCKET serv = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (UDT::ERROR == UDT::bind(serv, res->ai_addr, res->ai_addrlen)) {
		cout << "bind: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	freeaddrinfo(res);

	cout << "FusionFS file transfer is ready at port: " << service << endl;

	UDT::listen(serv, 10);

	sockaddr_storage clientaddr;
	int addrlen = sizeof(clientaddr);

	UDTSOCKET fhandle;

	while (true) {
		if (UDT::INVALID_SOCK == (fhandle = UDT::accept(serv, (sockaddr*)&clientaddr, &addrlen))) {
			cout << "accept: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		char clienthost[NI_MAXHOST];
		char clientservice[NI_MAXSERV];
		getnameinfo((sockaddr *)&clientaddr, addrlen, clienthost, sizeof(clienthost), clientservice, sizeof(clientservice), NI_NUMERICHOST|NI_NUMERICSERV);
		/* cout << "new connection: " << clienthost << ":" << clientservice << endl; */
		
		pthread_t filethread;
		pthread_create(&filethread, NULL, transfile, new UDTSOCKET(fhandle));
		pthread_detach(filethread);
	}

	UDT::close(serv);

	/* use this function to release the UDT library */
	UDT::cleanup();

	return 0;
}

/**
 * Thread to accept file request: download or upload
 */
void* transfile(void* usocket)
{
	UDTSOCKET fhandle = *(UDTSOCKET*)usocket;
	delete (UDTSOCKET*)usocket;

	/* aquiring file name information from client */
	char file[1024];
	int len;
	int is_recv; /* 0: download, 1: upload, 2: remove file, 3: make dir */
	
	/* get the request type: download or upload */
	if (UDT::ERROR == UDT::recv(fhandle, (char*)&is_recv, sizeof(int), 0)) {
		cout << "recv: " << UDT::getlasterror().getErrorMessage() << endl;
		return 0;   
	}
	
	/*
	 * The following is for upload
	 */
	if (1 == is_recv) {
		if (UDT::ERROR == UDT::recv(fhandle, (char*)&len, sizeof(int), 0)) {

			UDT::close(fhandle);

			cout << "recv: " << UDT::getlasterror().getErrorMessage() << endl;

			return 0;
		}

		if (UDT::ERROR == UDT::recv(fhandle, file, len, 0)) {

			UDT::close(fhandle);

			cout << "recv: " << UDT::getlasterror().getErrorMessage() << endl;

			return 0;
		}
		file[len] = '\0';

		/* open the file to write */
		fstream ofs(file, ios::out | ios::binary | ios::trunc);
		int64_t recvsize; 
		int64_t offset = 0;		
		
		/* get size information */
		int64_t size;

		if (UDT::ERROR == UDT::recv(fhandle, (char*)&size, sizeof(int64_t), 0)) {

			UDT::close(fhandle);
			ofs.close();

			cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		if (size < 0) {

			UDT::close(fhandle);
			ofs.close();

			cout << "cannot open file " << file << " on the server\n";
			return 0;
		}

		/* receive the file */
		if (UDT::ERROR == (recvsize = UDT::recvfile(fhandle, ofs, offset, size))) {

			UDT::close(fhandle);
			ofs.close();

			cout << "recvfile: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		ofs.close();
	}

	/*
	 * the following is for download
	 */
	if (0 == is_recv) {
		/*get the length of the filename*/
		if (UDT::ERROR == UDT::recv(fhandle, (char*)&len, sizeof(int), 0)) {

			UDT::close(fhandle);

			cout << "recv: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		/*get the file name*/
		if (UDT::ERROR == UDT::recv(fhandle, file, len, 0)) {

			UDT::close(fhandle);

			cout << "recv: " << UDT::getlasterror().getErrorMessage() << endl;

			return 0;
		}
		file[len] = '\0';

		/* open the file */
		fstream ifs(file, ios::in | ios::binary);
		ifs.seekg(0, ios::end);
		int64_t size = ifs.tellg();
		ifs.seekg(0, ios::beg);

		/* send file size information */
		if (UDT::ERROR == UDT::send(fhandle, (char*)&size, sizeof(int64_t), 0))	{

			UDT::close(fhandle);
			ifs.close();

			cout << "send: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		UDT::TRACEINFO trace;
		UDT::perfmon(fhandle, &trace);

		/* send the file */
		int64_t offset = 0;
		if (UDT::ERROR == UDT::sendfile(fhandle, ifs, offset, size)) {

			/* DFZ: This error might be triggered if the file size is zero, which is fine. */

			UDT::close(fhandle);
			ifs.close();

			cout << "sendfile: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		UDT::perfmon(fhandle, &trace);
		/* cout << "speed = " << trace.mbpsSendRate << "Mbits/sec" << endl; */

		ifs.close();
	}

	/*
	 * The following is for remove files
	 */
	if (2 == is_recv) {

		/*receive the length of the filename to be removed*/
		if (UDT::ERROR == UDT::recv(fhandle, (char*)&len, sizeof(int), 0)) {

			UDT::close(fhandle);

			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;

			return 0;
		}

		/*receive the filename string*/
		if (UDT::ERROR == UDT::recv(fhandle, file, len, 0)) {

			UDT::close(fhandle);

			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;

			return 0;
		}
		file[len] = '\0';

		/*remove the file*/
		int stat = unlink(file);
		if (stat < 0) {
			UDT::close(fhandle);
			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
		}

		/*send return status: success or fail*/
		int success = (stat < 0)? 1: 0;
		if (UDT::ERROR == UDT::send(fhandle, (char*)&success, sizeof(int), 0))	{
			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
			UDT::close(fhandle);
			return 0;
		}
	}

	/*
	 * The following is to make a physical directory on the local node
	 */
	if (3 == is_recv) {

		/*receive the length of the directory name to be created*/
		if (UDT::ERROR == UDT::recv(fhandle, (char*)&len, sizeof(int), 0)) {
			UDT::close(fhandle);
			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}

		/*receive the directory name*/
		if (UDT::ERROR == UDT::recv(fhandle, file, len, 0)) {
			UDT::close(fhandle);
			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
			return 0;
		}
		file[len] = '\0';

		/*create the directory*/
		struct stat info;
		int retstat = lstat(file, &info);
		if (retstat && (ENOENT == errno)) { /*does the pathname exist?*/
			char cmd[PATH_MAX] = {0};
			strcpy(cmd, "mkdir -p ");
			strcat(cmd, file);
			system(cmd);

			/*reset the status*/
			retstat = 0;
		}

		/*send return status: success or fail*/
		int success = (retstat < 0)? 1: 0;
		if (UDT::ERROR == UDT::send(fhandle, (char*)&success, sizeof(int), 0))	{
			cout << "rmfile: " << UDT::getlasterror().getErrorMessage() << endl;
			UDT::close(fhandle);
			return 0;
		}
	}

	/*clean up*/
	UDT::close(fhandle);

	return NULL;
}
