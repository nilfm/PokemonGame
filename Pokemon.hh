#ifndef POKEMON_HH
#define POKEMON_HH

#include "includes.hh"
#include "Move.hh"
#include "Type.hh"
#include "Pokebase.hh"

class Pokemon {
private:
    const static int MAX_LEVEL = 100;
    const static int MAX_XP = 55000;
    const static int MAX_MOVES = 4;
    Type type;
    std::string name;
    int xp, hp, level;
    Stats stats;
    Stats battle_stats;
    std::map<int, Move> moveset;
    std::vector<Move> moves;
    
public:
    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101 */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given */
    //NOTA: No oblidar augmentar la XP fins al punt necessari
    Pokemon(const Pokebase& p, int level);

    /* Pre: True */
    /* Post: Returns the current total XP for this pokemon */
    int get_xp() const;
    
    /* Pre: True */
    /* Post: Returns the current level for this pokemon */
    int get_level() const;
    
    /* Pre: True */
    /* Post: Returns the current HP for this pokemon */
    int get_hp() const;
    
    /* Pre: True */
    /* Post: Returns the current stats for this pokemon */
    Stats get_stats() const;

    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the name of this pokemon */
    std::string get_name() const;
    
    /* Pre: health contains a positive integer or -1 */
    /* Post: If health was -1, hp was restored to full. Otherwise, the pokemon restores health hp, without going over maxhp */
    void restore_health(int health);
};

#endif
