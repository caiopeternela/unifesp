import { Bike } from "./bike";
import { Rent } from "./rent";
import { User } from "./user";
import crypto from 'crypto';
import bcrypt from 'bcrypt'

export class App {
    users: User[] = []
    bikes: Bike[] = []
    rents: Rent[] = []

    addUser(user: User): void {
      if (this.users.some(rUser => rUser.email === user.email)) {
          throw new Error('User with same email already registered.')
      }

      const salt = bcrypt.genSaltSync(10);
      user.password = bcrypt.hashSync(user.password, salt);

      this.users.push(user);
    }

    authUser(userId: string, password: string): boolean {
      const user = this.users.find(user => user.id === userId)
      if (!user) {
          return false;
      }

      return bcrypt.compareSync(password, user.password);
    }
  
    findUser(email: string): User | undefined {
      return this.users.find(user => user.email === email)
    }
  
    registerUser(user: User): void {
      for (const rUser of this.users) {
        if (rUser.email === user.email) {
          throw new Error("Duplicate user.")
        }
      }
      user.id = crypto.randomUUID()
      this.users.push(user)
    }
  
    removeUser(user: User): void {
      this.users = this.users.filter(u => u.id !== user.id)
    }
  
    removeBike(bike: Bike): void {
      this.bikes = this.bikes.filter(b => b.id !== bike.id)
    }
  
    rentBike(bike: Bike, user: User, startDate: Date, endDate: Date): Rent {
      return Rent.create(this.rents, bike, user, startDate, endDate)
    }
  
    registerBike(bike: Bike): void {
      this.bikes.forEach(b => {
        if (b.id == bike.id) {
          throw new Error("Duplicate bike.")
        }
      })
      bike.id = crypto.randomUUID()
      this.bikes.push(bike)
    }

    listUsers(): User[] {
      return this.users;
    }

    listRents(): Rent[] {
      return this.rents;
    }

    listBikes(): Bike[] {
      return this.bikes;
    }
}
