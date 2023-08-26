import { AccountHolder } from './account-holder'

export class Account {
  private _balance: number = 0.0
  number: string
  holder: AccountHolder

  constructor(number: string, holder: AccountHolder) {
    this.number = number
    this.holder = holder
  }

  credit(amount: number): void {
    this._balance += amount
  }

  debit(amount: number): void {
    this._balance -= amount
  }

  get balance(): number {
    return this._balance
  }

  set balance(balance: number) {
    if (balance >= 0) this._balance = balance
  }
}