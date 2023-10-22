import { Bike } from "../bike"

export interface BikeRepo {
    find(id: number): Promise<Bike>
    add(bike: Bike): Promise<number>
    remove(id: number): Promise<void>
    update(id: number, bike: Bike): Promise<void>
    list(): Promise<Bike[]>
}