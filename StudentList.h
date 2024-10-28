#include <iostream>
#include <string>
using namespace std;

// Implement the "StudentList" data structure with a doubly linked list implementation.

class Student {
	public:
		string name;
		int id;
		float GPA;

		Student(string inName = "nobody", int inId = -1, float inGPA = 0.0) {
			name = inName;
			id = inId;
			GPA = inGPA;
		}
};

class Node {
public:
	Student data;
	Node *next;
	Node *prev;

	Node(Student x, Node *nextPtr = nullptr, Node *prevPtr = nullptr)
		: data(x), next(nextPtr), pre(prevPtr){}
};

class StudentList {
private:
	Node *head;
	Node *tail;
	int numStudents;

public:
		StudentList() : head(nullptr), tail(nullptr), numStudents(0){}
		int listSize() {
			return numStudents;
		}


		void addFront(Student s) {
			Node* newNode = new Node(s, head, nullptr);
			if(head != nullptr) {
				head-> prev = newNode;
			} else {
				tail = newNode;
			}
			head = newNode;
			numStudents++;
		}
		void addBack(Student s) {
			Node* newNode = new Node(s, nullptr, tail);
			if(tail != nullptr) {
				tail -> next = newNode;
			} else {
				head = newNode;
			}
			tail = newNode;
			numStudents++;
		}
		void printList() {
			Node* current = head; 
			while (current != nullptr) {
				cout<< "Name: " << current -> data.name << ", ID: " << current -> data.id << ", GPA: " << current -> data.GPA << endl;
				current = current -> next;
			}
		}
		void popFront() {
			if(head == nullptr) return;
			Node* temp = head;
			head = head -> next;
			if (head != nullptr) {
				head -> prev = nullptr;
			} else {
				tail = nullptr;
			}
			delete temp;
			numStudents--;
		}
		void popBack() {
			if (tail == nullptr) return;
			Node* temp = tail;
			tail = tail -> prev;
			if(tail != nullptr) {
				tail -> next = nullptr;
			} else {
				head = nullptr;
			}
			delete temp;
			numStudents--;
		}
		void insertStudent(Student s, int index) {
			if (index < 0 || index > numStudents) return;
			if (index == 0) {
				addFront(s);
				return;
			} else if (index == numStudents) {
				addBack(s);
				return;
			}
			Node* current = head;
			for(int i = 0; i < index - 1; i++) {
				current = current -> next;
			}
			Node* newNode = new Node(s, current -> next, current);
			current -> next -> prev = newNode;
			current -> next = newNode;
			numStudents++;
		}
		Student retrieveStudent(int idnumber) {
			Node* current = head;
			while(current != nullptr) {
				if (current -> data.id == idnumber) {
					return current -> data;
				}
				current = current -> next;
			}
			cout << "Student with ID " << idnumber << " not found." << endl;
			return Students();
		}
		void removeStudentById(int idnumber){
			Node* current = head; 
			while(current != nullptr) {
				if(current -> data.id == idnumber) {
					if(current -> prev != nullptr) {
						current -> prev -> next = current -> next;
					} else {
						head = current -> next;
					}
					if (current -> next != nullptr) {
						current -> next -> prev = current -> prev;
					} else {
						tail = current -> prev;
					}
					delete current;
					numStudents--;
					return;
			}
			current = current -> next;

		}
	}
		void updateGPA(int idnumber, float newGPA) {
			Node* current = head;
			while (current != nullptr) {
				if (current -> data.id == idnumber) {
					current -> data.GPA = newGPA;
					return;
				}
				current = current-> next;
			}
		}
		void mergeList(StudentList &otherlist) {
			if (otherlist.head == nullptr) return;
			if (head == nullptr) {
				head = otherlist.head;
				tail = otherlist.tail;
			} else {
				tail -> next = otherlist.head;
				otherlist.head-> prev = tail;
				tail = otherlist.tail;
			}
			numStudents += otherlist.numStudents;
			otherlist.head = otherlist.tail = nullptr;
			otherlist.numStudents = 0;
		}
		StudentList honorRoll(float minGPA) {
			StudentList honorList; 
			Node* current = head;
			while (current != nullptr) {
				if (current -> data.GPA >= minGPA) {
				honorList.addBack(current-> data);
			}
			current = current -> next;

		}
		return honorList;
	}	
};