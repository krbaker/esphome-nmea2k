#ifndef _GWTIMER_H
#define _GWTIMER_H
#include <vector>
#include <functional>
#include "esphome.h"
// #include <Arduino.h>
class GwIntervalRunner{
    public:
    using RunFunction=std::function<void(void)>;
    private:
    class Run{
        public:
        RunFunction runner;
        unsigned long interval=0;
        unsigned long last=0;
        Run(RunFunction r,unsigned long iv,unsigned long l=0):
            runner(r),interval(iv),last(l){}
        bool shouldRun(unsigned long now){
            if ((last+interval) > now) return false;
            last=now;
            return true;
        }
        bool runIf(unsigned long now){
            if (shouldRun(now)) {
                runner();
                return true;
            }
            return false;
        }
    };
    std::vector<Run> runners;
    unsigned long startTime=0;
    public:
    GwIntervalRunner(unsigned long now=esphome::millis()){
        startTime=now;
    }
    void addAction(unsigned long interval,RunFunction run,unsigned long start=0){
        if (start==0) start=startTime;
        runners.push_back(Run(run,interval,start));
    }
    bool loop(unsigned long now=esphome::millis()){
        bool rt=false;
        for (auto it=runners.begin();it!=runners.end();it++){
            if (it->runIf(now)) rt=true;
        }
        return rt;
    }
};
#endif