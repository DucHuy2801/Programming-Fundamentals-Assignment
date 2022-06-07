/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0) {
        this->x = x, this->y = y;
    }
    string toString() const {
        string x = to_string(this->x);
        string y = to_string(this->y);
        string res = "<Point[" + x + "," + y + "]>";
        return res;
    }

    int distanceTo(const Point& otherPoint) const {
        return ceil(sqrt((pow((this->x - otherPoint.x), 2) + pow((this->y - otherPoint.y), 2))));
    }
};
class Node {
private:
    Point point;
    Node* next;

    friend class Path;

public:
    Node(const Point& point = Point(), Node* next = NULL) {
        this->point = point, this->next = next;
    }
    string toString() const {
        string res = "<Node[" + this->point.toString() + "]>";
        return res;
    }
};

class Path {
private:
    Node* head;
    Node* tail;
    int count;
    int length;

public:
    Path() {
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
        this->length = -1;
    }
    ~Path() {
        if (head == tail) {
            head = tail = NULL;
        }
        else {
            while (this->head) {
                Node* temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
            head = tail = NULL;
        }
        this->count = 0;
        this->length = -1;
    }
    int calcLength(Node* node){
        if (this->count == 1) this->length = 0;
        else {
            int len = 0;
            Node* temp = head;
            while (temp->next) {
                int d = temp->point.distanceTo(temp->next->point);
                len += d;
                temp = temp->next;
            }
            this->length = len;
        }
        return this->length;
    }
    void addPoint(int x, int y) {
        Point p = Point(x, y);
        Node* node = new Node(p, NULL);
        if (!head && !tail) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
        this->count++;
        if (this->count == 1) this->length = 0;
        else this->length = calcLength(node);
    }
    string updateToStringNode() const{
        string res = "";
        if (this->count == 0) return res;
        else if (this->count == 1) {
            res = this->head->toString();
        }
        else {
            Node* node = this->head;
            for (int i = 1; i < this->count; i++) {
                res += node->toString() + ",";
                node = node->next;
            }
            res += node->toString();
        }
        return res;
    }
    string toString() const {
        string res = "<Path[count:" + to_string(this->count) + ",length:" + to_string(this->length) + ",[";
        string strPoint = this->updateToStringNode();
        res += strPoint + "]]>";
        return res;
    }
    Point getLastPoint() const {
        return this->tail->point;
    }
    int getLength() const{
        return this->length;
    }
};

class Character {
private:
    string name;
    Path * path;

public:
    Character(const string & name=""){
        this->name = name;
        this->path = new Path();
    }
    ~Character(){
        this->name = ""; 
        this->path->~Path();
    }

    string getName() const{
        return this->name;
    }
    void setName(const string & name){
        this->name = name;
    }

    void moveToPoint(int x, int y){
        this->path->addPoint(x, y);
    }
    string toString() const{
        string result = "<Character[name:" + this->name + ",path:" + this->path->toString() + "]>";
        return result;
    }
    Point getCurrentPosition() const{
        return this->path->getLastPoint();
    }
    int getLength() const{
        return this->path->getLength();
    }
};

bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {
    int l1 = chWatson.getLength(), l2 = chMurderer.getLength();
    if (l1 - l2 <= maxLength) {
        Point p1 = chMurderer.getCurrentPosition();
        Point p2 = chWatson.getCurrentPosition();
        outDistance = p1.distanceTo(p2);
        if (outDistance <= maxDistance) return true;
        else return false;
    }
    else{
        outDistance = -1;
        return false;
    }
    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */