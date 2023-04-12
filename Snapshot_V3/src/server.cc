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
#include<unordered_map>

#include "MyMessage_m.h"

using namespace omnetpp;

class Server:public cSimpleModule
{
    std::unordered_map<int,int> child;;
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


    std::vector<int>arr={1,2,3,4,5,6,7,8,9,10,11,12};
    //std::unordered_map<int,int> child;

    std::vector<int> left;
    std::vector<int>right;
    int i=0;
    int leftidx=2*i+1;
    int rightidx=2*i+2;

    child[arr[leftidx]]=-1;
    child[arr[rightidx]]=-1;

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
    EV<<getName()<<"lhosts via MyMessage:";
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

    msgl->setType(0);
    cModule *targetl=getParentModule()->getSubmodule(name);
    sendDirect(msgl->dup(),targetl, "in");


    delete msgl;

    // send data to right child

    MyMessage *msgr=new MyMessage("rdata");
    msgr->setHostsArraySize(n2);
    msgr->setType(0);

    for(int i=0;i<n2;i++)
    {
        msgr->setHosts(i,right[i]);
    }
    EV<<getName()<<"rhosts via MyMessage:";
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

//    MyMessage *timeout=new MyMessage("timeout");
//    timeout->setType(5);
//    scheduleAt(simTime()+10.0,timeout);

    delete msgr;



}
void Server::handleMessage(cMessage *msg)
{

    MyMessage *rmsg1 = check_and_cast<MyMessage *>(msg);
    EV<<"MSg recieved from :"<<rmsg1->getSource()<<" "<<endl;
    int data_size=rmsg1->getNodedataArraySize();
    EV<<"ALL NODES DATA:"<<endl;
    for(int i=0;i<data_size;i++)
    {
        EV<<rmsg1->getNodedata(i)<<" ";
    }
    delete rmsg1;

    // start new snashot msg
    MyMessage *msgr=new MyMessage("reqdata");
    msgr->setType(2);
    cModule *targetr=getParentModule()->getSubmodule("node1");
    sendDirect(msgr->dup(),targetr, "in");
    delete msgr;




}



