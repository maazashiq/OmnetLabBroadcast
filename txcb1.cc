
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class Txcb1 : public cSimpleModule
{
  protected:
    virtual void forwardMessage(cMessage *msg);
    virtual void forwardMessage2(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txcb1);

void Txcb1::initialize()
{
    if (getIndex() == 1) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}

void Txcb1::handleMessage(cMessage *msg)
{
    if (getIndex() == 1) {
        forwardMessage(msg);
    }
    else if(getIndex() == 4) {
        forwardMessage2(msg);
    }

}

void Txcb1::forwardMessage(cMessage *msg)
{
    // In this example, we send message to all gates connected to initial gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);
    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    // $o and $i suffix is used to identify the input/output part of a two way gate
    int outGateBaseId = gateBaseId("gate$o");
    for (int k = 0; k < n; k++)
        send(k==n-1 ? msg : msg->dup(), outGateBaseId+k);



}

void Txcb1::forwardMessage2(cMessage *msg)
{
    // Here, we further forward the message to the nodes which are not directly connected to initial gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);
    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    int outGateBaseId = gateBaseId("gate$o");
    for (int k = 1; k < n; k++)
        send(msg->dup(), outGateBaseId+k);



}
