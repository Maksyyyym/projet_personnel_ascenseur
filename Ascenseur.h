#ifndef ASCENSEUR_H
#define ASCENSEUR_H

#include "Personne.h"
#include <vector>
#include <string>
#include <list>
#include <ostream>
#include <fstream>
#include <queue>
#include <deque>
#include <algorithm>

class Ascenseur {
    public:
        Ascenseur(int p_nombreEtages, size_t p_capaciteMax, int p_etageCourant = 0);
        Ascenseur(std::ifstream& p_fichier);
        void ajoutEtage();
        int reqNombreEtages() const;
        int reqEtageCourant() const;
        size_t reqCapaciteMax() const;
        void parcoursAscenseur(std::vector <Personne>& ordreArrivee, std::vector <int>& etagesVisites, int& temps);

        bool operator()(const Personne &p1, const Personne &p2) const;

        friend std::ostream& operator<<(std::ostream &, const Ascenseur& p_ascenseur);
    private:
        int m_nombreEtages;
        int m_etageCourant;
        size_t m_capaciteMax;
        std::queue <Personne> m_personnes;
        class OrdreCroissantEtageEntree {
            public:
                bool operator() (const Personne &p1, const Personne &p2) const;
        };
        class OrdreDecroissantEtageEntree {
            public:
                bool operator() (const Personne &p1, const Personne &p2) const;
        };
        class OrdreCroissantEtageSortie {
        public:
            bool operator() (const Personne &p1, const Personne &p2) const;
        };
        class OrdreDecroissantEtageSortie {
        public:
            bool operator() (const Personne &p1, const Personne &p2) const;
        };

};

#endif //ASCENSEUR_H
