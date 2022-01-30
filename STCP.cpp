//
// Created by Afonso Martins on 29/01/2022.
//

#include "STCP.h"




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


STCP::STCP(bool andar, bool isNight) {
    this->stopsMap = mapStops();
    this->stopsInfo = readStopsInfo();
    this->linesInfo = readLinesInfo();
    this->linesStops = readLines(linesInfo);
    if(!isNight) {
        Graph g = toGraphDay(linesStops, stopsMap, stopsInfo, linesInfo);
        this->graph = g;
    }else {
        Graph g = toGraphNight(linesStops, stopsMap, stopsInfo, linesInfo);
        this->graph = g;
    }

    if(andar){
        graph = addWalkEdges(graph, stopsInfo);
    }

}


map<string, int> STCP::mapStops() {
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
        // cout << code << "  -  " << name << "  -  " << zone << "  -  " << latitude << "  -  " << longitude << endl;
        stopsMap.insert(pair<string, int>(code, count));
        count++;
    }

    //cout << count;

    return stopsMap;
}

vector<tuple<string,string,string,double,double>> STCP::readStopsInfo() {
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
        // cout << code << "  -  " << name << "  -  " << zone << "  -  " << latitude << "  -  " << longitude << endl;
        tuple<string,string,string,double,double> stopInfo;
        stopInfo = make_tuple(code, name, zone, lat, longi);

        stopsInfo.push_back(stopInfo);
        count++;
    }

    //cout << count;

    return stopsInfo;
}


vector<pair<string, bool>> STCP::readLinesInfo() {
    //Read lines info files, print them on the console to test and add to a vector of pairs(code, name)

    pair<string, bool> line;

    vector<pair<string, bool>> linesInfo;  //lines info

    string code, name;
    bool isNight;

    int count = 1;  //initialize node counter to 1

    ifstream lines;
    lines.open("..\\.\\dataset\\lines.csv");
    lines.ignore(1000, '\n');

    while (getline(lines, code, ',')) {
        getline(lines,name, '\n');
        if(code.find('M') != std::string::npos){
            isNight = true;
        }else{
            isNight = false;
        }
        linesInfo.push_back({code,isNight});
        //cout << code << "  ///  " << name << endl;
        count++;
    }

    //cout << count;

    return linesInfo;
}


vector<string> STCP::readLine(string filename) {
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

vector<pair<vector<string>, vector<string>>> STCP::readLines(vector<pair<string, bool>> linesInfo) {
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


Graph STCP::toGraphDay(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string,string,string,double,double>> stopsInfo, vector<pair<string, bool>> linesInfo) {
    Graph gDay(2487, true);
    int counter = 0;

    for (auto it = linesStops.begin(); it != linesStops.end(); it++) {

        pair<vector<string>, vector<string>> currentLine = (*it);

        vector<string> norm = currentLine.first;
        vector<string> rev = currentLine.second;

        //parse the normal direction
        //cout << "Parsing normal direction" << endl << endl;

        for ( auto et = norm.begin(); et != norm.end(); et++) {
            int origin = stops[*et];
            if((et+1)!=norm.end()) {
                int dest = stops[*(et+1)];
                tuple<string,string,string,double,double> info1 = stopsInfo[stops[*et]];
                tuple<string,string,string,double,double> info2 = stopsInfo[stops[*(et+1)]];
                double dist = haversine(get<3>(info1), get<4>(info1), get<3>(info2), get<4>(info2));
                //cout << " " << origin << " " << dest << endl;
                //add node to graph
                if(!linesInfo[counter].second){
                    gDay.addEdge(origin, dest, dist, linesInfo[counter].first);
                }


            }
            else {
                break;
            }
        }

        //cout << endl;

        //parse the reverse direction
        //cout << "Parsing reverse direction" << endl << endl;

        for (auto jt = rev.begin(); jt != rev.end(); jt++) {
            int origin = stops[*jt];
            if((jt+1)!=rev.end()) {
                int dest = stops[*(jt+1)];
                tuple<string,string,string,double,double> info1 = stopsInfo[stops[*jt]];
                tuple<string,string,string,double,double> info2 = stopsInfo[stops[*(jt+1)]];
                double lat1 = get<3>(info1);
                double lon1 = get<4>(info1);
                double dist = haversine(get<3>(info1), get<4>(info1), get<3>(info2), get<4>(info2));
                //cout << " " << origin << " " << dest << endl;
                //add node to graph
                if(!linesInfo[counter].second) {
                    gDay.addEdge(origin, dest, dist, linesInfo[counter].first);
                }
            }
            else {
                break;
            }
        }
        counter++;
    }

    return gDay;
}

Graph STCP::addWalkEdges(Graph g, vector<tuple<string,string,string,double,double>> stopsInfo) {
    Graph update = g;
    int s = g.getNodes().size()-1;
    for (int i = 0; i < s; i++) {
        for (int j = i+1; j < s; j++) {
            tuple<string,string,string,double,double> stop1 = stopsInfo[i];
            tuple<string,string,string,double,double> stop2 = stopsInfo[j];
            double dist = haversine(get<3>(stop1), get<4>(stop1), get<3>(stop2), get<4>(stop2));
            if (dist < 0.2) {
                update.addEdge(i,j, dist,"Caminhar");
                update.addEdge(j,i, dist,"Caminhar");
            }
        }
    }
    return update;
}

int STCP::getNodeNumber(string code) {
    return stopsMap[code];
}

list<string> STCP::doBFS(string origin, string dest, list<string>& linhas) {
    int o = getNodeNumber(origin);
    int d = getNodeNumber(dest);

    list<int> nodePath = graph.BFS_path(o,d, linhas);

    list<string> namePath;

    for (auto it = nodePath.begin(); it != nodePath.end(); it++) {
        namePath.push_back(get<1>(stopsInfo[*it]));
    }

    return namePath;
}

list<string> STCP::doDijkstra(string origin, string dest, list<string>& lines) {
    int o = getNodeNumber(origin);
    int d = getNodeNumber(dest);


    list<int> nodePath = graph.dijkstra_path(o,d, lines);

    list<string> namePath;

    for (auto it = nodePath.begin(); it != nodePath.end(); it++) {
        namePath.push_back(get<1>(stopsInfo[*it]));
    }

    return namePath;
}

const map<string, int> &STCP::getStopsMap() const {
    return stopsMap;
}

list<pair<string,string>> STCP::nearbyStops(double lat, double lon) {

    list<pair<string,string>> nearby;


    int s = graph.getNodes().size()-1;
    for (int i = 0; i < s; i++) {

            tuple<string,string,string,double,double> stop = stopsInfo[i];

            double dist = haversine(lat, lon, get<3>(stop), get<4>(stop));
            if (dist < 0.1) {
                nearby.push_back(make_pair(get<0>(stop), get<1>(stop)));
            }

    }
    return nearby;
}

STCP::STCP() {

}

Graph STCP::toGraphNight(vector<pair<vector<string>, vector<string>>> linesStops, map<string, int> stops, vector<tuple<string, string, string, double, double>> stopsInfo, vector<pair<string, bool>> linesInfo) {

        Graph gNight(2487, true);
        int counter = 0;

        for (auto it = linesStops.begin(); it != linesStops.end(); it++) {

            pair<vector<string>, vector<string>> currentLine = (*it);

            vector<string> norm = currentLine.first;
            vector<string> rev = currentLine.second;

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
                    if(linesInfo[counter].second) {
                        gNight.addEdge(origin, dest, dist, linesInfo[counter].first);
                    }

                }
                else {
                    break;
                }
            }

            //cout << endl;

            //parse the reverse direction
            //cout << "Parsing reverse direction" << endl << endl;

            for (auto jt = rev.begin(); jt != rev.end(); jt++) {
                int origin = stops[*jt];
                if((jt+1)!=rev.end()) {
                    int dest = stops[*(jt+1)];
                    tuple<string,string,string,double,double> info1 = stopsInfo[stops[*jt]];
                    tuple<string,string,string,double,double> info2 = stopsInfo[stops[*(jt+1)]];
                    double lat1 = get<3>(info1);
                    double lon1 = get<4>(info1);
                    double dist = haversine(get<3>(info1), get<4>(info1), get<3>(info2), get<4>(info2));
                    //cout << " " << origin << " " << dest << endl;
                    //add node to graph
                    if(linesInfo[counter].second) {
                        gNight.addEdge(origin, dest, dist, linesInfo[counter].first);
                    }
                }
                else {
                    break;
                }
            }
            counter++;
        }

        return gNight;
}
