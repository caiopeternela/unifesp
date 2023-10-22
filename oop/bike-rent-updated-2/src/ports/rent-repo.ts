import { Rent } from "../rent"

export interface RentRepo {
    add(rent: Rent): Promise<number>
    findOpen(bikeId: number, userEmail: string): Promise<Rent>
    update(id: number, rent: Rent): Promise<void>
    findOpenRentsFor(userEmail: string): Promise<Rent[]>
}