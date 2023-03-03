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

#include<string.h>
#include<omnetpp.h>

using namespace omnetpp;

class Server:public cSimpleModule
{
    cMessage *msg;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};
Define_Module(Server);

void Server::initialize()
{

    msg=new cMessage("Hello I am Sevrer.");
    for(int i=1;i<=6;i++)
    {
    //node[i]

        char c=i+'0';
        char name[12]="node";
        name[4]=c;

         cModule *target=getParentModule()->getSubmodule(name);
         cMessage *copymsg = msg->dup();
         sendDirect(copymsg,target, "in");

    }
    delete msg;

}
void Server::handleMessage(cMessage *msg)
{
    EV<<"MSg recieved from client:"<<msg;
//    msg=new cMessage("Hello I am server.");
//    cModule *target=getParentModule()->getSubmodule("client");
//    sendDirect(msg, target, "in");

}



