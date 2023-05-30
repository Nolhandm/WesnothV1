#ifndef WESNOTH_AI_CPP_UNIT_H
#define WESNOTH_AI_CPP_UNIT_H
#define TILE_SIZE 80
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utilitaire.hpp"
#include "Map.hpp"
class Unit {
public:
    Unit(sf::Texture* texture,int i,int j,bool hero=false);
    bool move(int i, int j);
    bool is_selected();
    void set_selected(bool b);
    int getPI();
    int getPJ();
    bool canRecrute(Map* m);
    void init();
    void update();
    void draw(sf::RenderWindow* win,sf::Font* font);
    void attack(Unit* unit);
    bool is_dead();
    void subiAttack(int deg);
    bool is_the_hero();
    ~Unit();

private:

    int m_pv;
    int m_attack;

    int m_PI;
    int m_PJ;
    int m_PX;
    int m_PY;
    bool m_hero;
    bool m_selected;
    bool m_dead;
    sf::Texture* m_texture;
    sf::Sprite m_sprite;
};


#endif
