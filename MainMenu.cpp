//
// Created by kwanzz on 28/01/2022.
//

#include "MainMenu.h"

void MainMenu::menu() {

    //initialize stcp
    this->stcp = STCP();



    char c;
    while (true) {
        pair<string,string> jef = enterParagens();
        system("CLS");
        std::cout << "Seleciona a tua preferência de caminho\n";
        std::cout << "\n[1] Caminho com menor distância"
                  << "\n[2] Caminho com menos paragens"
                  << "\n[0] Sair\n"
                  << "\n>";

        std::cin.clear();
        //cin.ignore(INT_MAX, '\n');
        std::cin >> c;
        cin.clear();
        switch (c) {
            //first cases to ask for
            case '1':

                menorDistancia(jef);
                break;
            case '2':
                menosParagens(jef);
                break;
            case '3':
                //func
                break;
            case '0':
                return;
            default:
                std::cout << "Opção inválida\n";
        }
    }

}

pair<int,int> MainMenu::enterLocation() {
    float lat, lon;
    bool exit = true;
    char c;
    int inicio,fim; //paragens de inicio e de fim

    while(exit){
        system("CLS");
        std::cout << "[STCPotas]\n";
        std::cout << "Queres inserir o codigo da paragem donde queres partir ou as coordenadas onde te encontras??" << endl;
        std::cout << "\n[1] Coordenadas"
                  << "\n[2] Código das paragens"
                  << "\n[0] Voltar atrás\n"
                  << "\n>";
        std::cin.clear();
        //cin.ignore(INT_MAX, '\n');
        std::cin >> c;
        cin.clear();
        switch(c){
            //coordenadas
            case '1':
                enterBeginningCoordinates();
                mostrarNearbyParagens();
                enterParagens();
                break;
            case '2':
                enterParagens();
                break;
            case '0':
                menu();
                exit = false;
                break;
            default:
                std::cout << "Tenta outra vez\n";
        }

    }

    pair<int,int> jef;
    return jef;
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
    return pair<double, double>();
}

void MainMenu::mostrarNearbyParagens() {

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
    cin >> aaa;

}

void MainMenu::menorDistancia(pair<string,string> jef) {


    list <string> path = stcp.doDijkstra(jef.first, jef.second);

    TextTable t( '-', '|', '+' );
    t.add(" ");
    t.endOfRow();

    for (auto i:path) {
        t.add(i);
        t.endOfRow();
    }

    cout << t;

    string aaa;
    cin >> aaa;

}




























