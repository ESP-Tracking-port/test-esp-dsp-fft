#!/usr/bin/python3

import random


FILE_SIGNAL = "signal.h"
CEIL = 255
SIGNAL_LEN = 20
NL = "\n"
DNL = "\n\n"


def real_gen_iter():
	yield "#include <cstdint>" + DNL
	yield "std::int16_t signal[] = {"  + NL

	for i in range(SIGNAL_LEN):
		yield '\t' + str(int(random.random() * CEIL)) + "," + NL  # Real part
		yield '\t' + "0," + NL  # Imaginary part

	yield "};" + NL
	yield "static constexpr std::size_t kSignalLen = sizeof(signal) / sizeof(signal[0]) / 2;"


def file_save(filename, content):
	with open(filename, 'w') as f:
		f.write(content)


def main():
	file_save(FILE_SIGNAL, ''.join(real_gen_iter()))

if __name__ == "__main__":
	main()
