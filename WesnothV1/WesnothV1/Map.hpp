#ifndef WESNOTH_AI_CPP_MAP_HPP
#define WESNOTH_AI_CPP_MAP_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utilitaire.hpp"
class Map {
public:
    Map(sf::Texture * texture, int N,int M,int * tab,int* tab2);
    void init();
    void update();
    void draw(sf::RenderWindow* win);
    bool putUnit(int i,int j);
    bool deleteUnit(int i,int j);
    bool tile_is_free(int i, int j);
    bool setTile(int i, int j, TYPE_TERRAINS t);
    TYPE_TERRAINS getTileType(int i, int j);
    int getM();
    int getN();

private:
    int m_N;
    int m_M;
    int* m_map;
    int* m_mapPositions;
    sf::Texture* m_texture;
    sf::Sprite m_sprites [10][10];
    //sf::CircleShape m_sprites [10][10];
};


#endif //WESNOTH_AI_CPP_MAP_HPP
