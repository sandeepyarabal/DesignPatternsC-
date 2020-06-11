
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
class MazeBuilder {
public:
    virtual void BuildMaze() { }
    virtual void BuildRoom(int room) { }
    virtual void BuildDoor(int roomFrom, int roomTo) { }
    virtual Maze* GetMaze() { return 0; }
//protected:
    MazeBuilder() {};
};


class MazeGame {
public:
    MazeGame() {};
    Maze* CreateMaze(MazeBuilder& builder);

private:

};


Maze* MazeGame::CreateMaze(MazeBuilder& builder) {
    builder.BuildMaze();
    builder.BuildRoom(1);
    builder.BuildRoom(2);
    builder.BuildDoor(1, 2);
    return builder.GetMaze();
}
int main()
{
    Maze* maze;
    MazeGame game;
    MazeBuilder builder;
    game.CreateMaze(builder);
    maze = builder.GetMaze();
    cout << "hello world";
    return 0;
}

