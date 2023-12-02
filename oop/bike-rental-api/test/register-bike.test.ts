import request from 'supertest'
import server from '../src/server'
import prisma from '../src/external/database/db'

describe('Register bike route', () => {
  beforeEach(async () => {
      await prisma.user.deleteMany({})
  })

  afterAll(async () => {
      await prisma.user.deleteMany({})
  })

  it('registers a bike with valid data', async () => {
      await request(server)
          .post('/api/bikes')
          .send({
              model: 'Mountain Bike',
              location: { latitude: 40.7128, longitude: -74.0060 },
              rate: 15
          })
          .expect(201)
          .then((res) => {
              expect(res.body.id).toBeDefined();
          });
  });

  it('returns 500 when trying to register a bike that causes an error', async () => {
      await request(server)
          .post('/api/bikes')
          .send({
              name: "caloi mountainbike",
              type: "mountain bike",
              bodySize: 1234,
              maxLoad: 1234,
              rate: 100.0, 
              description: "My bike",
              ratings: 5,
              imageUrl: "url1"
          })
          .expect(201);

      await request(server)
          .post('/api/bikes')
          .send({})
          .expect(500);
  });
});
