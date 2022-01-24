#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "graph.h"

using namespace std;






map<string, int> readStops() {
    //Read nodes from files and print them on the console to test

    map<string, int> stopsMap;

    string code, name, zone;
    string latitude, longitude;
    int count = 0;

    ifstream stops;
    stops.open("..\\.\\dataset\\stops.csv");
    stops.ignore(1000, '\n');

    while (getline(stops, code, ',')) {
        getline(stops, name, ',');
        getline(stops, zone, ',');
        getline(stops, latitude, ',');
        getline(stops, longitude, '\n');
        //cout << code << "  -  " << name << "  -  " << zone << "  -  " << latitude << "  -  " << longitude << endl;
        stopsMap.insert(pair<string, int>(code, count));
        count++;
    }

    cout << count;

    return stopsMap;
}


vector<pair<string, string>> readLinesInfo() {
    //Read lines info files, print them on the console to test and add to a vector of pairs(code, name)

    pair<string, string> line;

    vector<pair<string, string>> linesInfo;  //lines info

    string code, name;

    int count = 1;  //initialize node counter to 1

    ifstream lines;
    lines.open("..\\.\\dataset\\lines.csv");
    lines.ignore(1000, '\n');

    while (getline(lines, code, ',')) {
        getline(lines, name, '\n');
        linesInfo.push_back({code,name});
        //cout << code << "  ///  " << name << endl;
        count++;
    }

    cout << count;

    return linesInfo;
}


vector<string> readLine(string filename) {
    //Reads and puts in a vector all stops of a line in a certain direction
    vector<string> stops;

    ifstream linestops;
    linestops.open(filename);
    linestops.ignore(1000, '\n');

    string stop;

    while (getline(linestops, stop, '\n' )) {
        stops.push_back(stop);
    }

    return stops;
}

vector<pair<vector<string>, vector<string>>> readLines(vector<pair<string, string>> linesInfo) {
    //Reads both directions or each line and puts it in a vector of pairs of vectors(normal direction, reverse direction)

    vector<pair<vector<string>, vector<string>>> linestops;

    for (auto it = linesInfo.begin(); it != linesInfo.end(); it++) {
        string code = (*it).first;
        string file0 = "..\\.\\dataset\\line_" + code + "_0.csv";  //normal direction
        string file1 = "..\\.\\dataset\\line_" + code + "_1.csv";  //reverse direction
        vector<string> stops0 = readLine(file0);
        vector<string> stops1 = readLine(file1);

        pair<vector<string>, vector<string>> line = {stops0, stops1};
        linestops.push_back(line);
    }

    return linestops;
}


Graph toGraph(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops) {
    Graph g(2487, true);

    for (auto it = linesStops.begin(); it != linesStops.end(); it++) {

        pair<vector<string>, vector<string>> currentline = (*it);

        vector<string> norm = currentline.first;
        vector<string> rev = currentline.second;

        //parse the normal direction
        cout << "Parsing normal direction" << endl << endl;

        for ( auto et = norm.begin(); et != norm.end(); et++) {
            int origin = stops[*et];
            int dest = stops[*(et+1)];

            cout << " " << origin << " " << dest << endl;

            //add node to graph
            g.addEdge(origin,dest);
        }

        cout << endl << endl;


        //parse the reverse direction
        cout << "Parsing reverse direction" << endl << endl;

        for ( auto jt = rev.begin(); jt != rev.end(); jt++) {
            int origin = stops[*jt];
            int dest = stops[*(jt+1)];

            //cout << " " << origin << " " << dest << endl;

            //add node to graph
            g.addEdge(origin,dest);
        }

    }

   return g;
}


int main() {

    map<string, int> stops = readStops();

    vector<pair<string, string>> linesInfo = readLinesInfo();

    vector<pair<vector<string>, vector<string>>> linesStops = readLines(linesInfo);

    Graph graph = toGraph(linesStops, stops);







    return 0;
}
