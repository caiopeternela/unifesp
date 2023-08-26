import { User } from "./user"
import { Bike } from "./bike"
import { Station } from "./station"

const station = new Station("S1", 10)
const bike = new Bike("B1")
const user = new User("U1", "John", 100)

station.addBike(bike)

console.log(station.availableBikes)

user.rent(bike)

console.log(station.availableBikes)

user.startTime!.setHours(user.startTime!.getHours() - 2)
user.return(station)

console.log(user.balance)
console.log(station.availableBikes)