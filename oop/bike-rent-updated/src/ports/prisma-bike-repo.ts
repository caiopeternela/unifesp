import { BikeRepo } from "./bike-repo"
import { Bike } from "../bike"
import prisma from "../../prisma/client"

export class PrismaBikeRepo implements BikeRepo {
    private prismaClient = prisma

    async find(id: number): Promise<Bike> {
        const bike = this.prismaClient.bike.findUnique({
            where: { id: id }
        })

        if (!bike) return null

        return new Bike(
            bike.name,
            bike.type,
            bike.bodySize,
            bike.maxLoad,
            bike.rate,
            bike.ratings,
            bike.imageUrl,
            bike.available,
            bike.location,
        )
    }

    async add(bike: Bike): Promise<number> {
        const newBike = await this.prismaClient.bike.create({
            data: {
                name: bike.name,
                type: bike.type,
                bodySize: bike.bodySize,
                maxLoad: bike.maxLoad,
                rate: bike.rate,
                rating: bike.ratings,
                imageUrl: bike.imageUrl,
                available: bike.available,
                location: bike.location,
            }
        })
        return newBike.id
    }

    async remove(id: number): Promise<void> {
        await this.prismaClient.bike.delete({
            where: { id: id }
        })
    }

    async list(): Promise<Bike[]> {
        const bikes = prisma.bike.findMany()
        return bikes.map(bike => new Bike(
            bike.name,
            bike.type,
            bike.bodySize,
            bike.maxLoad,
            bike.rate,
            bike.ratings,
            bike.imageUrl,
            bike.available,
            bike.location,
        ))
    }

    async update(id: number, bike: Bike): Promise<void> {
        await this.prismaClient.bike.update({
            where: { id: id},
            data: {
                name: bike.name,
                type: bike.type,
                bodySize: bike.bodySize,
                maxLoad: bike.maxLoad,
                rate: bike.rate,
                rating: bike.ratings,
                imageUrl: bike.imageUrl,
                available: bike.available,
                location: bike.location,
            }
        })
    }
}