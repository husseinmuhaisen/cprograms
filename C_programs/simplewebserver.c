#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>


void main ()

{

	// this function will return the file descriptor of the socket.
	int s = socket(AF_INET, SOCK_STREAM, 0);

	/// suitable for ipv4
	struct sockaddr_in addr = {
		AF_INET,
		htons(8080),
		0 // bind to all net interfaces

	};
	// bind function to bind the socket to a certain address
	bind(s, &addr, sizeof(addr));

	// call the listen function
	listen(s, 10);
	int client_fd = accept(s, 0, 0);

	// fill it with zeros
	char buffer[256] = {0};
	// recieve the pakcet client is sending
	recv(client_fd, buffer, 256, 0);

	// GET /file.html...

	char* f = buffer + 5;
	*strchr(f, ' ') = 0; // search for a space and assign it to zero
	int opened_fd = open(f, O_RDONLY);
	
	sendfile(client_fd, opened_fd, 0, 256);

	close(opened_fd);
	close(client_fd);
	close(s);

}