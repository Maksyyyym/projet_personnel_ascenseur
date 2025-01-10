#include <iostream>
#include "Ascenseur.h"

using namespace std;

int main()
{
    ifstream f_trace1("traceAscenseur1.txt", ios::in);
    Ascenseur a(f_trace1);
    int temps = 0;
    std::vector <Personne> ordreArrivee;
    std::vector <int> etagesVisites;
    a.parcoursAscenseur(ordreArrivee, etagesVisites, temps);

    return 0;
}
