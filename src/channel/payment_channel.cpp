#include "payment_channel.h"
#include <iostream>

PaymentChannel::PaymentChannel(std::string id) 
    : channel_id(id), state(ChannelState::CLOSED), balance(0.0) {}

void PaymentChannel::open() {
    state = ChannelState::OPEN;
    std::cout << "Channel " << channel_id << " is now OPEN\n";
}

void PaymentChannel::close() {
    state = ChannelState::CLOSED;
    std::cout << "Channel " << channel_id << " is now CLOSED\n";
}

void PaymentChannel::addCommitmentTransaction(std::string tx) {
    commitment_transactions.push_back(tx);
    std::cout << "Added commitment transaction to channel " << channel_id << "\n";
}

void PaymentChannel::addHTLC(std::string htlc) {
    htlcs.push_back(htlc);
    std::cout << "Added HTLC to channel " << channel_id << "\n";
}

bool PaymentChannel::makePayment(double amount) {
    if (state != ChannelState::OPEN) {
        std::cout << "Cannot make payment: channel is not open\n";
        return false;
    }
    balance += amount;
    std::cout << "Payment of " << amount << " added to channel. New balance: " << balance << "\n";
    return true;
}

PaymentChannel::ChannelState PaymentChannel::getState() {
    return state;
}