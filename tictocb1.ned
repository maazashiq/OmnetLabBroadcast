//
// This file is part of an OMNeT++/OMNEST simulation example.
// Although it is not the same file as changes were made for learning purposes 
// in order to make it work with the broadcast C file.
//

simple Txcb1
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];  // declare two way connections
}

// using two way connections to further simplify the network definition
network Tictocb1
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tic[6]: Txcb1;
    connections:
        tic[0].gate++ <--> Channel <--> tic[1].gate++;
        tic[1].gate++ <--> Channel <--> tic[2].gate++;
        tic[1].gate++ <--> Channel <--> tic[4].gate++;
        tic[3].gate++ <--> Channel <--> tic[4].gate++;
        tic[4].gate++ <--> Channel <--> tic[5].gate++;
}