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