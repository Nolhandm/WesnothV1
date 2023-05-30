#include <iostream>
#include "Player.hpp"

using namespace std;

Player::Player(Map * map, sf::Texture* texture,sf::Font * font, int id){
    m_texture = texture;
    m_map = map;
    m_font = font;
    nb_villages =0;
    m_gold = 100;
    my_turn = 1-id;
    m_id = id;
    key_pressed= true;
    if(id==0){
        Village = Village_J1;
        Village_Adverse = Village_J2;
    }
    else{
        Village = Village_J2;
        Village_Adverse = Village_J1;
    }

}

void Player::init() {

    if(m_id == 0){
        m_units.push_back(new Unit(m_texture,0,0,true));
        m_map->putUnit(0,0);
    }
    if (m_id == 1){
        m_units.push_back(new Unit(m_texture,9,9,true));
        m_map->putUnit(9,9);
    }

    for(Unit* ptr : m_units){
        ptr->init();
    }
}


void Player::update(sf::Vector2i localPosition) {

    // supression unité mortes
    for(Unit* ptr : m_units) {
        if (ptr->is_dead()) {
            m_map->deleteUnit(ptr->getPI(),ptr->getPJ());
            m_units.remove(ptr);
            delete(ptr);
            break;//jsp pas pourquoi sinon ça marche pas il me fait une itération de plus
        }
    }
    int a =0;
        if (my_turn) {
            // gestion souris
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !key_pressed) {
                key_pressed =true; // interrupteur pour eviter plusieurs actions lorsque la touche est maintenue
                for(Unit* ptr : m_units) {
                    // si on clique sur la même case ou se situe l'unité cela la selectionne/déselectionne
                    if (hitbox((*ptr).getPI(), (*ptr).getPJ(), localPosition.x, localPosition.y)) {
                        selectUnit(ptr);
                    }
                        // on vérifie que l'unité est sélectionnée
                    else if ((*ptr).is_selected()) {
                        // boucle permettant de trouver la case ciblée par la souris
                        for (sf::Vector2i v: atteingnable(ptr->getPI(), ptr->getPJ())) {
                            // verif si on est pas en dehors de la carte
                            if (v.x >= 0 and v.x <= m_map->getN() and v.y <= m_map->getM() and v.y >= 0) {
                                // vérif si la case est bien celle ciblée
                                if (hitbox(v.x, v.y, localPosition.x, localPosition.y)) {
                                    //la case est libre on peut y déplacer l'unité
                                    if (m_map->tile_is_free(v.x, v.y)) {
                                        deplaceUnit(ptr, v.x, v.y);
                                    }
                                        //la case est occupée on va donc attaquer
                                    else {
                                        //vérification que c'est une unité ennemi
                                        if (m_adversary->getUnit(v.x, v.y) != nullptr) {
                                            ptr->attack(m_adversary->getUnit(v.x, v.y));
                                            //fin du tour
                                            my_turn = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // gestion du clavier
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) and !key_pressed) {
                for(Unit* ptr : m_units) {
                    // la fonction peut ne rien produire selon les conditions
                    key_pressed =true;
                    addUnit(ptr);
                }
            }
        }
    for(Unit* ptr : m_units) {
        // update des units
        ptr->update();
    }
    if(key_pressed and !sf::Mouse::isButtonPressed(sf::Mouse::Left) and !sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        key_pressed = false;
    }
}

void Player::draw(sf::RenderWindow* win) {
    for(Unit* ptr : m_units){
        ptr->draw(win,m_font);
    }
    // texte concernant le player :
    sf::Text text;
    text.setFont(*m_font);
    std::string s = "Player ";
    s+=to_string(m_id);
    s+=" : nb village : ";
    s+= to_string(nb_villages);
    s+=" , gold : ";
    s+= to_string(m_gold);
    text.setPosition(900,300+100*m_id);
    text.setString(s);
    text.setCharacterSize(16);
    win->draw(text);
}

void Player::addUnit(Unit *u) {
    // vérifie que l'unité est sur un chateau
    if ((*u).canRecrute(m_map)) {
        // récupération des cases voisines au chateau
        for (sf::Vector2i v: voisins((*u).getPI(), (*u).getPJ())) {
            // vérifie que la case n'est pas occupée par une autre unité
            if (m_map->tile_is_free(v.x, v.y)) {
                // création unité
                m_units.push_back(new Unit(m_texture, v.x, v.y, false));
                m_units.back()->init();
                // permet de placer un marqueur sur la carte pour que la case soit marquée comme occupée
                m_map->putUnit(v.x, v.y);
                m_gold-=20;
                // fin du tour
                my_turn = false;
                break;
            }
        }
    }
}

void Player::selectUnit(Unit * u) {
    // on inverse l'état de selection de l'unit
    u->set_selected(1-u->is_selected());
}
void Player::deplaceUnit(Unit *u, int i, int j) {

    // permet de placer un marqueur sur la carte pour que la case soit marquée comme occupée
    m_map->deleteUnit((*u).getPI(), (*u).getPJ());
    m_map->putUnit(i, j);
    (*u).move(i, j);

    // on vérifie si l'on vient de se placer sur un village
    if (m_map->getTileType(i, j) == Village_Vide){
        nb_villages++;
        m_map->setTile(i, j, Village);
    }else if(m_map->getTileType(i, j) == Village_Adverse){
        nb_villages++;
        m_map->setTile(i, j, Village);
        m_adversary->perteVillage(1);
    }
    //fin du tour
    my_turn = false;
}

void Player::perteVillage(int nb) {
    nb_villages-=nb;
}

int Player::Calcul_income() {
    int res = 2 + nb_villages - std::max(0,(int)m_units.size()-nb_villages);
    return res;
}

// Active le tour du joueur
void Player::setTurn() {
    my_turn= true;
    m_gold+=Calcul_income();
}

bool Player::is_turn() {
    return my_turn;
}

void Player::setAdversary(Player *player) {
    m_adversary=player;
}

Unit* Player::getUnit(int i, int j) {
    for(Unit* ptr : m_units){
        if(ptr->getPI()==i and ptr->getPJ()==j) {
            return ptr;
        }
    }
    return nullptr;
}

bool Player::Have_Losed() {
    for(Unit* ptr : m_units){
        if(ptr->is_the_hero()) {
            return false;
        }
    }
    return true;
}

Player::~Player() {
    /*for(Unit* ptr : m_units){
        ptr->~Unit();
    }*/
}
