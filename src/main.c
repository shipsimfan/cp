#include <los/filesystem.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s source destination\n", argv[0]);
		return 1;
	}

	int64_t src = open_file(argv[1], OPEN_READ);
	if(src < 0) {
		printf("Error while opening %s: %s\n", argv[1], strerror(src));
		return 1;
	}

	int64_t dest = open_file(argv[2], OPEN_WRITE | OPEN_TRUNCATE | OPEN_CREATE);
	if(dest < 0) {
		printf("Error while opening %s: %s\n", argv[2], strerror(dest));
		return 1;
	}

	// Copy loop
	char buffer[BUFFER_SIZE];
	while(1) {
		int64_t bytes_read = read_file(src, buffer, BUFFER_SIZE);
		
		if(bytes_read == -1) {
			return 0;
		} else if(bytes_read < -1) {
			printf("Error while reading %s: %s\n", argv[1], strerror(bytes_read));
			return 1;
		}

		int64_t status = write_file(dest, buffer, bytes_read);
		if(status < 0) {
			printf("Error while writing %s: %s\n", argv[2], strerror(status));
			return 1;
		}
	}
}
