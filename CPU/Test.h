#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>

class SimpleTest {
private:
    static std::vector<std::pair<std::string, std::function<void()>>> tests;
    static int passCount;
    static int failCount;

public:
    static void addTest(const std::string& name, std::function<void()> test) {
        tests.push_back(std::make_pair(name, test));
    }

    static void runAll() {
        for (const auto& test : tests) {
            std::cout << "Running test: " << test.first << std::endl;
            test.second();
        }
        std::cout << "\nTest results: " << passCount << " passed, " << failCount << " failed" << std::endl;
    }

    template<typename T>
    static void assertEqual(const T& expected, const T& actual, const std::string& message = "") {
        if (expected == actual) {
            std::cout << "PASS: " << message << std::endl;
            passCount++;
        } else {
            std::cout << "FAIL: " << message << " (Expected " << expected << ", got " << actual << ")" << std::endl;
            failCount++;
        }
    }

    static void assertTrue(bool condition, const std::string& message = "") {
        if (condition) {
            std::cout << "PASS: " << message << std::endl;
            passCount++;
        } else {
            std::cout << "FAIL: " << message << std::endl;
            failCount++;
        }
    }
};

std::vector<std::pair<std::string, std::function<void()>>> SimpleTest::tests;
int SimpleTest::passCount = 0;
int SimpleTest::failCount = 0;

#define TEST(name) \
    void name(); \
    struct name##_register { \
        name##_register() { SimpleTest::addTest(#name, name); } \
    } name##_register_instance; \
    void name()

#endif // SIMPLE_TEST_H