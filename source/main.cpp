///////////////////////////
// Program Name: FINAL PROJECT - BARE BONES 2
// Name: Andrew O'Kins
// Date: 11/20/2018
// Class and section: CS-172-1
////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <math.h>

#include "player.h"
#include "skeleton.h"

using namespace std;

// Creates (or rewrites) a text file that contains information on the all of the entities and then exits the program //
void SaveGame(string num, vector<Entity*> list){
  ofstream savefile;
  savefile.open("save" + num + ".txt");
  for (int i = 0; i < list.size(); i++){
    // If the entity is the player, write as a player //
    if (typeid(Player) == typeid(*list[i])){
      cout << "writing player\n";
      Player* p1 = dynamic_cast<Player*>(list[i]);
      savefile << p1 << endl;}

    if (typeid(Skeleton) == typeid(*list[i])){
      cout << "writing skeleton\n";
      Skeleton* s = dynamic_cast<Skeleton*>(list[i]);
      savefile << s << endl;
    }
  }
  savefile.close();
  for (int i = 0; i < list.size(); i++){
    delete list[i];
  }
  cout << "Game Saved";
  exit(0);
}

// Takes the entity vector and fills it with entities that were written on the text file //
void LoadGame(string name, vector<Entity*> &entities){
  // Open text file //
  ifstream loadfile;
  loadfile.open( name + ".txt");
  if (loadfile.fail()){
    cout << "Failed to open load file!";
    exit(0);}
  
  string word;
  string load_name;
  bool load_key;
  int load_hp;
  int load_x, load_y;

  while(!loadfile.eof()){
    loadfile >> word;
    // If it reached the last word (which would be a space due to how the entities are outputed), break since it'sn't reading new data //
    if (loadfile.eof()){break;}
    
    if (word == "Player"){
      // If the word is player, collect the data and push_back with a player entity //
      string load_name;
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_key;
      loadfile >> load_x >> load_y;
      entities.push_back(new Player(load_name, load_hp, load_x, load_y, load_key));
      cout << "Loaded Player entity...\n";
    }
    else if (word == "Skeleton"){
      // If the word is player, collect the data and push_back with a player entity //
      string load_name;
      loadfile >> load_name;
      loadfile >> load_hp;
      loadfile >> load_x >> load_y;
      entities.push_back(new Skeleton(load_name, load_hp, load_x, load_y));
      cout << "Loaded Skeleton entity...\n";
    }
  }
  cout << "Load complete.\n\n";
}

void NewGame(vector<Entity*> &entities){
  // Create player into the vector (No load game feature yet) //
    string name;
    cout << "Input a name for your character\n";
    cin >> name;
    entities.push_back(new Player(name, 10, 0,0, false));

    // Create a random number of skeletons and located randomly on the map//
    for (int i = 0; i < rand() % 10 + 1; i++){
      if (rand() % 4 == 1){
        entities.push_back(new Skeleton("Spooky", 5, (rand() % 20 + -20), (rand() % 20 + -20) ));
      }
      else if (rand() % 4 == 2){
        entities.push_back(new Skeleton("Scary", 5, (rand() % 20 ), (rand() % 20 + -20) ));
      }
      else {
        entities.push_back(new Skeleton("Scary", 5, (rand() % 20 ), (rand() % 20) ));
      }
    }
}

// This function is where the player inputs commands //
void PlayerTurn(vector<Entity*> entities){
      string command;
      string info;
      cout <<"Input command\n";
      cin >> command;
      cin >> info;
      if (command == "save"){
        SaveGame(info, entities);
      }

      if (command == "move"){   dynamic_cast<Player*>(entities[0])->move(info); }

      else if (command == "attack"){  dynamic_cast<Player*>(entities[0])->attack(); }

      else{ cout<< "Not a known command\n";}
}

// This function is where the skeleton determines which direction to go //
void SkeletonMovement(Skeleton* skeleton, Player* player){
  Location skel_loc = skeleton->getLOC();
  Location play_loc = player->getLOC();
  // If the skeleton and the player are at the same location, the skeleton doesn't need to move //
  if (!(skel_loc == play_loc)) {

    // If the x distance is greater than or equal for y, move focus onto the x direction //
    if ( abs(skel_loc.getLocX() - play_loc.getLocX()) >= abs(skel_loc.getLocY() - play_loc.getLocY()) ){
    
      // If moving east reduces the distance, move east.  If it doesn't, then moving west is the only logical option //
      if ( abs( abs( (skel_loc.getLocX())+1) - play_loc.getLocX() ) < abs( skel_loc.getLocX() - play_loc.getLocX() ) ){
        skeleton->move("east");
      }
      else ( skeleton->move("west") );
    }
    
    // If the y distance is greater than for x, move focus onto the y direction //
    else if ( abs(skel_loc.getLocX() - play_loc.getLocX() ) < abs( skel_loc.getLocY() - play_loc.getLocY() ) ){
    
      // Does the same thing as in terms of x, but instead with y //
      if ( abs( skel_loc.getLocY()+1 - play_loc.getLocY() ) < abs( skel_loc.getLocY() - play_loc.getLocY() ) ){
        skeleton->move("north");
      }
      else ( skeleton->move("south") );
    }

  }
}

// This function is where the "A.I." does its magic for the most part //
void SkeletonTurn(Skeleton* skeleton, Player* player){
  SkeletonMovement(skeleton, player);
  // I think this is broken :/ //
  skeleton->attack(player);
}



int main() {
    srand (time(NULL));
    vector<Entity*> entities;
    cout << "_BARE BONES 2_\n\n";
    while (true){
      char confirm;
      cout << "Load Game? y/n\n";

      cin >> confirm;
      if (confirm == 'y'){
        cout << "What is the name of your save? Don't include .txt\n";
        string saveName;
        cin >> saveName;
        LoadGame(saveName, entities);
        break;
      }
      else if (confirm == 'n'){
        NewGame(entities);
        break;
      }
      else {cout << "Not a correct response, type y or n\n"; continue;}
    }

    while (dynamic_cast<Player*>(entities[0])->getHP() > 0){
      // Player makes their turn, then checks to see if they got the key - need to make skeleton turn //
      PlayerTurn(entities);

     // A for loop where it gives each skeleton an individual turn //
      for (int i = 1; i < entities.size(); i++){
        SkeletonTurn( dynamic_cast<Skeleton*>(entities[i]), dynamic_cast<Player*>(entities[0]) );
      }
      cout << "_Player_\n";
      cout << entities[0]->getLOC() << endl;
      for (int i = 1; i < entities.size(); i++){
        cout << "_Skeleton_\n";
        cout << entities[i]->getLOC() << endl;
      }
    }

    cout << "You either just died, or you got the key... still need to implement...";
}