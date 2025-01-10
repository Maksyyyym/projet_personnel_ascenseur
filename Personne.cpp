#include "Personne.h"

Personne::Personne(const std::string &p_nom, int p_etageMontee, int p_etageDescente, int p_quantum) : m_nom(p_nom),
m_etageDescente(p_etageDescente), m_etageMontee(p_etageMontee), m_quantum(p_quantum), m_etat(ATTEND) {}

std::string Personne::reqNom() const {
    return m_nom;
}

int Personne::reqEtageEntree() const {
    return m_etageMontee;
}

int Personne::reqEtageSortie() const {
    return m_etageDescente;
}

int Personne::reqQuantum() const {
    return m_quantum;
}

Personne::etat Personne::reqEtat() const {
    return m_etat;
}

void Personne::asgEtat(const etat &p_etat) {
    m_etat = p_etat;
}
