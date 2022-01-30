//
// Created by Afonso Martins on 29/01/2022.
//

#ifndef PROJETOAED_STCP_H
#define PROJETOAED_STCP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "graph.h"

using namespace std;

/**
     * Classe que representa a rede de transportes da STCP, guardando internamente na aplicação todos os dados necessários ao seu funcionamento, bem como o seu ponto fundamental, o grafo.
     */
class STCP {

    map<string, int> stopsMap;
    vector<tuple<string,string,string,double,double>> stopsInfo;
    vector<pair<string, bool>> linesInfo;
    vector<pair<vector<string>, vector<string>>> linesStops;
    Graph graph = Graph(2487,true);

public:

    STCP(bool andar, bool isNight);

    STCP();
    /**
     * Mapeia o código de cada paragem para um inteiro, lendo do dataset
     * @return O map que faz corresponder as paragens a inteiros
     */
    map<string, int> mapStops();
    /**
     * Lê do dataset para um vetor tuplos com toda a informação sobre uma paragem: nome, código, zona ,latitude e longitude.
     * @return O vetor com todas as informações sobre cada paragem
     */
    vector<tuple<string,string,string,double,double>> readStopsInfo();
    /**
     * Lê do dataset para um vetor de pares <string, string> a informação de cada linha, sendo a primeira string o código e a segunda o nome da linha.
     * @return O vetor com todas as informações sobre cada linha
     */
    vector<pair<string, bool>> readLinesInfo();
    /**
     * Lê para um vetor de strings as paragens de uma linha
     * @param filename O nome do ficheiro a usar para ler do dataset
     * @return O vetor com todas as informações sobre as paragens de cada linha
     */
    vector<string> readLine(string filename);
    /**
     * Lê para um vetor de pares de vetores de strings, representando cada par uma linha e cada vetor dentro desse par a sua direção normal e inversa.
     * @param linesInfo O vetor que contém as informações sobre todas as linhas.
     * @return Todas as paragens em cada linha e em cada sentido.
     */
    vector<pair<vector<string>, vector<string>>> readLines(vector<pair<string, bool>> linesInfo);
    /**
     * Constrói o grafo com base nas estruturas de dados que contêm as informações lidas do dataset
     * @param linesStops O vetor que contém a informação sobre as paragens em cada linha
     * @param stops O map que faz corresponder as paragens a inteiros para usar como nós do grafo
     * @param stopsInfo O vetor de tuplos que contém as informações sobre as paragens
     * @param linesInfo O vetor de tuplos que contém as informações sobre as linhas
     * @return O grafo sobre o qual vão ser aplicados os algoritmos para a dterminação dos caminhos
     */
    Graph toGraphDay(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string,string,string,double,double>> stopsInfo, vector<pair<string, bool>> linesInfo);

    Graph toGraphNight(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string,string,string,double,double>> stopsInfo, vector<pair<string, bool>> linesInfo);

    /**
     * Adiciona arestas entre todos os nós (paragens) que estejam a menos de 200 metros entre si, representando que o utilizador se pode deslocar a peé entre elas.
     * @param g O grafo ao qual se vão adicionar as novas arestas
     * @param stopsInfo O vetor de tuplos que contém as informações sobre as paragens
     * @return O grafo atualizado com as novas arestas
     */
    Graph addWalkEdges(Graph g, vector<tuple<string,string,string,double,double>> stopsInfo);
    /**
     * @param code O código da paragem
     * @return O inteiro correspondente no mapping das paragens
     */
    int getNodeNumber(string code);
    /**
     * @param origin O código da paragem de origem
     * @param dest O código da paragem de destino
     * @return Lista com os nomes das paragens correspondentes ao menor caminho em termos de número de nós percorridos.
     */
    list<string> doBFS(string origin, string dest, list<string>& linhas);
    /**
     * @param origin O código da paragem de origem
     * @param dest O código da paragem de destino
     * @param lines Parâmetro para alterar, uma lista que após a execução da função estará preenchida com os códigos das linhas usadas para viajar entre paragens.
     * @return Lista com os nomes das paragens correspondentes ao menor caminho em termos de distÂncia percorrida.
     */
    list<string> doDijkstra(string origin, string dest, list<string>& lines);
    /**
     * @param lat A latitude do utilizador
     * @param lon A longitude do utilizador
     * @return Lista com as paragens num raio de 100 metros do utilizador.
     */
    list<pair<string,string>> nearbyStops(double lat, double lon);

    /**
    * @return O map criado com as stops
    */
    const map<string, int> &getStopsMap() const;
};


#endif //PROJETOAED_STCP_H
