import { UserRepo } from "./user-repo"
import { User } from "../user"
import prisma from "../../prisma/client"

export class PrismaUserRepo implements UserRepo {
  private prismaClient = prisma

  async find(email: string): Promise<User | null> {
    const user = await this.prismaClient.user.findUnique({
      where: { email: email },
    })

    if (!user) return null

    return new User(user.name, user.email, user.password, user.id)
  }

  async add(user: User): Promise<string> {
    const newUser = await this.prismaClient.user.create({
      data: {
        name: user.name,
        email: user.email,
        password: user.password,
      },
    })

    return newUser.id
  }

  async remove(email: string): Promise<void> {
    await this.prismaClient.user.delete({
      where: { email: email },
    })
  }

  async list(): Promise<User[]> {
    const users = await this.prismaClient.user.findMany()
    return users.map(user => new User(user.name, user.email, user.password, user.id))
  }
}