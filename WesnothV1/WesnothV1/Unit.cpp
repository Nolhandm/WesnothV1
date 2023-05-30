#include "Unit.hpp"
using namespace std;

Unit::Unit(sf::Texture* texture,int i,int j,bool hero){

    m_dead = false;

    m_PI =i;
    m_PJ =j;

    std::vector<int> res = coordonnesIJtoXY(i,j);
    m_PX = res[0];
    m_PY =res[1];

    m_hero = hero;
    if(m_hero){
        m_pv=20;
        m_attack=10;
    }
    else{
        m_pv = 10;
        m_attack =5;
    }
    m_texture = texture;
    m_selected =false;

}

void Unit::init() {
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sf::IntRect(TILE_SIZE*m_selected, TILE_SIZE * m_hero, TILE_SIZE, TILE_SIZE));
    m_sprite.setPosition(m_PX,m_PY);
}

void Unit::update() {
    // changement du sprite selon la selection
    m_sprite.setTextureRect(sf::IntRect(TILE_SIZE*m_selected, TILE_SIZE * m_hero, TILE_SIZE, TILE_SIZE));
    m_sprite.setPosition(m_PX,m_PY);
    if(m_pv<=0){
        m_dead = true;
    }
}


void Unit::draw(sf::RenderWindow* win, sf::Font* font) {
    win->draw(m_sprite);
    if(m_selected) {
        sf::Text text;
        text.setFont(*font);
        std::string s = "Unit PV : ";
        s += to_string(m_pv);
        text.setPosition(900, 600);
        text.setString(s);
        text.setCharacterSize(16);
        win->draw(text);
    }
}

bool Unit::move(int i,int j){

    m_PI =i;
    m_PJ =j;

    std::vector<int> res = coordonnesIJtoXY(i,j);
    m_PX = res[0];
    m_PY =res[1];
    m_selected = false;
    return true;
}

bool Unit::is_selected() {
    return m_selected;
}

void Unit::set_selected(bool b) {
    m_selected=b;
}

int Unit::getPI() {
    return m_PI;
}

int Unit::getPJ() {
    return m_PJ;
}

bool Unit::canRecrute(Map* map) {
    return m_hero and (map->getTileType(m_PI, m_PJ) == Chateau);
}

void Unit::attack(Unit *unit) {
    unit->subiAttack(m_attack);
    m_selected = false;
}

void Unit::subiAttack(int deg) {
    m_pv-=deg;
}

bool Unit::is_dead() {
    return m_dead;
}

bool Unit::is_the_hero() {
    return m_hero;
}

Unit::~Unit() {

}
