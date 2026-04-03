// fundamental data types for Lightning Network

#ifndef TYPES_H
#define TYPES_H

// Transaction types
typedef enum {
    PAYMENT,         // Standard payment transaction
    REFUND,          // Refund transaction
    CHANNEL_OPEN,    // Channel opening transaction
    CHANNEL_CLOSE,   // Channel closing transaction
    HTLC_TIMEOUT,     // HTLC timeout transaction
} TransactionType;

// Channel states
typedef enum {
    PENDING,         // Channel is in the process of opening
    ACTIVE,          // Channel is active and transactions can be processed
    CLOSED,          // Channel is closed and cannot be used
    DISPUTED,        // Channel has a dispute
} ChannelState;

// HTLC Structure
typedef struct {
    uint64_t amount;      // Amount locked in HTLC
    uint32_t lock_time;   // Time until HTLC is valid
    uint8_t *preimage;    // Preimage for the HTLC
} HTLC;

#endif // TYPES_H