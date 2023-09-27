import { Bike } from "./bike";
import { Rent } from "./rent";
import { User } from "./user";

export class App {
  users: User[] = []
  bikes: Bike[] = []
  rents: Rent[] = []
  pricePerHour: number = 10

  addUser(user: User): void {
    if (this.users.some(existingUser => existingUser.email === user.email)) {
      throw new Error("User with same email already registered.")
    }
    this.users.push(user)
  }

  findUser(email: string): User | undefined {
    return this.users.find(user => user.email === email)
  }

  authUser(email: string, password: string): boolean {
    const user = this.findUser(email)
    if (!user) {
      return false
    }
    return user.checkPassword(password)
  }

  registerBike(bike: Bike): void {
    if (this.bikes.some(existingBike => existingBike.id === bike.id)) {
      throw new Error("Duplicate bike.")
    }
    this.bikes.push(bike)
  }

  removeUser(user: User): void {
    this.users = this.users.filter(u => u.id !== user.id)
  }

  removeBike(bike: Bike): void {
    this.bikes = this.bikes.filter(b => b.id !== bike.id)
  }

  rentBike(email: string, bikeId: string): Bike | undefined {
    const user = this.findUser(email)
    if (!user) {
      throw new Error("User not found.")
    }
    
    const bike = this.bikes.find(bike => bike.id === bikeId)
    if (!bike) {
      throw new Error("Bike not found.")
    }
  
    if (!bike.availability) {
      throw new Error("Bike is not available for rent.")
    }
  
    bike.availability = false
    bike.rentedAt = new Date()
    return bike
  }

  updateBikeLocation(bikeId: string, latitude: number, longitude: number): void {
    const bike = this.bikes.find(bike => bike.id === bikeId)
    if (!bike) {
      throw new Error("Bike not found.")
    }
    bike.setLocation(latitude, longitude)
  }

  returnBike(bikeId: string): number | undefined {
    const bike = this.bikes.find(bike => bike.id === bikeId)
    if (!bike) {
      throw new Error("Bike not found.")
    }
    if (bike.availability) {
      throw new Error("Bike is already available.")
    }
    bike.availability = true
    const rentalHours = Math.ceil((new Date().getTime() - bike.rentedAt!.getTime()) / (1000 * 60 * 60))
    return rentalHours * this.pricePerHour
  }

  listUsers(): User[] {
    return this.users
  }

  listRents(): Rent[] {
    return this.rents
  }

  listBikes(): Bike[] {
    return this.bikes
  }
}