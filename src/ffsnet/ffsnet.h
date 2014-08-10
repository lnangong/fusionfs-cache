#ifndef _FFSNET_H_
#define _FFSNET_H_

int ffs_mkdir(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename);
int ffs_rmfile(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename);
int ffs_recvfile(const char *proto, const char *remote_ip, const char *server_port, const char *remote_filename, const char *local_filename);
int ffs_sendfile(const char *proto, const char *remote_ip, const char *server_port, const char *local_filename, const char *remote_filename);

#endif
