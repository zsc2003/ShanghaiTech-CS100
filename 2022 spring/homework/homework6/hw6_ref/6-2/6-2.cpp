#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Alarm;

class AlarmClock {
 public:
  AlarmClock() : m_hour(0), m_minute(0) {}
  virtual ~AlarmClock();
  void AddAlarm(Alarm *alarm);
  void Input();
  void TimeElapse();

 private:
  int m_hour;
  int m_minute;
  std::vector<Alarm *> m_alarms;
};

class Alarm {
 public:
  Alarm(int hour, int minute, std::string name)
      : m_active(true), m_hour(hour), m_minute(minute), m_name(name) {}
  virtual ~Alarm() = default;

  bool GetActive() const {
    return m_active;
  }
  int GetHour() const {
    return m_hour;
  }
  int GetMinute() const {
    return m_minute;
  }

  virtual void Trigger() = 0;

 protected:
  std::string Time() const {
    std::stringstream ss;
    ss << (m_hour < 10 ? "0" : "") << m_hour << ":"
       << (m_minute < 10 ? "0" : "") << m_minute;
    return ss.str();
  }

 protected:
  bool m_active;
  int m_hour;
  int m_minute;
  std::string m_name;
};

class RepeatableAlarm : public Alarm {
 public:
  RepeatableAlarm(int hour, int minute, std::string name)
      : Alarm(hour, minute, name) {}

  virtual void Trigger() {
    std::cout << "Alarm " << m_name << " has triggered at " << Time() << "."
              << std::endl;
  }
};

class SnoozeableAlarm : public Alarm {
 public:
  SnoozeableAlarm(int hour, int minute, std::string name)
      : Alarm(hour, minute, name) {}

  virtual void Trigger() {
    std::cout << "Alarm " << m_name << " has triggered at " << Time()
              << ". Snooze? (Y/N)" << std::endl;
    std::string input;
    std::cin >> input;
    if (input == std::string("Y")) {
      m_hour = (m_minute + 10) >= 60 ? (m_hour + 1) % 24 : m_hour;
      m_minute = (m_minute + 10) % 60;
    } else {
      m_active = false;
    }
  }
};

AlarmClock::~AlarmClock() {
  for (auto alarm : m_alarms) {
    delete alarm;
  }
}

void AlarmClock::TimeElapse() {
  for (const auto &alarm : m_alarms) {
    if (alarm->GetActive() && alarm->GetHour() == m_hour &&
        alarm->GetMinute() == m_minute) {
      alarm->Trigger();
    }
  }
  m_hour = (m_minute + 1) >= 60 ? (m_hour + 1) % 24 : m_hour;
  m_minute = (m_minute + 1) % 60;
}

void AlarmClock::AddAlarm(Alarm *alarm) {
  m_alarms.push_back(alarm);
}

void AlarmClock::Input() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string type, name;
    int hour, minute;
    std::cin >> type >> hour;
    std::cin.ignore(1, ':');
    std::cin >> minute >> name;
    if (type == std::string("R"))
      AddAlarm(new RepeatableAlarm(hour, minute, name));
    if (type == std::string("S"))
      AddAlarm(new SnoozeableAlarm(hour, minute, name));
  }
}

int main() {
  AlarmClock clock;
  for (int days = 0; days < 3; days++) {
    std::cout << "Do you want to add any alarms?" << std::endl;
    clock.Input();
    for (int minute = 0; minute < 24 * 60; minute++) {
      clock.TimeElapse();
    }
    std::cout << "A day has elapsed." << std::endl;
  }
  return 0;
}