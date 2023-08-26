"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Station = void 0;
class Station {
    constructor(id, pricePerHour) {
        this.bikes = [];
        this.id = id;
        this.pricePerHour = pricePerHour;
    }
    addBike(bike) {
        this.bikes.push(bike);
    }
    removeBike(bike) {
        this.bikes = this.bikes.filter(b => b.id !== bike.id);
    }
    get availableBikes() {
        return this.bikes.filter(bike => !bike.inUse);
    }
}
exports.Station = Station;
