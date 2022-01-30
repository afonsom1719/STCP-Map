//
// Created by kwanzz on 28/01/2022.
//

#include "MainMenu.h"

void MainMenu::menu() {

    //initialize stcp

    bool exiT = true;
    bool andar = false;
    char c;
    char b;
    pair<double,double> initialCoords;
    pair<string,string> paragens;


    system("CLS");
    std::cout << "[STCP]\n";
    std::cout << "Escolha uma opcao para determinar os locais de partida e chegada" << endl;
    std::cout << "\n[1] Coordenadas - inserir as suas coordenadas e ver paragens por perto"
              << "\n[2] Codigo das paragens - inserir diretamente os codigos das paragens"
              << "\n[0] Sair\n"
              << "\n>";
    std::cin.clear();
    //cin.ignore(INT_MAX, '\n');
    while(exiT){
        std::cin >> c;
        cin.clear();
        switch(c){
            //coordenadas
            case '1':
                system("CLS");
                std::cout << "[STCP]\n";
                std::cout << "Pretende andar a pe durante a sua viagem ou manter o percurso exclusivo de autocarro?" << endl;
                std::cout << "\n[1] Andar a pe"
                          << "\n[2] Exclusivo de autocarro"
                          << "\n>";
                std::cin.clear();

                std::cin >> b;
                cin.clear();
                system("CLS");
                std::cout << "Loading\n";
                if(b == '1'){ andar = true;}
                this->stcp = STCP(andar);
                initialCoords = enterBeginningCoordinates();
                paragens = mostrarNearbyParagens(initialCoords);
                exiT = false;
                break;
            case '2':
                system("CLS");
                std::cout << "[STCP]\n";
                std::cout << "Pretende andar a pe durante a sua viagem ou manter o percurso exclusivo de autocarro?" << endl;
                std::cout << "\n[1] Andar a pe"
                          << "\n[2] Exclusivo de autocarro"
                          << "\n>";
                std::cin.clear();
                std::cin >> b;
                cin.clear();
                system("CLS");
                std::cout << "Loading\n";
                if(b == '1'){ andar = true;}
                this->stcp = STCP(andar);
                paragens = enterParagens();
                exiT = false;
                break;
            case '0':
                exit(1);
                system("exit");
                return;
            default:
                std::cout << "Tente outra vez\n";
                exiT = true;
        }
    }
    pathPreference(paragens);
}

void MainMenu::pathPreference(pair<string,string> paragens){
        char c;
        system("CLS");
        std::cout << "Selecione a aua preferencia de caminho\n";
        std::cout << "\n[1] Caminho com menor distancia"
                  << "\n[2] Caminho com menos paragens"
                  << "\n[0] Voltar ao Menu\n"
                  << "\n>";

        std::cin.clear();
        //cin.ignore(INT_MAX, '\n');
        std::cin >> c;
        cin.clear();
        bool crl = true;
        while(crl) {
            switch (c) {
                //first cases to ask for
                case '1':
                    menorDistancia(paragens);
                    break;
                case '2':
                    menosParagens(paragens);
                    break;
                case '3':
                    //func futura??
                    break;
                case '0':
                    menu();
                    break;
                default:
                    std::cout << "Opcao invalida\n";
                    crl = false;

            }
        }
}



pair<string,string> MainMenu::enterParagens() {
    string paragem_I;
    string paragem_F;
    pair<string,string> paragens;

    while(true){
            system("CLS");
            std::cout << "Codigo da paragem de partida:" << endl;
            std::cout << "\n"
                      << "\n>";
            cin.clear();
            for(int i = 0;i < 2;i++) {
                if(i == 0){
                    cin.clear();
                    std::cin >> paragem_I;
                    auto stop_node = stcp.getStopsMap().find(paragem_I);
                    if (stop_node != stcp.getStopsMap().end()) {
                        paragens.first = (stop_node->first);
                    } else{
                        system("CLS");
                        std::cout << "Codigo da paragem de partida:" << endl;
                        i = -1;
                        continue;
                    }

                }
                if(i == 1){
                    system("CLS");
                    std::cout << "Codigo da paragem de chegada:" << endl;
                    std::cout << "\n"
                              << "\n>";
                    cin.clear();
                    std::cin >> paragem_F;
                    auto stop_node = stcp.getStopsMap().find(paragem_F);
                    if (stop_node != stcp.getStopsMap().end()) {
                        paragens.second = (stop_node->first);
                    }
                    else{
                        i = 0;
                        continue;
                    }
                }
            }
            break;
    }
    std::cout << paragens.first << "  "<< paragens.second <<endl;
    return paragens;
}


pair<double, double> MainMenu::enterBeginningCoordinates() {
    pair<double, double> coords;
    double lat;
    double lon;
    bool exit = true;
    while (exit){
        cin.clear();
        system("CLS");
        std::cout << "Insira a sua latitude:" << endl;
        std::cout << "\n"
                  << "\n>";
        cin.clear();
        std::cin >> lat;

        cin.clear();
        system("CLS");
        std::cout << "Insira a sua longitude:" << endl;
        std::cin >> lon;

        exit = false;
    }
    coords.first = lat; coords.second = lon;
    return coords;
}

pair<string, string> MainMenu::mostrarNearbyParagens(pair<double,double> initialCoords) {
    pair<string,string> paragens;
    string paragem_F; //paragem final
    bool exit = true;

    //initialCoords : coordenadas recebidas pelo input


    list<pair<string,string>> nearby = stcp.nearbyStops(initialCoords.first, initialCoords.second);
    TextTable t( '-', '|', '+' );
    t.add("Codigo da paragem");
    t.add("Nome");
    t.endOfRow();
    t.add(" ");
    t.add(" ");
    t.endOfRow();

    for (auto i:nearby) {
        t.add(i.first);
        t.add(i.second);
        t.endOfRow();
    }

    system("CLS");
    cout << t;
    /*
     * Funçao para mostrar as paragens + proximas
     * e escolher uma
     */

    std::cout << "\nInsira o codigo da paragem de partida:" << endl;
    std::cout << "\n"
              << "\n>";
    std::cin >> paragens.first;

    //paragens.first = "FGT2"; //isto era so um dummy -> colocar igual ao codigo da paragem anteriormente obtida
    while(exit){
        system("CLS");
        std::cout << "Insira o codigo da paragem de chegada:" << endl;
        std::cout << "\n"
                  << "\n>";
        cin.clear();
        std::cin >> paragem_F;
        auto stop_node = stcp.getStopsMap().find(paragem_F);
        if (stop_node != stcp.getStopsMap().end()) {
            paragens.second = (stop_node->first);
            exit = false;
        }
        else{
            continue;
        }
    }

    return paragens;
}

void MainMenu::menosParagens(pair<string,string> jef) {

    list <string> lines;
    list <string> path = stcp.doBFS(jef.first, jef.second, lines);
    auto lineIt = lines.begin();

    TextTable t( '-', '|', '+' );
    t.add("Paragens");
    t.add("Linhas/Caminhar");
    t.endOfRow();
    t.add(" ");
    t.add(" ");
    t.endOfRow();

    for (auto i:path) {
        t.add(i);
        t.add(*lineIt);
        t.endOfRow();
        if (lineIt != prev(lines.end())){
            lineIt = next(lineIt);
        }
    }

    cout << t;

    string aaa;
    std::cout << "\n"
              << "\n>";
    std::cout << "[0] Sair" << endl;
    cin >> aaa;
    menu();
    return;

}

void MainMenu::menorDistancia(pair<string,string> jef) {

    list <string> lines;
    list <string> path = stcp.doDijkstra(jef.first, jef.second, lines);
    auto lineIt = lines.begin();


    TextTable t( '-', '|', '+' );
    t.add("Paragens");
    t.add("Linhas/Caminhar");
    t.endOfRow();
    t.add(" ");
    t.add(" ");
    t.endOfRow();

    for (auto i:path) {
        t.add(i);
        t.add(*lineIt);
        t.endOfRow();
        if (lineIt != prev(lines.end())){
            lineIt = next(lineIt);
        }
    }

    cout << t;

    string aaa;
    std::cout << "\n"
              << "\n>";
    std::cout << "[0] Sair" << endl;
    cin >> aaa;
    menu();
    return;
}




























