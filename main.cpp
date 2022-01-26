#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "graph.h"


using namespace std;

static double haversine(double lat1, double lon1,
                        double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}




map<string, int> mapStops() {
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
        //
        // cout << code << "  -  " << name << "  -  " << zone << "  -  " << latitude << "  -  " << longitude << endl;
        stopsMap.insert(pair<string, int>(code, count));
        count++;
    }

    cout << count;

    return stopsMap;
}

vector<tuple<string,string,string,double,double>> readStopsInfo() {
    //Read nodes from files and print them on the console to test

    vector<tuple<string,string,string,double,double>> stopsInfo;

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
        double lat = stof(latitude);
        double longi = stof(longitude);
        //
        // cout << code << "  -  " << name << "  -  " << zone << "  -  " << latitude << "  -  " << longitude << endl;
        tuple<string,string,string,double,double> stopInfo;
        stopInfo = make_tuple(code, name, zone, lat, longi);

        stopsInfo.push_back(stopInfo);
        count++;
    }

    cout << count;

    return stopsInfo;
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


Graph toGraph(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string,string,string,double,double>> stopsInfo) {
    Graph g(2487, true);

    for (auto it = linesStops.begin(); it != linesStops.end(); it++) {

        pair<vector<string>, vector<string>> currentline = (*it);

        vector<string> norm = currentline.first;
        vector<string> rev = currentline.second;

        //parse the normal direction
        //cout << "Parsing normal direction" << endl << endl;

        for ( auto et = norm.begin(); et != norm.end(); et++) {
            int origin = stops[*et];
            if((et+1)!=norm.end()) {
                int dest = stops[*(et+1)];
                tuple<string,string,string,double,double> info1 = stopsInfo[stops[*et]];
                tuple<string,string,string,double,double> info2 = stopsInfo[stops[*(et+1)]];
                double lat1 = get<3>(info1);
                double lon1 = get<4>(info1);
                double dist = haversine(get<3>(info1), get<4>(info1), get<3>(info2), get<4>(info2));
                //cout << " " << origin << " " << dest << endl;
                //add node to graph
                g.addEdge(origin,dest);
            }
            else {
                break;
            }



        }

        cout << endl;

        //parse the reverse direction
        //cout << "Parsing reverse direction" << endl << endl;

        for ( auto jt = rev.begin(); jt != rev.end(); jt++) {
            int origin = stops[*jt];
            if((jt+1)!=rev.end()) {
                int dest = stops[*(jt+1)];
                //cout << " " << origin << " " << dest << endl;

                //add node to graph
                g.addEdge(origin,dest);
            }
            else {
                break;
            }
        }


    }

   return g;
}








int main() {

    map<string, int> stops = mapStops();

    vector<tuple<string,string,string,double,double>> stopsInfo = readStopsInfo();

    vector<pair<string, string>> linesInfo = readLinesInfo();

    vector<pair<vector<string>, vector<string>>> linesStops = readLines(linesInfo);

    Graph graph = toGraph(linesStops, stops, stopsInfo);









    //Testing

    list<int> test1 = graph.dijkstra_path(1175,1595);  //linha 1 na direção normal

    list<int> test2 = graph.dijkstra_path(1566,1580);  //OLVR1 - PAL2

    cout << endl;
    for (auto i:test1) {
        cout << "----->" << get<1>(stopsInfo[i]) ;
    }

    double haversinetest = haversine(41.14066938,-8.615876577,41.14383841,-8.621984753);

    cout << haversinetest;







    return 0;
}
