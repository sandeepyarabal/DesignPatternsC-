/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <vector>
#include <iostream> 
#include <algorithm> 
#include <functional> 
using namespace std;
 
class shape {
public:
  virtual void draw() const = 0;
 
  virtual void add(shape *g) {}

  virtual ~shape() {}
};
 
class circle : public shape {
public:
  void draw() const {
    cout << "circle draw()\n";
  }
};

class square : public shape {
public:
  void draw() const {
    cout << "square draw() \n";
  }
};



// Composite
class Composite : public shape {
public:
  void draw() const {
    // for each element in gList, call the draw member function
    for_each(gList.begin(), gList.end(), [](shape *ashape){ashape->draw();});
  }
 
  void add(shape *ashape) {
    gList.push_back(ashape);
  }
 
private:
  vector<shape*> gList;
};
 
int main()
{
  circle cir;
  cir.draw();
  square sq;
  sq.draw();


  Composite comp;
  comp.add(&cir);
  comp.add(&sq);

  comp.draw();

  return 0;
}
