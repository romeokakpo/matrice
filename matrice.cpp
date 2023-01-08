#include "matrice.h"

void Matrice::check_valide_size()
{
    (m_row > 0 && m_col > 0)?true:throw Matrice_Except
                              ("Les dimensions de la matrice doivent etre positif et non nuls.\n");
}

//Constructeurs
Matrice::Matrice(int dimension):
    m_row(dimension), m_col(dimension)
{
    check_valide_size();
    m_matrice.resize(m_row,std::vector<double>(m_col) );
}

Matrice::Matrice(int ligne, int colonne):
    m_row(ligne), m_col(colonne)
{
    check_valide_size();
    m_matrice.resize(m_row,std::vector<double>(m_col));
}

Matrice::Matrice(int ligne, int colonne, std::vector<double>& Container):
    m_row(ligne), m_col(colonne)
{
    check_valide_size();
    m_matrice.resize(m_row,std::vector<double>(m_col));
    Container.resize(m_row*m_col);
    for(int i{0}, k{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++,k++)
        {
            m_matrice[i][j] = Container[k];
        }
    }
}


Matrice::Matrice(int ligne, int colonne, std::vector<double>&& Container):
    m_row(ligne), m_col(colonne)
{
    check_valide_size();
    m_matrice.resize(m_row,std::vector<double>(m_col));
    Container.resize(m_row*m_col);
    for(int i{0}, k{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++,k++)
        {
            m_matrice[i][j] = Container[k];
        }
    }
}

//Remplir la matrice avec une valeur par défaut
Matrice& Matrice::fill(double n)
{
    (m_row && m_col)?true:throw Matrice_Except
                     ("Specifier les dimensions de la matrice avant de la remplir.\n");

    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++)
        {
            m_matrice[i][j] = n;
        }
    }
    return (*this);
}

//Construction d'une matrice diagonale
//Avec valeur
Matrice& Matrice::diag(double n)
{
    (m_row && m_col)?true:throw Matrice_Except
                     ("Specifier les dimensions de la matrice avant de la remplir.\n");
    (m_row == m_col)?true:throw Matrice_Except
                     ("La matrice n'est pas carree.\n");
    for(int i(0); i < m_row; i++)
        m_matrice[i][i] = n;
    return (*this);
}

//Avec Vector
Matrice& Matrice::diag(std::vector<double> Container)
{
    (m_row && m_col)?true:throw Matrice_Except
                     ("Specifier les dimensions de la matrice avant de la remplir.\n");
    (m_row == m_col)?true:throw Matrice_Except
                     ("La matrice n'est pas carree.\n");
    Container.resize(m_row);
    for(int i(0); i < m_row; i++)
        m_matrice[i][i] = Container[i];
    return (*this);
}

//Trace de la matrice
double Matrice::trace()
{
    (m_row == m_col)?true:throw  Matrice_Except
                     ("La matrice n'est pas carree.\n");
    double tr{};
    for(int i(0); i < m_row; i++)
        tr += (*this)(i,i);
    return tr;
}

//Matrice élévé à la puissance
Matrice Matrice::puissance(int n)
{
    (m_row == m_col)?true:throw  Matrice_Except
                     ("La matrice n'est pas carree.\n");
    //Matrice identité
    Matrice result = Matrice(m_row).diag(1);
    for(int i = 1; i <= n; i++)
    {
        result = result * (*this);
    }
    return (n==1)?(*this):result;
}

//Surcharge de l'addition
Matrice Matrice::operator+(Matrice& mat)
{
    bool b{m_row == mat.m_row && m_col == mat.m_col};
    b?true:throw Matrice_Except("La somme n'est pas possible, les matrices sont de tailles differentes.\n");
    Matrice result(mat.m_row, mat.m_col);
    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++)
        {
            result(i, j) = m_matrice[i][j] + mat(i ,j);
        }
    }
    return result;
}

//Produit de matrice argument par référence
Matrice Matrice::operator*(Matrice& mat)
{
    (m_col == mat.m_row)?true:
                         throw Matrice_Except
                         ("Le produit est impossible,les dimensions des matrices sont invalides.\n");
    Matrice result(m_row, mat.m_col);
    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < mat.m_col; j++)
        {
            for(int k{0}; k < m_col; k++)
            {
                result(i, j) = result(i, j) + m_matrice[i][k]* mat(k, j);
            }

        }
    }
    return result;
}

//Produit de matrice argument par valeur
Matrice Matrice::operator*(Matrice&& mat)
{
    (m_col == mat.m_row)?true:
                         throw Matrice_Except
                         ("Le produit est impossible,les dimensions des matrices sont invalides.\n");
    Matrice result(m_row, mat.m_col);
    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < mat.m_col; j++)
        {
            for(int k{0}; k < m_col; k++)
            {
                result(i, j) = result(i, j) + m_matrice[i][k]* mat(k, j);
            }

        }
    }
    return result;
}

//Transposée d'une matrice
Matrice Matrice::transpose()
{
    Matrice result(m_col, m_row);
    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++)
        {
            result(j, i) = m_matrice[i][j];
        }
    }
    return result;
}

//Déterminant de la matrice
double Matrice::determinant()
{
    (m_row == m_col)?true:throw  Matrice_Except
                     ("Determinant impossible, la matrice n'est pas carree.\n");

    return (m_col && m_row)?det(*this):throw  Matrice_Except
                            ("Determinant impossible, la matrice est vide.\n");;
}

//Calcul le déterminant de la matrice qu'on lui envoie(ordre >=2)
double Matrice::det(Matrice& mat) noexcept
{
    if(mat.m_row*mat.m_col == 1)
        return mat(0,0);
    std::vector<double> Container;
    double determinant{0};
    for(int j{0}; j < mat.m_col; j++)
    {
        if(!mat(0,j)) continue;//Permet de sauter l'étape quand on rencontre zéro
        for(int i{0}; i < mat.m_row; i++)
        {
            for(int k{0}; k < mat.m_col; k++)
            {
                if(i != 0 && k != j)
                    Container.push_back(mat(i,k));
            }
        }
        Matrice sub_mat(mat.m_row-1, mat.m_col-1,Container);
        Container.resize(0);
        determinant += ((!(j%2)?1:-1)*mat(0, j)*det(sub_mat));
    }
    return determinant;
}

//Détermination de la commatrice
Matrice Matrice::commatrice()
{
    (m_row == m_col)?true:throw  Matrice_Except
                     ("Commatrice impossible, la matrice n'est pas carree.\n");
    Matrice result(m_row,m_col);
    std::vector<double> Container;
    for(int i{0}; i < m_row; i++)
    {
        for(int j{0}; j < m_col; j++)
        {
            for(int k{0}; k < m_row; k++)
            {
                for(int l{0}; l < m_col; l++)
                {
                    if(i != k && l != j)
                        Container.push_back((*this)(k,l));
                }
            }
            Matrice sub_mat(m_row-1, m_col-1,Container);
            Container.resize(0);
            result(i,j) = (!((i+j)%2)?1:-1)*det(sub_mat);
        }
    }
    return result;
}

//Inverse de la matrice
Matrice Matrice::inverse()
{
    Matrice result(m_row,m_col);
    double det = determinant();
    det?true:throw Matrice_Except
        ("La matrice est inversible, le determinant est nul.\n");
    result = commatrice().transpose()*(1./det);
    return result;
}

//Impression de la matrice à l'écran
std::ostream& operator<<(std::ostream& flux, Matrice const& m)
{
    for(auto& line:m.m_matrice)
    {
        for(auto& col:line)
        {
            flux<<col<<" ";
        }
        flux<<"\n";
    }
    return flux;
}

//Surcharge de l'opérateur de multiplication par un entier
Matrice operator*(Matrice& mat, double const t)
{
    Matrice result(mat.m_row, mat.m_col);
    for(int i{0}; i < mat.m_row; i++)
    {
        for(int j{0}; j < mat.m_col; j++)
        {
            result(i, j) = mat(i, j) *t;
        }
    }
    return result;
}

Matrice operator*(Matrice&& mat, double const t)
{
    Matrice result(mat.m_row, mat.m_col);
    for(int i{0}; i < mat.m_row; i++)
    {
        for(int j{0}; j < mat.m_col; j++)
        {
            result(i, j) = mat(i, j) *t;
        }
    }
    return result;
}

//Cet opérateur nous permet d'accéder aux différentes cases de la matrice.
double& Matrice::operator()(int indexLine, int indexCol)
{
    (indexLine < m_row && indexCol < m_col)?
                true:throw Matrice_Except
                ("Indice de la matrice incorrect, on ne peut pas acceder a cet emplacement.\n");
    return m_matrice[indexLine][indexCol];
}
