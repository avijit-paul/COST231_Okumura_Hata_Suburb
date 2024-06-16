#include <stdio.h>
#include <math.h>

double correctionFactor(double f, double h_m) {
    double a_hm;
    if (f > 150 && f <= 200) {
        a_hm = 8.29 * pow(log10(1.54 * h_m), 2) - 1.1;
    } else if (f > 200) {
        a_hm = 3.2 * pow(log10(11.75 * h_m), 2) - 4.97;
    } else {
        a_hm = 0.8 + (1.1 * log10(f) - 0.7) * h_m - 1.56 * log10(f);
    }
    return a_hm;
}


double cost231Hata(double f, double d, double h_b, double h_m, int citySize) {
    double L;
    double a_hm = correctionFactor(f, h_m);
    if (citySize == 0) { // Suburb/Rural
        L = 46.3 + 33.9 * log10(f) - 13.82 * log10(h_b) - a_hm + (44.9 - 6.55 * log10(h_b)) * log10(d);
    } else { // Urban
        L = 46.3 + 33.9 * log10(f) - 13.82 * log10(h_b) - a_hm + (44.9 - 6.55 * log10(h_b)) * log10(d) + 3;
    }
    return L;
}

int main() {
    double frequency;  // MHz
    double distance;   // Km
    double baseHeight; // Meters
    double mobileHeight; // Meters
    int citySize;      // suburb or urban(0 for suburb/rural, 1 for urban)

    
    printf("Enter frequency (in MHz): ");
    scanf("%lf", &frequency);
    printf("Enter distance (in km): ");
    scanf("%lf", &distance);
    printf("Enter base station antenna height (in meters): ");
    scanf("%lf", &baseHeight);
    printf("Enter mobile station antenna height (in meters): ");
    scanf("%lf", &mobileHeight);
    printf("Enter city size (0 for small to medium-sized, 1 for metropolitan): ");
    scanf("%d", &citySize);

    
    double pathLoss = cost231Hata(frequency, distance, baseHeight, mobileHeight, citySize);

    
    printf("The path loss is: %.2f dB\n", pathLoss);

    return 0;
}
