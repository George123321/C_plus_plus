#include <iostream>
#include <vector>
#include <random>
#include <ctime>

#define N 1000000 // Number of particles
#define ntrial 100000 // The number of total evolutions
#define ds 0.01
#define Nbar 100 // The number of samples

double left = -1;
double right = 1;
double a = 2 * 1.5;
int nave = ntrial / Nbar;

void walk() {
    FILE *f;
    FILE *fNE;

    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\inf\output.csv)", "w");
    fprintf(f, "x\n");
    fclose(f);
    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\inf\output.csv)", "a");

    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\inf\outputNE.csv)", "w");
    fprintf(fNE, "N,E,E_r\n");
    fclose(fNE);
    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEq\output\inf\outputNE.csv)", "a");

    std::vector<double> xsite(N);
    double Vref = 0;


    std::mt19937 gen;
    std::uniform_real_distribution<> urd(0, 1);

    {
        #pragma omp parallel for
        for (int i = 0; i < xsite.size(); i++) {
            xsite[i] = right - (right - left) * urd(gen);
        }
    }

    if (f) {
        for (int i = 0; i < xsite.size(); i++) {
            fprintf(f, "%lf\n", xsite[i]);
        }
    }

    if (fNE) {
        fprintf(fNE, "%d,%f,%f\n", xsite.size(), Vref, Vref);
    }


    for (int trial = 0; trial < ntrial; trial++) {
        {
        #pragma omp parallel for
        for (int i = 0; i < xsite.size(); i++) {
            // Shift the pedestrian
            if (urd(gen) < 0.5) {
                xsite[i] = xsite[i] + ds;
            } else {
                xsite[i] = xsite[i] - ds;
            }
        }}

        for (int i = 0; i < xsite.size(); i++) {
            // Kill the pedestrian behind the barrier
            if (xsite[i] < -a/2 or xsite[i] > a/2){
                xsite.erase(xsite.begin() + i);
                i = i - 1;
            }
        }

        int dN = xsite.size() - N;
        int N_current = xsite.size();
        std::vector<double> xsiteNew;
        if (dN >= 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = urd(gen);
                if (r < dN / (N_current + 0.0)) {
                    xsite.erase(xsite.begin() + i);
                    i = i - 1;
                }
            }
        } else if (dN < 0) {
            {
            for (int i = 0; i < xsite.size(); i++) {
                double r = urd(gen);
                if (r < -dN / (N_current + 0.0)) {
                    xsiteNew.insert(xsiteNew.end(), xsite[i]);
                }
            }
            }
            xsite.insert(xsite.end(), xsiteNew.begin(), xsiteNew.end());
        }

        if (f and trial >= ntrial - 300) {
            for (int i = 0; i < xsite.size(); i++) {
                fprintf(f, "%lf\n", xsite[i]);
            }
        }
        if (!f) {
            printf("Something is wrong! Not f\n");
        }
        if (fNE) {
            fprintf(fNE, "%d,%f,%f\n", xsite.size(), 0.0, Vref);
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