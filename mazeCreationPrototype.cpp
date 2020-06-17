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
    Room(const Room&);

    void SetSide(int Dir, MapSite* wr)
    {
        _sides[Dir] = wr;
    };
    virtual Room* Clone() const;
    void Enter()
    {};
private:
    MapSite* _sides[4];
    int _roomNumber;
};

Room::Room(const Room& other) {
    _roomNumber = other._roomNumber;

}

Room* Room::Clone() const {
    return new Room(*this);
}
class Wall : public MapSite {
public:
    Wall() {};

    void Enter() {};
};

class Door : public MapSite {
public:
    Door() {};
    Door(Room* r1, Room* r2) {
        _room1 = r1;
        _room2 = r2;
    }
    Door(const Door&);
    virtual void Initialize(Room*, Room*);
    virtual Door* Clone() const;
    virtual void Enter() {};

private:
    Room* _room1;
    Room* _room2;

};

Door::Door(const Door& other) {
    _room1 = other._room1;
    _room2 = other._room2;
}
void Door::Initialize(Room* r1, Room* r2) {
    _room1 = r1;
    _room2 = r2;
}
Door* Door::Clone() const {
    return new Door(*this);
}

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
    MazeFactory() {};
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
};

class MazePrototypeFactory : public MazeFactory {
public:
    MazePrototypeFactory(  Door* d)
    {
        _prototypeDoor = d;
    }

    Door* MakeDoor(Room*, Room*);
private:

    Door* _prototypeDoor;
};


Door* MazePrototypeFactory::MakeDoor(Room* r1, Room* r2) {
    Door* door = _prototypeDoor->Clone();
    door->Initialize(r1, r2);
    return door;
}

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
    MazeFactory factory;
    game.CreateMaze(factory);


    /// <summary>
    /// not finished yet ,kaam abi baki hai
    /// </summary>
    /// <returns></returns>
    MazePrototypeFactory simpleMazeFactory(  new Door);
   // Maze* maze = game.CreateMaze(simpleMazeFactory);
    cout << "hello world";
    return 0;
}