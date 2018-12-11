///////////////////////////
// Program Name: FINAL PROJECT - BARE BONES 2
// Name: Andrew O'Kins
// Date: 11/20/2018
// Class and section: CS-172-1
////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <math.h>

#include "player.h"
#include "skeleton.h"
#include "item.h"

using namespace std;

// Sets up the walls of the map and randomly places the car somewhere on the map (these two objects are placed as the first two objects in the vector) //
void BuildMap(vector<Item*> &objects){
  objects.push_back(new Item('C', true, new Location( rand() % 20, rand() % 20) ));
  objects.push_back(new Item('K', true, new Location( rand() % 20, rand() % 20) ));
  // Creates the vertical sides of the map box //
  for (int y = 0; y <= 20; y++){
    objects.push_back(new Item('W', false, new Location( -1,y )));
    objects.push_back(new Item('W', false, new Location(21,y )));
  }
  // Creates the horizontal sides of the map box //
  for (int x = 0; x <= 20; x++){
    objects.push_back(new Item('W', false, new Location( x,-1 )));
    objects.push_back(new Item('W', false, new Location( x,21 )));
  }
}

// A function to just cout a bunch of new lines so that the screen gets a bit cleaner //
void ClearScreen(){
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

// Displays the entities and key and car //
void Display(vector<Entity*> entities, vector<Item*> items){
  // Show all of the locations for all of the entities
  ClearScreen();
  for (int i = 0; i < entities.size(); i++){
    cout << entities[i]->getName() << endl;
    cout << entities[i]->getLOC() << endl;
  }

  // Show location of key and car //
  for (int i = 0; i < items.size(); i++){
    if (items[i]->getType() == 'K'){
      cout << "Key \n" << items[i]->getLOC() << endl;
    }
    else if (items[i]->getType() == 'C'){
      cout << "Car \n" << items[i]->getLOC() << endl;
    }
  }
}

// Sets up a new game //
void NewGame(vector<Entity*> &entities, vector<Item*> &items){
  // Create player into the vector (No load game feature yet) //
    string name;
    cout << "Input a name for your character\n";
    cin >> name;
    entities.push_back(new Player(name, 4, new Location(rand() % 20, rand() % 20), false));
    cout << "Added player\n";
    // Create a random number of skeletons and located randomly on the map//
    for (int i = 0; i < rand() % 5 + 1; i++){
      if (rand() % 4 == 1){
        entities.push_back(new Skeleton("Spooky", 1, new Location((rand() % 20), (rand() % 20)) ) );
        cout << "Added a skeleton\n";
      }
      else if (rand() % 4 == 2){
        entities.push_back(new Skeleton("Scary", 1, new Location( (rand() % 20), (rand() % 20)) ) );
        cout << "Added a skeleton\n";
      }
      else {
        entities.push_back(new Skeleton("Skeleton", 1, new Location((rand() % 20), (rand() % 20)) ) );
        cout << "Added a skeleton\n";
      }
    }
    // Since this is a new game, has to build the map//
    BuildMap(items);
    Display(entities, items);
}

// Takes the entity vector and item vector and fills them up with the information that was written on the text file //
void LoadGame(string name, vector<Entity*> &entities, vector<Item*> &items){
  // Open an input text file based on the given name //
  ifstream loadfile;
  loadfile.open( name + ".txt");
  // If no load file exists, exit the program //
  if (loadfile.fail()){
    cout << "Failed to open load file!";
    exit(0);
  }
  // Setup all of the variables that are to be used to acquire the data when the reading begins //
  string word;
  string load_name;
  bool load_key;
  int load_hp;
  int load_x, load_y;
  char load_item_type;
  int load_traverse;
  int item_c = 1;
  int skel_c = 1;
  // Go through the file //
  while(loadfile >> word && !loadfile.eof()){
  // If it found an applicable word and hasn't reached the end of the file, read more and create the things //
    // If the word is player, collect the data and push_back with a player entity //  
    if (word == "Player") {
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_key;
      loadfile >> load_x >> load_y;
      entities.push_back(new Player(load_name, load_hp, new Location(load_x, load_y), load_key));
      cout << "Loaded Player entity...\n";
    }
    // If the word is skeleton, collect the data and push_back with a skeleton entity //
    else if (word == "Skeleton") {
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_x >> load_y;
      entities.push_back(new Skeleton(load_name, load_hp, new Location(load_x, load_y)));
      cout << "Loaded Skeleton entity #" << skel_c << endl;
    }
    // If the word is item, collect the data and add to the item vector //
    else if (word == "Item") {
      loadfile >> load_item_type;
      loadfile >> load_traverse;
      loadfile >> load_x >> load_y;
      if (load_traverse == 0){
        items.push_back(new Item(load_item_type, false, new Location(load_x, load_y)));}
      else if (load_traverse == 1){
        items.push_back(new Item(load_item_type, true , new Location(load_x, load_y)));}
      cout << "Loaded Item #" << item_c << endl;
      item_c++;
    }
  }
// Now that it is all loaded, close the file //
  loadfile.close();
  cout << "Load complete.\n\n";
  Display(entities, items);
}

// For when closing the program, deletes all of the pointers in the vectors //
void DeleteInfo(vector<Entity*> &entities, vector<Item*> &items){
  for (int i = 0; i < entities.size(); i++){
    delete entities[i];
  }
  for (int i = 0; i < items.size(); i++){
    delete items[i];
  }
}

// Creates (or rewrites) a text file that contains information on the all of the entities and then exits the program //
void SaveGame(string num, vector<Entity*> entities, vector<Item*> items){
  ofstream savefile;
  savefile.open("save" + num + ".txt");
  // Write down all of the entities //
  for (int i = 0; i < entities.size(); i++){
    // If the entity is the player, write as a player (differentiated because the player has unique properties) //
    if (typeid(Player) == typeid(*entities[i])){
      cout << "writing player\n";
      savefile << *dynamic_cast<Player*>(entities[i]) << endl;}
    // If the entity is a skeleton, write as a skeleton //
    else if (typeid(Skeleton) == typeid(*entities[i])){
      cout << "writing skeleton\n";
      savefile << *dynamic_cast<Skeleton*>(entities[i]) << endl;
    }
  }
  // Now write all of items (done in seperate loop so that it is clearly seperated) //
  for (int i = 0; i < items.size(); i++){
    cout << "writing item #" << i << endl;
    savefile << *items[i] << endl;
  }
  // Now close the file and delete the pointers of the vectors before exiting the program //
  savefile.close();
  DeleteInfo(entities, items);
  // With saving done, exit the game //
  cout << "Game Saved";
  exit(0);
}

// This function is where the skeleton determines which direction to go //
void SkeletonMovement(Skeleton* skeleton, Player* player, vector<Item*> items){
  // If the skeleton and the player are at the same location or one away or the distance in x and y is greater than 5, the skeleton doesn't move //
  if ((!(skeleton->getLOC() == player->getLOC()) &&
     (!(abs(skeleton->getLOC().getLocX() - player->getLOC().getLocX()) == 1) && !(abs(skeleton->getLOC().getLocY() - player->getLOC().getLocY()) == 1))) && (
     (abs(skeleton->getLOC().getLocX() - player->getLOC().getLocX()) < 5) ||
     (abs(skeleton->getLOC().getLocY() - player->getLOC().getLocY()) < 5) )) {
    // If the x distance is greater than or equal for y, move focus onto the x direction //
    if ( abs(skeleton->getLOC().getLocX() - player->getLOC().getLocX()) >= abs(skeleton->getLOC().getLocY() - player->getLOC().getLocY()) ){
      // If moving east reduces the distance, move east.  If it doesn't, then moving west is the only logical option //
      if ( abs( abs( (skeleton->getLOC().getLocX())+1) - player->getLOC().getLocX() ) < abs( skeleton->getLOC().getLocX() - player->getLOC().getLocX() ) ){
        skeleton->move("east", items);
      }
      else ( skeleton->move("west", items) );
    }
    // If the y distance is greater than for x, move focus onto the y direction //
    else if ( abs(skeleton->getLOC().getLocX() - player->getLOC().getLocX() ) < abs( skeleton->getLOC().getLocY() - player->getLOC().getLocY() ) ){
      // Does the same thing as in terms of x, but instead with y //
      if ( abs( skeleton->getLOC().getLocY()+1 - player->getLOC().getLocY() ) < abs( skeleton->getLOC().getLocY() - player->getLOC().getLocY() ) ){
        skeleton->move("north", items);
      }
      else ( skeleton->move("south", items) );
    }
  }
}

// Where the program goes when the player has achieved the win condition //
void WinGame(vector<Entity*> entities, vector<Item*> items){
  cout << "Congrats " << entities[0]->getName() << "! You successfully escaped the map!\n";
  cout << "There is absolutely no reward for beating the game y'know!\nGoodbye\n";
  DeleteInfo(entities, items);
  exit(0);
}

// This function is where the player inputs commands //
void PlayerTurn(vector<Entity*> entities, vector<Item*> items){
      string command;
      string info;
      cout <<"Input command\n";
      cin >> command;
      if (command == "save"){
        cin >> info;
        SaveGame(info, entities, items);
      }
      else if (command == "move"){
        cin >> info;
        dynamic_cast<Player*>(entities[0])->move(info, items); }

      else if (command == "attack"){      
        cin >> info;
        dynamic_cast<Player*>(entities[0])->attack(info, entities); }

      else if (command == "pickup"){
        // If the command is pickup, go through all of the items to find and see if the key is located where the player is, if yes then set player key to true and erase the key from items list //
        for (int i = 0; i < items.size(); i++){
          if (entities[0]->getLOC() == items[i]->getLOC() && items[i]->getType() == 'K'){
            dynamic_cast<Player*>(entities[0])->found_key();
            delete items[i];
            items.erase(items.begin() + i);
          }
        }
      }
      else if (command == "exit"){
        for (int i = 0; i < items.size(); i++){
          if (entities[0]->getLOC() == items[i]->getLOC() && dynamic_cast<Player*>(entities[0])->has_key()){
            WinGame(entities, items);
          }
        }
      }
      else {cout<< "Not a known command\n";}
}

// This function is where skeletons are called for attack and movement //
void SkeletonTurn(Skeleton* skeleton, Player* player, vector<Item*> items) {
  skeleton->attack(player);
  SkeletonMovement(skeleton, player, items);
}

int main() {
  // State the vectors and random seed //
    srand (time(NULL));
    vector<Entity*> entities;
    vector<Item*> items;
  // Title Screen //
    cout << "||||||    ||||   ||||||   ||||||   " << endl;
    cout << "||   ||  ||  ||  ||   ||  ||       " << endl;
    cout << "||||||   ||||||  ||||||   ||||||   " << endl;
    cout << "||   ||  ||  ||  ||  ||   ||       " << endl;
    cout << "||||||   ||  ||  ||   ||  ||||||   " << endl;
    cout << "  ||||||    ||||   ||   ||  ||||||  |||||  " << endl;
    cout << "  ||   ||  ||  ||  |||  ||  ||      ||" << endl;
    cout << "  ||||||   ||  ||  |||| ||  ||||||  |||||" << endl;
    cout << "  ||   ||  ||  ||  || ||||  ||         ||" << endl;
    cout << "  ||||||    ||||   ||  |||  ||||||  |||||" << endl;
    cout << "       |||||| ||||||    by Andrew O'Kins" << endl;
    cout << "         ||     ||     " << endl;
    cout << "         ||     ||     " << endl;
    cout << "         ||     ||     " << endl;
    cout << "       |||||| ||||||   " << endl << endl;
    
    while (true){
      // Prompt to load a game, if not it will automatically create a new game //
      char confirm;
      cout << "Load Game? (y/n)\n";
      cin >> confirm;
      if (confirm == 'y'){
        cout << "What is the name of your save? (Don't include .txt)\n";
        string saveName;
        cin >> saveName;
        LoadGame(saveName, entities, items);
        break;
      }
      else if (confirm == 'n'){
        NewGame(entities, items);
        break;
      }
      else {cout << "Not a correct response, type y or n\n"; continue;}
    }
    // Loops so that the game keeps going until there is a break or it exits //
    while (true){
      // The player's turn before the skeletons //
      PlayerTurn(entities, items);
      // A for loop where it gives each skeleton an individual turn //
      for (int i = 1; i < entities.size(); i++){
        // If the skeleton doesn't have positive hp, then erase that object //
        if(dynamic_cast<Skeleton*>(entities[i])->getHP() <= 0){
          delete entities[i];
          entities.erase( entities.begin() + i );
        }
        else SkeletonTurn( dynamic_cast<Skeleton*>(entities[i]), dynamic_cast<Player*>(entities[0]), items );
      }
      // Show the entities and items after all of the turns //
      Display(entities, items);
      
      // The health is not positive, break the loop and enter the lose ending that is at the end of main() //
      if (dynamic_cast<Player*>(entities[0])->getHP() <= 0){
        ClearScreen();
        break;
      }
    }

    // If the player "died", then they get this as the ending //
    cout << "  GAME OVER\n YOU GOT SPOOKED TO DEATH\n\n";
    if (dynamic_cast<Player*>(entities[0])->has_key()){
      cout << dynamic_cast<Player*>(entities[0])->getName() << " did get the key though!\n";
    }
    else {cout << dynamic_cast<Player*>(entities[0])->getName() << " didn't even get the key!\n";}
    DeleteInfo(entities, items);
    exit(0);
}