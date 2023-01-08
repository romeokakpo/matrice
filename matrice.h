#ifndef MATRICE_H
#define MATRICE_H

#include <vector>
#include <iostream>
#include "global_header.h"

class Matrice
{
public:
    Matrice():m_row(0), m_col(0)
    {};

    ///@brief Constructeur d'une matrice carre
    explicit Matrice(int dimension);

    Matrice(int ligne, int colonne);
    Matrice(int ligne, int colonne, std::vector<double>&& Container);
    Matrice(int ligne, int colonne, std::vector<double>& Container);

    ///@brief Initialise la matrice avec la valeur n
    Matrice& fill(double n);

    ///@brief Construction d'une matrice diagonale
    Matrice& diag(double n);
    Matrice& diag(std::vector<double> Container);

    ///@brief Trace de la matrice
    double trace();

    ///@brief Matrice élévé à la puissance n
    Matrice puissance(int n);

    ///@brief transposée de la matrice
    Matrice transpose();

    ///@brief Déterminant de la matrice
    double determinant();

    ///Commatrice de la matrice
    Matrice commatrice();

    ///@brief Inverse de la matrice
    Matrice inverse();

    ///@brief indexage de deux matrices
    double& operator()(int indexLine, int indexCol);

    ///@brief Produit de deux matrices
    Matrice operator*(Matrice& mat);
    Matrice operator*(Matrice&& mat);

    ///@brief Somme de deux matrices
    Matrice operator+(Matrice& mat);

private:
    int m_row, m_col;
    std::vector<std::vector<double>> m_matrice;

    void check_valide_size();
    double det(Matrice& mat) noexcept;

    ///@brief  Affichage d'une matrice à l'écran
    friend std::ostream& operator<<(std::ostream& flux, Matrice const& m);

    ///@brief Surchage de l'opérateur de multiplication d'un entier et d'une matrice
    friend Matrice operator*(Matrice& mat, double const t);

    friend Matrice operator*(Matrice&& mat, double const t);
};

//Surchage d'opérateur pour écrire une matrice sur le champ d'entrée
std::ostream& operator<<(std::ostream& flux, Matrice const& m);

//Surchage de l'opérateur de multiplication d'un entier et d'une matrice
//Argument par référence
Matrice operator*(Matrice& mat, double const t);

//Surchage de l'opérateur de multiplication d'un entier et d'une matrice
//Argument par valeur
Matrice operator*(Matrice&& mat, double const t);
#endif // MATRICE_H
