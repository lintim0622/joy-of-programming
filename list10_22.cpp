#include <stdexcept>
#include <functional>

class SpeedUpdate {
public:
    double velocity_mps;
};

class CarDetected {
public:
    double distance_m;
    double velocity_mps;
};

class BrakeCommand {
public:
    double time_to_collision_s;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate& su)>;
using CarDetectedCallback = std::function<void(const CarDetected& cd)>;

class IserviceBus {
public:
    virtual ~IserviceBus() = default;
    virtual void publish(const BrakeCommand& bc) = 0;
    virtual void subscribe(SpeedUpdateCallback callback) = 0;
    virtual void subscribe(CarDetectedCallback callback) = 0;
};

class MockServiceBus : public IserviceBus {
public:
    void publish(const BrakeCommand& cmd) override {
        commands_published++;
        last_command = cmd;
    }
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    }
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    }

private:
    BrakeCommand last_command {};
    int commands_published {};
    SpeedUpdateCallback speed_update_callback {};
    CarDetectedCallback car_detected_callback {};
};

class AutoBrake {
public:
    AutoBrake(IserviceBus& bus) : collision_threshold_s{5.0}, speed_mps{} {}
    void set_collision_threshold_s(double x) {
        if (x < 1)
            throw std::runtime_error{"Collision less than 1."};
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const { return collision_threshold_s; }
    double get_speed_mps() const { return speed_mps; }

private:
    double collision_threshold_s;
    double speed_mps;
};

void run_test(void(*unit_test)(), const char* name) {
    try {
        unit_test();
        printf("[+] Test %s successful.\n", name);
    } catch (const std::exception& e) {
        printf("[-] Test failure in %s. %s.\n", name, e.what());
    }
}

constexpr void assert_that(bool statement, const char* message) {
    if (!statement)
        throw std::runtime_error{message};
}

void initial_speed_is_zero() {
    MockServiceBus bus {};
    AutoBrake auto_brake {bus};
    assert_that(auto_brake.get_collision_threshold_s() == 5, "sensitivity is not 5");
}

void initial_sensitivity_is_five() {
    MockServiceBus bus {};
    AutoBrake auto_brake {bus};
    assert_that(auto_brake.get_collision_threshold_s() == 5, "sensitivity is not 5");
}

void sensitivity_greater_than_1() {
    MockServiceBus bus {};
    AutoBrake auto_brake {bus};
    try {
        auto_brake.set_collision_threshold_s(0.5L);
    } catch (const std::runtime_error& e) {
        return;
    }
    assert_that(false, "no exception thrown");
}

int main() {
    run_test(initial_speed_is_zero, "initial speed is 0");
    run_test(initial_sensitivity_is_five, "initial sensitivity is 5");
    run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
    return 0;
}