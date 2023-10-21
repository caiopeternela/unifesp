-- CreateTable
CREATE TABLE "Bike" (
    "id" TEXT NOT NULL PRIMARY KEY,
    "name" TEXT NOT NULL,
    "type" TEXT NOT NULL,
    "bodySize" INTEGER NOT NULL,
    "maxLoad" INTEGER NOT NULL,
    "rate" REAL NOT NULL,
    "description" TEXT NOT NULL,
    "ratings" REAL NOT NULL,
    "imageUrls" TEXT NOT NULL,
    "available" BOOLEAN NOT NULL DEFAULT true,
    "latitude" REAL NOT NULL,
    "longitude" REAL NOT NULL
);
