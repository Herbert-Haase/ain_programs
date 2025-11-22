//
// htwg_vector.h
//
// Stark vereinfachte Vektor-Klasse.
//
// Autor: H.Drachenfels
// Erstellt am: 18.01.2013
//

#ifndef HTWG_VECTOR_H
#define HTWG_VECTOR_H

namespace htwg
{
    template<typename T> class  vector
    {
    private:
        int n;
        T *v;
        // Objektkopien verhindern:
        vector(const vector& v);
        vector& operator=(const vector& v);
    public:
        vector(int n)
        {
            // Verbesserungsvorschlag: n < 0 pruefen
            this->n = n;
            this->v = new T[n]; // Feldelemente uninitialisiert
        }

        ~vector()
        {
            delete[] this->v;
        }

        int size() const
        {
            return this->n;
        }

        T& operator[](int i)
        {
            // Verbesserungsvorschlag: Index pruefen
            return this->v[i];
        }
    };
}

#endif

