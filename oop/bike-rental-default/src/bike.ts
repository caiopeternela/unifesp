import * as crypto from "crypto";

export class Bike {
  id: string
  availability: boolean
  location: {
    latitude: number
    longitude: number
  }
  rentedAt?: Date

  constructor(latitude: number = 0, longitude: number = 0) {
    this.id = crypto.randomUUID()
    this.availability = true
    this.location = {
      latitude: latitude,
      longitude: longitude,
    }
  }

  setLocation(latitude: number, longitude: number): void {
    this.location.latitude = latitude
    this.location.longitude = longitude
  }
}