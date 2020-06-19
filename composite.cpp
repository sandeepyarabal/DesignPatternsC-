
//mantosh4u design - pattern teken from net

#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>


/*****************************************/
template<typename T>
void display(const T& val) {
    std::cout << val << "\n";
}


using Watt = double;
using Currency = double;

/*****************************************/
class Equipment {
public:
    using EquipmentSmartPtr = std::shared_ptr<Equipment>;
    virtual ~Equipment() = default;
    std::string Name() { return _name; }
    virtual Watt Power() { return _power; }
    virtual Currency NetPrice() { return _price; }
    // fixed 20% percent discount
    virtual Currency DiscountPrice() { return (0.8 * NetPrice()); }
    virtual void Add(EquipmentSmartPtr x) { }
    virtual void Remove(EquipmentSmartPtr x) { }
protected:
    Equipment(std::string n) :_name(n) { }
private:
    std::string _name;
    Watt        _power{ 440 };
    Currency    _price{ 200 };
};


/*****************************************/
class FloopyDisk : public Equipment {
public:
    FloopyDisk(std::string n) :Equipment(n) {}
    virtual ~FloopyDisk() = default;
};


/*****************************************/
class Card : public Equipment {
public:
    Card(std::string n) :Equipment(n) {}
    virtual ~Card() = default;
};



/*****************************************/
//To find out whether items are in the composite objects
class Name_Equal {
private:
    Equipment::EquipmentSmartPtr val;
public:
    Name_Equal(const Equipment::EquipmentSmartPtr& v) :val(v) { }
    bool operator()(const Equipment::EquipmentSmartPtr& x) const {
        return (x->Name() == val->Name());
    }
};


/*****************************************/
class  CompositeEquipment : public Equipment {
public:
    virtual ~CompositeEquipment() = default;
    virtual Watt Power() override;
    virtual Currency NetPrice() override;
    virtual void Add(EquipmentSmartPtr) override;
    virtual void Remove(EquipmentSmartPtr) override;
protected:
    CompositeEquipment(std::string n) : Equipment(n) { }
private:
    void find_equipment(std::vector<EquipmentSmartPtr>&, EquipmentSmartPtr&);
    std::vector<EquipmentSmartPtr>  _equipment;
};

Watt CompositeEquipment::Power() {
    Watt total{};
    for (const auto& itr : _equipment)
        total += itr->Power();
    total += Equipment::Power();
    return total;
}

Currency CompositeEquipment::NetPrice() {
    Currency total{};
    for (const auto& itr : _equipment) {
        display(itr->Name());
        total += itr->NetPrice();
    }
    total += Equipment::NetPrice();
    return total;
}

void CompositeEquipment::Add(EquipmentSmartPtr entry) {
    _equipment.push_back(entry);
}

void CompositeEquipment::Remove(EquipmentSmartPtr entry) {
    find_equipment(_equipment, entry);
}

void CompositeEquipment::find_equipment(std::vector<EquipmentSmartPtr>& vec,
    EquipmentSmartPtr& entry) {
    Name_Equal eq(entry);
    auto itrpos = std::find_if(std::begin(vec), std::end(vec), eq);
    if (itrpos != std::end(vec)) {
        vec.erase(itrpos);
    }
}


/*****************************************/
class Chassis : public CompositeEquipment {
public:
    Chassis(std::string n) : CompositeEquipment(n) {}
    virtual ~Chassis() = default;
};


/*****************************************/
class Cabinet : public CompositeEquipment {
public:
    Cabinet(std::string n) : CompositeEquipment(n) {}
    virtual ~Cabinet() = default;
};


/*****************************************/
class Bus : public CompositeEquipment {
public:
    Bus(std::string n) : CompositeEquipment(n) {}
    virtual ~Bus() = default;
};




/*****************************************/
Equipment::EquipmentSmartPtr assemble_pc() {
    auto cabinet = std::make_shared<Cabinet>("PC Cabinet");
    auto chassis = std::make_shared<Chassis>("Chassis");
    cabinet->Add(chassis);

    auto bus = std::make_shared<Bus>("MCA Bus");
    auto card = std::make_shared<Card>("16Mbs Token Ring Card");
    bus->Add(card);
    chassis->Add(bus);
    auto floopy = std::make_shared<FloopyDisk>("3.5inch Floopy Disk");
    cabinet->Add(floopy);
    return cabinet;
}


/*****************************************/
int main() {
    auto pc = assemble_pc();
    std::cout << "The PC Name is: " << pc->Name() << "\n";
    std::cout << "The PC parts are: " << "\n";
    auto price = pc->NetPrice();
    std::cout << "The net price of PC is: " << price << "\n";

    return 0;
}