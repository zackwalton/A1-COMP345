#ifndef ORDERS_H
#define ORDERS_H

class OrdersList{
   public:
        OrdersList();
        int getSize();
        void add(Orders* other);
        void remove(int i);
        void move(int initial, int final);
        ostream& displayOrderList(ostream& myOrderList);
        OrdersList& operator=(const OrdersList& other);
        ~OrdersList(); 

    private: 
        std::vector<Orders*> listOfOrders;
        friend ostream& operator<<(ostream& myOrderList, OrdersList& otherList);

};

class Orders {
    public:
        Orders();
        Orders() = default;
        virtual Orders* copy() const = 0;
        virtual void execute() = 0; 
        virtual bool validate() = 0; 
        virtual ostream& displayOrder(ostream& myOrder) const = 0;
        virtual ~Orders() = default;

    private:
        friend ostream& operator<< (ostream& myOrder, Orders& O);
};
class Deploy : public Orders {
    Deploy();
    ~Deploy() override{};
    Deploy() = default; 
    Deploy(const Deploy& copyDeploy) = default; 
    Deploy& operator=(const Deploy& copyDeploy) = default; 
    ostream& displayOrder(ostream& myOrder) const override;

};

class Advance : public Orders {
public:
    Advance();
    ~Advance() override{};
    Advance() = default; 
    Advance(const Advance& copyAdvance) = default; 
    Advance& operator=(const Advance& copyAdvance) = default; 
    ostream& displayOrder(ostream& myOrder) const override;
};
class Bomb : public Orders {
public:
    Bomb();
    ~Bomb() override{};
    Bomb() = default; 
    Bomb(const Bomb& copyBomb) = default; 
    Bomb& operator=(const Bomb& copyBomb) = default; 
    ostream& displayOrder(ostream& myOrder) const override;
};
class Blockade : public Orders {
public:
    Blockade();
    ~Blockade() override{};
    Blockade() = default; 
    Blockade(const Blockade& copyBlockade) = default; 
    Blockade& operator=(const Blockade& copyBlockade) = default; 
    ostream& displayOrder(ostream& myOrder) const override;
};
class Airlift : public Orders {
public:
    Airlift();
    ~Airlift() override{};
    Airlift() = default; 
    Airlift(const Airlift& copyAirlift) = default; 
    Airlift& operator=(const Airlift& copyAirlift) = default; 
    ostream& displayOrder(ostream& myOrder) const override;
};
class Negotiate : public Orders {
public:
    Negotiate();
    ~Negotiate() override{};
    Negotiate() = default; 
    Negotiate(const Negotiate& copyNegotiate) = default; 
    Negotiate& operator=(const Negotiate& copyNegotiate) = default; 
    ostream& displayOrder(ostream& myOrder) const override;
};




#endif //ORDERS_H
