import { App } from "./app";
import { Bike } from "./bike";
import { User } from "./user";
import sinon from "sinon";

describe("App", () => {
  it("should correctly calculate the rent amount", async () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    const bike = new Bike()
    app.registerBike(bike)
    const clock = sinon.useFakeTimers()
    app.rentBike(user.email, bike.id)
    const hour = 1000 * 60 * 60
    clock.tick(2 * hour)
    const rentAmount = app.returnBike(bike.id)
    expect(rentAmount).toEqual(20)
    clock.restore()
  })

  it("should be able to move a bike to a specific location", () => {
    const app = new App()
    const bike = new Bike()
    app.registerBike(bike)
    const saoPaulo = { latitude: -23.550520, longitude: -46.633308 }
    app.updateBikeLocation(bike.id, saoPaulo.latitude, saoPaulo.longitude)
    expect(bike.location.latitude).toEqual(saoPaulo.latitude)
    expect(bike.location.longitude).toEqual(saoPaulo.longitude)
  })

  it("should throw an exception when trying to move an unregistered bike", () => {
    const app = new App()
    expect(() => {
      app.updateBikeLocation("fakeBikeId", -23.550520, -46.633308)
    }).toThrowError("Bike not found.")
  })
})