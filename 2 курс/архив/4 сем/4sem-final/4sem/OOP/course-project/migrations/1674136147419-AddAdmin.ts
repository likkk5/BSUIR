import { MigrationInterface, QueryRunner } from 'typeorm';

export class AddAdmin1674136147419 implements MigrationInterface {
  public async up(queryRunner: QueryRunner): Promise<void> {
    const adminName = 'admin';
    const adminEmail = 'admin@admin.com';
    const hashedPassword = '$2a$12$CvznUn5xwYpb8Kx3aOudCO5/Gq82an/9yM/jpnbkcbdHFBww6vmuS';

    await queryRunner.query(`
        INSERT INTO "user" (name, password, email, "normalizedEmail", role)
        VALUES ('${adminName}', '${hashedPassword}', '${adminEmail}', '${adminEmail}', 'admin');
    `);
  }

  public async down(queryRunner: QueryRunner): Promise<void> {
    await queryRunner.query(`
        DELETE FROM "user"
        WHERE "normalizedEmail" = 'admin@admin.com'
    `);
  }
}
