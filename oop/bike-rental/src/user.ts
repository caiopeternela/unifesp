import { Bike } from "./bike"
import { Station } from "./station"

export class User {
  id: string
  name: string
  bike?: Bike
  startTime?: Date
  balance: number

  constructor(id: string, name: string, balance: number) {
    this.id = id
    this.name = name
    this.balance = balance
  }

  rent(bike: Bike): void {
    if (!bike.inUse) {
      this.bike = bike
      bike.inUse = true
      this.startTime = new Date()
    } else {
      console.log("This bike is unavailable!")
    }
  }

  return(station: Station): void {
    if (this.bike && this.startTime) {
      const bill = station.pricePerHour * Math.ceil((new Date().getTime() - this.startTime!.getTime()) / (60 * 60 * 1000))
      this.balance -= bill
      this.bike!.inUse = false
      this.bike = undefined
    }
  }
}