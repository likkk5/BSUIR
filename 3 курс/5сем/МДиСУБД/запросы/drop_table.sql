DROP TABLE notification;
ALTER TABLE "user" DROP COLUMN phone_number;

ALTER TABLE guest DROP CONSTRAINT guest_passport_number_key;
ALTER TABLE guest ADD CONSTRAINT unique_passport UNIQUE (passport_number);
ALTER TABLE guest ADD CONSTRAINT check_residence CHECK (residence IS NOT NULL);
