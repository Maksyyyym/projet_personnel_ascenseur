#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>

class Personne{
  public:
    enum etat {
      ATTEND,
      ENROUTE,
      ARRIVEE
    };
    Personne(const std::string& p_nom, int p_etageMontee, int p_etageDescente, int quantum);
    std::string reqNom() const;
    int reqEtageEntree() const;
    int reqEtageSortie() const;
    int reqQuantum() const;
    etat reqEtat() const;
    void asgEtat(const etat& p_etat);
  private:
    std::string m_nom;
    int m_etageMontee;
    int m_etageDescente;
    int m_quantum;
    etat m_etat;
};

#endif //PERSONNE_H
