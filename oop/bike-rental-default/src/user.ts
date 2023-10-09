import * as crypto from "crypto"
import * as bcrypt from "bcrypt"

export class User {
  id: string
  email: string
  password: string
  passwordHash: string

  constructor(email: string, password: string) {
    this.id = crypto.randomUUID()
    this.email = email
    this.password = password
    this.passwordHash = this.setPassword(password)
  }

  setPassword(password: string): string {
    const salt = 10
    return bcrypt.hashSync(password, salt)
  }

  checkPassword(password: string): boolean {
    return bcrypt.compareSync(password, this.passwordHash)
  }
}