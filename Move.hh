#ifndef MOVE_HH
#define MOVE_HH

#include "Includes.hh"
#include "Type.hh"

class Move {
private:
    std::string name;
    Type type;
    int power, accuracy, maxpp, pp;
    bool special;
    Stats change_stats_opponent;
    Stats change_stats_own;
    Status status;
    
public:
    //CONSTRUCTORS
    /* Pre: True */
    /* Post: Default constructor */
    Move();

    /* Pre: True */
    /* Post: Assigns to the move the stats given */
    Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, int maxpp, const Stats& change_stats_opponent, const Stats& change_stats_own, const Status& status);

    //GETTERS
    /* Pre: True */
    /* Post: Returns the name of the move */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the type of the move */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the power of the move */
    int get_power() const;
    
    /* Pre: True */
    /* Post: Returns the accuracy of the move */
    int get_accuracy() const;
    
    /* Pre: True */
    /* Post: Returns the PP of the move */
    int get_pp() const;

    /* Pre: True */
    /* Post: Returns the maximum PP of the move */
    int get_maxpp() const;
    
    /* Pre: True */
    /* Post: Returns the struct that holds the stat changes caused on the opponent by the move */
    Stats get_change_stats_opponent() const;
    
    /* Pre: True */
    /* Post: Returns the struct that holds the stat changes caused on itself by the move */
    Stats get_change_stats_own() const;
    
    /* Pre: True */
    /* Post: Returns a 3-tuple of chances of getting poisoned, burnt, stunned */
    Status get_status() const;
    
    /* Pre: True */
    /* Post: Returns true iff the move is a special move */
    bool is_special() const;
    
    
    //SHOWERS
    /* Pre: True */
    /* Post: Prints a formatted list with the stats for this move */
    void print_stats() const;
    
    
    //ACTIONS
    /* Pre: True */
    /* Post: Restores this move's PP to its maximum value */
    void restore_pp(int restore);

    
    //SEARCHERS
    /* Pre: name is the name of a move that exists within the map */
    /* Post: Returns the move given my name */
    static Move search_move(const std::string& name, const std::map<int, std::vector<Move> >& moveset);
};

#endif
