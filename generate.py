#!/usr/bin/python3

import random
import math


FILE_SIGNAL = "signal.h"
CEIL = 255
SIGNAL_LEN = 64
NL = "\n"
DNL = "\n\n"


def real_gen_iter():
	yield "#include <cstdint>" + NL
	yield "#include <array>" + NL
	yield NL
	yield "using ValueType = std::int16_t" + NL
	yield "static constexpr std::size_t kSignalLen = %d;" % SIGNAL_LEN
	yield NL
	yield "std::array<std::int16_t, kSignalLen * 2> signal {{" + NL

	for i in range(SIGNAL_LEN):
		# yield '\t' + str(int(random.random() * CEIL)) + "," + NL  # Real part
		yield '\t' + str(int(math.cos(i) * CEIL)) + "," + NL  # Real part
		yield '\t' + "0," + NL  # Imaginary part

	yield "}};" + NL


def file_save(filename, content):
	with open(filename, 'w') as f:
		f.write(content)


def main():
	file_save(FILE_SIGNAL, ''.join(real_gen_iter()))

if __name__ == "__main__":
	main()
