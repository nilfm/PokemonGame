#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"

int main() {
    //Things to initialize
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    Item::initialize_items("Pokedata/Items.txt");
    
    //Welcome message
    std::cout << "Welcome to Pokegame" << std::endl << std::endl;
    
    //Show all saved games
    for (int i = 1; i <= 9; i++) {
        std::cout << "Game " << i << ": ";
        Gamesave save(i);
        if (save.is_empty()) { //file is empty
            std::cout << "Not started" << std::endl;
        }
        else {
            save.load();
            save.presentation();
        }
    }
    std::cout << std::endl;
    
    //Get input for which game to open
    std::string query = "Enter a number from 1 to 9 to choose the game to load. \nIf it's not started, a new game will start: ";
    std::string error = "Oops. Enter a number between 1 and 9."; 
    int choice = Input::read_int(1, 9, query, error);
    
    Gamesave gamesave(choice);
    Player player;
    //If new game
    if (gamesave.is_empty()) { 
        std::cout << "New game!" << std::endl;
        std::cout << "What's your name?" << std::endl;
        std::string name;
        std::cin >> name;
        std::cout << std::endl;
        player = Player(name);
        std::vector<Pokemon> team = player.get_team();
        std::cout << std::endl << "This is your team: " << std::endl << std::endl;
        for (int i = 0; i < 3; i++) {
            team[i].print_stats();
        }
    }
    //If continuing game
    else {
        std::cout << "Loading game " << choice << std::endl;
        gamesave.load();
        player = Player(gamesave);
        std::cout << "Hi, " << player.get_name() << std::endl << std::endl;
    }
    
    player.sort_team();
    
    //int trainers = player.get_trainers();
    //bool cont = true;
    //while (cont)
        //Menu:
        //  -Switch Pokemon around
        //  -Shop
        //  -See Pokemon stats
        //  -Next fight
        
        //When player picks next fight
        //trainers++;
        //Enemy enemy(trainers);
        //bool player_wins = fight(player, enemy); (STILL HAVE TO DECIDE WHETHER TO MAKE COMBAT CLASS)
        //if (player_wins) 
        //  -"yes you won!"
        //  -Pick a pokemon from enemy team (0 = dont want to pick any)
        //else
        //  -"oh no you lost"
        //  -cont = false;
        //  -register to high scores
    //
    
    //Save and quit
    gamesave.update(player.get_name(), player.get_money(), player.get_trainers(), player.get_team(), player.get_inventory());
    gamesave.save();
}
