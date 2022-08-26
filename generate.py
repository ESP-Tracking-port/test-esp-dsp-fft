#!/usr/bin/python3

import random
import math
import pathlib
import os


FILE_SIGNAL = "signal.h"
FILE_SIGNAL_FLOAT = "signalf32.h"
CEIL = 255
SIGNAL_LEN = 64
NL = "\n"
DNL = "\n\n"


def file_append(appendix, fname):

	if not os.path.exists(fname):
		mode = 0o774
		path = pathlib.Path(str(fname)).parent.resolve()

		if pathlib.Path(__file__).parent.resolve() != path \
				and not os.path.exists(path):
			os.makedirs(str(path), mode)

		with open(fname, 'w') as f:
			pass

	with open(fname, "a") as f:
		f.write(appendix)


def real_gen_iter(typestr, suffix="", tp=int):
	yield "#include <cstdint>" + NL
	yield "#include <array>" + NL
	yield NL
	yield "static constexpr std::size_t kSignal%sLen = %d;" % (suffix,
		SIGNAL_LEN)
	yield NL
	yield "std::array<%s, kSignalLen * 2> signal%s {{" % (typestr, suffix) + NL

	for i in range(SIGNAL_LEN):
		# yield '\t' + str(tp(random.random() * CEIL)) + "," + NL  # Real part
		yield '\t' + str(tp(math.cos(i) * CEIL)) + "," + NL  # Real part
		yield '\t' + "0," + NL  # Imaginary part

	yield "}};" + NL


def main():
	file_append(''.join(real_gen_iter("std::int16_t", "", int)), FILE_SIGNAL)
	file_append(''.join(real_gen_iter("float", "f", float)), FILE_SIGNAL_FLOAT)


if __name__ == "__main__":
	main()
