
//mantosh4u design - pattern teken from net

#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>
#include <list>
using namespace std;
class Subject;
class Observer {
public:
    virtual ~Observer() {};
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer() {};
};

class Subject {
public:
    virtual ~Subject() {};
    virtual void Attach(Observer*);
    virtual void Detach(Observer*) {};
    virtual void Notify();
protected:
    Subject() {};
private:
    list <Observer*>  _observers;
};
void Subject::Attach(Observer* o) {
    _observers.push_back(o);
}

void Subject::Notify() {
    for (auto P : _observers)
    {
        P->Update(this);
    }
}

class ClockTimer : public Subject {
public:
    ClockTimer() {};
    virtual int GetHour() { return 1; }
    virtual int GetMinute() { return 10; }
    virtual int GetSecond() { return 0; }
    void Tick() ;
};
void ClockTimer::Tick() {

    Notify();
}

class DigitalClock : public Observer {
public:
    DigitalClock(ClockTimer*);
   

    virtual ~DigitalClock() {
        _subject->Detach(this);
    };
    virtual void Update(Subject*) ;
    // overrides Observer operation
    virtual void Draw() ;
    // overrides Widget operation;
    // defines how to draw the digital clock
private:
    ClockTimer* _subject;
};
DigitalClock::DigitalClock(ClockTimer* s) {
    _subject = s;
    _subject->Attach(this);
}
void DigitalClock::Update(Subject* theChangedSubject) {
    if (theChangedSubject == _subject) {
        Draw();
    }
}
void DigitalClock::Draw() {
    // get the new values from the subject
    int hour = _subject->GetHour();
    int minute = _subject->GetMinute();

    cout << hour << "" << minute ;

    // etc.
    // draw the digital clock
}

/*****************************************/
int main() {
    ClockTimer* timer = new ClockTimer;
    DigitalClock* digitalClock = new DigitalClock(timer);
    digitalClock->Update(timer);
    cout << "hello";
    return 0;
}