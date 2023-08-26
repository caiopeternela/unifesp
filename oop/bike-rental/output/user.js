"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.User = void 0;
class User {
    constructor(id, name, balance) {
        this.id = id;
        this.name = name;
        this.balance = balance;
    }
    rent(bike) {
        if (!bike.inUse) {
            this.bike = bike;
            bike.inUse = true;
            this.startTime = new Date();
        }
        else {
            console.log("This bike is unavailable!");
        }
    }
    return(station) {
        if (this.bike && this.startTime) {
            const bill = station.pricePerHour * Math.ceil((new Date().getTime() - this.startTime.getTime()) / (60 * 60 * 1000));
            this.balance -= bill;
            this.bike.inUse = false;
            this.bike = undefined;
        }
    }
}
exports.User = User;
