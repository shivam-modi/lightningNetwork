// payment_channel.h

#ifndef PAYMENT_CHANNEL_H
#define PAYMENT_CHANNEL_H

#include <iostream>
#include <vector>
#include <string>

class PaymentChannel {
public:
    enum class ChannelState {
        OPEN,
        CLOSED,
        AWAITING_PAYMENT,
    };

    PaymentChannel(std::string id);
    void open();
    void close();
    void addCommitmentTransaction(std::string tx);
    void addHTLC(std::string htlc);
    bool makePayment(double amount);
    ChannelState getState();

private:
    std::string channel_id;
    ChannelState state;
    std::vector<std::string> commitment_transactions;
    std::vector<std::string> htlcs;
    double balance;
};

#endif // PAYMENT_CHANNEL_H
