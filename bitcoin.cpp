#ifndef Block_h
#define Block_h
#include <vector>
#include <ctime>
#include <iostream>
#ifndef Blockchain_h
#define Blockchain_h
#include <stdio.h>
#include <string>


using namespace std;


struct TransactionData
{
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
    
    TransactionData(){};
    
    TransactionData(double amt, std::string sender, std::string receiver, time_t time)
    {
        amount = amt;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
    };
};

#endif /* TransactionData_h */



class Block
{
private:
    int index;
    size_t blockHash;
    size_t previousHash;
    size_t generateHash();
    
public:
   
    Block(int idx, TransactionData d, size_t prevHash);
    
   
    int getIndex();
    
    
    size_t getHash();
    
    
    size_t getPreviousHash();
    
   
    TransactionData data;
    
    bool isHashValid();
};




class Blockchain
{
private:
    Block createGenesisBlock();
    vector<Block> chain;

public:
   
    Blockchain();
    
    
    vector<Block> getChain();
    Block *getLatestBlock();
    bool isChainValid();
    void addBlock(TransactionData data);
    void printChain();
};

#endif /* Blockchain_h */

Block::Block(int idx, TransactionData d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}


int Block::getIndex()
{
    return index;
}


size_t Block::generateHash()
{
    
    std::string toHashS = std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp);
    
    
    std::hash<std::string> tDataHash;
    std::hash<std::string> prevHash; 
    
    return tDataHash(toHashS) ^ (prevHash(std::to_string(previousHash)) << 1);
}

// Public Functions
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}



Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

std::vector<Block> Blockchain::getChain() {
    return chain;
}


Block Blockchain::createGenesisBlock()
{
    
    
    time_t current;
    cout<<"ENTER DATA FOR 1st Transaction"<<endl;
    string S1, R1;
    
    cout<<"ENTER SENDER KEY : ";
    cin>>S1;
    cout<<"ENTER RECEIVER KEY : ";
    cin>>R1;
    float amount;
    cout<<"ENTER AMOUNT : ";
    cin>>amount;
    
    TransactionData data0(amount, S1, R1, time(&current));
    
    Block genesis(0, data0, 0);
    return genesis;
}


Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size();
    std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }
        
        
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timestamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPreviousHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHashValid());
    }
}




int main(int argc, char const *argv[])
{
    
    Blockchain awesomeCoin;

    
    // Data for first block
    // int index =  currentBlock.getIndex();
    // cout<<"DO YOU WANT TO MAKE MORE TRANSACTION?? ENTER '0' for NO and '1'  for YES : "<<endl;
    
    // cin>>ans;
    // cout<<"ENTER DATA FOR "<< 2 <<"nd TRANSACTION"<<endl;

    
    // cout<<"ENTER SENDER KEY : ";
    // cin>>S1;
    // cout<<"ENTER RECEIVER KEY : ";
    // cin>>R1;
    // float amount;
    // cout<<"ENTER AMOUNT : ";
    // cin>>amount;
    // TransactionData data1(amount, S1, R1, time(&data1Time));
    // awesomeCoin.addBlock(data1);
    
    // time_t data2Time;
    // TransactionData data2(0.2233, "Martha", "Fred", time(&data2Time));
    // awesomeCoin.addBlock(data2);

    bool ans = 1;
    int a = 2;
    while(ans){
        time_t data1Time;
    string S1, R1;
    cout<<"DO YOU WANT TO MAKE MORE TRANSACTION?? ENTER '0' for NO and '1'  for YES : "<<endl;
    cin>>ans;
    if(ans == 0) break;
    cout<<"ENTER DATA FOR "<< a <<"th TRANSACTION"<<endl;
    cout<<"ENTER SENDER KEY : ";
    cin>>S1;


    cout<<"ENTER RECEIVER KEY : ";
    cin>>R1;
    float amount;
    cout<<"ENTER AMOUNT : ";
    cin>>amount;
    TransactionData data(amount, S1, R1, time(&data1Time));
    awesomeCoin.addBlock(data);
    a++;
    }

    
    
  
    printf("Is chain still valid? -> ");
    
    if(awesomeCoin.isChainValid()){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    
    
    Block *hackBlock = awesomeCoin.getLatestBlock();
    hackBlock->data.amount = 10000; 
    hackBlock->data.receiverKey = "shivam"; 

    // cout<<endl;
    cout<<"TO SEE DATA ENTER '1' "<<endl;
    bool ans2;
    cin>>ans2;
    if(ans2){
    awesomeCoin.printChain();
    }
    
    
    

    cout<<endl;
    printf("\nIs chain still valid? %d\n", awesomeCoin.isChainValid());
    
    return 0;
   
}