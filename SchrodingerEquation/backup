#include <iostream>

#define N 50
#define srange 2
#define ntrial 4000000 // количество попыток всего
#define ds 0.1
#define k 1.0
#define m 1.0
#define h 1.0
#define Nbar 20 // число усреднений - число средних энергий на выходе программы


double V(double x) {
    return 0.5*k*x*x;
}

void walk() {
    double xsite[100*N];
    double Vref = 0;

    for (int i = 0; i < N; i++) {
        xsite[i] = (0.5 - (double)rand()/RAND_MAX) * srange;
        Vref += V(xsite[i]);
    }
    Vref = Vref/N;

    int psi[1000];
    int Ninitial = N;
    int Nwalker = N;
    double D = h*h/(2*m);
    double dt = ds*ds/D;
    int nave = ntrial/Nbar;
    double nequil = 0.1*ntrial;
    double Esum = 0;

    for (int trial = 0; trial < ntrial; trial++) {
        double Vsum = 0;
        for (int i = Ninitial - 1; i >= 0 ; i--) {
            // смещаем пешехода
            if ((double)rand()/RAND_MAX < 0.5) {
                xsite[i] = xsite[i] + ds;
            }
            else {
                xsite[i] = xsite[i] - ds;
            }

            double dV = (V(xsite[i]) - Vref) * dt;
            double r = (double)rand()/RAND_MAX;
            if (dV < 0 and r < -dV) {
                xsite[Nwalker] = xsite[i];
                Nwalker++;
                Vsum += 2*V(xsite[i]);
            }
            else
                Vsum += V(xsite[i]);
            if (dV > 0 and r < dV) {
                xsite[i] = xsite[Nwalker - 1];
                Nwalker--;
            }
            else
                Vsum += V(xsite[i]);
        }

        double Vmean = Vsum/Nwalker;
        if ((trial + 1) % nave == 0) { // если пришло время усреднять
            double Emean = (Esum + Vmean)/nave; // надо добавить последнюю и усреднить
            std::cout << Emean << " " << Nwalker << " " << Vref << std::endl;
            Esum = 0;
        }
        else {
            Esum += Vmean;
        }

        if (trial > nequil) { // отбросили первые сколько-то испытаний
            for (int i = 0; i < Ninitial; i++) {
                psi[i] += 1;
            }
        }

        Vref = Vmean - (Nwalker - N)/(N*dt);
        Ninitial = Nwalker;
    }
}



int main() {
    walk();
    return 0;
}