#include <iostream>
#include <algorithm>
#include <iterator>
#include "esp_dsp.h"
#include "signal.h"
#include "signalf32.h"

static constexpr const char *kDelimiterDefault = "\n";

template <class T>
void arrout(const T &aIterable, std::size_t aSize, const char *aDelimiter = kDelimiterDefault)
{
	using ValueType = decltype(aIterable[0]);
	std::size_t count = 0;
	std::copy(&aIterable[0], &aIterable[aSize], std::ostream_iterator<ValueType>(std::cout, aDelimiter));
}

template <class T>
void arrouts(const T &arr, const char *aDelimiter = kDelimiterDefault)
{
	arrout(arr.data(), arr.size(), aDelimiter);
}

int testu16()
{
	std::array<std::int16_t, 1024> sCoefficients;
	arrouts(signal);
	dsps_fft2r_init_sc16(sCoefficients.data(), sCoefficients.size());
	dsps_fft2r_sc16_ansi_(signal.data(), kSignalLen, sCoefficients.data());
	dsps_bit_rev_sc16_ansi(signal.data(), signal.size());
//	arrouts(signal);
	dsps_fft2r_sc16_ansi_(signal.data(), kSignalLen, sCoefficients.data());
	dsps_bit_rev_sc16_ansi(signal.data(), signal.size());
//	arrout(signal, kSignalLen * 2);

	return 0;
}

int testf32()
{
	const auto N = kSignalfLen;
	float *y_cf = signalf.data();
	dsps_fft2r_init_fc32(NULL, 4096);
	// Here you have your complex signal.

//	arrouts(signalf);

	// FFT calculated here
	dsps_fft2r_fc32(y_cf, N);
	// Bit reverse
	dsps_bit_rev_fc32(y_cf, N);
	// Here you have your complex FFT spectrum

	// Here you can make your operations with complex spectrum at y_cf
//	arrouts(signalf);

	// FFT calculated here
	dsps_fft2r_fc32(y_cf, N);
	// Bit reverse
	dsps_bit_rev_fc32(y_cf, N);
	// Here you have your original complex signal in time domain.
	// y_cf[i*2 + 0] == x1[i]*wind(i)*N;
	// y_cf[i*2 + 1] == 0;
//	arrouts(signalf);
	// You can make multiplication with constant here:
	dsps_mulc_f32(y_cf, y_cf, 2*N, 1.0f / N, 1, 1);
	arrouts(signalf);
}

int main()
{
	testu16();
//	testf32();

	return 0;
}
