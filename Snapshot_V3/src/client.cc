
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
public:
    std::unordered_map<int,int> child_c;;
    int currid;
    bool isleaf=false;
    bool sent=false;
    MyMessage *timeout;
    Node();
    virtual ~Node();

    std::vector<int>data;
    std::vector<int>backupdata;


    cMessage *msg;
    MyMessage *sndata;

    virtual void initialize() override ;
    virtual void handleMessage(cMessage *msg) override;
    void forward(MyMessage *msgr,int id);

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
void Node::forward(MyMessage *msgr,int id)
{

    char name[14]="node";
    char digits[]={'z','z','z','z','z','z','z','z','z','z'};

    int j=convert_to_charClient(id,digits);
    j-=1;
    int k=4;
    while(j>=0 and digits[j]!='z')
    {
        name[k]=digits[j];
        k+=1;
        j-=1;
    }
    // get module (ip) by name of node and send data to it

    cModule *targetl=getParentModule()->getSubmodule(name);
    sendDirect(msgr->dup(),targetl, "in");



}

Node::Node()
{
    timeout = sndata = nullptr;
}

Node::~Node()
{
    cancelAndDelete(timeout);
    delete sndata;
}




void Node::handleMessage(cMessage *msg)
{
        bool alldone=true;
        MyMessage *rmsg = check_and_cast<MyMessage *>(msg);
        int rdata_size=rmsg->getHostsArraySize();
        timeout=new MyMessage("timeout");

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
                int parentId=(currid)/2;
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
                delete sndata;

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
                    child_c[rdata[leftidx]]=9999;
                }
                if(rightidx<rdata_size)
                {
                    right.push_back(rdata[rightidx]);
                    child_c[rdata[rightidx]]=9999;
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

                    // reset values
                    this->sent=false;
                    std::vector<int> keys;
                    for(auto item:this->child_c)
                    {
                        keys.push_back(item.first);
                    }
                    for(auto key:keys)
                    {
                        this->child_c[key]=9999;
                    }


                    if(currid<4)
                    {
                      cancelEvent(timeout);
                    //MyMessage *timeout=new MyMessage("timeout");
                    timeout->setType(5);
                    scheduleAt(simTime()+6.0,timeout);
                    delete msgl;
                    }
                    else
                    {

                        //MyMessage *timeout=new MyMessage("timeout");
                        cancelEvent(timeout);
                        timeout->setType(5);
                        scheduleAt(simTime()+2.0,timeout);
                        delete msgl;

                    }
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

                    // reset values
                    this->sent=false;
                    std::vector<int> keys;
                    for(auto item:child_c)
                    {
                        keys.push_back(item.first);
                    }
                    for(auto key:keys)
                    {
                        this->child_c[key]=9999;
                    }

                    if(currid<4)
                    {

                    //MyMessage *timeout=new MyMessage("timeout");
                    cancelEvent(timeout);
                    timeout->setType(5);
                    scheduleAt(simTime()+6.0,timeout);
                    delete msgr;
                    }
                    else
                    {

                        //MyMessage *timeout=new MyMessage("timeout");
                        cancelEvent(timeout);
                        timeout->setType(5);
                        scheduleAt(simTime()+2.0,timeout);
                        delete msgr;

                    }
                }
            }

        }
          // if feedback msg came from child

        else if(rmsg->getType()==1)
        {
            EV<<"at:"<<getName();

            child_c[rmsg->getSource()]=2;

            int data_size=rmsg->getNodedataArraySize();

            EV<<"received from id:"<<rmsg->getSource();
            EV<<" Recieved data:"<<endl;
            for(int i=0;i<data_size;i++)
            {
                data.push_back(rmsg->getNodedata(i));
                backupdata.push_back(rmsg->getNodedata(i));
                EV<<data[i]<<" ";
            }

        }


        // request data type msg and curr node is not leaf node so forward to all child
        else if(rmsg->getType()==2 and isleaf==false)
        {
            for(auto item:child_c)
            {
                forward(rmsg,item.first);
            }
            //reset values
            this->sent=false;
            std::vector<int> keys;

            for(auto item:child_c)
            {
                keys.push_back(item.first);
            }
            for(auto key:keys)
            {
                this->child_c[key]=9999;
            }

            if(currid<4)
            {

            //MyMessage *timeout=new MyMessage("timeout");
             cancelEvent(timeout);
            timeout->setType(5);
            scheduleAt(simTime()+6.0,timeout);


            }
            else
            {

               // MyMessage *timeout=new MyMessage("timeout");
                cancelEvent(timeout);
                timeout->setType(5);
                scheduleAt(simTime()+2.0,timeout);


            }

        }

        // it is leaf node and got msg of request data so now send reply msg to its parent

        else if(rmsg->getType()==2 and isleaf==true)
        {

            int parentId=(currid)/2;
            MyMessage *replymsg=new MyMessage("reply");

            replymsg->setSource(currid);  // give source id so that at reciver side they can mark true on this id

            replymsg->setNodedataArraySize(1);
            replymsg->setNodedata(0, currid+600);
            replymsg->setType(1);

            forward(replymsg,parentId);
            delete replymsg;



        }


        // on retransmit request (type=6)  from parent and curr is not leaf so  send backedup sndata

        else if(rmsg->getType()==6)
        {
            bool alldone3=true;
            for(auto id:this->child_c)
            {
                // if data not received from this id send retransmit request
                if(id.second!=2)
                {
                    alldone3=false;
                    EV<<"At: "<<getName()<<" On retransmit request. data not came from:"<<id.first;

                    MyMessage *retransmit=new MyMessage("retransmit please");
                    retransmit->setType(6);
                    retransmit->setSource(currid);
                    forward(retransmit,id.first);
                    delete retransmit;

                     // self msg after timout time
                }
            }


            if(alldone3=false)
            {
               // MyMessage *timeout=new MyMessage("timeout");
                cancelEvent(timeout);
               timeout->setType(6);
               timeout->setSource(rmsg->getSource());
               scheduleAt(simTime()+2.0,timeout);

            }
            else{
                MyMessage *sndata2=new MyMessage("on retransmit");
                sndata2->setNodedataArraySize(backupdata.size());
                sndata2->setType(1);
                sndata2->setSource(currid);

                for(int i=0;i<backupdata.size();i++)
                {
                    sndata2->setNodedata(i, backupdata[i]);

                }
                int id=rmsg->getSource();
                int  parentId=id;
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
                if((strcmp("node2", getName()) == 0) or(strcmp("node3", getName()) == 0) )
                {
                    EV<<"Inside retransmit: "<<getName() <<" Sending to:"<<"node0";
                    cModule *targetPL=getParentModule()->getSubmodule("node1");
                    sendDirect(sndata2->dup(),targetPL, "in");
                    //delete sndata;

                }
                else if(strcmp("node1", getName()) == 0)
                {
                    EV<<"Inside retransmit: "<<getName() <<" Sending to:"<<"server";
                    cModule *targetPS=getParentModule()->getSubmodule("server");
                    sendDirect(sndata2->dup(),targetPS, "in");
                    //delete sndata;

                }
                else
                {
                    EV<<"Inside retransmit: "<<getName() <<" Sending to:"<<name;
                    cModule *targetP=getParentModule()->getSubmodule(name);
                    sendDirect(sndata2->dup(),targetP, "in");
                }
                delete sndata2;
                backupdata.clear();
                this->sent=true;

            }
        }


        // check after timeout time it will recieve self msg of type =5




        else if(rmsg==timeout or rmsg->getType()==5)
        {
            bool alldone2=true;
            EV<<"At: "<<getName()<<" on self timeout";
             for(auto id:child_c)
                {
                    // if data not received from this id send retransmit request
                    if(id.second!=2)
                    {
                        alldone2=false;
                        //retransmitrequest msg
                        EV<<"At: "<<getName()<<" still data not came from:"<<id.first;


                        MyMessage *retransmit=new MyMessage("retransmit please");
                        retransmit->setType(6);
                        retransmit->setSource(currid);
                        forward(retransmit,id.first);
                        delete retransmit;

                                             // self msg after timout time
                    }
                }
             if(alldone2==false)
             {
//                MyMessage *timeout=new MyMessage("timeout");
                cancelEvent(timeout);
                timeout->setType(5);
                timeout->setSource(rmsg->getSource());
                alldone=false;
                scheduleAt(simTime()+1.0,timeout);
             }

             else if(alldone2==true and this->sent==false)
                {
                    // send its own message combined with all other to currid's parent

                    int parentId;
                    parentId=(currid)/2;


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



                    sndata=new MyMessage("sndata");
                    sndata->setSource(currid);
                    sndata->setType(1);

                    // add cuurr nodes da
                    if(currid!=0)
                    {
                        data.push_back(currid+500);
                        backupdata.push_back(currid+500);
                    }


                    sndata->setNodedataArraySize(data.size());

                    for(int i=0;i<data.size();i++)
                    {
                        sndata->setNodedata(i, data[i]);
                        backupdata.push_back(data[i]);
                    }


                   if(strcmp("node1", getName()) == 0)
                    {
                        EV<<"Inside node 1:"<<" 2:"<<child_c[2]<<" 3:"<<child_c[3];
                        if((child_c[2]==2) and (child_c[3]==2))
                        {
                            EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<"server";
                            cModule *targetPS=getParentModule()->getSubmodule("server");
                            sendDirect(sndata->dup(),targetPS, "in");
                        }


                    }
                    else{


                            if(strcmp("node5", getName()) == 0)
                            {
                                if (uniform(0,1)<0.8)
                                {
                                    bubble("msg lost");
                                    this->sent=false;
                                }
                                else
                                {
                                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<name;
                                    cModule *targetP=getParentModule()->getSubmodule(name);
                                    sendDirect(sndata->dup(),targetP, "in");
                                    this->sent=true;
                                }
                            }
                            else
                                {
                                EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<name;
                                cModule *targetP=getParentModule()->getSubmodule(name);
                                sendDirect(sndata->dup(),targetP, "in");
                                this->sent=true;
                                }
                         }


                    //reset all child values, reset data vector;

                   this->sent=true;


                } // if alldone end

             } // if isleaf or not end


        EV<<"child of curr node: "<<currid;
        for(auto id:child_c)
        {
            EV<<" "<<id.first<<" "<<id.second;
        }


     if(isleaf==false)
     {


        for(auto id:child_c)
        {
            // if data not received from this id send retransmit request
            if(id.second!=2)
            {
                alldone=false;
                                     // self msg after timout time
            }
        }


     if(alldone==true and this->sent==false)
        {
            // send its own message combined with all other to currid's parent

            int parentId;
            parentId=(currid)/2;


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



            sndata=new MyMessage("sndata");
            sndata->setSource(currid);
            sndata->setType(1);

            // add cuurr nodes da
            if(currid!=0)
            {
                data.push_back(currid+500);
                backupdata.push_back(currid+500);
            }



            sndata->setNodedataArraySize(data.size());

            for(int i=0;i<data.size();i++)
            {
                sndata->setNodedata(i, data[i]);
                backupdata.push_back(data[i]);
            }


           if(strcmp("node1", getName()) == 0)
            {
                EV<<"Inside node 1:"<<" 2:"<<child_c[2]<<" 3:"<<child_c[3];
                if((child_c[2]==2) and (child_c[3]==2))
                {
                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<"server";
                    cModule *targetPS=getParentModule()->getSubmodule("server");
                    sendDirect(sndata->dup(),targetPS, "in");
                    this->sent=true;
                }


            }
            else{
                if(strcmp("node5", getName()) == 0)
                {
                    if (uniform(0,1)<0.8)
                    {
                        bubble("msg lost");
                        this->sent=false;
                    }
                    else
                    {
                        EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<name;
                        cModule *targetP=getParentModule()->getSubmodule(name);
                        sendDirect(sndata->dup(),targetP, "in");
                        this->sent=true;
                    }
                }
                else
                    {
                    EV<<"Inside Normal Node: "<<getName() <<" Sending to:"<<name;
                    cModule *targetP=getParentModule()->getSubmodule(name);
                    sendDirect(sndata->dup(),targetP, "in");
                    this->sent=true;
                    }
                }
            //reset all child values, reset data vector;

//            std::vector<int> keys;
//            for(auto item:child_c)
//            {
//                keys.push_back(item.first);
//            }
//            for(auto key:keys)
//            {
//                this->child_c[key]=9999;
//            }
            data.clear();

        } // if alldone end


    }
}
















