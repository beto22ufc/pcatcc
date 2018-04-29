#include "Ponto.h"
#include "math.h"
#include <stdio.h>
Ponto::Ponto()
{
    //ctor
}
Ponto::~Ponto()
{
    //dtor
}
Ponto::Ponto(float x, float y, float z) {
    coor[0] = x;
    coor[1] = y;
    coor[2] = z;

}
void Ponto::rotaciona(float angle){
    glRotatef(angle,0.0,1.0,0.0);
    //printf("antes de rotacionar: \n%f %f %f",coor[0],coor[1],coor[2]);
    //coor[0] = coor[0]*cos(angle) - sin(angle)*coor[2];
    //coor[2] = coor[0]*sin(angle) + cos(angle)*coor[2];
    //printf("depois de rotacionar: \n%f %f %f",coor[0],coor[1],coor[2]);
}

