import { App } from "./app"
import { Bike } from "./bike"
import { User } from "./user"
import sinon from "sinon"

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

  it("should be able to add a new user", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    expect(app.findUser(user.email)).toEqual(user)
  })

  it("should throw an error if trying to add a user with an existing email", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    expect(() => app.addUser(new User("user@email.com", "456"))).toThrowError("User with same email already registered.")
  })

  it("should authenticate user with correct credentials", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    expect(app.authUser(user.email, "123")).toBeTruthy()
  })

  it("should not authenticate user with incorrect credentials", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    expect(app.authUser(user.email, "456")).toBeFalsy()
  })

  it("should register a bike successfully", () => {
    const app = new App()
    const bike = new Bike()
    app.registerBike(bike)
    expect(app.bikes).toContain(bike)
  })

  it("should throw an error when trying to register a duplicate bike", () => {
    const app = new App()
    const bike = new Bike()
    app.registerBike(bike)
    expect(() => app.registerBike(bike)).toThrowError("Duplicate bike.")
  })

  it("should remove a user successfully", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    app.addUser(user)
    app.removeUser(user)
    expect(app.users).not.toContain(user)
  })

  it("should remove a bike successfully", () => {
    const app = new App()
    const bike = new Bike()
    app.registerBike(bike)
    app.removeBike(bike)
    expect(app.bikes).not.toContain(bike)
  })

  it("should rent an available bike successfully", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    const bike = new Bike()
    app.addUser(user)
    app.registerBike(bike)
    const rentedBike = app.rentBike(user.email, bike.id)
    expect(rentedBike).toEqual(bike)
    expect(rentedBike?.availability).toBeFalsy()
  })

  it("should throw an error when trying to rent an unavailable bike", () => {
    const app = new App()
    const user = new User("user@email.com", "123")
    const bike = new Bike()
    app.addUser(user)
    app.registerBike(bike)
    bike.availability = false
    expect(() => app.rentBike(user.email, bike.id)).toThrowError("Bike is not available for rent.")
  })

  it("should throw an error when trying to rent a bike to an unregistered user", () => {
    const app = new App()
    const bike = new Bike()
    app.registerBike(bike)
    expect(() => app.rentBike("fake@email.com", bike.id)).toThrowError("User not found.")
  })
})