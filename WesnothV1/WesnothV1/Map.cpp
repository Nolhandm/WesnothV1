#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utilitaire.hpp"

Map::Map(sf::Texture * texture, int N, int M, int * tab, int* tab2) {
    m_N = N;
    m_M = M;
    m_map = tab;
    m_mapPositions = tab2;
    m_texture = texture;
}

void Map::init() {
    for(int i =0;i<m_N;i++){
        for(int j =0;j<m_M;j++){

            m_sprites[i][j].setTexture(*m_texture);
            m_sprites[i][j].setTextureRect(sf::IntRect(TILE_SIZE*m_map[i*m_M+j],0,TILE_SIZE,TILE_SIZE));

            /*sf::CircleShape sprite(TILE_SIZE/2);
            sprite.setTexture(&m_texture);
            sprite.setTextureRect(sf::IntRect(TILE_SIZE*m_map[i*m_M+j],0,TILE_SIZE,TILE_SIZE));
            m_sprites[i][j] = sprite;*/

            std::vector<int> position = coordonnesIJtoXY(i,j);
            m_sprites[i][j].setPosition(position[0],position[1]);


        }
    }
}

void Map::update() {
    for(int i =0;i<m_N;i++) {
        for (int j = 0; j < m_M; j++) {
            m_sprites[i][j].setTextureRect(sf::IntRect(TILE_SIZE * m_map[i * m_M + j], 0, TILE_SIZE, TILE_SIZE));
        }
    }
}

void Map::draw(sf::RenderWindow* win) {
    for(int i =0;i<m_N;i++){
        for(int j =0;j<m_N;j++){
            win->draw(m_sprites[i][j]);
        }
    }
}

TYPE_TERRAINS Map::getTileType(int i, int j) {
    TYPE_TERRAINS res;
    int a = m_map[i*m_M+j];
    switch(a){
        case 0:
            res = Chateau;
            break;
        case 1 :
            res = Village_Vide;
            break;
        case 2:
            res = Village_J1;
            break;
        case 3:
            res = Village_J2;
            break;
        default:
            res = Autre;
    }
    return res;
}

bool Map::putUnit(int i, int j) {
    if(tile_is_free(i,j)){
        m_mapPositions[i*m_M+j]=1;
        return true;
    }
    return false;
}

bool Map::deleteUnit(int i, int j) {
    m_mapPositions[i*m_M+j]=0;
    return true;
}

bool Map::tile_is_free(int i, int j) {
    return !m_mapPositions[i*m_M+j];
}

bool Map::setTile(int i, int j, TYPE_TERRAINS t) {
    m_map[i*m_M+j] = t;
    return true;
}

int Map::getN() {
    return m_N;
}

int Map::getM() {
    return m_M;
}