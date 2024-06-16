#include <iostream>
#include <cmath>
#include <xlnt/xlnt.hpp>

// correction factor
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

// path loss
double cost231Hata(double f, double d, double h_b, double h_m, int citySize) {
    double L;
    double a_hm = correctionFactor(f, h_m);
    if (citySize == 0) { // suburb
        L = 46.3 + 33.9 * log10(f) - 13.82 * log10(h_b) - a_hm + (44.9 - 6.55 * log10(h_b)) * log10(d);
    } else { // urban
        L = 46.3 + 33.9 * log10(f) - 13.82 * log10(h_b) - a_hm + (44.9 - 6.55 * log10(h_b)) * log10(d) + 3;
    }
    return L;
}

int main() {
    xlnt::workbook wb;
    wb.load("path_loss_data.xlsx"); 
    xlnt::worksheet ws = wb.active_sheet();

    
    for (auto row : ws.rows(false)) {
        double frequency = row[0].value<double>();      // MHz
        double distance = row[1].value<double>();       // Km
        double baseHeight = row[2].value<double>();     // Meters
        double mobileHeight = row[3].value<double>();   // Meters
        int citySize = row[4].value<int>();             // 0 for suburb, 1 for urban

        
        double pathLoss = cost231Hata(frequency, distance, baseHeight, mobileHeight, citySize); // path loss

        
        std::cout << "Frequency: " << frequency << " MHz, "
                  << "Distance: " << distance << " km, "
                  << "Base Height: " << baseHeight << " m, "
                  << "Mobile Height: " << mobileHeight << " m, "
                  << "City Size: " << (citySize == 0 ? "Small to Medium" : "Metropolitan") << ", "
                  << "Path Loss: " << pathLoss << " dB" << std::endl;
    }

    return 0;
}
