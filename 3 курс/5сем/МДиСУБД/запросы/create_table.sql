CREATE TABLE role (
    id SERIAL PRIMARY KEY,
    role_name VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE "user" (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    login VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    role_id INT NOT NULL REFERENCES role(id),
    phone_number VARCHAR(20),
    email VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE guest (
    id SERIAL PRIMARY KEY,
    user_id INT NOT NULL REFERENCES "user"(id),
    passport_number VARCHAR(20) NOT NULL UNIQUE,
    residence VARCHAR(255)
);

CREATE TABLE room (
    room_number SERIAL PRIMARY KEY,
    room_type VARCHAR(50) NOT NULL,
    cost_for_night DECIMAL(10, 2) NOT NULL CHECK (cost_for_night >= 0),
    room_status VARCHAR(50) NOT NULL,
    photo BYTEA,
    UNIQUE (room_number)
);

CREATE TABLE reservation (
    id SERIAL PRIMARY KEY,
    reservation_date TIMESTAMP NOT NULL,
    check_in_date TIMESTAMP NOT NULL,
    check_out_date TIMESTAMP NOT NULL,
    reservation_status VARCHAR(50) NOT NULL,
    room_number INT NOT NULL,
    guest_id INT NOT NULL REFERENCES guest(id),
    cost DECIMAL(10, 2) NOT NULL CHECK (cost >= 0)
);

CREATE TABLE service (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    cost DECIMAL NOT NULL CHECK (cost >= 0),
    photo BYTEA
);

CREATE TABLE feedback (
    id SERIAL PRIMARY KEY,
    guest_id INT NOT NULL REFERENCES guest(id),
    feedback_datetime TIMESTAMP NOT NULL,
    feedback_text TEXT,
    rating INT NOT NULL CHECK (rating >= 1 AND rating <= 5)
);

CREATE TABLE notification (
    id SERIAL PRIMARY KEY,
    notification_datetime TIMESTAMP NOT NULL,
    notification_text TEXT NOT NULL
);

CREATE TABLE "order" (
    id SERIAL PRIMARY KEY,
    order_datetime TIMESTAMP NOT NULL,
    reservation_id INT NOT NULL REFERENCES reservation(id),
    order_status VARCHAR(50) NOT NULL,
    notification_id INT NULL REFERENCES notification(id),
    employee_id INT NOT NULL REFERENCES "user"(id),
    cost DECIMAL(10, 2) NOT NULL CHECK (cost >= 0)
);

CREATE TABLE service_in_order (
    id SERIAL PRIMARY KEY,
    service_id INT NOT NULL REFERENCES service(id),
    order_id INT NOT NULL REFERENCES "order"(id),
    employee_id INT NOT NULL REFERENCES "user"(id),
    amount INT NOT NULL CHECK (amount > 0)
);

CREATE TABLE promocode (
    id SERIAL PRIMARY KEY,
    code VARCHAR(50) NOT NULL,
    promocode_status BOOLEAN NOT NULL,
    sale_type VARCHAR(20) NOT NULL,
    sale_amount DECIMAL(10, 2) NOT NULL CHECK (sale_amount >= 0),
    promocode_start_date TIMESTAMP NOT NULL,
    promocode_expiration_date TIMESTAMP NOT NULL,
    promocode_date_of_use TIMESTAMP
);

CREATE TABLE reservation_promocodes (
    id SERIAL PRIMARY KEY,
    promocode_id INT NULL REFERENCES promocode(id),
    reservation_id INT NOT NULL REFERENCES reservation(id),
    quantity INT CHECK (quantity >= 0)
);

