
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
        _sides[Dir] = wr;
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
    Room* RoomNo(int) {};
private:
    // ...
};

class MazeGame {
public:
    MazeGame() {};
    Maze* CreateMaze();
    virtual Maze* MakeMaze() const
    {
        return new Maze;
    }
    virtual Room* MakeRoom(int n) const
    {
        return new Room(n);
    }
    virtual Wall* MakeWall() const
    {
        return new Wall;
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const
    {
        return new Door(r1, r2);
    }
};


Maze* MazeGame::CreateMaze() {
    Maze* aMaze = MakeMaze();
    Room* r1 = MakeRoom(1);
    Room* r2 = MakeRoom(2);
    Door* theDoor = MakeDoor(r1, r2);
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    r1->SetSide(North, MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, MakeWall());
    r1->SetSide(West, MakeWall());
    r2->SetSide(North, MakeWall());
    r2->SetSide(East, MakeWall());
    r2->SetSide(South, MakeWall());
    r2->SetSide(West, theDoor);
    return aMaze;
}
int main()
{
    Maze* maze;
    MazeGame game;
    game.CreateMaze();
 
    cout << "hello world";
    return 0;
}

