#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>

#ifndef __PAYMENT_PAYMENT_HPP_
#define __PAYMENT_PAYMENT_HPP_

using namespace std;

/// O(t^3)
/// \param transactions Transactions.
/// \param delta Considered zero.
/// \return Unnecessary transactions removed.
unordered_map<string, unordered_map<string, double> >
RemoveUnnecessaryTransactions(const unordered_map<string, unordered_map<string, double> > &transactions,
                              const double delta = 1e-5) {
    unordered_map<string, unordered_map<string, double> > resp, inve;
    // O(t * tx * ti), where t = transactions.size()
    // O(t^3)
    for (auto &x : transactions) {
        // O(tx * (1 + ti + 1) ), where tx = x.second.size()
        // O(tx * ti)
        for (auto &y : x.second) {
            if (resp.find(x.first) != resp.end() && resp[x.first].find(y.first) != resp[x.first].end()) {
                // O(1), linear time only occurs if all hashes collide
                resp[x.first][y.first] += y.second;
                inve[y.first][x.first] += y.second;
            } else if (inve.find(x.first) != inve.end()) {
                bool found = false;
                auto temp = y.first;
                auto bestValue = y.second;
                // O(ti), where ti = inve.size()
                for (auto &z : inve[x.first]) {
                    if (z.second >= y.second) {
                        if (!found || z.second >= bestValue) {
                            temp = z.first;
                            bestValue = y.second;
                        }
                        found = true;
                    }
                }
                // O(1)
                if (found) {
                    // O(1), linear time only occurs if all hashes collide
                    resp[temp][x.first] -= bestValue;
                    inve[x.first][temp] -= bestValue;
                    if (abs(resp[temp][x.first]) < delta) {
                        resp[temp].erase(resp[temp].find(x.first));
                        inve[x.first].erase(inve[x.first].find(temp));
                    }

                    // O(1), linear time only occurs if all hashes collide
                    resp[temp][y.first] += bestValue;
                    inve[y.first][temp] += bestValue;
                    if (abs(resp[temp][y.first]) < delta) {
                        resp[temp].erase(resp[temp].find(y.first));
                        inve[y.first].erase(inve[y.first].find(temp));
                    }
                } else {
                    // O(1), linear time only occurs if all hashes collide
                    resp[x.first][y.first] = y.second;
                    inve[y.first][x.first] = y.second;
                }
            } else {
                // O(1), linear time only occurs if all hashes collide
                resp[x.first][y.first] = y.second;
                inve[y.first][x.first] = y.second;
            }
        }
    }
    return resp;
}

/// O(t^3)
/// \param inputTransactions Transactions from the input.
/// \param resultSorted Indicates if should sort the result.
/// \param delta Considered zero.
/// \return Transactions processed.
vector<tuple<string, string, double> >
ProcessTransactions(vector<tuple<string, double> > inputTransactions, bool resultSorted = true,
                    const double delta = 1e-5) {
    int size = inputTransactions.size();
    if (size % 2 == 1) {
        throw invalid_argument("Invalid number of transactions.");
    }
    // Using a unsorted map to find the values in constant time
    // O(t), where t = inputTransactions.size()
    unordered_map<string, unordered_map<string, double> > transactions;
    for (int i = 0; i < size; i += 2) {
        auto value1 = inputTransactions[i];
        auto value2 = inputTransactions[i + 1];
        if (get<0>(value2) < get<0>(value1)) {
            swap(value1, value2);
        }

        auto user1 = get<0>(value1);
        auto user2 = get<0>(value2);
        if (user1 == user2) {
            throw invalid_argument("Transactions must have different source and destination.");
        }
        if (transactions.find(user1) == transactions.end()) {
            transactions.emplace(user1, unordered_map<string, double>());
        }
        if (transactions[user1].find(user2) == transactions[user1].end()) {
            transactions[user1].emplace(user2, 0);
        }
        if (abs(get<1>(value1)) - abs(get<1>(value2)) > delta) {
            throw invalid_argument("Transactions must have the same value.");
        }
        // O(1), linear time only occurs if all hashes collide
        transactions[user1][user2] += get<1>(value2);
    }
    {
        unordered_map<string, unordered_map<string, double> > tempTransactions;
        // O(t2) = Sum(tx) for all x in transactions, but Sum(tx) == t
        // O(t2) = O(t)
        for (auto &x : transactions) {
            // O(tx), where tx = x.second.size()
            for (auto &y : x.second) {
                if (y.second > 0) {
                    // O(1), linear time only occurs if all hashes collide
                    tempTransactions[x.first][y.first] = y.second;
                } else {
                    // O(1), linear time only occurs if all hashes collide
                    tempTransactions[y.first][x.first] = -y.second;
                }
            }
        }
        // O(t^3)
        transactions = RemoveUnnecessaryTransactions(tempTransactions, delta);
    }

    vector<tuple<string, string, double> > resp;
    if (resultSorted) {
        // Creating the map to sort the result
        // O(t3) = Sum(tx * log(tx)) for all x in transactions
        for (auto &x : map<string, unordered_map<string, double> >(transactions.begin(), transactions.end())) {
            // O(tx + tx * log(tx) ), where tx = x.second.size()
            // O(tx * log(tx) )
            for (auto &y : map<string, double>(x.second.begin(), x.second.end())) {
                resp.push_back(make_tuple(x.first, y.first, y.second));
            }
        }
    } else {
        // O(t4) = Sum(tx) for all x in transactions, but Sum(tx) == t
        // O(t4) = O(t)
        for (auto &x : transactions) {
            // O(tx), where tx = x.second.size()
            for (auto &y : x.second) {
                resp.push_back(make_tuple(x.first, y.first, y.second));
            }
        }
    }
    return resp;
}

#endif
