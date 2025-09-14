import { DataSource } from 'typeorm';
import { POSTGRES } from 'config';

import * as Entities from '@libs/entities';

import * as Migrations from './migrations';

const entities = Object.values(Entities);
const migrations = Object.values(Migrations);

export const dataSource = new DataSource({
  type: 'postgres',
  host: POSTGRES.HOST,
  port: POSTGRES.PORT,
  username: POSTGRES.USERNAME,
  password: POSTGRES.PASSWORD,
  database: POSTGRES.DB,
  migrationsRun: false,
  entities,
  synchronize: true,
  migrations: migrations,
});
