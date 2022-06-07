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
    Point(int x=0, int y=0){
        this->x = x;
        this->y = y;
    }
    string toString() const{
        string res = "";
        string s1 = "<Point[", s2 = ",", s3 = "]>";
        res += s1 + to_string(this->x) + s2 + to_string(this->y) + s3;
        return res;
    }

    int distanceTo(const Point & otherPoint) const{
        return round(sqrt(pow((this->x - otherPoint.x), 2) + pow((this->y - otherPoint.y), 2)));
    }
};
class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point & point=Point(), Node * next=NULL){
        this->point = point;
        this->next = next;
    }
    string toString() const{
        string res = "";
        string s1 = "<Node[<", s2 = "]>]>";
        res += s1 + point.toString() + s2;
        return res;
    }
};

class Path {
private:
    Node * head;
    Node * tail;
    int count;
    int length;

public:
    Path(){
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
        this->length = -1;
    }
    ~Path(){
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
        this->length = -1;
    }

    void addPoint(int x, int y){
        Point p = Point(x, y);
        Node* node = new Node(p, NULL);
        if (!head && !tail) head = tail = node;
        else{
            tail->next = node;
            tail = node;
        }
        this->count++;
        if (count == 1) this->length = 0;
        else{
            int len = 0;
            Node* temp = head;
            while (temp->next){
                int d = temp->point.distanceTo(temp->next->point);
                temp = temp->next;
                len += d;
            }
            this->length = len;
        }
    }
    string toString() const{
        string res = "";
        res += "<Path[count:" + to_string(this->count) + ",length:" + to_string(this->length) + ",[";
        Node* temp = head;
        string strPoint = "";
        while(temp){
            strPoint += temp->toString();
            if (!temp->next) strPoint += ",";
        }
        res += strPoint + "]]>";
        return res;
    }
    Point getLastPoint() const{
        Point res = tail->point;
        return res;
    }
    
    
};

class Character {
private:
    string name;
    Path * path;

public:
    Character(const string & name=""){
        this->name = name;
    }
    ~Character();

    string getName() const{
        return this->name;
    }
    void setName(const string & name){
        this->name = name;
    }

    void moveToPoint(int x, int y);
    string toString() const;
};

inline bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {

    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */