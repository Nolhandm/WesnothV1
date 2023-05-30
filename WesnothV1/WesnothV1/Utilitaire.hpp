

#ifndef WESNOTH_AI_CPP_UTILITAIRE_HPP
#define WESNOTH_AI_CPP_UTILITAIRE_HPP
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#define TILE_SIZE 80

// fonction permettant d'obtenir les positions x et y du sprite correspondant à la tuile i,j
std::vector<int> coordonnesIJtoXY(int i,int j);

// fonction permettant de trouver quelle tuile i,j correspond à celle pointée par la souris
bool hitbox(int i,int j,int x,int y);

// fonction permettant de récupérer les coordonnées des 6 voisins
std::list<sf::Vector2i> voisins(int i, int j);

// permet de récupérer toutes les cases atteignables par un perso
std::list<sf::Vector2i> atteingnable(int i, int j) ;

// prédicat permettant de comparer 2 vector2i (<=)
bool pred(sf::Vector2i const& v,sf::Vector2i const& v2);

std::list<sf::Vector2i> trifusion(std::list<sf::Vector2i>);

enum TYPE_TERRAINS{
    Chateau = 0,
    Village_Vide = 1,
    Village_J1 = 2,
    Village_J2 = 3,
    Autre = 4,
};

#endif //WESNOTH_AI_CPP_UTILITAIRE_HPP
