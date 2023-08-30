"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.App = void 0;
class App {
    constructor() {
        this.users = [];
        this.bikes = [];
        this.rents = [];
    }
    addUser(user) {
        if (this.users.some(rUser => { return rUser.email === user.email; })) {
            throw new Error('User with same email already registered.');
        }
        this.users.push(user);
    }
}
exports.App = App;
