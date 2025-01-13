#include <iostream>
#include "Ascenseur.h"

using namespace std;

int main()
{
    ifstream f_trace1("traceAscenseur3.txt", ios::in);
    Ascenseur a(f_trace1);
    int temps, indicateur = 0;
    std::vector <Personne> ordreArrivee;
    std::vector <int> etagesVisites;
    a.parcoursAscenseur(ordreArrivee, etagesVisites, temps, indicateur);
    cout << endl;
    cout << "Temps de transport : " << temps << endl;
    cout << "Etages visites (en ordre) : " << endl;
    for (int i = 0; i < etagesVisites.size(); ++i) {
        if(i == etagesVisites.size()-1)
            cout << etagesVisites[i] << endl;
        else
            cout << etagesVisites[i] << ", ";
    }
    cout << "Ordre d'arrivee a l'etage de destination : " << endl;
    for (int i = 0; i < ordreArrivee.size(); ++i) {
        if(i == ordreArrivee.size()-1)
            cout << ordreArrivee[i].reqNom() << endl;
        else
            cout << ordreArrivee[i].reqNom() << ", ";
    }
    cout << a;
    return 0;
}
