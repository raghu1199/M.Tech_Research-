
/*
 * server.cc
 *
 *  Created on: Mar 3, 2023
 *      Author: raghu
 */

#include<omnetpp.h>
#include<cstring>
#include<vector>
#include<queue>

#include "MyMessage_m.h"

using namespace omnetpp;

class Node:public cSimpleModule
{
    cMessage *msg;
    virtual void initialize() override ;
    virtual void handleMessage(cMessage *msg) override;

};
Define_Module(Node);


// handling nodes names like node23,node234,node23456
int convert_to_charClient(int num,char *digits)
{
    int i=0,rem;

    while(num>0)
    {
        rem=num%10;
        digits[i]=rem+'0';
        num/=10;
        i+=1;
    }

    return i;
}

void bfs_c(int i,std::vector<int>&ans,std::vector<int>&arr)
{

    int n=arr.size();
    std::queue<int> q;
    q.push(i);
    while(q.empty()==false)
    {

        int leftidx,rightidx;

        i=q.front();
        q.pop();
        leftidx=2*i+1;
        rightidx=2*i+2;
        if(leftidx<n)
        {
            ans.push_back(arr[leftidx]);
            q.push(leftidx);
        }
        if(rightidx<n)
        {
            ans.push_back(arr[rightidx]);
            q.push(rightidx);
        }
    }
}

void Node::initialize()
{


//    msg=new cMessage("Hello I am Client.");
//    cModule *target=getParentModule()->getSubmodule("server");
//    sendDirect(msg, target, "in");



}

void Node::handleMessage(cMessage *msg)
{
    MyMessage *rmsg = check_and_cast<MyMessage *>(msg);

    int rdata_size=rmsg->getHostsArraySize();
    std::vector<int> rdata(rdata_size,0);
    //std::vector<int>childlist;

    EV<<getName()<<" received data:";
    for(int i=0;i<rdata_size;i++)
    {
        rdata[i]=rmsg->getHosts(i);
        EV<<rdata[i]<<" ";
    }

    std::vector<int> left;
    std::vector<int>right;
    int i=0;
    int leftidx=2*i+1;
    int rightidx=2*i+2;
    left.push_back(rdata[leftidx]);
    right.push_back(rdata[rightidx]);

    bfs_c(leftidx,left,rdata);
    bfs_c(rightidx,right,rdata);

    int n1=left.size();
    int n2=right.size();

    // send for left child

    MyMessage *msgl=new MyMessage("ldata");
    msgl->setHostsArraySize(n1);
    for(int i=0;i<n1;i++)
    {
        msgl->setHosts(i,left[i]);
    }
    EV<<"left hosts via MyMessage:";
    for(int i=0;i<n1;i++)
    {
        EV<<msgl->getHosts(i)<<" ";
    }
    // handling names like node2345,node 234,..
    char name[14]="node";
    char digits[]={'z','z','z','z','z','z','z','z','z','z'};
    int j=convert_to_charClient(rdata[leftidx],digits);
    j-=1;
    int k=4;
    while(j>=0 and digits[j]!='z')
    {
        name[k]=digits[j];
        //printf("%s ",name);
        k+=1;
        j-=1;
    }
    // get module (ip) by name of node and send data to it
    cModule *targetl=getParentModule()->getSubmodule(name);
    sendDirect(msgl->dup(),targetl, "in");
    delete msgl;

    // send to right child
    MyMessage *msgr=new MyMessage("rdata");
    msgr->setHostsArraySize(n2);

    for(int i=0;i<n2;i++)
    {
        msgr->setHosts(i,right[i]);
    }
    EV<<"right hosts via MyMessage:";
    for(int i=0;i<n2;i++)
    {
        EV<<msgr->getHosts(i)<<" ";
    }

    // handling names of node
    j=convert_to_charClient(rdata[rightidx],digits);
    j-=1;
    k=4;
    while(j>=0 and digits[j]!='z')
    {
        name[k]=digits[j];
        //printf("%s ",name);
        k+=1;
        j-=1;
    }

    cModule *targetr=getParentModule()->getSubmodule(name);
    sendDirect(msgr->dup(),targetr, "in");
    delete msgr;



}






