#ifndef pidMotorControl_h
#define pidMotorControl_h
#define LIBRARY_VERSION 1.0.0

#include <PID_v1.h>

class pidControl{
public:
	pidControl(uint16_t,uint16_t,uint16_t ,float ,float ,float);
	PID workPID;

private:
	uint16_t _encRead;
	uint16_t _output;
	uint16_t _setPoint;
	float _kp;
	float _ki;
	float _kd;
	int mode=DIRECT;
	//PID workPID();
	
};
#endif






class Customer {
public:
    Customer(void);
    Customer(string,char,int);
};







#include "Customer.h"

class Node {
   public:

      Node(void); //default constructor
      Node(string,char,int); //Node constructor with customer details

      Node* left;
      Node* right;
      Node* parent;
      Customer customer;
};







Node::Node() : left(nullptr),
               right(nullptr),
               parent(nullptr),
               customer() {}

Node::Node(string x, char y, int z) : left(nullptr),
                                      right(nullptr),
                                      parent(nullptr),
                                      customer(x, y, z) {}