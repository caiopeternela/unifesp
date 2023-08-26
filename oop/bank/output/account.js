"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Account = void 0;
class Account {
	constructor(number, holder) {
    this._balance = 0.0;
    this.number = number;
    this.holder = holder;
  }
  
	credit(amount) {
    this._balance += amount;
  }
  
	debit(amount) {
    this._balance -= amount;
  }
    
	get balance() {
    return this._balance;
  }
    
	set balance(balance) {
    if (balance >= 0)
      this._balance = balance;
    }
}
exports.Account = Account;