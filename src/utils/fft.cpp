#include "fft.h"
#include <vector>
#include <complex>
#include <fftw3.h>
#include <cmath>
#include <algorithm>

/**
 * Compute the FFT of the given samples and return the magnitude spectrum.
 * 
 * @param samples Input signal samples (time domain).
 * @param sample_rate Sampling rate of the input signal.
 * @return Vector containing magnitudes of the frequency spectrum.
 */
std::vector<double> compute_fft(const std::vector<double>& samples, int sample_rate) {
    int n = samples.size(); // Number of samples
    std::vector<double> magnitudes(n / 2); // Magnitudes of frequencies

    // Allocate FFTW input and output arrays
    fftw_complex* in = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * n));
    fftw_complex* out = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * n));

    // Copy samples to FFTW input
    for (int i = 0; i < n; ++i) {
        in[i][0] = samples[i]; // Real part
        in[i][1] = 0.0;        // Imaginary part
    }

    // Create and execute FFT plan
    fftw_plan plan = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    // Compute magnitudes for the first n/2 frequencies
    for (int i = 0; i < n / 2; ++i) {
        double real = out[i][0];
        double imag = out[i][1];
        magnitudes[i] = sqrt(real * real + imag * imag);
    }

    // Cleanup FFTW resources
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return magnitudes;
}

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
double find_dominant_frequency(const std::vector<double>& magnitudes, int sample_rate) {
    // Find the index of the maximum magnitude
    auto max_iter = std::max_element(magnitudes.begin(), magnitudes.end());
    int max_index = std::distance(magnitudes.begin(), max_iter);

    // Calculate the corresponding frequency
    int n = magnitudes.size() * 2; // Total number of FFT input samples
    double frequency_resolution = static_cast<double>(sample_rate) / n; // Bin width in Hz
    double dominant_frequency = max_index * frequency_resolution;

    return dominant_frequency;
}
