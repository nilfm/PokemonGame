#ifndef POKEMON_HH
#define POKEMON_HH

#include "Includes.hh"
#include "Move.hh"
#include "Type.hh"
#include "Pokebase.hh"
#include "Pokedex.hh"

class Pokemon {
private:
    const static int MAX_LEVEL = 100;
    const static int MAX_XP = 55000;
    const static int MAX_MOVES = 4;
    int level_evolution;
    std::string next_evolution;
    std::string type;
    std::string name;
    int xp, hp, level;
    Stats stats;
    Stats per_level_min;
    Stats per_level_max;
    Stats battle_stats;
    Status status;
    std::map<int, std::vector<Move> > moveset;
    std::vector<Move> moves;
    
public:
    //CONSTRUCTORS
    /* Pre: True */
    /* Post: Default constructor */
    Pokemon();

    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101 */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given */
    Pokemon(const Pokebase& p, int level);
    
    //This is for evolving Pokemon and keeping movesets
    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101 */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given, with the moveset given */
    Pokemon(const Pokebase& p, int level, const std::vector<Move>& moves, int xp, int missing_hp);
    
    //This is for loading a Pokemon through a Gamesave
    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101, every string in moves refers to a valid Move */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given, with the moveset given, with the current stats given */
    Pokemon(const Pokebase& p, int level, int xp, const Stats& current, const std::vector<std::string> moves);


    //GETTERS
    /* Pre: True */
    /* Post: Returns a reference to this pokemon's moves */
    std::vector<Move> get_moves() const;
    
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
    /* Post: Returns the evolution level for this pokemon (-1 if it does not evolve) */
    int get_level_evolution() const;
    
    /* Pre: True */
    /* Post: Returns the next evolutionary stage for this pokemon */
    std::string get_next_evolution() const;
    
    /* Pre: True */
    /* Post: Returns the current stats for this pokemon */
    Stats get_stats() const;
    
    /* Pre: True */
    /* Post: Returns the current battle stats for this pokemon */
    Stats get_battle_stats() const;
    
    /* Pre: True */
    /* Post: Returns the current status for this pokemon */
    Status get_status() const;

    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    std::string get_type() const;
    
    /* Pre: True */
    /* Post: Returns the name of this pokemon */
    std::string get_name() const;
    
    
    //SETTERS
    /* Pre: True */
    /* Post: Adds to the battle stats the stats given */
    void add_battle_stats(const Stats& st);
    
    /* Pre: True */
    /* Post: The battle stats for this Pokemon are reset to their defaults */
    void reset_battle_stats();
    
    /* Pre: change is a binary 3-tuple */
    /* Post: For each 1 in change, the Pokemon heals that status */
    void restore_status(const Status& change);
    
    /* Pre: health contains a positive integer or -1 */
    /* Post: If health was -1, hp was restored to full. Otherwise, the pokemon restores health hp, without going over maxhp */
    void restore_health(int health);

    /* Pre: 0 <= pos < number of moves this Pokemon has */
    /* Post: The move at position pos has restored the PP given */
    void restore_pp(int pos, int restore);
    
    /* Pre: True */
    /* Post: All the Pokemon's moves have max PP */
    void restore_all_pp();
    
    /* Pre: True */
    /* Post: All the Pokemon's moves have restored restore PP */
    void restore_all_moves_pp(int restore);
    
    /* Pre: dmg >= 0 */
    /* Post: The Pokemon has received dmg damage, and returns true iff it has fainted */
    bool receive_damage(int dmg);
    
    /* Pre: xp > 0 */
    /* Post: The Pokemon has gained the XP, may have leveled up and/or evolved */
    void gain_xp(int xp);
    
    /* Pre: True */
    /* Post: If burned or poisoned will take damage, and may recover from them */
    void handle_status();
    
    /* Pre: True */
    /* Post: Poisons the Pokemon */
    void get_poisoned();
    
    /* Pre: True */
    /* Post: Burns the Pokemon */
    void get_burned();
    
    /* Pre: True */
    /* Post: Stuns the Pokemon */
    void get_stunned();
    
    /* Pre: move is in the Pokemon's active moves, move has PP > 0 */
    /* Post: The PP for move have been decremented in 1 */
    void decrement_pp(const Move& move);
    
    
    //ACTIONS
    /* Pre: name_evolution is a valid pokemon name, 0 < level < 101 */
    /* Post: The pokemon object becomes its evolution, at the level give, with the same moveset */
    void evolve();

    /* Pre: The Pokemon has achieved enough XP to level up for 1 level */
    /* Post: The Pokemon is one level higher, has evolved if necessary, and has learned a new move if necessary */
    void level_up();
    
    /* Pre: The Pokemon wants to learn this move at this level */
    /* Post: If the Pokemon has less than MAX_MOVES moves, it learns the move automatically.
     *       Otherwise, it asks the player for a move to forget */
    void learn_move(const Move& move);


    //SHOWERS
    /* Pre: True */
    /* Post: Prints a formatted list with the stats for this Pokemon */
    void print_stats() const;
    
    /* Pre: True */
    /* Post: Prints a formatted list with the moves for this Pokemon */
    void print_moves() const;

};

#endif
