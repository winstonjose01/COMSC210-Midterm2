#include <iostream>
#include <vector>
#include <fstream>
#include <random>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//Function prototype
vector <string> read_names(string &);

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t" << current->data << "\n";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    string get_tail_data(){
        if (tail){
            return tail->data;
        }
        return (" ");
    }
};
// This function reads names from names.txt
// arguments: a string (filename)
// returns: a vector with names
vector <string> read_names(string filename){
    ifstream file (filename);   // Input filestream
    vector <string> names;      // Initialize a vector to store names
    string name;        
    if(!file){                  // Check if the file was succesfully opened
        cout << "Cound not open the file" << endl;
    }
    while (getline(file,name)){     //Read lines from the file until the end of file
        names.push_back(name);      // Add each name to the vector
    }
    return names;
}

int main() {
    //cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList line;
    vector <string> names = read_names("names.txt");
    int time_step = 1;

    // Add 5 customers when the store opens
    cout << "Store opens: " << endl;
    for (int i = 0; i < 5 && i < names.size() ; i++){
        line.push_back(names[i]);
        cout << "\t" << names[i] << " joined the line" << endl;
    }
    cout << "Resulting line: " << endl;
    line.print();

    srand(time(0)); // Seed the random generator
    // Simulate the steps
    while (time_step <= 10) {
        cout << "Time step #" << time_step << ":" << endl;

        int action = rand() % 100;  // Random number between 0-99

        // A customer being helped at the beginning of the line(40%)
        if (action < 40){
            line.pop_front();
        }
        // A new customer joining the end of the line(60%)
        else if(action < 100){
            if (!names.empty()){
                string new_customer = names[rand() % names.size()]; // Pick a name
                line.push_back(new_customer);
                cout << new_customer << " joined the line" << endl;

            }
        }
        if (rand() % 100 < 20){
            cout << line.get_tail_data() << " is leaving the line";
            line.pop_back();
        }
      
    }

    return 0;
}