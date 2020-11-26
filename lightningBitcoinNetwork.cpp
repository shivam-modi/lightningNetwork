#include<iostream>
#include<ctime>
#include<vector>
#include<string>

using namespace std;

//some necessarities
time_t now = time(0);

//transaction
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

//Balance sheet
class BalanceSheet{
  private:
    double senderAmount;
    double recieverAmount;
    size_t senderHash;
    size_t recieverHash;
  public: 
    BalanceSheet(double, double);
    void changeBalance(double amt, size_t hash);
    size_t getRecieverHash(){
      return recieverHash;
    }
};

BalanceSheet:: BalanceSheet(double sender, double reciever){
  senderAmount = sender;
  recieverAmount = reciever;
}

void BalanceSheet:: changeBalance(double amt, size_t transferHash){
  senderAmount -= amt;
  recieverAmount += amt; 
}

//channel member
struct LNChannelMember{
  string ChannelSignkey;
  int amount;
  size_t transactionHash;
  size_t blockId;
  
  LNChannelMember *newChannelMember(string, int, size_t, size_t);
};

//lightning channel(including the all conditions)
class LightningChannel{
  private: 
      LNChannelMember *m1;
      LNChannelMember *m2; 
      size_t senderHash;
      size_t recieverHash;
      double recieverAmount;
      double senderAmount;
      double totalAmount;
      int noOfTransaction;
      int maxTransaction;
      BalanceSheet *balanceSheet;

    public:
      LightningChannel(size_t, size_t, double, double, int);
      void changeAmount(double, size_t);
      //checking for intermediate transaction
      bool isTransactionValid(size_t);
      //checking limit of transaction
      bool isLimitReached();
      //closing the channel
      void closeChannel();
      //updating a balance sheet
   
};

LightningChannel :: LightningChannel(size_t sender, size_t receiver, double recAmt, double senAmt, int max){
  senderHash = sender;
  recieverHash = receiver;
  recieverAmount = recAmt;
  senderAmount = senAmt;
  maxTransaction = max;
  noOfTransaction = 0;

  balanceSheet = new BalanceSheet(senAmt, recAmt);
}

void LightningChannel :: changeAmount(double send, size_t transferHash){
   if(isTransactionValid(transferHash) && !isLimitReached()){
           balanceSheet->changeBalance(send, transferHash);
           noOfTransaction++;
   } else if(!isLimitReached()) {
     cout<<"Transaction not valid\n";
   } else{
     cout<<"Limit reached for transaction, closing the channel\n";
     closeChannel();
   }
}

bool LightningChannel::isLimitReached(){
  return maxTransaction == noOfTransaction;
}

bool LightningChannel::isTransactionValid(size_t transferHash){
  return balanceSheet->getRecieverHash() == transferHash;
}

void LightningChannel::closeChannel(){
       
}

