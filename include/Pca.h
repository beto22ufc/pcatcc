#ifndef PCA_H
#define PCA_H
#include <vector>
#include <Ponto.h>
#define DIMEN 3


class Pca
{
    public:
        Pca();
        Pca(std::vector<Ponto>* pontos, Ponto* vetorMedia);
        calculaVetorMedio();
        calculaMatrizCovariancia();
        calculaAutoValor();
        Ponto pontoMedio;
        Ponto* vetorMediaAux;
        double matrizCovariacia[DIMEN][DIMEN];
        std::vector <Ponto>* vetorPontos;
        virtual ~Pca();



    protected:

    private:
};

#endif // PCA_H
