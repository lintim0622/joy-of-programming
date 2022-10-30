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

template <typename T>
class AutoBrake {
public:
    AutoBrake(const T& publish) : collision_threshold_s{5.0}, speed_mps{}, publishs{publish} {}
    void observe(const SpeedUpdate& cd) {}
    void observe(const CarDetected& cd) {}
    void set_collision_threshold_s(double x) {
        // if (x < 1)
        //     throw std::runtime_error{"Collision less than 1."};
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const { return collision_threshold_s; }
    double get_speed_mps() const { return speed_mps; }

private:
    double collision_threshold_s;
    double speed_mps;
    const T& publishs;
};

constexpr void assert_that(bool statement, const char* message) {
    if (!statement)
        throw std::runtime_error{message};
}

void initial_speed_is_zero() {
    std::function<void(const BrakeCommand& bc)> func { [](const BrakeCommand& bc) { return; } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
}

void run_test(void(*unit_test)(), const char* name) {
    try {
        unit_test();
        printf("[+] Test %s successful.\n", name);
    } catch (const std::exception& e) {
        printf("[-] Test failure in %s. %s.\n", name, e.what());
    }
}

void sensitivity_greater_than_1() {
    std::function<void(const BrakeCommand& bc)> func { [](const BrakeCommand& bc) { return; } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    try {
        auto_brake.set_collision_threshold_s(0.5L);
    } catch (const std::exception& e) {
        return;
    }
    assert_that(false, "no exception thrown");
}

int main() {
    run_test(initial_speed_is_zero, "initial speed is 0");
    run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
    return 0;
}