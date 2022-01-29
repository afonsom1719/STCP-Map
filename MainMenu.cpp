//
// Created by kwanzz on 28/01/2022.
//

#include "MainMenu.h"

void MainMenu::menu() {

    //initialize stcp
    this->stcp = STCP();
    bool exiT = true;
    char c;
    pair<double,double> initialCoords;
    pair<string,string> paragens;


    system("CLS");
    std::cout << "[STCPotas]\n";
    std::cout << "Queres inserir o codigo da paragem donde queres partir ou as coordenadas onde te encontras??" << endl;
    std::cout << "\n[1] Coordenadas"
              << "\n[2] Codigo das paragens"
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
                initialCoords = enterBeginningCoordinates();
                paragens = mostrarNearbyParagens(initialCoords);
                exiT = false;
                break;
            case '2':
                paragens = enterParagens();
                exiT = false;
                break;
            case '0':
                exit(1);
                system("exit");
                return;
            default:
                std::cout << "Tenta outra vez\n";
                exiT = true;
        }
    }
    pathPreference(paragens);
}

void MainMenu::pathPreference(pair<string,string> paragens){
        char c;
        system("CLS");
        std::cout << "Seleciona a tua preferência de caminho\n";
        std::cout << "\n[1] Caminho com menor distância"
                  << "\n[2] Caminho com menos paragens"
                  << "\n[0] Volta Atrás\n"
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
                    std::cout << "Opção inválida\n";
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
            std::cout << "Insere o código da paragem de partida:" << endl;
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
                        std::cout << "Insere o código da paragem de partida correto seu burro:" << endl;
                        i = -1;
                        continue;
                    }

                }
                if(i == 1){
                    system("CLS");
                    std::cout << "Insere o código da paragem de chegada:" << endl;
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
    while (true){
        cin.clear();
        system("CLS");
        std::cout << "Insere a latitude:" << endl;
        std::cout << "\n"
                  << "\n>";
        cin.clear();
        std::cin >> lat;

        cin.clear();
        system("CLS");
        std::cout << "Insere a longitude:" << endl;
        std::cin >> lon;

        break;
    }
    coords.first = lat; coords.second = lon;
    return coords;
}

pair<string, string> MainMenu::mostrarNearbyParagens(pair<double,double> initialCoords) {
    pair<string,string> paragens;
    string paragem_F; //paragem final
    bool exit = true;

    //initialCoords : coordenadas recebidas pelo input

    /*
     * Funçao para mostrar as paragens + proximas
     * e escolher uma
     */

    paragens.first = "FGT2"; //isto era so um dummy -> colocar igual ao codigo da paragem anteriormente obtida
    while(exit){
        system("CLS");
        std::cout << "Insere o código da paragem de chegada:" << endl;
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


    list <string> path = stcp.doBFS(jef.first, jef.second);

    TextTable t( '-', '|', '+' );
    t.add(" ");
    t.endOfRow();

    for (auto i:path) {
        t.add(i);
        t.endOfRow();
    }

    cout << t;

    string aaa;
    std::cout << "\n"
              << "\n>";
    std::cout << "Prime qualquer tecla para voltar ao menu inicial:" << endl;
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

    string aaa;
    std::cout << "\n"
              << "\n>";
    std::cout << "Prime qualquer tecla para voltar ao menu inicial:" << endl;
    cin >> aaa;
    menu();
    return;
}




























