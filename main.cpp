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

void print(Node* table[], int size);

void remove(Node* table[]);

void reset(Node* table[], int size);

void printChain(Node* current);
int main(){
  bool quit = false;//bool to check when user wants to quit
  Node* table[100];
  char input[7];
  int currentID = 0;
  int size = sizeof(table)/sizeof(table[0]);
  reset(table, size);
  /*
  ofstream firstNames;
  firstNames.open("Test.txt");
  char name[10];
  getline(firstNames, name);
  cout << name;
  firstNames.close();
  */
  
  while(!quit){
    cout << "Type a valid command(ADD, PRINT, DELETE, QUIT)" << endl;//Prompt user for input
    size = sizeof(table)/sizeof(table[0]);
    cout << size << endl;
    cin >> input;
    if(strcmp(input,"ADD") == 0){//If user wants to add
      addStudent(table, currentID);
    }
    else if(strcmp(input,"PRINT") == 0){//If user wants to print
      cout << sizeof(table) << endl;
      print(table, size);
    }
    else if(strcmp(input,"DELETE") == 0){//If user wants to delete
      remove(table);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
 
  return 0;
}
void addStudent(Node* table[], int &currentID){
  Node* newPoint = new Node();
  strcpy(newPoint->firstName, "K");
  strcpy(newPoint->lastName, "R");
  newPoint->id = currentID;
  newPoint->gpa = 4.12;
  table[(currentID%100)] = newPoint;
  currentID++;
  return;
}

void print(Node* table[], int size){
  for(int i = 0; i < size; i++){
    printChain(table[i]);
  }
  return;
}

void printChain(Node* current){
  if(current != NULL){
    cout << "here" << endl;
    cout << current->firstName << " " << current->lastName << endl;
    printChain(current->next);
  }
  return;
}


void remove(Node* table[]){
  return;
}

void reset(Node* table[], int size){
  for(int i = 0; i < size; i++){
    table[i] = NULL;
  }
}
