#ifndef COMBAT_HH
#define COMBAT_HH

#include "Includes.hh"
#include "Player.hh"
#include "Pokemon.hh"
#include "Move.hh"
#include "Type.hh"

class Combat {
private:
    Player& player, enemy;
    
public:
    //CONSTRUCTORS
    /* Pre: both player and enemy have a full Pokemon team (3) */
    /* Post: A combat is initialized between player and enemy */
    Combat(Player& _player, Player& _enemy);
    
    
    //ACTIONS
    /* Pre: True */
    /* Post: Returns 0 if battle goes on, 1 if player beats enemy, 2 if enemy beats player */
    int play_turn();
    
    /* Pre: Player just won a combat */
    /* Post: Player has picked a pokemon from the enemy team to swap for one of his pokemon, or chosen to do nothing */
    void pick_enemy_pokemon();
    
    /* Pre: k is either 1 or 2 */
    /* Post: If k is 1, player attacks enemy. Else, enemy attacks player. Returns true iff defender has fainted */
    static bool attack(int k, Player& player, Player& enemy, Move& move);
    
    //SHOWERS
    /* Pre: True */
    /* Post: Shows current status of the game */
    void show_current_game();
    
    
    //AUXILIARY
    /* Pre: True */
    /* Post: Returns the damage done by this move on the defender. Critical, missed, not_effective, little_effective, very_effective indicates what the hit has done */
    static int calculate_damage(const Pokemon& attacker, const Pokemon& defender, const Move& move, bool& critical, bool& missed, bool& not_effective, bool& little_effective, bool& very_effective, bool& stunned);
    
    /* Pre: True */
    /* Post: returns 1 if player1 attacks first, 2 otherwise */
    static int pick_first(int speed1, int speed2);
    
    /* Pre: True */
    /* Post: Returns true iff the player has no alive Pokemon */
    static bool has_lost(const Player& p);
};

#endif
