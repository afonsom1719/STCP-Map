//
// Created by kwanzz on 28/01/2022.
//

#ifndef PROJETOAED_MAINMENU_H
#define PROJETOAED_MAINMENU_H

#include<iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include "list"
#include "graph.h"
#include "TextTable.h"
#include <algorithm>
#include "STCP.h"

/**
     * Classe que representa o menu da aplicação.
     */

class MainMenu {

    STCP stcp;

public:

    /**
     * Função que inicia a aplicação, lendo os dados e organizando a informação, e dá display ao menu inicial.
     */
    void menu();
/**
     * Função que pergunta ao utilizador qual o tipo de caminho que pretende que a aplicação determine.
     * @param paragens O par que contém os códigos das paragens inicial e final definidas pelo utilizador,
     */
    void pathPreference(pair<string,string> paragens);
    /**
     * Função que pergunta ao utilizador os códigos das paragens de início e de fim e as retorna num par de strings.
     * @return O par com os códigos das paragens introduzidas.
     */
    pair<string, string> enterParagens();
    /**
     * Função que pergunta ao utilizador a sua localização em coordenadas(latitude e longitude) e as retorna num par de doubles.
     * @return O par com as coordenadas introduzidas.
     */
    pair<double,double> enterBeginningCoordinates();

    /**
     * Função que determina e dá display às paragens num raio de 100 metros desde as coordenadas introduzidas pelo utilizador..
     * @param initialCoords O par de doubles que indica a latitude e a longitude do utilizador.
     */
    pair<string,string> mostrarNearbyParagens(pair<double,double> initialCoords);

    /**
     * Função que determina e dá display ao caminho mais curto em termos de distância geográfica entre as paragens selecionadas pelo utilizador.
     * @param jef O par de strings que indica os códigos das paragens de início e de fim.
     */
    void menorDistancia(pair<string,string> jef);
    /**
     * Função que determina e dá display ao caminho mais curto em termos de número de paragens entre as paragens selecionadas pelo utilizador.
     * @param jef O par de strings que indica os códigos das paragens de início e de fim.
     */
    void menosParagens(pair<string,string> jef);


};


#endif //PROJETOAED_MAINMENU_H
