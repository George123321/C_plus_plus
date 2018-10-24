#include <iostream>
#include <fstream>
#include <vector>

#define N 50
#define srange 2
#define ntrial 100 // количество эволюций всего
#define ds 0.1
#define k 1.0
#define m 1.0
#define h 1.0
#define Nbar 10 // число усреднений - число средних энергий на выходе программы


double V(double x) {
    return 0.5*k*x*x;
}

void walk() {
    FILE *f;
    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\output.csv)", "w");
    fprintf(f, "x\n");
    fclose(f);
    f = fopen(R"(C:\Users\George\Desktop\git_projects\C_plus_plus\SchrodingerEquation\output.csv)", "a");

    //double xsite[100*N];
    std::vector<double> xsite(N);
    double Vref = 0;

    for (int i = 0; i < N; i++) {
        xsite[i] = (0.5 - (double) rand() / RAND_MAX) * srange;
        Vref += V(xsite[i]);
    }
    Vref = Vref / N;

    int ninitial = N;
    int nwalker = N;
    //double D = h*h/(2*m);
    double D = 0.5;
    double dt = ds*ds/(2*D);
    int nave = ntrial/Nbar;
    double nequil = 0.1*ntrial;
    double Esum = 0;

    for (int trial = 0; trial < ntrial; trial++) {
        double Vsum = 0;
        for (auto it = xsite.begin(); it != xsite.end() ; it++) {
            // смещаем пешехода
            if ((double)rand()/RAND_MAX < 0.5) {
                *it = *it + ds;
            }
            else {
                *it = *it - ds;
            }

            double dV = (V(*it) - Vref) * dt;
            double r = (double)rand()/RAND_MAX;
            if (dV < 0) {
                if (r < -dV) {
                    xsite.insert(xsite.end(), *it);
                    nwalker++;
                    Vsum += 2*V(*it);
                    //printf("%f\n", dV);
                }
                else {
                    Vsum += V(*it);
                }

            }
            else {
                if (r < dV) {
                    //xsite[i] = xsite[nwalker - 1]; // TODO: не учитывается последний пешеход
                    xsite.erase(it);
                    nwalker--;
                }
                else
                    Vsum += V(*it);
            }
        }

        double Vmean = Vsum/nwalker;
        if ((trial + 1) % nave == 0) { // если пришло время усреднять
            double Emean = (Esum + Vmean)/nave; // надо добавить последнюю и усреднить
            std::cout << Emean << " " << nwalker << " " << Vref << std::endl;
            Esum = 0;
        }
        else {
            Esum += Vmean;
        }

        if (trial > nequil) { // отбросили первые сколько-то испытаний
            if (f) {
                for (int i = 0; i < N; i++) {
                    fprintf(f, "%lf\n", xsite[i]);
                }
            }

        }

        Vref = Vmean - (nwalker - N)/(N*dt); // TODO: как себя ведет система без вырвнивания потенциала (график)
        ninitial = nwalker;
    }
    fclose(f);
}
