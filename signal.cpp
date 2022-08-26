#include <iostream>
#include <algorithm>
#include <iterator>
#include "esp_dsp.h"
#include "signal.h"

static std::int16_t sCoefficients[kSignalLen / 2];

template <class T>
void arrout(const T &aIterable, std::size_t aSize, std::size_t aStep = 1, const std::size_t aStartFrom = 0,
	const char *aDelimiter = ", ")
{
	using ValueType = decltype(aIterable[0]);
	std::size_t count = 0;

	std::copy_if(&aIterable[0], &aIterable[aSize - 1], std::ostream_iterator<ValueType>(std::cout, aDelimiter),
		[&count, aStep, aStartFrom](const ValueType &)
		{
			const bool ret = count % aStep == 0 && count > aStartFrom;
			++count;

			return ret;
		});
}

int main()
{
	dsps_fft2r_init_sc16(sCoefficients, kSignalLen);
	dsps_fft2r_sc16_ansi_(signal, kSignalLen / 2, sCoefficients);
	arrout(signal, kSignalLen);

	return 0;
}
