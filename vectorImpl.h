//
//  Nom du fichier : vectorImpl.h
//
// =============================================
//
//  Nom de l'étudiant : Béatrice Gagnon
//  Nom de l'étudiant : Sahar Saoudi
//
// =============================================

#ifndef _vectorImpl_h
#define _vectorImpl_h


///////////////////////////////////////////////////
//clear (vide la memoire dynamique)

template <typename T>
void vector<T>::clear()
{
    delete[] m_debut;
    m_debut = m_finDim = m_finCap = nullptr;

}

///////////////////////////////////////////////////
//resize (modifie la dimension)

template <typename T>
void vector<T>::resize(size_t nDIM)
{
    if (nDIM > m_finCap-m_debut)
    {
        reserve(2 * (m_finCap - m_debut)+1);
    }
    else {
        m_finDim += nDIM - size();

    }

}


///////////////////////////////////////////////////
//reserve (modifie la capacite)

template <typename T>
void vector<T>::reserve(size_t nCAP)
{
    if (nCAP > m_finCap-m_debut)
    {
        vector<T> copie(nCAP);
        for (size_t i = 0;i < size();++i)
        {
            copie[i] = m_debut[i];
        }
        copie.m_finDim = copie.m_debut + size();
        clear();
        swap(copie);
    }
    else if (nCAP ==0)
    {
        clear();
    }
}

///////////////////////////////////////////////////
//fonctions d'acces a un element sauf front et back
//push_back
//pop_back
//operator[]
//operator[]const
//at
//at const

template <typename T>
void vector<T>::push_back(const T& x)
{
    if (m_finCap <= m_finDim)
    {
        resize(size() + 1);
    }
    *m_finDim++ = x;
}

template <typename T>
void vector<T>::pop_back()
{
    if (!empty())
    {
        *--m_finDim = T();
    }
}

template <typename T>
T& vector<T>::operator[](size_t i)
{
    return *(m_debut + i);

}

template <typename T>
const T& vector<T>::operator[](size_t i)const
{
    return *(m_debut + i);
}

template <typename T>
T& vector<T>::at(size_t i)
{
    if (i > m_finDim - m_debut)
    {
        throw std::out_of_range("out of range");
    }
    return *(m_debut + i);
}
template <typename T>
const T& vector<T>::at(size_t i)const
{
    if (i > m_finDim - m_debut)
    {
        throw std::out_of_range("out of range");
    }
    return *(m_debut + i);
}


#endif // vectorImpl_h
