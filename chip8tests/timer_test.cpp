#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <future>
#include "../src/chip8timer.hpp"
#include "../src/constants.hpp"

using namespace chip8;

void test_timer_thread(int seconds, std::promise<void> exitSignal){

    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    exitSignal.set_value();

}

TEST(timer_tests, check_add_time_exceptions){

    chip8Timer testTimer(constants::DELAY_MAX_DELTA_TIME, constants::DELAY_CYCLE_LENGTH);
    EXPECT_THROW({
        try{
            testTimer.addTime(256);
        }
        catch (InvalidTimerValueException& e){
            throw;
        }
    }, InvalidTimerValueException);

    EXPECT_THROW({
        try{
            testTimer.addTime(-1);
        }
        catch (InvalidTimerValueException& e){
            throw;
        }
    }, InvalidTimerValueException);

    EXPECT_NO_THROW({
        try{
            testTimer.addTime(255);
        }
        catch (InvalidTimerValueException& e){
            throw;
        }
    });

    EXPECT_NO_THROW({
        try{
            testTimer.addTime(0);
        }
        catch (InvalidTimerValueException& e){
            throw;
        }
    });

}

TEST (timer__test, check_delay_timer_accuracy){

    std::promise<void> exitSignal;
    std::future<void> futureObj = exitSignal.get_future();

    std::thread asyncThread(test_timer_thread, 3, std::move(exitSignal));

    chip8Timer testTimer(constants::DELAY_MAX_DELTA_TIME, constants::DELAY_CYCLE_LENGTH);
    testTimer.addTime(200);

    while (futureObj.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready){
        testTimer.step();
    }

    EXPECT_EQ(20, testTimer.getTimeInt());

    asyncThread.join();
    
}