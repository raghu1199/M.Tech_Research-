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
#include<vector>
#include<queue>

#include "MyMessage_m.h"

using namespace omnetpp;

class Server:public cSimpleModule
{
    cMessage *msg;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};
Define_Module(Server);

// handling nodes names like node23,node234,node23456
int convert_to_char(int num,char *digits)
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

void bfs(int i,std::vector<int>&ans,std::vector<int>&arr)
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

void Server::initialize()
{

    std::vector<int>arr={0,1,2,3,4,5,6,7,8,9,10,11};

    std::vector<int> left;
    std::vector<int>right;
    int i=0;
    int leftidx=2*i+1;
    int rightidx=2*i+2;
    left.push_back(arr[leftidx]);
    right.push_back(arr[rightidx]);

    bfs(leftidx,left,arr);
    bfs(rightidx,right,arr);


    int n1=left.size();
    int n2=right.size();
    // send for left child

    MyMessage *msgl=new MyMessage("ldata");
    msgl->setHostsArraySize(n1);

    for(int i=0;i<n1;i++)
    {
        msgl->setHosts(i,left[i]);
    }
    EV<<"hosts via MyMessage:";
    for(int i=0;i<n1;i++)
    {
        EV<<msgl->getHosts(i)<<" ";
    }
    // handling names like node23,node245,node3456
    char name[14]="node";
    char digits[]={'z','z','z','z','z','z','z','z','z','z'};
    int j=convert_to_char(arr[leftidx],digits);
    j-=1;
    int k=4;
    while(j>=0 and digits[j]!='z')
    {
        name[k]=digits[j];
        //printf("%s ",name);
        k+=1;
        j-=1;
    }

    cModule *targetl=getParentModule()->getSubmodule(name);
    sendDirect(msgl->dup(),targetl, "in");
    delete msgl;

    // send data to right child

    MyMessage *msgr=new MyMessage("rdata");
    msgr->setHostsArraySize(n2);

    for(int i=0;i<n2;i++)
    {
        msgr->setHosts(i,right[i]);
    }
    EV<<"hosts via MyMessage:";
    for(int i=0;i<n2;i++)
    {
        EV<<msgr->getHosts(i)<<" ";
    }
    // reseting naming array
    for(int i=0;i<10;i++)
    {
        digits[i]='z';
    }
    // handling names
    j=convert_to_char(arr[rightidx],digits);
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
void Server::handleMessage(cMessage *msg)
{
    EV<<"MSg recieved from client:"<<msg;
//    msg=new cMessage("Hello I am server.");
//    cModule *target=getParentModule()->getSubmodule("client");
//    sendDirect(msg, target, "in");

}



