use std::io::{BufRead, BufReader, BufWriter, Write};
use std::io::{Read};
use std::io;

fn main() {
	let stdin = io::stdin();
	let stdout = io::stdout();

    let fin = BufReader::new(stdin.lock());
	let mut fout = BufWriter::new(stdout.lock());

	/* States:
	 * 0: Normal mode
	 * 1: Found start slash
	 * 2: Found start star
	 * 3: Found end star
	 * 4: C++ comment mode, deactivated on newline
	 */
	let mut state: u32 = 0; // u32 is often faster than u64

	for ch in fin.bytes().map(|x| x.unwrap()) {
		if state == 0 {
			if ch == b'/' {
				state = 1;
			} else {
				write!(&mut fout, "{}", ch as char).expect("Failed to write");
			}
		} else if state == 1 {
			if ch == b'*' {
				state = 2;
			} else if ch == b'/' {
				state = 4;
			} else {
				write!(&mut fout, "/{}", ch as char).expect("Failed to write");
				state = 0;
			}
		} else if state == 2 {
			if ch == b'*' {
				state = 3;
			}
		} else if state == 3 {
			if ch == b'/' {
				state = 0;
				continue;
			} else {
				state = 2;
			}
		} else if state == 4 {
			if ch == b'\n' {
				state = 0;
				write!(&mut fout, "\n").expect("Failed to write");
			}
		}
	}
}
