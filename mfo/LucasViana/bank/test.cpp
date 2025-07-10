#include <assert.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "bank.hpp"

using json = nlohmann::json;
using namespace std;

enum class Action {
  Init,
  Deposit,
  Withdraw,
  Transfer,
  BuyInvestment,
  SellInvestment,
  Unknown
};

Action stringToAction(const std::string& actionStr) {
  static const std::unordered_map<std::string, Action> actionMap = {
      {"init", Action::Init},
      {"deposit_action", Action::Deposit},
      {"withdraw_action", Action::Withdraw},
      {"transfer_action", Action::Transfer},
      {"buy_investment_action", Action::BuyInvestment},
      {"sell_investment_action", Action::SellInvestment}};

  auto it = actionMap.find(actionStr);
  if (it != actionMap.end()) {
    return it->second;
  } else {
    return Action::Unknown;
  }
}

int int_from_json(json j) {
  string s = j["#bigint"];
  return stoi(s);
}

map<string, int> balances_from_json(json j) {
  map<string, int> m;
  for (auto it : j["#map"]) {
    m[it[0]] = int_from_json(it[1]);
  }
  return m;
}

map<int, Investment> investments_from_json(json j) {
  map<int, Investment> m;
  for (auto it : j["#map"]) {
    m[int_from_json(it[0])] = {.owner = it[1]["owner"],
                               .amount = int_from_json(it[1]["amount"])};
  }
  return m;
}

BankState bank_state_from_json(json state) {
  map<string, int> balances = balances_from_json(state["balances"]);
  map<int, Investment> investments =
      investments_from_json(state["investments"]);
  int next_id = int_from_json(state["next_id"]);
  return {.balances = balances, .investments = investments, .next_id = next_id};
}

void printBankState(const BankState& state) {
  // Balances
  std::cout << "Balances:" << std::endl;
  if (state.balances.empty()) {
    std::cout << "  No balances found." << std::endl;
  } else {
    for (const auto& pair : state.balances) {
      std::cout << "  Account: " << pair.first << ", Balance: " << pair.second
                << std::endl;
    }
  }

  // Investments
  std::cout << "Investments:" << std::endl;
  if (state.investments.empty()) {
    std::cout << "  No investments found." << std::endl;
  } else {
    for (const auto& pair : state.investments) {
      std::cout << "  Investment ID: " << pair.first << std::endl;
      std::cout << "    Owner: " << pair.second.owner
                << ", Amount: " << pair.second.amount << std::endl;
    }
  }
}

int main() {
  for (int i = 0; i < 5000; i++) {
    cout << "Trace #" << i << endl;
    std::ifstream f("traces/out" + to_string(i) + ".itf.json");
    json data = json::parse(f);

    // Estado inicial: começamos do mesmo estado incial do trace
    BankState bank_state =
        bank_state_from_json(data["states"][0]["bank_state"]);

    auto states = data["states"];
    for (auto state : states) {
      string action = state["mbt::actionTaken"];
      json nondet_picks = state["mbt::nondetPicks"];

      string error = "";

      // Próxima transição
      switch (stringToAction(action)) {
        case Action::Init: {
          cout << "initializing" << endl;
          break;
        }
        case Action::Deposit: {
          string depositor = nondet_picks["depositor"]["value"];
          int amount = int_from_json(nondet_picks["amount"]["value"]);

          cout << "Depositing " << amount << " from " << depositor << endl;
          error = deposit(bank_state, depositor, amount);

          break;
        }
        case Action::Withdraw: {
          string withdrawer = nondet_picks["withdrawer"]["value"];

          int amount = int_from_json(nondet_picks["amount"]["value"]);
          cout << "Withdrawing " << amount << " from " << withdrawer << endl;
          error = withdraw(bank_state, withdrawer, amount);

          break;
        }
        case Action::Transfer: {
          string sender = nondet_picks["sender"]["value"];
          string receiver = nondet_picks["receiver"]["value"];
          int amount = int_from_json(nondet_picks["amount"]["value"]);

          cout << "Transfering " << amount << " from " << sender << " to "
               << receiver << endl;
          error = transfer(bank_state, sender, receiver, amount);

          break;
        }
        case Action::BuyInvestment: {
          string buyer = nondet_picks["buyer"]["value"];
          int amount = int_from_json(nondet_picks["amount"]["value"]);

          cout << "Buying " << amount << " investment from " << buyer << endl;
          error = buy_investment(bank_state, buyer, amount);

          break;
        }
        case Action::SellInvestment: {
          string seller = nondet_picks["seller"]["value"];
          int investment_id = int_from_json(nondet_picks["id"]["value"]);

          cout << "Selling investment with ID " << investment_id << " from "
               << seller << endl;
          error = sell_investment(bank_state, seller, investment_id);

          break;
        }
        default: {
          cout << "TODO: fazer a conexão para as outras ações. Ação: " << action
               << endl;
          error = "";
          break;
        }
      }

      cout << endl;
      std::cout << "--- Bank State ---" << std::endl;
      printBankState(bank_state);
      cout << endl;

      std::cout << "--- Expected Bank State ---" << std::endl;
      BankState expected_bank_state = bank_state_from_json(state["bank_state"]);
      printBankState(expected_bank_state);

      string expected_error = string(state["error"]["tag"]).compare("Some") == 0
                                  ? state["error"]["value"]
                                  : "";
      cout << "Actual error:" << error << endl;
      cout << "Expected error: " << expected_error << endl;
      cout << "------------------" << endl;

      assert(error == expected_error);
      assert(bank_state == expected_bank_state);
    }
  }
  return 0;
}
