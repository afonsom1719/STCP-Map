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


class MainMenu {

    STCP stcp;

public:

    void menu();

    void pathPreference(pair<string,string> paragens);

    pair<string, string> enterParagens();

    pair<double,double> enterBeginningCoordinates();

    pair<string,string> mostrarNearbyParagens(pair<double,double> initialCoords);

    void menorDistancia(pair<string,string> jef);

    void menosParagens(pair<string,string> jef);


};


#endif //PROJETOAED_MAINMENU_H
