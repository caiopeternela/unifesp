export class OpenRentError extends Error {
  public readonly name = "OpenRentError"

  constructor() {
      super("User has open rents.")
  }
}