#include "Pca.h"
#include <vector>
#include <math.h>
#include <Ponto.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define DIMEN 3


Pca::Pca()
{
    //ctor
}
Pca::Pca(std::vector<Ponto>* pontos, Ponto* vetorMedia){
    this->vetorPontos = pontos;
    this->vetorMediaAux = vetorMedia;
    calculaVetorMedio();
    calculaMatrizCovariancia();
}

Pca::~Pca()
{

}

Pca::calculaVetorMedio() {
    float somatorioX = 0.0;
    float somatorioY = 0.0;
    float somatorioZ = 0.0;
    printf("somatorio x inicial: %f \n",somatorioX);
    for (unsigned int i = 1;i < vetorPontos->size();i++) {
        somatorioX = somatorioX + vetorPontos->at(i).coor[0];
        somatorioY = somatorioY + vetorPontos->at(i).coor[1];
        somatorioZ = somatorioZ + vetorPontos->at(i).coor[2];
    }
    printf("somatorio x, y, z \n");
    printf("[ %f,",somatorioX);
    printf("  %f,",somatorioY);
    printf("  %f ]",somatorioZ);
    printf("\n\n");

    pontoMedio.coor[0] = somatorioX/vetorPontos->size();
    pontoMedio.coor[1] = somatorioY/vetorPontos->size();
    pontoMedio.coor[2] = somatorioZ/vetorPontos->size();
    printf("pontoMedio \n");
    printf("[ %f,",pontoMedio.coor[0]);
    printf("  %f,",pontoMedio.coor[1]);
    printf("  %f ]",pontoMedio.coor[2]);
    //calculaMatrizCovariancia();
}

Pca::calculaMatrizCovariancia(){
    double auxiliar = 0.0;
    for (unsigned int i=0;i<DIMEN;i++) {
        for (unsigned int j=0;j<DIMEN;j++) {
            //printf("\nTAMANHO DO VECTOR:  %i \n",this->vetorPontos->size());
            //system("pause");
            auxiliar = 0.0;
            for (unsigned int k=0;k<this->vetorPontos->size();k++) {
                printf("\nvalor do vetor %i %f \n\n",k,this->vetorPontos->at(k).coor[i]);
                auxiliar = auxiliar + ((this->vetorPontos->at(k).coor[i] - this->pontoMedio.coor[i])*(this->vetorPontos->at(k).coor[j] - this->pontoMedio.coor[j]));
                //printf("valor%f \n",auxiliar);

            }

            this->matrizCovariacia[i][j] = auxiliar/(this->vetorPontos->size());


        }
    }
    printf("\nmatriz de covariancia\n[");
    for (unsigned int i=0;i<DIMEN;i++) {
        for (unsigned int j=0;j<DIMEN;j++) {
            printf("%f    ", this->matrizCovariacia[i][j]);
        }
        printf("\n");
    }
}
Pca::calculaAutoValor(){}
