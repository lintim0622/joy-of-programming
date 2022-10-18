#include <cstdio>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

class ConsoleLogger : public Logger {
public:
    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

class FileLogger : public Logger {
public:
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};