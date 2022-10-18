#include "list5_11.cpp"

class Bank {
public:
    Bank(Logger& logger) : logger { logger } {};
    void make_transfer(long from, long to, long amount) {
        logger.log_transfer(from, to, amount);
    }

private:
    Logger& logger;
};

int main() {
    ConsoleLogger logger;
    Bank bank { logger };
    bank.make_transfer(1000L, 2000L, 49.95);
    bank.make_transfer(2000L, 4000L, 20.00);
    return 0;
}