#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip> 
#include <fstream>

using namespace std;

struct Node{
  char firstName[100];
  char lastName[100];
  float gpa;
  int id;
  Node* next = NULL;
};

void addStudent(Node* table[], int &currentID);

void print(Node* table[]);

void remove(Node* table[]);

void reset(Node* table[]);

int main(){
  bool quit = false;//bool to check when user wants to quit
  Node* table[100];
  char input[7];
  int currentID = 0;
  reset(table);
  ofstream firstNames;
  firstNames.open("Test.txt");
  char name[10];
  getline(firstNames, name);
  cout << name;
  firstNames.close();
  /*
  while(!quit){
    cout << "Type a valid command(ADD, PRINT, DELETE, QUIT)" << endl;//Prompt user for input
    cin >> input;
    if(strcmp(input,"ADD") == 0){//If user wants to add
      addStudent(table, currentID);
      cout << table[currentID-1]->firstName << endl;
    }
    else if(strcmp(input,"PRINT") == 0){//If user wants to print
      print(table);

    }
    else if(strcmp(input,"DELETE") == 0){//If user wants to delete
      remove(table);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
  */
  return 0;
}
void addStudent(Node* table[], int &currentID){
  Node* newPoint = new Node();
  strcpy(newPoint->firstName, "K");
  strcpy(newPoint->lastName, "R");
  newPoint->id = currentID;
  currentID++;
  newPoint->gpa = 4.12;
  table[currentID%100] = newPoint;
  currentID++;
  return;
}

void print(Node* table[]){
  return;
}

void remove(Node* table[]){
  return;
}

void reset(Node* table[]){
  for(int i = 0; i < sizeof(table)/sizeof(table[0]); i++){
    table[i] = NULL;
  }
}
