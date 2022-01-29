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

class STCP {

    map<string, int> stopsMap;
    vector<tuple<string,string,string,double,double>> stopsInfo;
    vector<pair<string, string>> linesInfo;
    vector<pair<vector<string>, vector<string>>> linesStops;
    Graph graph = Graph(2487,true);

public:

    STCP();
    map<string, int> mapStops();
    vector<tuple<string,string,string,double,double>> readStopsInfo();
    vector<pair<string, string>> readLinesInfo();
    vector<string> readLine(string filename);
    vector<pair<vector<string>, vector<string>>> readLines(vector<pair<string, string>> linesInfo);
    Graph toGraph(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string,string,string,double,double>> stopsInfo, vector<pair<string, string>> linesInfo);
    Graph addWalkEdges(Graph g, vector<tuple<string,string,string,double,double>> stopsInfo);

    const Graph &getGraph() const;

    int getNodeNumber(string code);
    list<string> doBFS(string origin, string dest);
    list<string> doDijkstra(string origin, string dest);

    const map<string, int> &getStopsMap() const;
};


#endif //PROJETOAED_STCP_H
