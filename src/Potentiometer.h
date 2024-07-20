#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer {
public:
    void begin(int pin, int interval);
    int read();
    void update(unsigned long currentTime);
    void checkConnection();
    bool isConnected();

private:
    int _pin;
    int _lastValue;
    unsigned long _lastReadTime;
    int _interval;
    void readAndNotify();
};

#endif
