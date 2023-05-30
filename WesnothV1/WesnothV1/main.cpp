#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"
#include "Unit.hpp"
#include "Player.hpp"

int main() {
    // crétion de la fenêtre de jeu
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Application", sf::Style::Close);
    //window.setVerticalSyncEnabled(true); Pour activer la synchro de la fréquence de rafraichissement avec celle de l'écran

    // Construction de la map
    int const N(10);
    int const M(10);
    int map2D[N][M] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 1, 4, 4, 4},
                       {1, 4, 4, 4, 4, 4, 4, 4, 1, 4},
                       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 0, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 1, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},};

    // conversion de la map en un tableau 1 dimension
    int map1D[N * M];
    int mapPositions[N * M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map1D[i * M + j] = map2D[i][j];
            mapPositions[i * M + j] = 0;
        }
    }
    // Chargement de la police
    sf::Font font;
    font.loadFromFile("c:/Users/nolha/Documents/GitHub/Saves/WesnothV1/WesnothV1/Font/arial.ttf");

    // chargement des textures pour les Map et les unités
    sf::Texture textureMap;
    textureMap.loadFromFile("c:/Users/nolha/Documents/GitHub/Saves/WesnothV1/WesnothV1/idees_map/brouillon.png");
    sf::Texture textureUnit1;
    textureUnit1.loadFromFile("c:/Users/nolha/Documents/GitHub/Saves/WesnothV1/WesnothV1/idees_map/perso.png");
    sf::Texture textureUnit2;
    textureUnit2.loadFromFile("c:/Users/nolha/Documents/GitHub/Saves/WesnothV1/WesnothV1/idees_map/perso2.png");

    // Instanciation de la map
    Map my_map(&textureMap, N, M, map1D, mapPositions);
    // Instanciation des joueurs
    Player player0(&my_map, &textureUnit1, &font, 0);
    Player player1(&my_map, &textureUnit2, &font, 1);

    player0.setAdversary(&player1);
    player1.setAdversary(&player0);

    // id du player dont c'est le tour
    int actualPlayer = 0;

    //Initialisation
    my_map.init();
    player0.init();
    player1.init();

    // texte d'affichage
    sf::Text text;
    text.setFont(font);
    text.setPosition(900, 100);
    int var = 0;
    for(sf::Vector2i v : atteingnable(5,5)){
        printf("%d , %d \n",v.x,v.y);
        var++;
    }
    printf("var : %d\n",var);

    while (window.isOpen()) {
        std::string s = "Victoire du joueur : ";
        s += to_string(1-actualPlayer);
        text.setString(s);
        while (!player0.Have_Losed() and !player1.Have_Losed() and window.isOpen()) {
            //position de la souris par rapport à la fenêtre;
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            sf::Event event;
            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed)
                    window.close();
            }

            //update
            player0.update(localPosition);
            player1.update(localPosition);
            my_map.update();
            //draw
            window.clear();
            my_map.draw(&window);
            player0.draw(&window);
            player1.draw(&window);

            std::string s = "Tour du joueur : ";
            s += to_string(actualPlayer);
            text.setString(s);
            window.draw(text);
            window.display();

            if (actualPlayer == 0) {
                if (!player0.is_turn()) {
                    player1.setTurn();
                    actualPlayer = 1;
                }
            }
            if (actualPlayer == 1) {
                if (!player1.is_turn()) {
                    player0.setTurn();
                    actualPlayer = 0;
                }
            }
        }
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }

    //std::cout << "dzdzdzd";;
    return 0;
}