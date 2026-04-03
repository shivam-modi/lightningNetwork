#include <iostream>
#include <string>

class HTLCManager {
public:
    void createHTLC(const std::string& lockHash, int timeout) {
        // Implementation to create a Hash Time Lock Contract
        std::cout << "HTLC created with lock hash: " << lockHash << " and timeout: " << timeout << std::endl;
    }

    void claimHTLC(const std::string& lockHash, const std::string& preImage) {
        // Implementation to claim the HTLC using the pre-image
        std::cout << "HTLC claimed with lock hash: " << lockHash << " using pre-image: " << preImage << std::endl;
    }

    void refundHTLC(const std::string& lockHash) {
        // Implementation to refund the HTLC back to the sender if timeout occurs
        std::cout << "HTLC refunded with lock hash: " << lockHash << std::endl;
    }
};

int main() {
    HTLCManager htlcManager;
    htlcManager.createHTLC("dummy_hash", 300);
    htlcManager.claimHTLC("dummy_hash", "dummy_preimage");
    htlcManager.refundHTLC("dummy_hash");
    return 0;
}