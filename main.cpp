/*

This is a class that uses a hash table to store students

Last modified: 3/13/22

By: Kushal Rao with help from Nihal on the pulling lines from .txt files

*/

//Imports
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip> 
#include <fstream>

using namespace std;
struct Node{//Struct to hold values
  char firstName[100];
  char lastName[100];
  float gpa;
  int id;
  Node* next = NULL;
};
//Methods
Node** addStudents(Node** table, int &currentID, int &size);
void printAll(Node** table, int size);
void print(Node** table, int size);
void remove(Node** table, int size);
void reset(Node* table[], int size);
void printChain(Node* current);
Node** rehash(Node** table, Node** new_table, int &size, int currentID);
  
int main(){
  srand(time(0));
  bool quit = false;//bool to check when user wants to quit
  Node** table = new Node*[100];//Create intial table
  char input[7];
  int currentID = 0;//Start ID count at 0
  int size = 100;
  reset(table, size);//Set all values in the table to NULL
  while(!quit){
    cout << "Type a valid command(ADD, PRINT, DELETE, QUIT)" << endl;//Prompt user for input
    cin >> input;
    if(strcmp(input,"ADD") == 0){//If user wants to add students
      table = addStudents(table, currentID, size);
    }
    else if(strcmp(input,"PRINT") == 0){//If user wants to print a specific student
      print(table, size);
    }
    else if(strcmp(input,"DELETE") == 0){//If user wants to delete a specific student
      remove(table, size);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
  return 0;
}
Node** addStudents(Node** table, int &currentID, int &size){
  int students;//How many students user wants to add
  cout << "How many students do you want to add" << endl;
  cin >> students;
  for(int i = 0; i < students; i++){
    char input[100];
    char firstName[100];
    char lastName[100];
    fstream ffile("firstName.txt");
    fstream lfile("lastName.txt");
    int count;
    int num = (rand() % 20) + 1;
    int num2 = (rand() % 20) + 1;
    Node* newPoint = new Node();
    count = 1;
    //Get a first name
    while (ffile.getline(input,100, '\n')) {
      if (count == num) {
	strcpy(firstName,input);
	count++;
      }
      count++;
    }
    ffile.close();
    count = 1;
    //Get a last name
    while (lfile.getline(input,100, '\n')) {
      if (count == num2) {
	strcpy(lastName,input);
	count++;
      }
      count++;
    }
    lfile.close();
    //create random GPA
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    r *= 23;
    while(r > 4){
      r -= 4;
      while(r < 2){
	r += 1;
      }
    }
    //Add name and GPA to the node
    strcpy(newPoint->firstName, firstName);
    strcpy(newPoint->lastName, lastName);
    newPoint->id = currentID;
    newPoint->gpa = r;
    //Add student to the right place
    if(table[(currentID)%size] == NULL){//If there are no collisions
      table[(currentID%size)] = newPoint;//Add the new student to the hash table
    }
    else{
      if(table[(currentID)%size]->next == NULL){//If there is 1 collision
	table[currentID%size]->next = newPoint;//Add the new student to the hash table
      }
      else{
	if(table[(currentID)%size]->next->next == NULL){//If there is 2 collisions
	  table[currentID%size]->next->next = newPoint;//Add the new student to the hash table
	}
	else{//If there is 3 create new table
	  Node** new_table = new Node*[size*2];//New table twice the size
	  reset(new_table, size*2);//Set all new table values to NULL
	  table = rehash(table, new_table, size, currentID);//Add values to new table
	  table[currentID%size]->next = newPoint;//Add the new student to the hash table
	}
      }
    }
    currentID++;
  }
  return table;
}
//Method to rehash students into the new table
Node** rehash(Node** table, Node** new_table, int &size, int currentID){
  int oldSize = size;
  size = size*2;//Double size
  for(int i = 0; i < currentID; i++){//For all the nodes in old table
    if(i < oldSize){//If it is in the first node in the chain
      new_table[(i%size)] = table[(i)%oldSize];
      
    }
    else if(i < oldSize*2){//If it is the second node in the chain
      new_table[(i%size)] = table[(i)%oldSize]->next;
    }
    else{//If it is the last node in the chain
      new_table[i%size]->next = table[(i)%oldSize]->next->next;
    }
  }
  for(int i = size/2; i < size; i++){
    new_table[(i%size)]->next = NULL;//Set all values to NULL if it is needed
  }
  return new_table;
}
//Method to print all students
void printAll(Node** table, int size){
  //For all table slots, print entire chain
  for(int i = 0; i < size; i++){
    printChain(table[i]);
  }
  return;
}
//Method to print an individual student
void print(Node** table, int size){
  int i;
  Node* current;
  cout << "What is the ID# of the student you wish to print?" << endl;
  cin >> i;
  cin.clear();
  //Get right student
  if(table[i%size]->id == i){
    current = table[i%size];
  }
  else if(table[i%size]->next->id == i){
    current = table[i%size]->next;
  }
  else if(table[i%size]->next->next->id == i){
    current = table[i%size]->next->next;
  }
  //Print out name GPA and ID
    cout << current->firstName << " " << current->lastName << " GPA: " <<  fixed << setprecision(2) << current->gpa << " ID: " << current->id << endl;
}
//Reccursive method to print a chain
void printChain(Node* current){
  if(current != NULL){
    cout << current->firstName << " " << current->lastName << " GPA: " <<  fixed << setprecision(2) << current->gpa << " ID: " << current->id << endl;
    printChain(current->next);
  }
  return;
}
//Method to remove a specific student
void remove(Node** table, int size){
  int i;
  cout << "What is the ID# of the student you wish to remove?" << endl;
  cin >> i;
  cin.clear();
  //Find right student and over right it with what comes after
  if(table[i%size]->id == i){
    table[i%size] = table[i%size]->next;
  }
  else if(table[i%size]->next->id == i){
    table[i%size]->next = table[i%size]->next->next;
  }
  else if(table[i%size]->next->next->id == i){
    table[i%size]->next->next = NULL;
  }
  return;
}
//Method to set all values in a table to NULL
void reset(Node** table, int size){
  for(int i = 0; i < size; i++){
    table[i] = NULL;
  }
}
