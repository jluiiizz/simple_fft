#include <stdio.h>
#include <math.h>
#include <complex.h>

double PI;
typedef double complex cpl;

void _fft(cpl buffer[], cpl output[], int n, int step) {
    if (step < n) {
        _fft(output, buffer, n, step * 2);
        _fft(output + step, buffer + step, n, step * 2);

        for (int i = 0; i < n; i += 2 * step) {
            cpl t = cexp(-I * PI * i / n) * output[i + step];
            buffer[i /2] = output[i] + t;
            buffer[(i + n)/2] = output[i] - t;
        }
    }
}

void fft(cpl buffer[], int n) {
    cpl output[n];
    for (int i = 0; i < n; i++) {
        output[i] = buffer[i];
    }

    _fft(buffer, output, n, 1);
}

void show(const char *str, cpl buffer[]) {
    printf("%s", str);

    for (int i = 0; i < 8; i++) {
        if (!cimag(buffer[i])) {
            printf("%g ", creal(buffer[i]));
        } else {
            printf("(%g, %g) ", creal(buffer[i]), cimag(buffer[i]));
        }
    }
}

int main() {
    PI = M_PI;
    cpl buffer[] = {1, 1, 1, 1, 0, 0, 0, 0};

    show("Data: ", buffer);
    fft(buffer, 8);
    show("\n FFT: ", buffer);

    return 0;
}