BEGIN
  EXECUTE IMMEDIATE 'DROP TABLE meal_categories CASCADE CONSTRAINTS';
EXCEPTION
  WHEN OTHERS THEN IF SQLCODE != -942 THEN RAISE; END IF;
END;
/
BEGIN
  EXECUTE IMMEDIATE 'DROP TABLE meals CASCADE CONSTRAINTS';
EXCEPTION
  WHEN OTHERS THEN IF SQLCODE != -942 THEN RAISE; END IF;
END;
/

CREATE TABLE meal_categories (
  category_id   NUMBER PRIMARY KEY,
  category_name VARCHAR2(100) NOT NULL
);

CREATE TABLE meals (
  meal_id     NUMBER PRIMARY KEY,
  meal_name   VARCHAR2(100) NOT NULL,
  price       NUMBER(6,2),
  calories    NUMBER,
  category_id NUMBER,
  CONSTRAINT fk_meal_category FOREIGN KEY (category_id) REFERENCES meal_categories(category_id)
);


INSERT INTO meal_categories (category_id, category_name) VALUES (1, 'Salads');
INSERT INTO meal_categories (category_id, category_name) VALUES (2, 'Main Dishes');
INSERT INTO meal_categories (category_id, category_name) VALUES (3, 'Desserts');
INSERT INTO meal_categories (category_id, category_name) VALUES (4, 'Beverages');
COMMIT;

INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (1, 'Caesar Salad with Chicken', 450.00, 320, 1);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (2, 'Vegetable Salad', 300.00, 150, 1);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (3, 'Beef Stroganoff with Potatoes', 650.00, 600, 2);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (4, 'Mushroom Risotto', 550.00, 480, 2);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (5, 'Cheesecake', 400.00, 420, 3);
COMMIT;


SELECT * FROM meal_categories;
SELECT * FROM meals;
