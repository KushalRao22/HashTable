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

void addStudents(Node* table[], int &currentID, int size);

void print(Node* table[], int size);

void remove(Node* table[]);

void reset(Node* table[], int size);

void printChain(Node* current);

Node** rehash(Node* table[], Node* new_table[], int &size, int currentID);
  
int main(){
  srand(time(0));
  bool quit = false;//bool to check when user wants to quit
  Node* table[10];
  char input[7];
  int currentID = 0;
  int size = sizeof(table)/sizeof(table[0]);
  cout << size << endl;
  reset(table, size);
  while(!quit){
    cout << "Type a valid command(ADD, PRINT, DELETE, QUIT)" << endl;//Prompt user for input
    size = sizeof(table)/sizeof(table[0]);
    //cout << size << endl;
    cin >> input;
    if(strcmp(input,"ADD") == 0){//If user wants to add
      addStudents(table, currentID, size);
    }
    else if(strcmp(input,"PRINT") == 0){//If user wants to print
      //cout << sizeof(table) << endl;
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
void addStudents(Node* table[], int &currentID, int size){
  int students;
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
    while (ffile.getline(input,100, '\n')) {
      if (count == num) {
	strcpy(firstName,input);
	count++;
      }
      count++;
    }
    ffile.close();
    count = 1;
    while (lfile.getline(input,100, '\n')) {
      if (count == num2) {
	strcpy(lastName,input);
	count++;
      }
      count++;
    }
    lfile.close();
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    r *= 23;
    while(r > 4){
      r -= 4;
      while(r < 2){
	r += 1;
      }
    }
    strcpy(newPoint->firstName, firstName);
    strcpy(newPoint->lastName, lastName);
    newPoint->id = currentID;
    newPoint->gpa = r;
    if(table[(currentID)%size] == NULL){
      table[(currentID%size)] = newPoint;
    }
    else{
      if(table[(currentID)%size]->next == NULL){
	table[currentID%size]->next = newPoint;
      }
      else{
	if(table[(currentID)%size]->next->next == NULL){
	  table[currentID%size]->next->next = newPoint;
	}
	else{
	  Node* new_table[size*2];
	  reset(new_table, size*2);
	  table = rehash(table, new_table, size, currentID);
	  cout << endl << endl << endl << endl << endl;
	  table[currentID%size]->next = newPoint;
	  print(table, size);
	}
      }
    }
    currentID++;
  }
  
  return;
}

Node** rehash(Node* table[], Node* new_table[], int &size, int currentID){
  int oldSize= size;
  size = size*2;
  for(int i = 0; i < currentID; i++){ 
    
    if(i < oldSize){
      cout << "here" << endl;
      new_table[(i%size)] = table[(i)%oldSize];
    }
    else if(i < oldSize*2){
      cout << "here2" << endl;
	new_table[(i%size)] = table[(i)%oldSize]->next;
    }
    else{
      cout << i << endl;
      new_table[i%size]->next = table[(i)%oldSize]->next->next;
    }
    if(i > oldSize){
      new_table[(i%size)]->next = NULL;
    }
  }
  print(new_table, size);
  return new_table;
}

void print(Node* table[], int size){
  for(int i = 0; i < size; i++){
    printChain(table[i]);
  }
  return;
}

void printChain(Node* current){
  if(current != NULL){
    //cout << "here" << endl;
    cout << current->firstName << " " << current->lastName << " GPA: " << current->gpa << " " << current->id << endl;
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
