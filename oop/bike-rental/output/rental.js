"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Rental {
    constructor(user, bike) {
        this.user = user;
        this.bike = bike;
        this.startTime = new Date();
        bike.isRented = true;
    }
    endRental(station) {
        this.endTime = new Date();
        this.bike.isRented = false;
        station.addBike(this.bike);
        const durationInMinutes = (this.endTime.getTime() - this.startTime.getTime()) / 60000;
        const cost = durationInMinutes * Rental.pricePerMinute;
        this.user.deductAmount(cost);
    }
}
Rental.pricePerMinute = 0.50;
