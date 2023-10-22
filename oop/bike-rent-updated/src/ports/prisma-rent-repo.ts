import { RentRepo } from "./rent-repo"
import { Rent } from "../rent"
import prisma from "../../prisma/client"

export class PrismaRentRepo implements RentRepo {
    private prismaClient = prisma

    async add(rent: Rent): Promise<number> {
        const newRent = await this.prismaClient.rent.create({
            data: {
              start: rent.start,
              bike: rent.bike,
              user: rent.user,
            },
          })
      
        return newRent.id
    }

    async findOpen(bikeId: number, userEmail: string): Promise<Rent> {
        const openRent = await this.prismaClient.rent.findUnique({
          where: {
            user: {
              email: userEmail,
            },
            bike: {
                id: bikeId
            },
            end: undefined
          },
          //include: {
            // bike: true,
            // user: true,
        //  },
        });

        return new Rent(openRent.bike, openRent.user, openRent.start)
    }

    async update(id: number, rent: Rent): Promise<void> {
        await this.prismaClient.bike.update({
            where: { id: id},
            data: {
                start: rent.start,
                bike: rent.bike,
                user: rent.user,
            }
        })
    }

    async findOpenRentsFor(userEmail: string): Promise<Rent[]> {
        const openRents = await this.prismaClient.rent.findMany({
            where: {
              user: {
                email: userEmail,
              },
              end: undefined
            },
            //include: {
              // user: true,
          //  },
          });

        return openRents.map(openRent => new Rent(openRent.bike, openRent.user, openRent.start))
    }
}