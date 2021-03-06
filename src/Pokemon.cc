#include "../inc/Pokemon.hh"

//CONSTRUCTORS
Pokemon::Pokemon() {}

Pokemon::Pokemon(const Pokebase& p, int level) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    this->level = level;
    
    //Calculate stats at that level
    xp = 5*level*(level-1);
    per_level_min   = p.get_level_stats_min();
    per_level_max   = p.get_level_stats_max();
    stats.attack    = p.get_base_stats().attack    + Random::randint((level-1)*per_level_min.attack, (level-1)*per_level_max.attack);
    stats.defense   = p.get_base_stats().defense   + Random::randint((level-1)*per_level_min.defense, (level-1)*per_level_max.defense);
    stats.spattack  = p.get_base_stats().spattack  + Random::randint((level-1)*per_level_min.spattack, (level-1)*per_level_max.spattack);
    stats.spdefense = p.get_base_stats().spdefense + Random::randint((level-1)*per_level_min.spdefense, (level-1)*per_level_max.spdefense);
    stats.speed     = p.get_base_stats().speed     + Random::randint((level-1)*per_level_min.speed, (level-1)*per_level_max.speed);
    stats.maxhp     = p.get_base_stats().maxhp     + Random::randint((level-1)*per_level_min.maxhp, (level-1)*per_level_max.maxhp);
    hp = stats.maxhp;
    battle_stats    = stats;
    status.poison = status.burn = status.stun = 0;
    
    //Evolution stuff
    level_evolution = p.get_level_evolution();
    if (level_evolution != -1) next_evolution = p.get_next_evolution();
    
    //Choose 4 random moves the Pokemon can learn at that level
    moveset = p.get_moveset();
    std::vector<Move> possible_moves;
    for (int i = 1; i <= level; i++) {
        std::map<int, std::vector<Move> >::iterator it = moveset.find(i);
        if (it != moveset.end()) {
            for (int j = 0; j < (int)(it->second).size(); j++) possible_moves.push_back((it->second)[j]);
        }
    }
    for (int i = 0; i < 4 and (int)possible_moves.size() > 0; i++) {
        int rnd = Random::randint(0, (int)possible_moves.size()-1);
        moves.push_back(possible_moves[rnd]);
        possible_moves.erase(possible_moves.begin()+rnd);
    }
}

Pokemon::Pokemon(const Pokebase& p, int level, const std::vector<Move>& moves, int xp, int missing_hp) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    this->level = level;
    this->xp = xp;
    
    //Calculate stats at that level
    per_level_min   = p.get_level_stats_min();
    per_level_max   = p.get_level_stats_max();
    stats.attack    = p.get_base_stats().attack    + (level-1)*Random::randint(per_level_min.attack, per_level_max.attack);
    stats.defense   = p.get_base_stats().defense   + (level-1)*Random::randint(per_level_min.defense, per_level_max.defense);
    stats.spattack  = p.get_base_stats().spattack  + (level-1)*Random::randint(per_level_min.spattack, per_level_max.spattack);
    stats.spdefense = p.get_base_stats().spdefense + (level-1)*Random::randint(per_level_min.spdefense, per_level_max.spdefense);
    stats.speed     = p.get_base_stats().speed     + (level-1)*Random::randint(per_level_min.speed, per_level_max.speed);
    stats.maxhp     = p.get_base_stats().maxhp     + (level-1)*Random::randint(per_level_min.maxhp, per_level_max.maxhp);
    hp = std::max(1, stats.maxhp - missing_hp);
    battle_stats    = stats;
    
    //Evolution stuff
    level_evolution = p.get_level_evolution();
    if (level_evolution != -1) next_evolution = p.get_next_evolution();

    //Give it the given moves
    this->moves = moves;
    this->moveset = p.get_moveset();
}

Pokemon::Pokemon(const Pokebase& p, int level, int xp, const Stats& current, const std::vector<std::string> moves) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    this->level = level;
    this->xp = xp;
    
    //Copy stats
    per_level_min   = p.get_level_stats_min();
    per_level_max   = p.get_level_stats_max();
    stats.attack    = current.attack;
    stats.defense   = current.defense;
    stats.spattack  = current.spattack;
    stats.spdefense = current.spdefense;
    stats.speed     = current.speed;
    stats.maxhp     = current.maxhp;
    battle_stats    = stats;
    status.poison = status.burn = status.stun = 0;
    hp = stats.maxhp;

    //Evolution stuff
    level_evolution = p.get_level_evolution();
    if (level_evolution != -1) next_evolution = p.get_next_evolution();

    //Give it the given moves (fatal d'eficiencia lol)
    this->moveset = p.get_moveset();
    for (int i = 0; i < (int)moves.size(); i++) {
        Move to_push = Move::get_move(moves[i]);
        (this->moves).push_back(to_push);
    }
}


//GETTERS
std::vector<Move> Pokemon::get_moves() const {
    return moves;
}

int Pokemon::get_xp() const {
    return xp;
}

int Pokemon::get_level() const {
    return level;
}

int Pokemon::get_hp() const {
    return hp;
}

int Pokemon::get_level_evolution() const {
    return level_evolution;
}

std::string Pokemon::get_next_evolution() const {
    return next_evolution;
}

Stats Pokemon::get_stats() const {
    return stats;
}

Stats Pokemon::get_battle_stats() const {
    return battle_stats;
}

std::string Pokemon::get_name() const {
    return name;
}

std::string Pokemon::get_type() const {
    return type;
}

Status Pokemon::get_status() const {
    return status;
}


//SETTERS
void Pokemon::add_battle_stats(const Stats& st) {
    battle_stats.attack = std::max(1, battle_stats.attack + st.attack);
    battle_stats.defense = std::max(1, battle_stats.defense + st.defense);
    battle_stats.spattack = std::max(1, battle_stats.spattack + st.spattack);
    battle_stats.spdefense = std::max(1, battle_stats.spdefense + st.spdefense);
    battle_stats.speed = std::max(1, battle_stats.speed + st.speed);
    battle_stats.maxhp = std::max(1, battle_stats.maxhp + st.maxhp);
}

void Pokemon::reset_battle_stats() {
    battle_stats = stats;
}

void Pokemon::restore_health(int health) {
    if (health == -1) hp = stats.maxhp;
    else hp = std::min(stats.maxhp, hp + health);
}

void Pokemon::restore_pp(int pos, int restore) {
    assert(pos >= 0 and pos < (int)moves.size());
    moves[pos].restore_pp(restore);
}

void Pokemon::restore_all_pp() {
    for (int i = 0; i < (int)moves.size(); i++) {
        restore_pp(i, -1);
    }
}

void Pokemon::restore_all_moves_pp(int restore) {
    for (int i = 0; i < (int)moves.size(); i++) {
        restore_pp(i, restore);
    }
}

void Pokemon::restore_status(const Status& change) {
    if (change.poison == 1) status.poison = 0;
    if (change.burn == 1) status.burn = 0;
    if (change.stun == 1) status.stun = 0;
}

bool Pokemon::receive_damage(int dmg) {
    hp = std::max(0, hp-dmg);
    return (hp == 0);
}

void Pokemon::gain_xp(int xp) {
    this->xp = std::min(xp+this->xp, 5*100*101);
    while (this->xp >= 5*level*(level+1) and level != 100) level_up();
}

void Pokemon::handle_status() {
    if (status.poison != 0) {
        if (Random::randint(0, 100) > 100/status.poison) {
            status.poison = 0;
            std::cout << name << " has recovered from its poison" << std::endl;
        }
        else status.poison++;
    }
    if (status.burn != 0) {
        if (Random::randint(0, 100) > 100/status.burn) {
            status.burn = 0;
            std::cout << name << " has recovered from its burn" << std::endl;
        }
        else status.burn++;
    }
    if (status.stun != 0) {
        if (Random::randint(0, 100) > 100/status.stun) {
            status.stun = 0;
            std::cout << name << " has recovered from its stun" << std::endl;
        }
        else status.stun++;
    }
    
    
    if (status.poison != 0) {
        int old_hp = hp;
        hp = std::max(1, (int)(0.95*hp));
        std::cout << name << " has taken " << old_hp - hp << " damage from poison" << std::endl;
    }
    else if (status.burn != 0) {
        int old_hp = hp;
        hp = std::max(1, (int)(0.95*hp));
        std::cout << name << " has taken " << old_hp - hp << " damage from its burn" << std::endl;
    }
}

void Pokemon::get_poisoned() {
    status.poison = 1;
    status.burn = 0;
    status.stun = 0;
}

void Pokemon::get_burned() {
    status.poison = 0;
    status.burn = 1;
    status.stun = 0;
}

void Pokemon::get_stunned() {
    status.poison = 0;
    status.burn = 0;
    status.stun = 1;
}

void Pokemon::decrement_pp(const Move& move) {
    for (int i = 0; i < (int)moves.size(); i++) {
        if (moves[i].get_name() == move.get_name()) {
            assert(moves[i].get_pp() > 0);
            moves[i].decrement_pp();
            return;
        }
    }
}


//ACTIONS
void Pokemon::evolve() {
    std::string old_name = name;
    std::cout << "Your " << name << " wants to evolve to a " << next_evolution << "!" << std::endl;
    std::string query = "Enter 1 to evolve, 2 to prevent evolution: ";
    std::string error = "Oops. Enter either 1 or 2";
    int choice = Input::read_int(1, 2, query, error);
    if (choice == 2) std::cout << "Evolution stopped" << std::endl << std::endl;
    else {
        Pokebase p = Pokedex::get_pokebase(next_evolution);
        *this = Pokemon(p, level, moves, xp, stats.maxhp-hp);
        std::cout << "Your " << old_name << " just evolved to a " << name << "!" << std::endl << std::endl;
    }
}

void Pokemon::level_up() {
    level++;
    //Calculate improvements
    Stats improv;
    improv.attack    = Random::randint(per_level_min.attack, per_level_max.attack);
    improv.defense   = Random::randint(per_level_min.attack, per_level_max.attack);
    improv.spattack  = Random::randint(per_level_min.attack, per_level_max.attack);
    improv.spdefense = Random::randint(per_level_min.attack, per_level_max.attack);
    improv.speed     = Random::randint(per_level_min.attack, per_level_max.attack);
    improv.maxhp     = Random::randint(per_level_min.attack, per_level_max.attack);
    //Write improvements
    std::cout << name << " leveled up to level " << level << "!" << std::endl << std::endl;
    std::cout << name << " gained " << improv.attack << " attack." << std::endl;
    std::cout << name << " gained " << improv.defense << " defense." << std::endl;
    std::cout << name << " gained " << improv.spattack << " special attack." << std::endl;
    std::cout << name << " gained " << improv.spdefense << " special defense." << std::endl;
    std::cout << name << " gained " << improv.speed << " speed." << std::endl;
    std::cout << name << " gained " << improv.maxhp << " maximum HP." << std::endl << std::endl;
    //Add improvements to stats
    stats.attack += improv.attack;
    stats.defense += improv.defense;
    stats.spattack += improv.spattack;
    stats.spdefense += improv.spdefense;
    stats.speed += improv.speed;
    stats.maxhp += improv.maxhp;
    battle_stats.attack += improv.attack;
    battle_stats.defense += improv.defense;
    battle_stats.spattack += improv.spattack;
    battle_stats.spdefense += improv.spdefense;
    battle_stats.speed += improv.speed;
    battle_stats.maxhp += improv.maxhp;
    hp += improv.maxhp;
    //If necessary, (ask to) evolve
    if (level >= level_evolution and level_evolution != -1) {
        evolve();
    }
    //If necessary, (ask to) learn a new move
    std::map<int, std::vector<Move> >::iterator it = moveset.find(level);
    if (it != moveset.end()) { 
        for (int j = 0; j < (int)(it->second).size(); j++) learn_move((it->second)[j]);
    }
}

void Pokemon::learn_move(const Move& move) {
    std::string move_name = move.get_name();
    if (moves.size() < MAX_MOVES) { //Less than 4 moves, learns automatically.
        moves.push_back(move);
        std::cout << name << " learned " << move_name << "!" << std::endl;
    }
    else {
        std::cout << name << " wants to learn " << move_name << "." << std::endl;
        std::cout << "But " << name << " cannot learn more than " << MAX_MOVES << " moves." << std::endl;
        std::cout << "Do you want " << name << " to forget a move and learn " << move_name << "?" << std::endl;
        std::string query = "Enter 1, 2, 3 or 4 to forget the corresponding move. Enter 0 to not learn " + move_name + ": ";
        std::string error = "Oops. Enter a number between 0 and 4";
        std::cout << "Your moves are: " << std::endl 
        << "  1. " << moves[0].get_name() << std::endl
        << "  2. " << moves[1].get_name() << std::endl
        << "  3. " << moves[2].get_name() << std::endl
        << "  4. " << moves[3].get_name() << std::endl << std::endl;
        int choice = Input::read_int(0, 4, query, error);
        if (choice == 0) std::cout << name << " didn't learn " << move_name << "." << std::endl << std::endl;
        else {
            std::string old_move = moves[choice-1].get_name();
            moves[choice-1] = move;
            std::cout << "Puff. " << name << " forgot " << old_move << " and learned " << move_name << "!" << std::endl << std::endl;
        }
    }
}


//SHOWERS
void Pokemon::print_stats() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Total XP: " << xp << std::endl;
    std::cout << "XP to next level: ";
    if (level == 100) std::cout << "ALREADY MAX LEVEL" << std::endl;
    else std::cout << 5*level*(level+1) - xp << std::endl;
    
    std::cout << "Attack: " << stats.attack << std::endl;
    std::cout << "Defense: " << stats.defense << std::endl;
    std::cout << "Special Attack: " << stats.spattack << std::endl;
    std::cout << "Special Defense: " << stats.spdefense << std::endl;
    std::cout << "Speed: " << stats.speed << std::endl;
    std::cout << "Maximum HP: " << stats.maxhp << std::endl;

    for (int i = 0; i < (int)moves.size(); i++) {
        std::cout << std::endl << "Move #" << i+1 << std::endl;
        moves[i].print_stats();
    }
    std::cout << std::endl << std::endl;
}

void Pokemon::print_moves() const {
    std::cout << std::endl << "Moves: " << std::endl;
    for (int i = 0; i < (int)moves.size(); i++) {
        std::cout << "  " << i+1 << ". " << moves[i].get_name() << "   PP " << moves[i].get_pp() << "/" << moves[i].get_maxpp() << std::endl;
    }
    std::cout << std::endl;
}


