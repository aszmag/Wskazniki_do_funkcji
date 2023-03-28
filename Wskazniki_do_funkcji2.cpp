#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>

using namespace std;

double f(double x) {
    return x * x - 4;
}

double calka(double (*f)(double), double a, double b) {
    double dx = 1e-5;
    double suma = 0;
    for (double x = a + .5 * dx; x < b; x += dx)
        suma += f(x);
    return suma * dx;
}


double pochodna1(double (*f)(double), double x) {
    double h = 1e-8;
    return (f(x + h) - f(x)) / h;
}


double pochodna2(double (*f)(double), double x) {
    double h = 1e-4;
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

bool MZbisekcja(double (*f)(double), double &mz, double a, double b) {
    double fa = f(a), fb = f(b);
    if (fa * fb > 0) return false;
    for (int i = 0; i < 40; ++i) {
        double s = .5 * (a + b);
        double fs = f(s);
        if (fb * fs > 0) b = s, fb = fs;
        else a = s, fa = fs;
    }
    mz = .5 * (a + b);
    return true;
}

bool MZsieczne(double (*f)(double), double &mz, double a, double b) {
    double fa = f(a), fb = f(b);
    if (fa * fb > 0) return false;
    for (int i = 0; i < 20; ++i) {
        double s = a + fa * (b - a) / (fa - fb);
        double fs = f(s);
        if (fb * fs > 0) b = s, fb = fs;
        else a = s, fa = fs;
    }
    mz = a + fa * (b - a) / (fa - fb);
    return true;
}

int main()
{
    cout << fixed << setprecision(12);
    cout << "Calka = " << calka(sin, 0, M_PI) << '\n';

    cout << "Pierwsza pochodna: " << pochodna1(f, 0) << '\n';
    cout << "Druga pochodna:    " << pochodna2(f, 0) << '\n';

    double mz;
    if (!MZbisekcja(f, mz, 1, 4)) cout << "Brak miejsca zerowego\n";
    else cout << "Miejsce zerowe bisekcja: " << mz << '\n';
    if (!MZsieczne(f, mz, 1, 4)) cout << "Brak miejsca zerowego\n";
    else cout << "Miejsce zerowe sieczne: " << mz << '\n';

    for (double x = -1000, f1 = f(x), dx = .01; x < 1000; x += dx) {
        double fx = f(x + dx);
        if (fx * f1 <= 0)
            if (MZbisekcja(f, mz, x, x + dx)) cout << "Miejsce zerowe: " << mz << '\n';
        f1 = fx;
    }
    cout << "\n";
}
