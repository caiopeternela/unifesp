import { Account } from './account'
import { AccountHolder } from './account-holder'

const john = new AccountHolder('John', '111222333-45')
const johnsAccount = new Account('123-45', john)

johnsAccount.credit(100.0)
johnsAccount.balance = -10

console.log("John's balance: ", johnsAccount.balance)
console.log(john)