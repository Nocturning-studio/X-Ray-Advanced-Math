#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

#define XRTEST_STRINGIFY_IMPL(x) #x
#define XRTEST_STRINGIFY(x)      XRTEST_STRINGIFY_IMPL(x)

class TestRunner
{
public:
    static TestRunner& instance()
    {
        static TestRunner runner;
        return runner;
    }

    void addResult(const std::string& testName, bool passed, const std::string& info = "")
    {
        if (passed)
        {
            ++passedCount_;
            if (verbose_)
                std::cout << "[PASS] " << testName;
        }
        else
        {
            ++failedCount_;
            if (verbose_)
                std::cout << "[FAIL] " << testName;
        }
        if (!info.empty() && verbose_)
            std::cout << "  (" << info << ")";
        if (verbose_)
            std::cout << std::endl;
    }

    void setVerbose(bool verbose) { verbose_ = verbose; }

    int printSummary()
    {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Tests passed: " << passedCount_ << std::endl;
        std::cout << "Tests failed: " << failedCount_ << std::endl;
        if (failedCount_ == 0)
            std::cout << "All tests passed!" << std::endl;
        else
            std::cout << "Some tests FAILED!" << std::endl;
        std::cout << "========================================" << std::endl;

        return failedCount_ == 0 ? 0 : 1;
    }

private:
    TestRunner() = default;

    int passedCount_ = 0;
    int failedCount_ = 0;
    bool verbose_    = true;
};

#define CHECK(expr) \
    do { \
        bool result = (expr); \
        TestRunner::instance().addResult( \
            XRTEST_STRINGIFY(expr), result, \
            result ? "" : "value was false" \
        ); \
    } while(0)

#define CHECK_EQ(a, b) \
    do { \
        auto va = (a); \
        auto vb = (b); \
        bool result = (va == vb); \
        std::ostringstream info; \
        if (!result) info << va << " != " << vb; \
        TestRunner::instance().addResult( \
            XRTEST_STRINGIFY(a) " == " XRTEST_STRINGIFY(b), \
            result, info.str() \
        ); \
    } while(0)

#define CHECK_NE(a, b) \
    do { \
        auto va = (a); \
        auto vb = (b); \
        bool result = (va != vb); \
        std::ostringstream info; \
        if (!result) info << va << " == " << vb; \
        TestRunner::instance().addResult( \
            XRTEST_STRINGIFY(a) " != " XRTEST_STRINGIFY(b), \
            result, info.str() \
        ); \
    } while(0)

#define CHECK_THROW(expr, exception_type) \
    do { \
        bool caught = false; \
        try { expr; } \
        catch (const exception_type&) { caught = true; } \
        catch (...) {} \
        TestRunner::instance().addResult( \
            "throws " XRTEST_STRINGIFY(exception_type) ": " XRTEST_STRINGIFY(expr), \
            caught, caught ? "" : "did not throw" \
        ); \
    } while(0)

#define CHECK_NO_THROW(expr) \
    do { \
        bool ok = true; \
        try { expr; } \
        catch (...) { ok = false; } \
        TestRunner::instance().addResult( \
            "no throw: " XRTEST_STRINGIFY(expr), ok, ok ? "" : "unexpected exception" \
        ); \
    } while(0)

inline void setTestVerbose(bool verbose)
{
    TestRunner::instance().setVerbose(verbose);
}
