#ifndef HTLC_H
#define HTLC_H

#include <string>
#include <vector>
#include <ctime>
#include <stdint.h>

enum class HTLCState {
    OFFERED,
    ACCEPTED,
    FULFILLED,
    FAILED,
    TIMED_OUT
};

struct HTLCData {
    uint64_t id;
    uint64_t amount_msat;
    uint32_t expiry;
    uint8_t payment_hash[32];
    uint8_t payment_preimage[32];
    HTLCState state;
    time_t created_at;
    time_t fulfilled_at;
};

class HTLCManager {
private:
    std::vector<HTLCData> htlcs;
    uint64_t htlc_counter;
    
public:
    HTLCManager();
    uint64_t create_htlc(uint64_t amount_msat, uint32_t expiry, const uint8_t payment_hash[32]);
    bool accept_htlc(uint64_t htlc_id);
    bool fulfill_htlc(uint64_t htlc_id, const uint8_t preimage[32]);
    bool fail_htlc(uint64_t htlc_id);
    bool timeout_htlc(uint64_t htlc_id);
    HTLCData* get_htlc(uint64_t htlc_id);
    const std::vector<HTLCData>& get_all_htlcs() const;
    bool validate_preimage(const uint8_t preimage[32], const uint8_t hash[32]);
    bool is_htlc_expired(uint64_t htlc_id);
    void remove_htlc(uint64_t htlc_id);
    ~HTLCManager();
};

#endif // HTLC_H