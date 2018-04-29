#ifndef PONTO_H
#define PONTO_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Ponto
{
    public:
        Ponto();
        virtual ~Ponto();
        Ponto(float x, float y, float z);
        void rotaciona(float angle);
        int id;
        float coor[3];

    protected:

    private:
};

#endif // PONTO_H
