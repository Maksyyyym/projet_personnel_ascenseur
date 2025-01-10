#include "Ascenseur.h"

using namespace std;

std::ostream& operator<<(std::ostream& p_os, const Ascenseur& p_ascenseur){
    p_os <<"   |   |         " << endl;
    for (int i = p_ascenseur.reqNombreEtages(); i > -1; --i) {
        if(p_ascenseur.reqEtageCourant() == i) {
            p_os <<
                "-------|---------" << endl <<
                "|               " << i << endl;
        }
        else if(i == p_ascenseur.reqEtageCourant()-1) {
            p_os <<
                "-------|---------" << endl <<
                "       I        " << i << endl;

        }
        else if(i > p_ascenseur.reqEtageCourant()){
            p_os <<
                "   |   |---------" << endl <<
                "   |   I        " << i << endl;
        }
        else {
            p_os <<
                "       |---------" << endl <<
                "       I        " << i << endl;
        }
    }
    p_os << "-------|---------" << endl;
    p_os << "Arret a l'etage " << p_ascenseur.reqEtageCourant() << endl;
    return p_os;
}

Ascenseur::Ascenseur(int p_nombreEtages, size_t p_capaciteMax, int p_etageCourant): m_nombreEtages(p_nombreEtages), m_etageCourant(p_etageCourant), m_capaciteMax(p_capaciteMax) {
}

Ascenseur::Ascenseur(std::ifstream &p_fichier) {
    string s_nombreEtages;
    string s_capaciteMax;
    string nom;
    int etageMontee;
    int etageDescente;
    int quantum;
    getline(p_fichier, s_nombreEtages);
    getline(p_fichier, s_capaciteMax);
    m_nombreEtages = stoi(s_nombreEtages);
    m_capaciteMax = stoi(s_capaciteMax);
    m_etageCourant = 0;

    while(!p_fichier.eof()) {
        p_fichier >> nom;
        p_fichier >> etageMontee;
        p_fichier >> etageDescente;
        p_fichier >> quantum;
        Personne p(nom, etageMontee, etageDescente, quantum);
        m_personnes.push(p);
    }
    p_fichier.close();
}

int Ascenseur::reqNombreEtages() const {
    return m_nombreEtages;
}

int Ascenseur::reqEtageCourant() const {
    return m_etageCourant;
}

size_t Ascenseur::reqCapaciteMax() const {
    return m_capaciteMax;
}

void Ascenseur::parcoursAscenseur(std::vector <Personne>& ordreArrivee, std::vector <int>& etagesVisites, int& temps) {
    deque <Personne> fileHautAttente;
    deque <Personne> fileBasAttente;
    deque <Personne> fileHautEnRoute;
    deque <Personne> fileBasEnRoute;
    string etat = "haut";

    Personne p = m_personnes.front();
    while(!m_personnes.empty() || !fileHautAttente.empty() || !fileBasAttente.empty() || !fileHautEnRoute.empty() || !fileBasEnRoute.empty()) {
        etagesVisites.push_back(m_etageCourant);

        //Embarquement des personnes sur l'étage courant
        while(p.reqQuantum() == temps && !m_personnes.empty()) {
            if(p.reqEtageEntree() == m_etageCourant) {
                if (etat == "haut")
                    fileHautEnRoute.push_back(p);
                if (etat == "bas")
                    fileBasEnRoute.push_back(p);
                p.asgEtat(Personne::ENROUTE);
            }
            else {
                if(p.reqEtageEntree() > m_etageCourant)
                    fileHautAttente.push_back(p);
                else
                    fileBasAttente.push_back(p);
                p.asgEtat(Personne::ATTEND);
            }
            m_personnes.pop();
            try {
                p = m_personnes.front();
            }
            catch(std::length_error& e) {
                break;
            }
        }

        //Gestion entrée/sortie personnes
        if (etat == "haut") {
            // Vérification s'il y a des personnes qui entrent
            if(!fileHautAttente.empty()) {
                std::sort(fileHautAttente.begin(), fileHautAttente.end(), OrdreCroissantEtageEntree());
                Personne hA = fileHautAttente.front();
                while(hA.reqEtageEntree() == m_etageCourant && !fileHautAttente.empty()) {
                    if(hA.reqEtageSortie() >= m_etageCourant)
                        fileHautEnRoute.push_back(hA);
                    else
                        fileBasEnRoute.push_back(hA);
                    hA.asgEtat(Personne::ENROUTE);
                    fileHautAttente.pop_front();
                    try {
                        hA = fileHautAttente.front();
                    }
                    catch(std::length_error& e) {
                        break;
                    }

                }
            }
            // Vérification s'il y a des personnes qui sortent
            if(!fileHautEnRoute.empty()) {
                std::sort(fileHautEnRoute.begin(), fileHautEnRoute.end(), OrdreCroissantEtageSortie());
                Personne hER = fileHautEnRoute.front();
                while(hER.reqEtageSortie() == m_etageCourant && !fileHautEnRoute.empty()) {
                    ordreArrivee.push_back(hER);
                    hER.asgEtat(Personne::ARRIVEE);
                    fileHautEnRoute.pop_front();
                    try {
                        hER = fileHautEnRoute.front();
                    }
                    catch(std::length_error& e) {
                        break;
                    }
                }
            }
        }
        if (etat == "bas") {
            // Vérification s'il y a des personnes qui entrent
            if(!fileBasAttente.empty()) {
                std::sort(fileBasAttente.begin(), fileBasAttente.end(), OrdreDecroissantEtageEntree());
                Personne bA = fileBasAttente.front();
                while(bA.reqEtageEntree() == m_etageCourant && !fileBasAttente.empty()) {
                    if(bA.reqEtageSortie() <= m_etageCourant)
                        fileBasEnRoute.push_back(bA);
                    else
                        fileHautEnRoute.push_back(bA);
                    bA.asgEtat(Personne::ENROUTE);
                    fileBasAttente.pop_front();
                    try {
                        bA = fileBasAttente.front();
                    }
                    catch(std::length_error& e) {
                        break;
                    }
                }
            }
            // Vérification s'il y a des personnes qui sortent
            if(!fileBasEnRoute.empty()) {
                std::sort(fileBasEnRoute.begin(), fileBasEnRoute.end(), OrdreDecroissantEtageSortie());
                Personne bER = fileBasEnRoute.front();
                while(bER.reqEtageSortie() == m_etageCourant && !fileBasEnRoute.empty()) {
                    ordreArrivee.push_back(bER);
                    bER.asgEtat(Personne::ARRIVEE);
                    fileHautEnRoute.pop_front();
                    try {
                        bER = fileHautEnRoute.front();
                    }
                    catch(std::length_error& e) {
                        break;
                    }
                }
            }
        }

        // Mise à jour de la direction
        if(fileHautAttente.empty() && fileHautEnRoute.empty() && (!fileBasAttente.empty() || !fileBasEnRoute.empty()))
            etat = "bas";
        if(fileBasAttente.empty() && fileBasEnRoute.empty() && (!fileHautAttente.empty() || !fileHautEnRoute.empty()))
            etat = "haut";

        // Changement d'étage (1 quantum)
        if(etat == "bas")
            --m_etageCourant;
        if(etat == "haut")
            ++m_etageCourant;
        ++temps;
    }
}

bool Ascenseur::OrdreCroissantEtageEntree::operator()(const Personne &p1, const Personne &p2) const {
    return p1.reqEtageEntree() < p2.reqEtageEntree();
}

bool Ascenseur::OrdreDecroissantEtageEntree::operator()(const Personne &p1, const Personne &p2) const {
    return p1.reqEtageEntree() > p2.reqEtageEntree();
}

bool Ascenseur::OrdreCroissantEtageSortie::operator()(const Personne &p1, const Personne &p2) const {
    return p1.reqEtageSortie() < p2.reqEtageSortie();
}

bool Ascenseur::OrdreDecroissantEtageSortie::operator()(const Personne &p1, const Personne &p2) const {
    return p1.reqEtageSortie() > p2.reqEtageSortie();
}

