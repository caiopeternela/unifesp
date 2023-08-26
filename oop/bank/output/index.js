"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const account_1 = require("./account");
const account_holder_1 = require("./account-holder");

const john = new account_holder_1.AccountHolder('John', '111222333-45');
const johnsAccount = new account_1.Account('123-45', john);

johnsAccount.credit(100.0);
johnsAccount.balance = -10;

console.log("John's balance: ", johnsAccount.balance);
console.log(john);