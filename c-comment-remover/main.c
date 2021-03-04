#include <stdio.h>
#include <stdlib.h>

/* # Comment remover
 * Remove c-style comments from a file. Currently only reads from stdin, and
 * outputs to stdout.
 */
// #ifdef BUFSIZ
// #define BUFFER_SIZE BUFSIZ
// #else
#define BUFFER_SIZE 1024*8
// #endif

int main() {
	/* States:
	 * 0: Normal mode
	 * 1: Found start slash
	 * 2: Found start star
	 * 3: Found end star
	 * 4: C++ comment mode, deactivated on newline
	 */
	unsigned int state = 0;
	size_t n = 0;
	unsigned char buffer[BUFFER_SIZE], *buftmp, ch = 0;
	buffer[BUFFER_SIZE - 1] = '\0';

	while ((fread(buffer, 1, BUFFER_SIZE - 1, stdin)) > 0) {
		buftmp = buffer;
		while ((ch = *(buftmp++)) != '\0') {
			if (state == 0) {
				if (ch == '/') {
					state = 1;
				} else {
					printf("%c", (unsigned char)ch);
				}
			} else if (state == 1) {
				if (ch == '*') {
					state = 2;
				} else if (ch == '/') {
					state = 4;
				} else {
					printf("/");
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
					printf("\n");
				}
			}
		}
	}

	return 0;
}
