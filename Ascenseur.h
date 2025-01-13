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

/**
 * \class Ascenseur
 * \brief Classe représentant le concept d'un ascenseur.
 * Tout objet Ascenseur possède les attributs tels que le nombre
 * d'étages, l'étage courant, la capacité de la cabine, la capacité maximale de personnes qu'il est possible de
 * transporter dans la cabine, la file d'attente de personnes qui appelent l'ascenseur à un certain moment et la
 * direction (haut ou bas). À noter que tout ascenseur débute son voyage à l'étage 0 (non comptabilisé dans le nombre d'étages
 * de l'ascenseur) avec une cabine vide.
 *
 * Il est possible de simuler le parcours de l'ascenseur en fournissant à son constructeur un fichier de format .txt
 * possédant les informations suivante : le nombre d'étage à la première ligne; la capacité maximale à la deuxième
 * ligne; le nom de l'objet Personne suivi de l'étage d'entrée, d'étage de sortie et du temps d'appel d'ascenseur aux
 * lignes subséquentes. Ainsi, l'ascenseur enregistre son scénario de transport qui dépend du nombre de passagers
 * l'appelant aux moments différents et ayant des étages d'arrivée et de destination différents. À noter que les
 * personnes dont les informations sont notées dans le fichier doivent être disposées en ordre d'arrivée.
 *
 * En utilisant la méthode parcoursAscenseur(), il est possible de déterminer l'ordre d'arrivée des personnes à leurs
 * étages de destination respectives, les étages visités lors du parcous en ordre et le temps du parcours
 */
class Ascenseur {
    public:
        enum direction {
            haut,
            bas
          };
        Ascenseur(int p_nombreEtages, size_t p_capaciteMax, int p_etageCourant = 0, size_t p_capacite = 0);
        Ascenseur(std::ifstream& p_fichier);
        int reqNombreEtages() const;
        int reqEtageCourant() const;
        size_t reqCapaciteMax() const;
        size_t reqCapacite() const;
        void asgCapacite(size_t p_capacite);
        void parcoursAscenseur(std::vector <Personne>& ordreArrivee, std::vector <int>& etagesVisites, int& temps, int& indicateur);
        friend std::ostream& operator<<(std::ostream &, const Ascenseur& p_ascenseur);
    private:
        int m_nombreEtages;
        int m_etageCourant;
        size_t m_capaciteMax;
        size_t m_capacite;
        std::queue <Personne> m_personnes;
        direction m_direction;
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
