use std::io::{BufRead, BufReader, BufWriter, Write};
use std::io;

fn main() {
    let fin = BufReader::new(io::stdin());
	let mut fout = BufWriter::new(io::stdout());

	/* States:
	 * 0: Normal mode
	 * 1: Found start slash
	 * 2: Found start star
	 * 3: Found end star
	 * 4: C++ comment mode, deactivated on newline
	 */
	let mut state: u32 = 0; // u32 is often faster than u64

	for line in fin.lines() {
		for ch in line.expect("Failed to line").chars() {
			if state == 0 {
				if ch == '/' {
					state = 1;
				} else {
					write!(&mut fout, "{}", ch).expect("Failed to write");
				}
			} else if state == 1 {
				if ch == '*' {
					state = 2;
				} else if ch == '/' {
					state = 4;
				} else {
					write!(&mut fout, "{}", ch).expect("Failed to write");
					state = 0;
				}
			} else if state == 2 {
				if ch == '*' {
					state = 3;
				}
			} else if state == 3 {
				if ch == '/' {
					state = 0;
					continue;
				} else {
					state = 2;
				}
			}
		}
		if state == 0 || state == 4 {
			write!(&mut fout, "\n").expect("Failed to write");
		}
	}
}
