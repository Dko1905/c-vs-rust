#include <stdio.h>
#include <stdlib.h>

/* # Comment remover
 * Remove c-style comments from a file. Currently only reads from stdin, and
 * outputs to stdout.
 */
#ifdef BUFSIZ
#define BUFFER_SIZE BUFSIZ
#else
#define BUFFER_SIZE 1024*8
#endif

int main() {
	/* States:
	 * 0: Normal mode
	 * 1: Found start slash
	 * 2: Found start star
	 * 3: Found end star
	 * 4: C++ comment mode, deactivated on newline
	 */
	unsigned int state = 0;
	size_t n = 0, read = 0, write = 0;
	unsigned char *buffer, ch = 0;
	buffer = calloc(BUFFER_SIZE, 1);
	buffer[BUFFER_SIZE - 1] = '\0';

	while ((read = fread(buffer, 1, BUFFER_SIZE - 1, stdin)) > 0) {
		write = 0;
		for (n = 0; n < read; ++n) {
			ch = buffer[n];
			if (state == 0) {
				if (ch == '/') {
					state = 1;
				} else {
					buffer[write++] = ch;
				}
			} else if (state == 1) {
				if (ch == '*') {
					state = 2;
				} else if (ch == '/') {
					state = 4;
				} else {
					buffer[write++] = '/';
					buffer[write++] = ch;
					state = 0;
				}
			} else if (state == 2) {
				if (ch == '*') {
					state = 3;
				}
			} else if (state == 3) {
				if (ch == '/') {
					state = 0;
					continue;
				} else {
					state = 2;
				}
			} else if (state == 4) {
				if (ch == '\n') {
					state = 0;
					buffer[write++] = '\n';
				}
			}
		}
		fwrite(buffer, 1, write, stdout);
	}

	return 0;
}
