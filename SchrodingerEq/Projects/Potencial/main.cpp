#include <iostream>
#include <vector>
#include <random>
#include <ctime>

#define N 1000000 // Number of particles
#define ntrial 500 // The number of total evolutions
#define ds 0.1
#define Nbar 20 // The number of samples
#define k 1.0
#define m 1.0
#define h 1.0

double left = -5;
double right = 2;
double D = h * h / (2 * m);
double dt = ds * ds / (2 * D);
int nave = ntrial / Nbar;

double V(double x) {
    return 0.5 * k * x * x;
}

void walk() {
    FILE *f;
    FILE *fNE;

    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\output.csv)", "w");
    fprintf(f, "x\n");
    fclose(f);
    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\output.csv)", "a");

    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\outputNE.csv)", "w");
    fprintf(fNE, "N,E,E_r\n");
    fclose(fNE);
    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\outputNE.csv)", "a");

    std::vector<double> xsite(N);
    double Vref = 0;

    std::mt19937 gen;
    std::uniform_real_distribution<> urd(0, 1);

    for (int i = 0; i < xsite.size(); i++) {
        xsite[i] = right - (right - left) * urd(gen);
        Vref += V(xsite[i]);
    }
    Vref = Vref / xsite.size();

    if (f) {
        for (int i = 0; i < xsite.size(); i++) {
            fprintf(f, "%lf\n", xsite[i]);
        }
    }
    if (fNE) {
        fprintf(fNE, "%d,%f,%f\n", xsite.size(), Vref, Vref);
    }

    for (int trial = 0; trial < ntrial; trial++) {
        double Vmean = 0;

        std::vector<double> xsiteNew;
        for (int i = 0; i < xsite.size(); i++) {
            double dV = (V(xsite[i]) - Vref) * dt;
            double r = urd(gen);
            if (dV < 0) {
                if (r < -dV) {
                    xsiteNew.insert(xsiteNew.end(), xsite[i]);
                    Vmean += V(xsite[i]); // Only for new particle
                }
            } else {
                if (r < dV) {
                    xsite.erase(xsite.begin() + i);
                    i = i - 1;
                }
            }
            // Shift the pedestrian
            if (!(dV > 0 and r < dV)) { // If the pedestrian is alive
                if (urd(gen) < 0.5) {
                    xsite[i] = xsite[i] + ds;
                } else {
                    xsite[i] = xsite[i] - ds;
                }
            }
            Vmean += V(xsite[i]);
        }
        xsite.insert(xsite.end(), xsiteNew.begin(), xsiteNew.end());
        Vmean = Vmean / xsite.size();

        double V_ref_new = 0;
        int dN = xsite.size() - N;
        int N_current = xsite.size();
        std::vector<double> xsiteNew1;
        if (dN >= 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = urd(gen);
                if (r < dN / (N_current + 0.0)) {
                    xsite.erase(xsite.begin() + i);
                    i = i - 1;
                } else {
                    V_ref_new += V(xsite[i]);
                }
            }
        } else if (dN < 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = urd(gen);
                if (r < -dN / (N_current + 0.0)) {
                    xsiteNew1.insert(xsiteNew1.end(), xsite[i]);
                    V_ref_new += 2 * V(xsite[i]);
                } else {
                    V_ref_new += V(xsite[i]);
                }
            }
            xsite.insert(xsite.end(), xsiteNew1.begin(), xsiteNew1.end());
        }
        Vref = V_ref_new / xsite.size();

        if (f and trial > ntrial + 1 - 300) {
            for (int i = 0; i < xsite.size(); i++) {
                fprintf(f, "%lf\n", xsite[i]);
            }
        }
        if (!f) {
            printf("Something is wrong! Not f\n");
        }
        if (fNE) {
            fprintf(fNE, "%d,%f,%f\n", xsite.size(), Vmean, Vref);
        } else { printf("Something is wrong! Not NE\n"); }

        if ((trial + 1) % nave == 0) {
            double perc = (double) trial / (double) ntrial * 100;
            std::cout << perc << " percent of work completed" << std::endl;
        }
    }

}

int main() {
    walk();
}