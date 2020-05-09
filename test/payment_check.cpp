#include <unordered_set>
#include <vector>
#include <iostream>
#include <chrono>
#include <tuple>

#include <stdlib.h>
#include <time.h>

#include "gtest/gtest.h"
#include "payment.cpp"

TEST(payment, trivial_case) {
    const vector<tuple<string, string, double> > excpectedAnswer = vector<tuple<string, string, double> >();
    const vector<tuple<string, double>> transactionsInput = vector<tuple<string, double> >();
    EXPECT_EQ(excpectedAnswer, ProcessTransactions(transactionsInput));
}

TEST(payment, given_example) {
    const vector<tuple<string, string, double> > excpectedAnswer = vector<tuple<string, string, double> >({
        make_tuple("u1", "u2", 6),
        make_tuple("u1", "u3", 3)
    });
    const vector<tuple<string, double>> transactionsInput = vector<tuple<string, double> >({
        make_tuple("u1", -10), make_tuple("u2", 10),
        make_tuple("u2", -3), make_tuple("u3", 3),
        make_tuple("u2", -1), make_tuple("u1", 1)
    });
    EXPECT_EQ(excpectedAnswer, ProcessTransactions(transactionsInput));
}

TEST(payment, simple_example) {
    const vector<tuple<string, string, double> > excpectedAnswer = vector<tuple<string, string, double> >({
        make_tuple("a4", "e5", 12),
        make_tuple("a5", "b4", 2),
        make_tuple("u1", "u2", 10),
        make_tuple("u2", "u3", 3),
        make_tuple("u4", "u5", 5)
    });
    const vector<tuple<string, double>> transactionsInput = vector<tuple<string, double> >({
        make_tuple("u1", -10), make_tuple("u2", 10),
        make_tuple("u2", -3), make_tuple("u3", 3),
        make_tuple("u4", -5), make_tuple("u5", 5),
        make_tuple("a4", -12), make_tuple("e5", 12),
        make_tuple("b4", 2), make_tuple("a5", -2)
    });
    EXPECT_EQ(excpectedAnswer, ProcessTransactions(transactionsInput));
}

TEST(payment, resume_transactions_example) {
    const vector<tuple<string, string, double> > excpectedAnswer = vector<tuple<string, string, double> >({
        make_tuple("u1", "u3", 10)
    });
    const vector<tuple<string, double>> transactionsInput = vector<tuple<string, double> >({
        make_tuple("u1", -10), make_tuple("u2", 10),
        make_tuple("u2", -10), make_tuple("u3", 10)
    });
    EXPECT_EQ(excpectedAnswer, ProcessTransactions(transactionsInput));
}

TEST(payment, resume_transactions_example_2) {
    const vector<tuple<string, string, double> > excpectedAnswer = vector<tuple<string, string, double> >({
        make_tuple("u4", "u6", 5),
        make_tuple("u4", "u7", 5)
    });
    const vector<tuple<string, double>> transactionsInput = vector<tuple<string, double> >({
        make_tuple("u4", -10), make_tuple("u5", 10),
        make_tuple("u5", -5), make_tuple("u6", 5),
        make_tuple("u5", -5), make_tuple("u7", 5)
    });
    EXPECT_EQ(excpectedAnswer, ProcessTransactions(transactionsInput));
}
