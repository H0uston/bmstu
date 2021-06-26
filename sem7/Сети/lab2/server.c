#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "info.h"

void perror_and_exit(char *s)
{
	perror(s);
	exit(1);
}

char digit(int num)
	{
		switch (num) {
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		case 16: return 'G';
		case 17: return 'I';
	}
}

int dectox_int(int a, int p, char *s)
{
	int num = (int)a;
	int rest = num % p;
	num /= p;
	if (num == 0)
	{
		s[0] = digit(rest);
		s[1] = '\0';
		return 1;
	}
	int k = dectox_int(num, p, s);
	s[k++] = digit(rest);
	s[k] = '\0';
	return k;
}


int main(void)
{
	struct sockaddr_in server_addr, client_addr;
	int sock, slen = sizeof(client_addr);
	char buf[MSG_LEN];
	char result[MSG_LEN] = { 0 };

	printf("Server started\n");

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		perror_and_exit("socket");

	memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SOCK_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, &server_addr, sizeof(server_addr)) == -1)
		perror_and_exit("bind");

	while (1)
	{
		if (recvfrom(sock, buf, MSG_LEN, 0, &client_addr, &slen) == -1)
			perror_and_exit("recvfrom()");

		int number = atoi(buf);
		printf("Received number: %d\n", number);
		dectox_int(number, 2, &result);
		printf("In bin: %s\n", result);

		dectox_int(number, 8, &result);
		printf("In oct: %s\n", result);

		dectox_int(number, 16, &result);
		printf("In hex: %s\n", result);

		dectox_int(number, 18, &result);
		printf("In variant: %s\n", result);
	}

	close(sock);
	return 0;
}