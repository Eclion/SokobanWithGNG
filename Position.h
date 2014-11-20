#ifndef Position_H
#define Position_H


#include <iostream>


using namespace std;

class Position
{
    public:

    Position();

    Position(int x,int y);

    virtual ~Position();

    ///\fn int GetX()
    ///\brief Get the X value
    ///
    ///Get the Position X parameter
    ///
    ///\return X value
    int GetX() { return m_X; }

    ///\fn void SetX(int val)
    ///\brief Set the X value
    ///
    ///Set  the Position X parameter
    ///
    ///\param val : next value of X
    void SetX(int val) { m_X = val; }

    ///\fn int GetY()
    ///\brief Get the Y value
    ///
    ///Get the Position Y parameter
    ///
    ///\return Y value
    int GetY() { return m_Y; }

    ///\fn void SetY(int val)
    ///\brief Set the Y value
    ///
    ///Set  the Position Y parameter
    ///
    ///\param val : next value of Y
    void SetY(int val) { m_Y = val; }

    Position operator^(Position b);
    virtual void print(std::ostream& os);

    friend std::ostream& operator<<(std::ostream& os, Position& obj);

    protected:

    int m_X;/// Position X parameter
    int m_Y;/// Position Y parameter
};

#endif // VECT_H
