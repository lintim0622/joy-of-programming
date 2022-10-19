#include "list5_11.cpp"

class Bank {
public:
    Bank(Logger* logger) : logger { logger } {
        set_logger(logger);
    }
    void set_logger(Logger* new_logger) { logger = new_logger; }
    void make_transfer(long from, long to, long amount) {
        if (logger)
            logger->log_transfer(from, to, amount);
    }

private:
    Logger* logger;
};

int main() {
    ConsoleLogger console_logger;
    FileLogger file_logger;
    Bank bank { &console_logger };
    bank.make_transfer(1000L, 2000L, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(2000L, 4000L, 20.00);
    return 0;
}