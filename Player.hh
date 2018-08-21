#ifndef PLAYER_HH
#define PLAYER_HH

#include "Includes.hh"
#include "Pokemon.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"
#include "Move.hh"
#include "Item.hh"

class Player {
private:
    const static std::string gamesave_address;
    const static std::string address_extension;
    const static int MAX_POKEMON = 3;
    int slot;
    std::string name;
    int money, trainers;
    std::vector<Pokemon> team;
    std::map<Item, int> inventory;
    
public:
    //CONSTRUCTORS
    /* Pre: True */
    /* Post: Default constructor */
    Player();
    
    /* Pre: True */
    /* Post: Slot constructor */
    Player(int slot);


    //SAVE/LOAD
    /* Pre: This player hasn't loaded yet, the slot isn't empty */
    /* Post: Reads the file at the corresponding slot and loads the game */
    void load();
    
    /* Pre: True */
    /* Post: Removes all the contents from the file associated to the player */
    void save_empty() const;

    /* Pre: True */
    /* Post: Saves the given data to the file associated to the player */
    void save() const;


    //GETTERS
    /* Pre: True */
    /* Post: Returns the address for the file for the player */
    std::string get_address() const;
    
    /* Pre: True */
    /* Post: Returns the player's name */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the player's money */
    int get_money() const;
    
    /* Pre: True */
    /* Post: Returns the player's amount of trainers beaten */
    int get_trainers() const;
    
    /* Pre: True */
    /* Post: Returns the player's team */
    std::vector<Pokemon> get_team() const;
    
    /* Pre: True */
    /* Post: Returns the player's inventory */
    std::map<Item, int> get_inventory() const;
    
    /* Pre: True */
    /* Post: Returns true if the player's file address refers to an empty file */
    bool is_empty() const;
    
    
    //SETTERS
    /* Pre: True */
    /* Post: Sets the player's name */
    void set_name(const std::string& name);
    
    /* Pre: True */
    /* Post: Sets the player's team */
    void set_team(const std::vector<Pokemon>& team);
    
    /* Pre: True */
    /* Post: Adds one to the trainers counter */
    void increment_trainers();
    
    /* Pre: True */
    /* Post: Adds added to the money */
    void increment_money(int added);
    
    /* Pre: True */
    /* Post: Every pokemon has max HP and PP on every move */
    void heal_pokemon();
    
    /* Pre: 0 <= i < MAX_POKEMON */
    /* Post: The Pokemon at position i (0-indexed) has been replaced by p */
    void set_pokemon(const Pokemon& p, int i);
    
    /* Pre: item is present in the inventory */
    /* Post: The amount of item present has decremented by 1, and been removed if it gets to 0 */
    void decrement_item(const std::string& item);
    
    
    //SHOWERS
    /* Pre: The file is not empty, the player is loaded */
    /* Post: Prints a formatted output to the console of name and trainers */
    void presentation() const;
    
    /* Pre: True */
    /* Post: Displays a formatted list with the stats for the team */
    void show_team_stats() const;
    
    /* Pre: True */
    /* Post: Displays a formatted line for each Pokemon with their level and HP */
    void show_team_inline() const;
    
    /* Pre: True */
    /* Post: Displays a formatted list with the items you have */
    void show_inventory() const;
    
    
    //ACTIONS
    /* Pre: k is a valid position on the team, it is a valid Item */
    /* Post: The item has been used on the Pokemon at position p */
    void use_item(int k, const Item& it);

    /* Pre: True */
    /* Post: Asks user for input and returns a starting team of Pokemon */
    std::vector<Pokemon> choose_starters() const;
    
    /* Pre: True */
    /* Post: Asks player to swap Pokemon around in their team */
    void sort_team();

    /* Pre: True */
    /* Post: The player has shopped for items */
    void shop();

    /* Pre: 0 <= i, j < MAX_POKEMON */
    /* Post: The pokemon at positions i and j in the team have been swapped */
    void swap_pokemon(int i, int j);

};

#endif
