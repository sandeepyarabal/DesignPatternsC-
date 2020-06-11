
#include <iostream>

using namespace std;

enum  Direction { North, South, East, West };
class MapSite {
public:
    virtual void Enter() = 0;
};
class Room : public MapSite {
public:
    Room(int roomNo)
    {
        _roomNumber = roomNo;
    };
   
    void SetSide(int Dir, MapSite* wr)
    {
        _sides[Dir]= wr;
    };
    void Enter()
    {};
private:
    MapSite* _sides[4];
    int _roomNumber;
};
class Wall : public MapSite {
public:
    Wall() {};
    void Enter() {};
};
class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0) {};
    void Enter() {};
   
private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class Maze {
public:
    Maze() {};
    void AddRoom(Room*) {};
    Room* RoomNo(int) {} ;
private:
    // ...
};

int main()
{
    Maze* aMaze = new Maze;
    Room* r1 = new Room(1);
    Room* r2 = new Room(2);
    Door* theDoor = new Door(r1, r2);
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    r1->SetSide(North, new Wall);
    r1->SetSide(East, theDoor);
    r1->SetSide(South, new Wall);
    r1->SetSide(West, new Wall);
    r2->SetSide(North, new Wall);
    r2->SetSide(East, new Wall);
    r2->SetSide(South, new Wall);
    r2->SetSide(West, theDoor);
    cout << "hello world";
    return 0;
}

