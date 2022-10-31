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
    void observe(const SpeedUpdate& cd) { speed_mps = cd.velocity_mps; }
    void observe(const CarDetected& cd) {
        const double relative_velocity_mps = speed_mps - cd.velocity_mps;
        const double time_to_collision_s = cd.distance_m / relative_velocity_mps;
        if (time_to_collision_s >= 0 && time_to_collision_s <= collision_threshold_s)
            publishs(BrakeCommand{ time_to_collision_s });
    }
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

void initial_sensitivity_is_five() {
    std::function<void(const BrakeCommand& bc)> func { [](const BrakeCommand& bc) { return; } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    assert_that(auto_brake.get_collision_threshold_s() == 5L, "sensitivity is not 5");
}

void sensitivity_grater_than_1() {
    std::function<void(const BrakeCommand& bc)> func { [](const BrakeCommand& bc) { return; } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    try {
        auto_brake.set_collision_threshold_s(0.5L);
    } catch (const std::exception& e) {
        return;
    }
    assert_that(false, "no exception thrown");
}

void speed_is_saved() {
    std::function<void(const BrakeCommand& bc)> func { [](const BrakeCommand& bc) { return; } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    auto_brake.observe(SpeedUpdate{100L});
    assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");

    auto_brake.observe(SpeedUpdate{50L});
    assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");

    auto_brake.observe(SpeedUpdate{0L});
    assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
}

void alert_when_imminent() {
    int brake_commands_published {};
    std::function<void(const BrakeCommand& bc)> func { [&brake_commands_published](const BrakeCommand& bc) {
        brake_commands_published++;
    } };
    AutoBrake<std::function<void(const BrakeCommand& bc)>> auto_brake { func };
    auto_brake.set_collision_threshold_s(10L);
    auto_brake.observe(SpeedUpdate{100L});
    auto_brake.observe(CarDetected{100L, 0L});
    assert_that(brake_commands_published == 1, "brake commands published not one");
}

int main() {
    run_test(initial_speed_is_zero, "initial speed is 0");
    run_test(initial_sensitivity_is_five, "initial sensitivity is five");
    run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
    run_test(speed_is_saved, "speed is saved");
    run_test(alert_when_imminent, "alert when imminent");
    return 0;
}