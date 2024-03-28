// Nom du fichier : dequeImpl.h
// Description : Implémentation d'une deque circulaire
//
//
// =============================================
//
// Nom de l'étudiante : Béatrice Gagnon
// Nom de l'étudiante : Sahar Saoudi
//
// =============================================

#ifndef _dequeImpl_h
#define _dequeImpl_h

template <typename T>
deque<T>::deque(const deque& source)
{
    m_size = source.m_size;
    m_cap = source.m_cap;
    m_zero = source.m_zero;

    if (m_size > 0) {
        m_debut = new T * [m_cap];
        m_debut[(m_zero + m_cap - 1) % m_cap] = nullptr;

        for (size_t i = 0; i < m_size; ++i)
        {
            m_debut[(m_zero + i) % m_cap] = new T(source[i]);
        }
    }
    else { m_debut = nullptr; }
}


// Méthode pour redimensionner la deque
template <typename T>
void deque<T>::resize(size_t nSize)
{
    if (nSize < m_size) {
        for (size_t i = nSize; i < m_size; ++i) {
            delete m_debut[(m_zero + i) % m_cap];
            m_debut[(m_zero + i) % m_cap] = nullptr;
        }
    }
    else if (nSize > m_size) {
        reserve(nSize * 2 +1);

        for (size_t i = m_size; i < nSize; ++i) {
            m_debut[(m_zero + i) % m_cap] = new T();
        }
    }
    m_size = nSize;
}


// Méthode pour réserver de la mémoire pour la deque
template <typename T>
void deque<T>::reserve(size_t nCap)
{
    if (m_cap < nCap) {
        T** copie = new T * [nCap];

        for (size_t i = 0; i < m_size; ++i) {
            copie[i] = m_debut[(m_zero + i) % m_cap];
        }

        // Set remaining elements to nullptr
        for (size_t i = m_size; i < nCap; ++i) {
            copie[i] = nullptr;
        }

        delete[] m_debut;
        m_zero = 0;
        m_cap = nCap;
        m_debut = copie;
    }
}

// Opérateur [] pour accéder aux éléments de la deque
template <typename T>
T& deque<T>::operator[](size_t i)
{
    return **(m_debut + (i + m_zero) % m_cap);
}

// Méthode at() pour accéder aux éléments de la deque avec vérification des limites
template <typename T>
T& deque<T>::at(size_t i) {
    if (i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return **(m_debut + (i + m_zero) % m_cap);
}

// Surcharge de l'opérateur [] version constante
template <typename T>
const T& deque<T>::operator[](size_t i)const
{
    return **(m_debut + (i + m_zero) % m_cap);
}

// Méthode constante at() avec vérification des limites
template <typename T>
const T& deque<T>::at(size_t i) const {
    if (i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return **(m_debut + (i + m_zero) % m_cap);
}

// Méthode pour ajouter un élément à la fin de la deque
template <typename T>
void deque<T>::push_back(const T& val) {
    if (m_cap <= m_size) {
        reserve(m_cap * 2 + 1);
    }

    m_debut[(m_size + m_zero) % m_cap] = new T(val);
    m_size++;
}

// Méthode pour supprimer l'élément à la fin de la deque
template <typename T>
void deque<T>::pop_back()
{
    if (!empty())
    {
        size_t fin = (m_zero + m_size - 1) % m_cap;

        delete m_debut[fin];
        m_debut[fin] = nullptr;

        --m_size;
    }
}

// Méthode pour ajouter un élément au début de la deque
template <typename T>
void deque<T>::push_front(const T& val)
{
    if (m_cap <= m_size + 1)
    {
        reserve(m_cap * 2 + 1);
    }

    m_zero = (m_zero - 1 + m_cap) % m_cap;

    m_debut[m_zero] = new T(val);

    ++m_size;
}

// Méthode pour supprimer l'élément au début de la deque
template <typename T>
void deque<T>::pop_front()
{
    if (!empty())
    {
        delete m_debut[m_zero];
        m_debut[m_zero] = nullptr;

        m_zero = (m_zero + 1) % m_cap;

        --m_size;
    }
}

#endif // dequeImpl_h
