#include <iostream>
#include <fstream>
#include <vector>

#define N 50
#define srange 2
#define ntrial 10000 // количество эволюций всего
#define ds 0.1
#define k 1.0
#define m 1.0
#define h 1.0
#define Nbar 10 // число усреднений - число средних энергий на выходе программы


double V(double x) {
    return 0.5 * k * x * x;
}

void walk(short ref) {
    FILE *f;
    FILE *fNE;

    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\output.csv)", "w");
    fprintf(f, "x\n");
    fclose(f);
    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\output.csv)", "a");

    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\outputNE.csv)", "w");
    fprintf(fNE, "N,E\n");
    fclose(fNE);
    fNE = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\outputNE.csv)", "a");

    //double xsite[100*N];
    std::vector<double> xsite(N);
    double Vref = 0;

    for (int i = 0; i < xsite.size(); i++) {
        xsite[i] = (0.5 - (double) rand() / RAND_MAX) * srange;
        Vref += V(xsite[i]);
    }
    Vref = Vref / xsite.size();

    int nwalker = N; // Теперь этот параметр по сути xsite.size()
    //double D = h*h/(2*m);
    double D = 0.5;
    double dt = ds * ds / (2 * D);
    int nave = ntrial / Nbar;
    double nequil = 0.1 * ntrial;
    double Esum = 0;

    for (int trial = 0; trial < ntrial; trial++) {
        double Vsum = 0;
        for (int i = 0; i < xsite.size(); i++) {
            // смещаем пешехода
            if ((double) rand() / RAND_MAX < 0.5) {
                xsite[i] = xsite[i] + ds;
            } else {
                xsite[i] = xsite[i] - ds;
            }

            double dV = (V(xsite[i]) - Vref) * dt;
            double r = (double) rand() / RAND_MAX;
            if (dV < 0) {
                if (r < -dV) {
                    xsite.insert(xsite.end(), xsite[i]);
                    nwalker++;
                    Vsum += 2 * V(xsite[i]); // TODO: 2?
                } else {
                    Vsum += V(xsite[i]);
                }

            } else {
                if (r < dV) {
                    //xsite[i] = xsite[xsite.size() - 1]; // TODO(DONE!): не учитывается последний пешеход
                    xsite.erase(xsite.begin() + i);
                    nwalker--;
                } else
                    Vsum += V(xsite[i]);
            }
        }

        double Vmean = Vsum / (int) xsite.size();
        if (fNE) {
            fprintf(fNE, "%d,%f\n", xsite.size(), Vmean);
        }

        if ((trial + 1) % nave == 0) { // если пришло время усреднять
            double Emean = (Esum + Vmean) / nave; // надо добавить последнюю и усреднить
            std::cout << Emean << " " << xsite.size() << " " << Vref << std::endl;
            Esum = 0;
        } else {
            Esum += Vmean;
        }

        /*
        if (trial > nequil) { // отбросили первые сколько-то испытаний
            if (f) {
                for (int i = 0; i < N; i++) {
                    fprintf(f, "%lf\n", xsite[i]);
                }
            }
        }
        else {
            if (f10) {
                for (int i = 0; i < N; i++) {
                    fprintf(f10, "%lf\n", xsite[i]);
                }
            }
        }*/

        if (f) {
            for (int i = 0; i < N; i++) {
                fprintf(f, "%lf\n", xsite[i]);
            }
        }

        if (ref != 0) {
            Vref = Vmean - ((int) xsite.size() - N) /
                           (N * dt); // (DONE)TODO: как себя ведет система без вырвнивания потенциала (график)
        } else { Vref = Vmean; }
    }
    fclose(f);
    fclose(fNE);
}


int main() {
    walk(1);

    // (DONE)TODO: посмотреть, что будет в первых 10% с волновой функцией, E, N(от врмемени)
    // (DONE)TODO: построить пси от х теоретическую
    return 0;
}