import { Bike } from "./bike"

export class Station {
    id: string
    bikes: Bike[] = []
    pricePerHour: number

    constructor(id: string, pricePerHour: number) {
      this.id = id
      this.pricePerHour = pricePerHour
    }

    addBike(bike: Bike): void {
      this.bikes.push(bike)
    }

    removeBike(bike: Bike): void {
      this.bikes = this.bikes.filter(b => b.id !== bike.id);
    }

    get availableBikes(): Array<Bike> {
      return this.bikes.filter(bike => !bike.inUse)
    }
}