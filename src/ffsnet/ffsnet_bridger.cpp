/**
 * File: ffsnet_bridger.cpp
 * Desc: This is a C wrapper to call the ffsnet library
 * Author: dzhao8@hawk.iit.edu
 * History:
 * 		06/25/2011 - initial development
 *
 * Compile to a shared library:
 *		g++ -fPIC ffsnet_bridger.cpp --shared -o libffsnet_bridger.so -L. -lffsnet
 *
 */

int ffs_mkdir(const char *, const char *, const char *, const char *);
int ffs_rmfile(const char *, const char *, const char *, const char *);
int ffs_recvfile(const char *, const char *, const char *, const char *, const char *);
int ffs_sendfile(const char *, const char *, const char *, const char *, const char *);

#ifdef __cplusplus
extern "C" {
#endif

	int ffs_mkdir_c(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename) {
		return ffs_mkdir(proto, remote_ip, server_port, remote_filename);
	}

	int ffs_rmfile_c(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename) {
		return ffs_rmfile(proto, remote_ip, server_port, remote_filename);
	}

	int ffs_recvfile_c(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename, const char *local_filename) {
		return ffs_recvfile(proto, remote_ip, server_port, remote_filename, local_filename);
	}

	int ffs_sendfile_c(const char *proto, const char *remote_ip, const char *server_port, const char *local_filename, const char *remote_filename) {
		return ffs_sendfile(proto, remote_ip, server_port, local_filename, remote_filename);
	}

#ifdef __cplusplus
}
#endif
