
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
#include<unordered_map>
#include<string.h>

#include "MyMessage_m.h"

using namespace omnetpp;

class Node:public cSimpleModule
{
    std::unordered_map<int,int> child_c;;
    int currid;
    bool isleaf=false;

    std::vector<int>data;

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

        if(rmsg->getType()==0)
        {


            std::vector<int> rdata(rdata_size,0);
            //std::vector<int>childlist;

            EV<<getName()<<" received data:";
            for(int i=0;i<rdata_size;i++)
            {
                rdata[i]=rmsg->getHosts(i);
                EV<<rdata[i]<<" ";
            }
            currid=rdata[0];

            // Leaf Node
            if(rdata_size==1)
            {
                isleaf=true;
                int parentId=(currid-1)/2;
                char name[14]="node";
                char digitsf[]={'z','z','z','z','z','z','z','z','z','z'};
                int j=convert_to_charClient(parentId,digitsf);
                j-=1;
                int k=4;
                while(j>=0 and digitsf[j]!='z')
                {
                    name[k]=digitsf[j];
                    //printf("%s ",name);
                    k+=1;
                    j-=1;
                }
                EV<<"Inside Leaf Sending to:"<<name;
                MyMessage *sndata=new MyMessage("sndata");
                sndata->setSource(currid);
                sndata->setType(1);

                sndata->setNodedataArraySize(1);
                sndata->setNodedata(0, currid+500);

                cModule *targetL=getParentModule()->getSubmodule(name);
                sendDirect(sndata->dup(),targetL, "in");

            }
            else
            {
                std::vector<int> left;
                std::vector<int>right;
                int i=0;
                int leftidx=2*i+1;
                int rightidx=2*i+2;



                if(leftidx<rdata_size)
                {
                    left.push_back(rdata[leftidx]);
                    child_c[rdata[leftidx]]=-1;
                }
                if(rightidx<rdata_size)
                {
                    right.push_back(rdata[rightidx]);
                    child_c[rdata[rightidx]]=-1;
                }


                bfs_c(leftidx,left,rdata);
                bfs_c(rightidx,right,rdata);

                int n1=left.size();
                int n2=right.size();

                // send for left child

                MyMessage *msgl=new MyMessage("ldata");
                msgl->setHostsArraySize(n1);
                msgl->setType(0);

                for(int i=0;i<n1;i++)
                {
                    msgl->setHosts(i,left[i]);
                }
                EV<<"left:";
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
                if(leftidx<=rdata_size-1)
                {
                    cModule *targetl=getParentModule()->getSubmodule(name);
                    sendDirect(msgl->dup(),targetl, "in");
                    delete msgl;
                }

                // send to right child

                MyMessage *msgr=new MyMessage("rdata");
                msgr->setHostsArraySize(n2);
                msgr->setType(0);

                for(int i=0;i<n2;i++)
                {
                    msgr->setHosts(i,right[i]);
                }
                EV<<"right hosts:";
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

                if(rightidx<=rdata_size-1)
                {
                    cModule *targetr=getParentModule()->getSubmodule(name);
                    sendDirect(msgr->dup(),targetr, "in");
                    delete msgr;
                }
            }

        }
          // if feedback msg

            else if(rmsg->getType()==1)
            {
                EV<<"at:"<<getName();

                child_c[rmsg->getSource()]=1;

                int data_size=rmsg->getNodedataArraySize();

                EV<<"received from id:"<<rmsg->getSource();
                EV<<" Recieved data:"<<endl;
                for(int i=0;i<data_size;i++)
                {
                    data.push_back(rmsg->getNodedata(i));
                    EV<<data[i]<<" ";
                }

            }

        // check from all child data received or not
        if(isleaf==false)
        {
            bool alldone=true;

            for(auto id:child_c)
            {
                if(id.second==-1)
                {
                    alldone=false;
                    //retransmitrequest msg
                    EV<<"at: "<<getName()<<" still data not came from:"<<id.first;
                }
            }

            if(alldone==true)
            {
                // send its own message combined with all other to currid's parent

                int parentId=(currid-1)/2;
                char name[14]="node";
                char digitsf[]={'z','z','z','z','z','z','z','z','z','z'};

                if (parentId!=0)
                {

                    int j=convert_to_charClient(parentId,digitsf);
                    j-=1;
                    int k=4;
                    while(j>=0 and digitsf[j]!='z')
                    {
                        name[k]=digitsf[j];
                        //printf("%s ",name);
                        k+=1;
                        j-=1;
                    }

                }
                MyMessage *sndata=new MyMessage("sndata");
                sndata->setSource(currid);
                sndata->setType(1);

                // add cuurr nodes data
                if(currid!=0)
                {
                    data.push_back(currid+500);
                }
                sndata->setNodedataArraySize(data.size());

                for(int i=0;i<data.size();i++)
                {
                    sndata->setNodedata(i, data[i]);
                }

                if((strcmp("node1", getName()) == 0) or(strcmp("node2", getName()) == 0) )
                {
                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<"node0";
                    cModule *targetPL=getParentModule()->getSubmodule("node0");
                    sendDirect(sndata->dup(),targetPL, "in");

                }
                else if(strcmp("node0", getName()) == 0)
                {
                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<"server";
                    cModule *targetPS=getParentModule()->getSubmodule("server");
                    sendDirect(sndata->dup(),targetPS, "in");

                }
                else{
                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<name;
                    cModule *targetP=getParentModule()->getSubmodule(name);
                    sendDirect(sndata->dup(),targetP, "in");

                }



            } // if alldone end

         } // if isleaf or not end
}














