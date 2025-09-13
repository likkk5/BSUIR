CREATE INDEX idx_role_name ON roles(role_name);

CREATE INDEX idx_user_login ON "user"(login);
CREATE INDEX idx_user_email ON "user"(email);

CREATE INDEX idx_guest_passport ON guest(passport_number);

CREATE INDEX idx_room_type ON room(room_type);

CREATE INDEX idx_reservation_room ON reservation(room_number);
CREATE INDEX idx_reservation_guest ON reservation(guest_id);

CREATE INDEX idx_service_name ON service(name);

CREATE INDEX idx_feedback_guest ON feedback(guest_id);

CREATE INDEX idx_notification_datetime ON notification(notification_datetime);

CREATE INDEX idx_order_status ON "order"(order_status);
CREATE INDEX idx_order_employee ON "order"(employee_id);

CREATE INDEX idx_service_in_order_service ON service_in_order(service_id);
CREATE INDEX idx_service_in_order_order ON service_in_order(order_id);

CREATE INDEX idx_promocode_code ON promocode(code);

CREATE INDEX idx_reservation_promocode ON reservation_promocodes(promocode_id);
CREATE INDEX idx_reservation_id ON reservation_promocodes(reservation_id);

DROP INDEX IF EXISTS idx_reservation_promocode;
CREATE UNIQUE INDEX idx_reservation_promocode ON reservation_promocodes(promocode_id);