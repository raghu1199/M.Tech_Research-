/*
 * unittled2.cc
 *
 *  Created on: Mar 3, 2023
 *      Author: raghu
 */

/*
 * untitled1.cc
 *
 *  Created on: Mar 3, 2023
 *      Author: raghu
 */




/*
 * server.cc
 *
 *  Created on: Mar 3, 2023
 *      Author: raghu
 */

#include<omnetpp.h>
#include<cstring>

using namespace omnetpp;

class Node:public cSimpleModule
{
    cMessage *msg;
    virtual void initialize() override ;
    virtual void handleMessage(cMessage *msg) override;

};
Define_Module(Node);

void Node::initialize()
{


//    msg=new cMessage("Hello I am Client.");
//    cModule *target=getParentModule()->getSubmodule("server");
//    sendDirect(msg, target, "in");



}
void Node::handleMessage(cMessage *msg)
{
    EV<<getName() <<":MSg recived from server:"<<msg;
    delete msg;
    msg=new cMessage("Hello I am CLient.");
    cModule *target=getParentModule()->getSubmodule("server");
    sendDirect(msg, target, "in");
}






