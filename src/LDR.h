#ifndef LDR_H
#define LDR_H

class LDR {
public:
    void begin(int pin, int interval);
    int read();
    void update(unsigned long currentTime);
    void checkConnection();
    bool isConnected();
     void readAndNotify();

private:
    int _pin;
    int _lastValue;
    unsigned long _lastReadTime;
    int _interval;
   
};

#endif
