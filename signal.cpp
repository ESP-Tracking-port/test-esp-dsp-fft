#include <iostream>
#include <algorithm>
#include <iterator>
#include "esp_dsp.h"
#include "signal.h"

template <class T>
void arrout(const T &aIterable, std::size_t aSize, std::size_t aStep = 1, const std::size_t aStartFrom = 0,
	const char *aDelimiter = ", ")
{
	using ValueType = decltype(aIterable[0]);
	std::size_t count = 0;

	std::copy_if(&aIterable[0], &aIterable[aSize], std::ostream_iterator<ValueType>(std::cout, aDelimiter),
		[&count, aStep, aStartFrom](const ValueType &)
		{
			const bool ret = count % aStep == 0 && count > aStartFrom;
			++count;

			return ret;
		});

	std::cout << std::endl << std::endl;
}

template <class T>
void arrouts(const T &arr, std::size_t aStep = 1, const std::size_t aStartFrom = 0, const char *aDelimiter = ", ")
{
	arrout(arr.data(), arr.size(), aStep, aStartFrom, aDelimiter);
}

int testu16()
{
	static std::array<std::int16_t, 4096> sCoefficients;
	static auto buf = signal;
	arrouts(buf);
	dsps_fft2r_init_sc16(sCoefficients.data(), sCoefficients.size());
	dsps_fft2r_sc16_ansi_(buf.data(), kSignalLen, sCoefficients.data());
	dsps_bit_rev_sc16_ansi(buf.data(), buf.size());
	arrouts(buf);
	dsps_fft2r_sc16_ansi_(buf.data(), kSignalLen, sCoefficients.data());
	dsps_bit_rev_sc16_ansi(buf.data(), buf.size());
	arrout(buf, kSignalLen * 2, 1);

	return 0;
}

int main()
{
	return testu16();
}
