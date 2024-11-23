#ifndef FFT_H
#define FFT_H

#include <vector>

/**
 * Computes the FFT of the given samples and returns the magnitude spectrum.
 *
 * @param samples Input signal samples (time domain).
 * @param sample_rate Sampling rate of the input signal.
 * @return Vector containing magnitudes of the frequency spectrum.
 */
std::vector<double> compute_fft(const std::vector<double>& samples, int sample_rate);

/**
 * Function to find the dominant frequency in the FFT data
 * 
 * This function analyzes the magnitude spectrum obtained from the FFT to determine
 * the frequency with the highest magnitude, which is considered the dominant frequency.
 *
 * @param magnitudes A vector containing the magnitudes of the frequency bins from the FFT.
 * @param sample_rate The sampling rate of the input signal.
 * @return The dominant frequency in Hz.
 */
double find_dominant_frequency(const std::vector<double>& magnitudes, int sample_rate);

#endif // COMPUTE_FFT_H
