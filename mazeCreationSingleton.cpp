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
class MazeFactory {
public:
    static MazeFactory* Instance() {
        if (_instance == 0) {
            _instance = new MazeFactory;
        }
        return _instance;
    };
   
    virtual Maze* MakeMaze() const
    {
        return new Maze;
    }
    virtual Wall* MakeWall() const
    {
        return new Wall;
    }
    virtual Room* MakeRoom(int n) const
    {
        return new Room(n);
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const
    {
        return new Door(r1, r2);
    }

protected:
    MazeFactory() {};
private:
    static MazeFactory* _instance;
};
MazeFactory* MazeFactory::_instance = 0;

class MazeGame {
public:
    MazeGame() {};
    Maze* CreateMaze(MazeFactory& factory);

private:

};
Maze* MazeGame::CreateMaze(MazeFactory& factory)
{
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);
    Door* aDoor = factory.MakeDoor(r1, r2);
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    r1->SetSide(North, factory.MakeWall());
    r1->SetSide(East, aDoor);
    r1->SetSide(South, factory.MakeWall());
    r1->SetSide(West, factory.MakeWall());
    r2->SetSide(North, factory.MakeWall());
    r2->SetSide(East, factory.MakeWall());
    r2->SetSide(South, factory.MakeWall());
    r2->SetSide(West, aDoor);
    return aMaze;
}
int main()
{
    MazeGame game; 
    MazeFactory* factory = MazeFactory::Instance();
    game.CreateMaze(*factory);
    cout << "hello world";
    return 0;
}