import { PrismaBikeRepo } from "../../../src/external/database/prisma-bike-repo"
import { Bike } from "../../../src/bike"
import prisma from "../../../src/external/database/db"

describe("PrismaBikeRepo", () => {
    beforeEach(async () => {
        await prisma.bike.deleteMany({})
    })

    afterAll(async () => {
        await prisma.bike.deleteMany({})
    })

    it("adds a bike in the database", async () => {
        const bike = new Bike(
            "test bike",
            "mountain",
            18,
            100,
            9.99,
            "A good bike",
            4.5,
            "url1, url2",
            true,
            40.7128,
            -74.0060
        )
        const repo = new PrismaBikeRepo()
        const bikeId = await repo.add(bike)
        expect(bikeId).toBeDefined()
        const persistedBike = await repo.find(bikeId)
        expect(persistedBike.name).toEqual(bike.name)
    })

    it("removes a bike from the database", async () => {
        const bike = new Bike(
            "test bike",
            "mountain",
            18,
            100,
            9.99,
            "A good bike",
            4.5,
            "url1, url2",
            true,
            40.7128,
           -74.0060 
        )
        const repo = new PrismaBikeRepo()
        const bikeId = await repo.add(bike)
        await repo.remove(bikeId)
        const removedBike = await repo.find(bikeId)
        expect(removedBike).toBeNull()
    })

    it("lists bikes in the database", async () => {
        const bike1 = new Bike(
            "bike1",
            "road",
            16,
            80,
            8.99,
            "Fast road bike",
            4.0,
            "url1",
            true,
            34.0522,
           -118.2437
        )
        const bike2 = new Bike(
            "bike2",
            "electric",
            20,
            120,
            15.99,
            "Eco-friendly bike",
            4.8,
            "url2",
            true,
            37.7749,
           -122.4194
        )
        const repo = new PrismaBikeRepo()
        await repo.add(bike1)
        await repo.add(bike2)
        const bikeList = await repo.list()
        expect(bikeList.length).toEqual(2)
    })
})