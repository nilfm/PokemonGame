# PokemonGame

Attempt to make a Pokemon copy where you can take a team and fight through trainers until you lose.

### Classes:

Pokedex: Has info about every Pokemon

Pokebase: Has info about a specific Pokemon in order to generate one

Pokemon: Has an instance of a Pokemon, with its level, xp, etc

Move: Has info about an instance of a Pokemon move

Type: Has all the info related to types (fire, water, etc)

Input: Has all the necessary input checking mechanisms

Player: Has info about a player's Pokemon team, items, and actions he can do with them

Gamesave: Has all the info that needs to be saved and loaded back

Enemy: Has all the info and functions required for a bot to play against you

### TODO

+ Make txt files for every Pokemon  
+ Completely re-do that piece of trash Combat class
+ Make it possible to get stunned/burned/poisoned
+ Redo Enemy to inherit from Player and be called AI (since all it would have is AI functions)  

### BUGS

+ Charmander/Charmeleon sometimes do like 2k damage with Ember (hasn't happened in a while)  
+ PP not going down (maybe references will work)  
