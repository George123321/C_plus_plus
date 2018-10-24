#include <iostream>
#include <vector>

#define N 1000000
#define srange 1
#define ntrial 5// количество эволюций всего
#define ds 0.1
#define k 1.0
#define m 1.0
#define h 1.0
#define Nbar 20 // число усреднений - число средних энергий на выходе программы
#include <limits>
#include <math.h>

double V1(double x) {
    return 0.5 * k * x * x;
}

double V(double x) {
    return 0;
}


void walk1(short ref) {
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

    //double xsite[100*N];
    std::vector<double> xsite(N);
    double Vref = 0;

    for (int i = 0; i < xsite.size(); i++) {
        xsite[i] = (0.5 - rand() / (RAND_MAX + 1.0)) * srange;
        Vref += V(xsite[i]);
    }
    Vref = Vref / xsite.size();

    if (f) {
        for (int i = 0; i < N; i++) {
            fprintf(f, "%lf\n", xsite[i]);
        }
    }

    int nwalker = N; // Теперь этот параметр по сути xsite.size()
    //double D = h*h/(2*m);
    double D = 0.5;
    double dt = ds * ds / (2 * D);
    int nave = ntrial / Nbar;
    double Esum = 0;

    for (int trial = 0; trial < ntrial; trial++) {
        double Vsum = 0;

        std::vector<double> xsiteNew;
        for (int i = 0; i < xsite.size(); i++) {
            double dV = (V(xsite[i]) - Vref) * dt;
            double r = rand() / (RAND_MAX + 1.0);
            if (dV < 0) {
                if (r < -dV) {
                    xsiteNew.insert(xsiteNew.end(), xsite[i]);
                    nwalker++;
                    Vsum += 2*V(xsite[i]); // (DONE)TODO: 2? - сейчас 2 не ставим, т.к. мы еще встретим эту частицу
                } else {
                    Vsum += V(xsite[i]);
                }
            } else {
                if (r < dV) {
                    //xsite[i] = xsite[xsite.size() - 1]; // TODO(DONE!): не учитывается последний пешеход
                    xsite.erase(xsite.begin() + i);
                    i = i - 1; //!!!!!
                    nwalker--;
                } else
                    Vsum += V(xsite[i]);
            }
            // смещаем пешехода
            if(!(dV > 0 and r < dV)) { // если пешеход остался жив
                if (rand() / (RAND_MAX + 1.0) < 0.5) {
                    xsite[i] = xsite[i] + ds;
                } else {
                    xsite[i] = xsite[i] - ds;
                }
            }
            //printf("%d\n", xsite.size());
        }
        xsite.insert(xsite.end(), xsiteNew.begin(), xsiteNew.end());
        //xsiteNew.clear();

        double Vmean = Vsum / (int) xsite.size();
        if (fNE) {
            fprintf(fNE, "%d,%f,%f\n", xsite.size(), Vmean, Vref);
        }

        if ((trial + 1) % nave == 0) { // если пришло время усреднять
            double Emean = (Esum + Vmean) / nave; // надо добавить последнюю и усреднить
            std::cout << Emean << " " << xsite.size() << " " << Vref << std::endl;
            Esum = 0;
        } else {
            Esum += Vmean;
        }

        if (f and trial > ntrial + 1 - 300) {
            for (int i = 0; i < xsite.size(); i++) {
                fprintf(f, "%lf\n", xsite[i]);
            }
        }

        /*
        if (ref != 0) {
            Vref = Vmean - ((int) xsite.size() - N) / (N * dt); // (DONE)TODO: как себя ведет система без вырвнивания потенциала (график)
        } else { Vref = Vmean; }*/


        double V_ref_new = 0;
        int dN = xsite.size() - N;
        int N1 = xsite.size();
        std::vector<double> xsiteNew1;
        if (dN >= 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = rand() / (RAND_MAX + 1.0);
                if (r < dN/(N1+0.0)) {
                    xsite.erase(xsite.begin() + i);
                    i = i - 1; //!!!!!
                    nwalker--;
                }
                else {
                    V_ref_new += V(xsite[i]);
                }
            }
        }
        else if (dN < 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = rand() / (RAND_MAX + 1.0);
                if (r < -dN/(N1+0.0)) {
                    xsiteNew1.insert(xsiteNew1.end(), xsite[i]);
                    V_ref_new += 2*V(xsite[i]);
                }
                else {
                    V_ref_new += V(xsite[i]);
                }
            }
            xsite.insert(xsite.end(), xsiteNew1.begin(), xsiteNew1.end());
        }

        Vref = V_ref_new / xsite.size();
    }
    fclose(f);
    fclose(fNE);
}

void walk(short ref) {
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

    //double xsite[100*N];
    std::vector<double> xsite(N);
    double Vref = 0;

    for (int i = 0; i < xsite.size(); i++) {
        xsite[i] = (rand() / (RAND_MAX + 1.0)) * srange;
        Vref += V(xsite[i]);
    }
    Vref = Vref / xsite.size();

    if (f) {
        for (int i = 0; i < N; i++) {
            fprintf(f, "%lf\n", xsite[i]);
        }
    }

    if (fNE) {
        fprintf(fNE, "%d,%f,%f\n", xsite.size(), 0.0, Vref);
    }


    int nwalker = N; // Теперь этот параметр по сути xsite.size()
    //double D = h*h/(2*m);
    double D = 0.5;
    double dt = ds * ds / (2 * D);
    int nave = ntrial / Nbar;

    for (int trial = 0; trial < ntrial; trial++) {
        for (int i = 0; i < xsite.size(); i++) {
            // смещаем пешехода
            if (rand() / (RAND_MAX + 1.0) < 0.5) {
                xsite[i] = xsite[i] + ds;
            } else {
                xsite[i] = xsite[i] - ds;
            }



            // пишем удаление за пределами ямы
            if (xsite[i] < 0 or xsite[i] > 3){
                xsite.erase(xsite.begin() + i);
                i = i - 1; //!!!!!
                nwalker--;
            }
        }

        double Vmean = 0;
        if (fNE) {
            fprintf(fNE, "%d,%f,%f\n", xsite.size(), Vmean, Vref);
        }

        /*
        if ((trial + 1) % nave == 0) { // если пришло время усреднять
            double Emean = 0; // надо добавить последнюю и усреднить
            std::cout << Emean << " " << xsite.size() << " " << Vref << std::endl;
        }*/

        if (!f and trial == 1) {
            for (int i = 0; i < xsite.size(); i++) {
                if (fabs(xsite[i] - 0.386932) <= 0.000005) {
                    printf("i = %d, xsite[i] = %f\n", i, xsite[i]);
                }
                fprintf(f, "%lf\n", xsite[i]);
            }
        }

        /*
        if (ref != 0) {
            Vref = Vmean - ((int) xsite.size() - N) / (N * dt); // (DONE)TODO: как себя ведет система без вырвнивания потенциала (график)
        } else { Vref = Vmean; }*/

        int dN = xsite.size() - N;
        int N1 = xsite.size();
        std::vector<double> xsiteNew1;
        if (dN >= 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = rand() / (RAND_MAX + 1.0);
                if (r < dN/(N1+0.0)) {
                    xsite.erase(xsite.begin() + i);
                    i = i - 1; //!!!!!
                    nwalker--;
                }
            }
        }
        else if (dN < 0) {
            for (int i = 0; i < xsite.size(); i++) {
                double r = rand() / (RAND_MAX + 1.0);
                if (r < -dN/(N1+0.0)) {
                    xsiteNew1.insert(xsiteNew1.end(), xsite[i]);
                }
            }
            xsite.insert(xsite.end(), xsiteNew1.begin(), xsiteNew1.end());
        }

        Vref = 0;
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