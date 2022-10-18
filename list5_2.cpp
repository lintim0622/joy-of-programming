#include <cstdio>
#include <stdexcept>

class FileLogger {
public:
    void log_transfer(long from, long to, double amount) {
        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

class ConsoleLogger {
public:
    void log_transfer(long from, long to, double amount) {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

enum class LoggerType {
    console, 
    File
};

class Bank {
public:
    Bank() : type { LoggerType::console } {};
    void set_logger(LoggerType new_type) { type = new_type; }
    void make_transfer(long from, long to, double amount) {
        switch (type) {
            case LoggerType::console : {
                consolelogger.log_transfer(from, to, amount);
                break;
            }
            case LoggerType::File : {
                filelogger.log_transfer(from, to, amount);
                break;
            }
            default: {
                throw std::logic_error("Unknown Logger type encountered.");
                break;
            } 
        }
    }

private:
    LoggerType type;
    ConsoleLogger consolelogger;
    FileLogger filelogger;
};

int main() {
    Bank bank;
    bank.make_transfer(1000L, 2000L, 49.95);
    bank.make_transfer(2000L, 4000L, 20.00);
    bank.set_logger(LoggerType::File);
    bank.make_transfer(3000L, 2000L, 75.00);
    return 0;
}